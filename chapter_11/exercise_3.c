/*
 * ============================================================================
 * PURPOSE:
 * This is the "Internet Knock-Knock Server". It implements a custom protocol 
 * (IKKP) where the server tells a knock-knock joke to any client that connects.
 * It uses send() and recv() for two-way communication.
 *
 * WHAT IT TEACHES:
 * 1. Full server lifecycle: socket -> bind -> listen -> accept.
 * 2. SO_REUSEADDR: Preventing the "Address already in use" error.
 * 3. send() and recv(): Two-way data transfer over sockets.
 * 4. Signal handling: Closing the socket gracefully on Ctrl+C.
 * 5. Custom protocol: Strict rules for client-server interaction.
 * ============================================================================
 */

#include <stdio.h>      // For printf, fprintf, puts
#include <string.h>     // For strlen, strerror, strncasecmp
#include <errno.h>      // For errno (error number)
#include <stdlib.h>     // For exit
#include <sys/socket.h> // For socket, bind, listen, accept, send, recv
#include <arpa/inet.h>  // For htons, htonl, INADDR_ANY
#include <unistd.h>     // For close
#include <signal.h>     // For sigaction, SIGINT

// ============================================================================
// READY-BAKE FUNCTIONS (From Page 479)
// ============================================================================

// 1. Error handler: Prints a custom message + system error, then exits.
void error(char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

// 2. Open a listener socket: Creates a TCP socket for IPv4.
int open_listener_socket()
{
    int s = socket(PF_INET, SOCK_STREAM, 0);
    if (s == -1) {
        error("Can't open socket");
    }
    return s;
}

// 3. Bind to a port: Associates the socket with port 30000.
void bind_to_port(int socket, int port)
{
    struct sockaddr_in name;
    name.sin_family = PF_INET;
    name.sin_port = (in_port_t)htons(port); // Convert port to network byte order
    name.sin_addr.s_addr = htonl(INADDR_ANY); // Accept connections on any IP
    
    // Allow immediate reuse of the port (fixes "Address already in use")
    int reuse = 1;
    if (setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(int)) == -1) {
        error("Can't set the reuse option on the socket");
    }
    
    int c = bind(socket, (struct sockaddr *)&name, sizeof(name));
    if (c == -1) {
        error("Can't bind to socket");
    }
}

// 4. Send a string to a client: Wraps send() with error checking.
int say(int socket, char *s)
{
    int result = send(socket, s, strlen(s), 0);
    if (result == -1) {
        fprintf(stderr, "%s: %s\n", "Error talking to the client", strerror(errno));
    }
    return result;
}

// 5. Read a string from a client: Reads until newline or buffer is full.
// This is important because recv() might not get all characters in one call.
int read_in(int socket, char *buf, int len)
{
    char *s = buf;
    int slen = len;
    int c = recv(socket, s, slen, 0);
    
    // Keep reading until we hit a newline ('\n') or run out of space.
    while ((c > 0) && (s[c-1] != '\n')) {
        s += c; 
        slen -= c;
        c = recv(socket, s, slen, 0);
    }
    
    if (c < 0) 
        return c; // Error occurred
    else if (c == 0) 
        buf[0] = '\0'; // Connection closed, return empty string
    else
        s[c-1] = '\0'; // Replace the newline with a null terminator
        
    return len - slen; // Return the number of characters read
}

// ============================================================================
// GLOBAL VARIABLE & SIGNAL HANDLER
// ============================================================================

int listener_d; // Global variable to store the main socket

// Signal handler: Closes the socket gracefully when Ctrl+C is pressed.
void handle_shutdown(int sig)
{
    if (listener_d) {
        close(listener_d);
    }
    fprintf(stderr, "Bye!\n");
    exit(0);
}

// Helper for catching signals (from previous chapter)
int catch_signal(int sig, void (*handler)(int))
{
    struct sigaction action;
    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    return sigaction(sig, &action, NULL);
}

// ============================================================================
// MAIN FUNCTION (The Knock-Knock Protocol)
// ============================================================================

int main(int argc, char *argv[])
{
    // 1. Catch SIGINT (Ctrl+C) to close the socket gracefully.
    if (catch_signal(SIGINT, handle_shutdown) == -1) {
        error("Can't set the interrupt handler");
    }

    // 2. Create the socket and bind to port 30000.
    listener_d = open_listener_socket();
    bind_to_port(listener_d, 30000);

    // 3. Listen for connections (queue length 10).
    if (listen(listener_d, 10) == -1) {
        error("Can't listen");
    }

    struct sockaddr_storage client_addr;
    unsigned int address_size = sizeof(client_addr);
    puts("Waiting for connection");

    char buf[255]; // Buffer for reading client responses

    // 4. Infinite loop to handle multiple clients.
    while (1) {
        // 5. Accept a connection from a client.
        int connect_d = accept(listener_d, (struct sockaddr *)&client_addr, &address_size);
        if (connect_d == -1) {
            error("Can't open secondary socket");
        }

        // 6. Send the welcome message and the first part of the joke.
        // If say() succeeds, it returns the number of bytes sent (> 0).
        if (say(connect_d, "Internet Knock-Knock Protocol Server\r\nVersion 1.0\r\nKnock! Knock!\r\n> ") != -1) {
            
            // 7. Read the client's response into the buffer.
            read_in(connect_d, buf, sizeof(buf));
            
            // 8. Check if the client said "Who's there?"
            // strncasecmp returns 0 if the strings match (case-insensitive).
            // If it returns non-zero, the client said something wrong.
            if (strncasecmp("Who's there?", buf, 12)) {
                say(connect_d, "You should say 'Who's there?'!");
            } else {
                // 9. The client said the right thing. Continue the joke.
                if (say(connect_d, "Oscar\r\n> ") != -1) {
                    read_in(connect_d, buf, sizeof(buf));
                    
                    if (strncasecmp("Oscar who?", buf, 10)) {
                        say(connect_d, "You should say 'Oscar who?'!\r\n");
                    } else {
                        say(connect_d, "Oscar silly question, you get a silly answer\r\n");
                    }
                }
            }
        }
        // 10. Close the connection with this client.
        close(connect_d);
    }

    return 0;
}
