#include "network/UDP.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <cstdint>
#include <vector>
#include <stdexcept>


namespace Net {

    UDPSocket::UDPSocket() {
        socketHandle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (socketHandle == INVALID_SOCKET) {
            throw std::runtime_error("Failed to create UDP socket");
        }

    }

    UDPSocket::~UDPSocket() {
        if (socketHandle != INVALID_SOCKET) {
            closesocket(socketHandle);
        }
    }

    bool UDPSocket::bindSocket(uint16_t port) {
        sockaddr_in address;
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port);
        return bind(socketHandle, (sockaddr*)&address, sizeof(address)) == 0;
    }

    bool UDPSocket::sendTo(const sockaddr_in &target, const uint8_t *data, size_t size) {

        if (socketHandle==INVALID_SOCKET || !data || size==0) {
            throw std::runtime_error("Invalid socket or data");
        }
        int sentBytes = ::sendto(
        socketHandle,
        reinterpret_cast<const char*>(data),
        static_cast<int>(size),
        0,
        reinterpret_cast<const sockaddr*>(&target),
        sizeof(target)
    );
        return sentBytes == static_cast<int>(size);
    }

    int UDPSocket::receiveFrom(uint8_t *buffer, size_t bufferSize, sockaddr_in &sender) {
        socklen_t senderLen = sizeof(sender);
        int receivedBytes = recvfrom(socketHandle,
            reinterpret_cast<char*>(buffer),
            static_cast<int>(bufferSize),
            0, reinterpret_cast<sockaddr*>(&sender),
            &senderLen);
        if (receivedBytes == SOCKET_ERROR) {
            throw std::runtime_error("Failed to receive data");
        }
        return receivedBytes;

    }
}
