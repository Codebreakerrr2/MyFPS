#pragma once
#include "network/UDP.h"
#include "network/NetPacket.h"

namespace Net {
    class Client {
    public:
        bool Init(const char* serverIP, uint16_t serverPort);
        void SendPlayerState(const PlayerStatePacket& state);
        bool Receive(PlayerStatePacket& outState);
    private:
        UDPSocket socket;
        sockaddr_in serverAddr{};

    };
}
