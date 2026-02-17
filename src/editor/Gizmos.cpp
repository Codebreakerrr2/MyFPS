#include  "editor/Gizmos.h"

#include "engine/Input.h"
#include "engine/Renderer.h"

namespace Editor {

    //! this function will be fixed later this is kinda weird shit i have to make a nice blender parser
    void Gizmos::drawGizmos(Engine::Entity &entity, Engine::Camera &camera) {
        //draw at the center of the entity 3d coordinate and rotation bow with some nice colors
        // by pulling, squeezing of the 3d coordiante mesh change the mesh size by rotating the bow
        //rotate the mesh, all done by mouse, for position changing use keyboard. for more please implement
        // for now its enough.

        // transform x,y,z to the entity center and rotate them correctly so they make 3d coordinate
        /*
        XAxisShape.transform = entity.transform;
        YAxisShape.transform.position = entity.transform.position;
        ZAxisShape.transform.position = entity.transform.position;
        sphereShape.transform.position = entity.transform.position;
        Engine::RenderEntity(XAxisShape,camera);
        Engine::RenderEntity(YAxisShape,camera);
        Engine::RenderEntity(ZAxisShape,camera);
        Engine::RenderEntity(sphereShape,camera);
*/





    }
    //! this function should also be made new but at the moment we use keyboard no heavy gui logik

    void Gizmos::manipulateEntity(Engine::Entity& entity)
    {
        float scaleFactor  = 1.1f;
        float moveFactor   = 0.1f;   // additive Bewegung ist besser!
        float rotateFactor = 1.0f;

        if (Engine::IsKeyPressed(GLFW_KEY_LEFT_CONTROL))
        {
            // 🔹 SCALE
            if (Engine::IsKeyPressed(GLFW_KEY_S))
            {
                if (Engine::IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
                    entity.transform.scale = entity.transform.scale *0.9f;   // kleiner
                else
                    entity.transform.scale = entity.transform.scale *scaleFactor; // größer
            }

            // 🔹 MOVE X/Y
            if (Engine::IsKeyPressed(GLFW_KEY_M))
            {
                if (Engine::IsKeyPressed(GLFW_KEY_RIGHT))
                    entity.transform.position.x += moveFactor;

                if (Engine::IsKeyPressed(GLFW_KEY_LEFT))
                    entity.transform.position.x -= moveFactor;

                if (Engine::IsKeyPressed(GLFW_KEY_UP))
                    entity.transform.position.y += moveFactor;

                if (Engine::IsKeyPressed(GLFW_KEY_DOWN))
                    entity.transform.position.y -= moveFactor;
            }

            // 🔹 MOVE Z
            if (Engine::IsKeyPressed(GLFW_KEY_Z))
            {
                if (Engine::IsKeyPressed(GLFW_KEY_RIGHT))
                    entity.transform.position.z += moveFactor;

                if (Engine::IsKeyPressed(GLFW_KEY_LEFT))
                    entity.transform.position.z -= moveFactor;
            }
        }
    }




    }

