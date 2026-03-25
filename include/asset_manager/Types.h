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

//---------------Operator__Overloading for ComponentType--------------------------------//

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
//_________________________COMPONENTS_______________________________________//

struct Entity{
    EntityID id;
};

struct TransformComponent{
    Math::Vec3 position {0.0f};
    Math::Vec3 rotation {0.0f};   // Euler (radians)
    Math::Vec3 scale    {1.0f};

    // Model-Matrix aus Position / Rotation / Scale
    Math::Mat4 GetModelMatrix() const {
        return Math::Mat4::Translation(position) *
          Math::Mat4::RotationX(rotation.x) *
          Math::Mat4::RotationY(rotation.y) *
          Math::Mat4::RotationZ(rotation.z) *
          Math::Mat4::Scale(scale);
    }
};

struct MaterialComponent{
       assetHandler<IShader> shader;
    Math::Vec3 color;
     Material() = default;

    Material(ShaderID shader, Math::Vec3 c)
        : shader(shader), color(c) {}
    // eventuell Meherer Sachen 

    
};


struct MeshComponent{

    assetHandler<IMesh> mesh;


}
//_________________________________________ functions for ComponentType and Components________________________________//

template<typename T>
constexpr ComponentType ComponentToType(){
   if constexpr (std::is_same_v<T, TransformComponent>) return ComponentType::TRANSFORM;
    else if constexpr (std::is_same_v<T, MeshComponent>) return ComponentType::MESH;
    else if constexpr (std::is_same_v<T, MaterialComponent>) return ComponentType::MATERIAL;
    else static_assert(!std::is_same_v<T, T>, "Unsupported component in conversion to componentType");

}











//____________________________________________________________________________________________________________________//

//handel template

template<typename T>
struct assetHandler{

    const std::function<T*()> getAsset;

    const std::function<const T*()> getConstAsset;

    assetHandler(const std::function<T*()>& ga,const std::function<const T*()> gca ): getAsset(ga), getConstAsset(gca){}
        //ohne const
    T* operator()()  {return getAsset();}

    //mit const, natürlich muss dann assetmanager entsprechend const haben
    const T* operator()() const {return getConstAsset();}
}

}//namespace