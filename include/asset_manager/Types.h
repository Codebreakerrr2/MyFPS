#pragma once
#include "math/Mat4.h"
#include <functional>



// actually only pool stuff here otherwise it can get Very BIG

namespace SHADER {
    class IShader;
}

namespace MESH {
    class IMesh;
}



namespace Asset::Types {
    //---------------- IDS----------------//
    using EntityID = uint32_t;
    using ShaderID = uint32_t;
    using ComponentMask = uint32_t; //Bit Masks
    using MeshID = uint32_t;
    //_____________________________________//
    // So this template is ok but its just annoying passing a function and i really dont need it now , so i would just go with something simpler
    //handel template
    /*
        template<typename T>
        struct assetHandler{

             std::function<T*()> getAsset;

             std::function<const T*()> getConstAsset;

            assetHandler(const std::function<T*()>& ga,const std::function<const T*()> gca ): getAsset(ga), getConstAsset(gca){}
            //ohne const
            T* operator()()  {return getAsset();}

            //mit const, natürlich muss dann assetmanager entsprechend const haben
            const T* operator()() const {return getConstAsset();}
        };
    */
    template<typename T, typename F>
struct assetHandler {
        T ID;
        std::function<F*()> get;

        // rvalue version (move)
        assetHandler(T id, std::function<F*()>&& func)
            : ID(id), get(std::move(func)) {}

        // lvalue version (copy)
        assetHandler(T id, const std::function<F*()>& func)
            : ID(id), get(func) {}
    };
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

    struct Init {
        Math::Vec3 pos{0.0f};
        Math::Vec3 rot{0.0f};
        Math::Vec3 scale{1.0f};
    };
    TransformComponent()= default;
    TransformComponent(const Init& init):position(init.pos),rotation(init.rot),scale(init.scale){};

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
       assetHandler<ShaderID,SHADER::IShader> shader;
    Math::Vec3 color = {1.0f, 1.0f, 1.0f};


    struct Init {
        ShaderID id=0;
        std::function<SHADER::IShader*()> get =nullptr;
        Math::Vec3 color = {1.0f, 1.0f, 1.0f};
    };

     MaterialComponent() :shader(0,nullptr) {}
    MaterialComponent (const  Init& init): shader(init.id,init.get),color(init.color) {}
    // eventuell Meherer Sachen


};


struct MeshComponent{

    assetHandler<MeshID, MESH::IMesh> mesh;
    struct Init {
        MeshID id =0;
        std::function<MESH::IMesh*()> get = nullptr;
    };
    MeshComponent(): mesh(0,nullptr){}
    MeshComponent(const  Init& init): mesh(init.id,init.get){}

};
//_________________________________________ functions for ComponentType and Components________________________________//

template<typename T>
constexpr ComponentType ComponentToType(){
   if constexpr (std::is_same_v<T, TransformComponent>) return ComponentType::TRANSFORM;
    else if constexpr (std::is_same_v<T, MeshComponent>) return ComponentType::MESH;
    else if constexpr (std::is_same_v<T, MaterialComponent>) return ComponentType::MATERIAL;
    else static_assert(!std::is_same_v<T, T>, "Unsupported component in conversion to componentType");

}











//____________________________________________________________________________________________________________________//



}//namespace