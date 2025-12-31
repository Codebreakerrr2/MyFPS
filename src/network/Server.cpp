#include "network/Server.h"

namespace Net {

    bool Server::Init(uint16_t port) {
        if (!socket.bindSocket(port)) {
            return false;
        }
        running = true;
        return true;
    }

    void Server::Run() {
        while (running) {
            try {
                PlayerStatePacket packet{};
                sockaddr_in sender{};

                int bytes = socket.receiveFrom(
                    reinterpret_cast<uint8_t*>(&packet),
                    sizeof(packet),
                    sender
                );

                if (bytes != sizeof(packet))
                    continue;

                if (packet.type != PacketType::PlayerState)
                    continue;

                if (discardOldPacket(packet))
                    continue;

                // Register / update client
                auto& client = clients[packet.playerID];
                client.addr = sender;
                client.state = packet;

                // Broadcast to other clients
                for (auto& [id, otherClient] : clients) {
                    if (id == packet.playerID)
                        continue;

                    socket.sendTo(
                        otherClient.addr,
                        reinterpret_cast<const uint8_t*>(&packet),
                        sizeof(packet)
                    );
                }
            }
            catch (...) {
                // Prevent server crash
                continue;
            }
        }
    }

    void Server::Stop() {
        running = false;
    }

    bool Server::discardOldPacket(const PlayerStatePacket& state) {
        auto it = clients.find(state.playerID);
        if (it == clients.end())
            return false; // new client

        if ((int32_t)(state.sequence - it->second.lastSequence) <= 0) {
            return true; // discard packet
        }

        it->second.lastSequence = state.sequence;
        return false;
    }

}
