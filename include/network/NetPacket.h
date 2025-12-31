#pragma once
#include <cstdint>
#include "Math/Vec.h"

#pragma pack(push, 1)

enum class PacketType : uint8_t {
    PlayerState = 1
};

struct PlayerStatePacket {
    uint32_t sequence =1;
    PacketType type;
    uint32_t playerID;
    Math::Vec3 position;
    Math::Vec3 rotation;
};

#pragma pack(pop)
