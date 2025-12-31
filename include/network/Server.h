#pragma once
#include "network/UDP.h"
#include "network/NetPacket.h"
#include <unordered_map>

namespace Net {

    class Server {
    public:
        bool Init(uint16_t port);
        void Run();
        void Stop();
        bool discardOldPacket(const PlayerStatePacket &state);


    private:
        struct ClientInfo {
            sockaddr_in addr{};
            PlayerStatePacket state;
            uint32_t lastSequence = 1;
        };

        UDPSocket socket;
        bool running = false;
        std::unordered_map<uint32_t, ClientInfo> clients;

    };

}
