/*
 * ============================================================================
 * PURPOSE:
 * This program is a simple TCP server that listens on port 30000.
 * When a client connects, it sends a random piece of advice and closes 
 * the connection. It also demonstrates how to fix the "Address already in use"
 * error using setsockopt() and SO_REUSEADDR.
 *
 * WHAT IT TEACHES:
 * 1. B.L.A.B. (Bind, Listen, Accept, Begin) sequence for creating a server.
 * 2. SO_REUSEADDR: Why ports stay "sticky" and how to reuse them immediately.
 * 3. setsockopt(): Changing the behavior of a socket.
 * 4. send(): Sending data over a network socket (instead of fprintf).
 * ============================================================================
 */

#include <stdio.h>      // For printf, fprintf, puts
#include <stdlib.h>     // For exit, rand
#include <string.h>     // For strlen, strerror
#include <unistd.h>     // For close
#include <errno.h>      // For errno
#include <sys/socket.h> // For socket, bind, listen, accept, send
#include <arpa/inet.h>  // For htons, htonl, INADDR_ANY

// ============================================================================
// HELPER FUNCTION: error
// ============================================================================
// A simple function to print an error message and exit the program.
// It uses 'errno' and 'strerror' to provide the exact system error.
void error(char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main(int argc, char *argv[])
{
    // 1. Array of advice strings.
    // The "\r\n" at the end is required for network protocols (Carriage Return + Line Feed).
    char *advice[] = {
        "Take smaller bites\r\n",
        "Go for the tight jeans. No they do NOT make you look fat.\r\n",
        "One word: inappropriate\r\n",
        "Just for today, be honest. Tell your boss what you *really* think\r\n",
        "You might want to rethink that haircut\r\n"
    };

    // ========================================================================
    // STEP 1: CREATE A SOCKET
    // ========================================================================
    // socket() creates an endpoint for communication.
    // PF_INET = IPv4, SOCK_STREAM = TCP (reliable connection).
    int listener_d = socket(PF_INET, SOCK_STREAM, 0);
    if (listener_d == -1) {
        error("Can't open socket");
    }

    // ========================================================================
    // STEP 2: THE FIX - PREVENT "ADDRESS ALREADY IN USE"
    // ========================================================================
    // When a server stops, the port remains "sticky" for ~30 seconds.
    // This means you can't restart the server immediately.
    // setsockopt() with SO_REUSEADDR tells the OS to reuse the port immediately.
    int reuse = 1;
    if (setsockopt(listener_d, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(int)) == -1) {
        error("Can't set the reuse option on the socket");
    }

    // ========================================================================
    // STEP 3: BIND TO A PORT (B.L.A.B. - B)
    // ========================================================================
    // We bind the socket to port 30000 and any available IP address.
    struct sockaddr_in name;
    name.sin_family = PF_INET;
    name.sin_port = (in_port_t)htons(30000); // Convert port to network byte order
    name.sin_addr.s_addr = htonl(INADDR_ANY); // Accept connections on any IP
    
    if (bind(listener_d, (struct sockaddr *)&name, sizeof(name)) == -1) {
        error("Can't bind to socket");
    }

    // ========================================================================
    // STEP 4: LISTEN FOR CONNECTIONS (B.L.A.B. - L)
    // ========================================================================
    // The server listens for incoming connections. The queue length is 10.
    if (listen(listener_d, 10) == -1) {
        error("Can't listen");
    }
    puts("Waiting for connection");

    // ========================================================================
    // STEP 5: ACCEPT AND SEND (B.L.A.B. - A and B)
    // ========================================================================
    // Infinite loop to handle multiple clients one by one.
    while (1) {
        struct sockaddr_storage client_addr;
        unsigned int address_size = sizeof(client_addr);
        
        // accept() waits for a client. When connected, it returns a NEW socket (connect_d).
        int connect_d = accept(listener_d, (struct sockaddr *)&client_addr, &address_size);
        if (connect_d == -1) {
            error("Can't open secondary socket");
        }

        // Pick a random advice (0 to 4).
        char *msg = advice[rand() % 5];

        // send() sends the message over the socket.
        // Unlike fprintf(), send() is designed for network communication.
        if (send(connect_d, msg, strlen(msg), 0) == -1) {
            error("send");
        }

        // Close the connection with this client.
        close(connect_d);
    }

    return 0;
}
