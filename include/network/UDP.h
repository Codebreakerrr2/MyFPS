#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <cstdint>
#include <vector>

#pragma comment(lib, "ws2_32.lib")

namespace Net {

    class UDPSocket {
    public:
        UDPSocket();
        ~UDPSocket();

        bool bindSocket(uint16_t port);

        bool sendTo(
            const sockaddr_in& target,
            const uint8_t* data,
            size_t size
        );

        int receiveFrom(
            uint8_t* buffer,
            size_t bufferSize,
            sockaddr_in& sender
        );
        UDPSocket(const UDPSocket&) = delete;
        UDPSocket& operator=(const UDPSocket&) = delete;


    private:
        SOCKET socketHandle = INVALID_SOCKET;
    };

}
