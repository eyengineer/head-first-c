/*
 * ============================================================================
 * PURPOSE:
 * This program creates a simple TCP server that listens on port 30000.
 * When a client connects, it sends a random piece of advice and then closes
 * the connection. The server runs in an infinite loop to handle multiple clients.
 *
 * WHAT IT TEACHES:
 * 1. B.L.A.B. (Bind, Listen, Accept, Begin) sequence for servers.
 * 2. send(): Sending data over a socket (instead of fprintf).
 * 3. rand(): Generating random numbers.
 * 4. The importance of error checking (pointed out in the book).
 * ============================================================================
 */

#include <stdio.h>      // For printf, fprintf, puts
#include <stdlib.h>     // For exit, rand, srand
#include <string.h>     // For strlen, strerror
#include <unistd.h>     // For close
#include <errno.h>      // For errno
#include <sys/socket.h> // For socket, bind, listen, accept, send
#include <arpa/inet.h>  // For htons, htonl, INADDR_ANY

// ============================================================================
// HELPER FUNCTION: error
// ============================================================================
// This function prints an error message to Standard Error (stderr) and exits.
// It uses 'errno' and 'strerror' to provide a detailed system error message.
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
    // Each string ends with "\r\n" (Carriage Return + Line Feed).
    // This is the standard format for network protocols (like HTTP).
    char *advice[] = {
        "Take smaller bites\r\n",
        "Go for the tight jeans. No they do NOT make you look fat.\r\n",
        "One word: inappropriate\r\n",
        "Just for today, be honest. Tell your boss what you *really* think\r\n",
        "You might want to rethink that haircut\r\n"
    };

    // ========================================================================
    // STEP 1: CREATE A SOCKET (B.L.A.B. - The 'S' in socket)
    // ========================================================================
    // socket() creates an endpoint for communication.
    // PF_INET = IPv4 protocol family.
    // SOCK_STREAM = TCP (reliable, connection-oriented).
    // 0 = Default protocol (TCP).
    int listener_d = socket(PF_INET, SOCK_STREAM, 0);
    if (listener_d == -1) {
        error("Can't open socket");
    }

    // ========================================================================
    // STEP 2: BIND (B.L.A.B. - The 'B')
    // ========================================================================
    // We need to bind the socket to a specific port (30000) and IP address.
    // struct sockaddr_in is the structure used for IPv4 addresses.
    struct sockaddr_in name;
    
    // Set the address family to IPv4.
    name.sin_family = PF_INET;
    
    // Set the port number. htons() converts from host byte order to network byte order.
    // Network byte order is Big-Endian. Most computers are Little-Endian.
    name.sin_port = (in_port_t)htons(30000);
    
    // Set the IP address. INADDR_ANY means "accept connections on any IP address".
    // htonl() converts the IP address to network byte order.
    name.sin_addr.s_addr = htonl(INADDR_ANY);
    
    // Bind the socket to the address and port.
    // We cast 'name' to (struct sockaddr *) because bind() expects a generic address.
    if (bind(listener_d, (struct sockaddr *)&name, sizeof(name)) == -1) {
        error("Can't bind to socket");
    }

    // ========================================================================
    // STEP 3: LISTEN (B.L.A.B. - The 'L')
    // ========================================================================
    // listen() marks the socket as passive (ready to accept connections).
    // The second argument (10) is the backlog: the maximum number of pending connections.
    if (listen(listener_d, 10) == -1) {
        error("Can't listen");
    }
    puts("Waiting for connection");

    // ========================================================================
    // STEP 4: ACCEPT AND BEGIN (B.L.A.B. - The 'A' and 'B')
    // ========================================================================
    // The server runs an infinite loop to handle multiple clients.
    while (1) {
        
        // struct sockaddr_storage is a generic structure that can hold any address type (IPv4 or IPv6).
        struct sockaddr_storage client_addr;
        unsigned int address_size = sizeof(client_addr);
        
        // accept() waits for a client to connect.
        // When a client connects, it returns a NEW socket descriptor (connect_d).
        // This new descriptor is used for the actual communication with that specific client.
        // listener_d is still used to accept new connections.
        int connect_d = accept(listener_d, (struct sockaddr *)&client_addr, &address_size);
        if (connect_d == -1) {
            error("Can't open secondary socket");
        }

        // ====================================================================
        // STEP 5: SEND DATA (BEGIN)
        // ====================================================================
        // Pick a random advice from the array.
        // rand() % 5 generates a random number between 0 and 4.
        char *msg = advice[rand() % 5];

        // send() sends the message to the client.
        // It takes the connection descriptor, the message, its length, and flags.
        // flags = 0 means default behavior.
        // Unlike fprintf(), send() is designed for sockets.
        if (send(connect_d, msg, strlen(msg), 0) == -1) {
            error("send");
        }

        // Close the connection with this client.
        // The server is now ready to accept the next client.
        close(connect_d);
    }

    return 0;
}
