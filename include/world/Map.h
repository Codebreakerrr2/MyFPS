#pragma once
#include <vector>
namespace Engine { class Camera; }  // Forward Declaration
namespace Engine { class Entity; }
namespace World {


    //bool LoadMap(const std::string& path);

    // Update pro Frame (falls z.B. bewegliche Objekte, Türen)
   // void UpdateMap(float deltaTime);

   // void RenderMap();
    class Map {

        //bool LoadMap(const std::string& path);




    public:
        std::vector<Engine::Camera*> cameras;
        std::vector<Engine::Entity*> entities;
     //   void addCamera(Engine::Camera* camera);
     //   void removeCamera(Engine::Camera* camera);
        void addEntity(Engine::Entity* entity);
        void removeEntity(Engine::Entity* entity);
        void RenderMap(Engine::Camera& camera);
    };


}
