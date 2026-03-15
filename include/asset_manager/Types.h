#pragma once
#include <cstdint>
#include "geometry/Geometry.h"
#include "math/Mat4.h"




// actually only pool stuff here otherwise it can get Very BIG

namespace Asset::Types{

//---------------- IDS----------------//
using EntityID = uint32_t;
using ShaderID = uint32_t;
using ComponentMask = uint32_t; //Bit Masks

//_____________________________________//



//---------------types-------------------------------------------------------------------------------------------------------------//


enum ComponentType : uint32_t{
    TRANSFORM = 1 << 0,
    MATERIAL =  1 << 1,
    MESH =      1 << 2,
    SHADER =    1 << 3,
    RENDERER =  1 << 4,
    PHYSICS =   1 << 5,
    AABB =      1 << 6

    
};

//---------------Operator__Overloading--------------------------------//

// joining two Components with Or Opeation
inline ComponentMask operator|(ComponentType a ,ComponentType b){
    return static_cast<ComponentMask>(a) |  static_cast<ComponentMask>(b);
}
// comparing ComponentType a to b with AND
inline ComponentMask operator&(ComponentType a ,ComponentType b){
    return static_cast<ComponentMask>(a) &  static_cast<ComponentMask>(b);
}
// Negating the Whole ComponentType
inline ComponentMask operator~(ComponentType a ){
    return ~static_cast<ComponentMask>(a);
}
// joining  a mask to a componentType
inline ComponentMask& operator|=(ComponentMask& a ,ComponentType b){
     a |=  static_cast<ComponentMask>(b);
     return a;
}

// comparing  a mask to a componentType
inline ComponentMask operator&(ComponentMask a ,ComponentType b){
    return a &  static_cast<ComponentMask>(b);
}

//_____________________________________________________________________//

struct Entity{
    EntityID id;
};

struct Transform{
    Math::Vec3 position {0.0f};
    Math::Vec3 rotation {0.0f};   // Euler (radians)
    Math::Vec3 scale    {1.0f};

    // Model-Matrix aus Position / Rotation / Scale
    Math::Mat4 GetModelMatrix() const;
};

struct Material{
    ShaderID id;
    Math::Vec3 color;
     Material() = default;

    Material(ShaderID shader, Math::Vec3 c)
        : id(shader), color(c) {}
    // eventuell Meherer Sachen 

    
};
struct Mesh {
        uint32_t VAO = 0;
        uint32_t  VBO = 0;
        uint32_t  EBO = 0;      // optional (0 = nicht benutzt)
        uint32_t vertexCount = 0;
        uint32_t indexCount = 0;
        bool indexed = false;
        Geometry::AABB boundingBox{0,0}; // for new LoadMesh functions please dont forget this!
    };




}//namespace