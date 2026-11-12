/*
 * ============================================================================
 * PURPOSE:
 * This program is a simple HTTP web client. It connects to a web server
 * (Wikipedia in this case), sends an HTTP GET request, and downloads
 * the contents of the web page to display on the screen.
 *
 * WHAT IT TEACHES:
 * 1. getaddrinfo(): Resolving a domain name (like "en.wikipedia.org") to an IP address.
 * 2. connect(): Establishing a connection to a remote server.
 * 3. send() and recv(): Sending HTTP requests and receiving HTML data.
 * 4. HTTP Protocol: Structuring a GET request with headers.
 * ============================================================================
 */

#include <stdio.h>      // For printf, fprintf, sprintf
#include <string.h>     // For strlen, strerror
#include <errno.h>      // For errno
#include <stdlib.h>     // For exit
#include <sys/socket.h> // For socket, connect, send, recv
#include <arpa/inet.h>  // For socket structures
#include <unistd.h>     // For close
#include <netdb.h>      // For getaddrinfo, freeaddrinfo

// ============================================================================
// HELPER FUNCTION: error
// ============================================================================
// Prints a custom error message along with the system error (strerror), then exits.
void error(char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

// ============================================================================
// FUNCTION: open_socket
// ============================================================================
// This function creates a socket, resolves the hostname to an IP address,
// and connects to the remote server on the specified port.
int open_socket(char *host, char *port)
{
    // 1. Set up hints for getaddrinfo.
    // hints is a structure that tells getaddrinfo what kind of socket we want.
    struct addrinfo *res;
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    
    // Allow IPv4 or IPv6.
    hints.ai_family = PF_UNSPEC;
    // We want a TCP stream socket.
    hints.ai_socktype = SOCK_STREAM;

    // 2. Resolve the domain name (host) and port to a network address.
    // getaddrinfo returns a linked list of address structures in 'res'.
    if (getaddrinfo(host, port, &hints, &res) == -1) {
        error("Can't resolve the address");
    }

    // 3. Create the socket using the information from getaddrinfo.
    int d_sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (d_sock == -1) {
        error("Can't open socket");
    }

    // 4. Connect the socket to the remote server.
    // We use the address information stored in 'res'.
    int c = connect(d_sock, res->ai_addr, res->ai_addrlen);
    
    // 5. Free the memory allocated by getaddrinfo (we don't need it anymore).
    freeaddrinfo(res);
    
    if (c == -1) {
        error("Can't connect to socket");
    }
    
    // Return the connected socket descriptor.
    return d_sock;
}

// ============================================================================
// FUNCTION: say
// ============================================================================
// Sends a string over the socket. Wraps send() with error checking.
int say(int socket, char *s)
{
    int result = send(socket, s, strlen(s), 0);
    if (result == -1) {
        fprintf(stderr, "%s: %s\n", "Error talking to the server", strerror(errno));
    }
    return result;
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main(int argc, char *argv[])
{
    int d_sock;
    
    // 1. Open a socket to Wikipedia on port 80 (HTTP).
    // The function handles getaddrinfo and connect internally.
    d_sock = open_socket("en.wikipedia.org", "80");
    
    char buf[255];
    
    // 2. Build the HTTP GET request.
    // The path comes from the command line (argv[1]).
    // The HTTP version is 1.1.
    // Note: The path must end with \r\n.
    sprintf(buf, "GET /wiki/%s HTTP/1.1\r\n", argv[1]);
    say(d_sock, buf);
    
    // 3. Send the Host header.
    // HTTP/1.1 requires the Host header to tell the server which website we want.
    // It must end with two \r\n sequences to mark the end of the headers.
    say(d_sock, "Host: en.wikipedia.org\r\n\r\n");
    
    char rec[256];
    
    // 4. Receive the response from the server in chunks.
    int bytesRcvd = recv(d_sock, rec, 255, 0);
    
    // Loop until recv returns 0 (connection closed) or -1 (error).
    while (bytesRcvd) {
        if (bytesRcvd == -1) {
            error("Can't read from server");
        }
        
        // Null-terminate the received data so we can print it as a string.
        rec[bytesRcvd] = '\0';
        
        // Print the received HTML to the screen.
        printf("%s", rec);
        
        // Read the next chunk.
        bytesRcvd = recv(d_sock, rec, 255, 0);
    }
    
    // 5. Close the socket when done.
    close(d_sock);
    
    return 0;
}
