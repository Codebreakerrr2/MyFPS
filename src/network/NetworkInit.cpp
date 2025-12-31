#include "network/NetworkInit.h"
#include <winsock2.h>
#include <stdexcept>

#pragma comment(lib, "ws2_32.lib")

namespace Net {

    static bool initialized = false;

    bool Init() {
        if (initialized) return true;

        WSADATA wsa;
        if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
            return false;
        }

        initialized = true;
        return true;
    }

    void Shutdown() {
        if (initialized) {
            WSACleanup();
            initialized = false;
        }
    }

}
