#include "network/Client.h"
namespace Net {

    bool Client::Init(const char *serverIP, uint16_t serverPort) {
        socket.bindSocket(0);
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(serverPort);
        inet_pton(AF_INET, serverIP, &serverAddr.sin_addr);
        return true;
    }

    void Client::SendPlayerState(const PlayerStatePacket &state) {
        socket.sendTo(serverAddr, (const uint8_t*)&state, sizeof(PlayerStatePacket));
    }

    bool Client::Receive(PlayerStatePacket &outState) {
        sockaddr_in SenderAddr;
        int bytes=  socket.receiveFrom((uint8_t*)&outState, sizeof(PlayerStatePacket), SenderAddr);
        return bytes == sizeof(PlayerStatePacket);
    }
}
