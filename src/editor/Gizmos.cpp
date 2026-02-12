#include  "editor/Gizmos.h"

#include "engine/Renderer.h"

namespace Editor {
    void Gizmos::drawGizmos(Engine::Entity &entity, Engine::Camera &camera) {
        //draw at the center of the entity 3d coordinate and rotation bow with some nice colors
        // by pulling, squeezing of the 3d coordiante mesh change the mesh size by rotating the bow
        //rotate the mesh, all done by mouse, for position changing use keyboard. for more please implement
        // for now its enough.

        // transform x,y,z to the entity center and rotate them correctly so they make 3d coordinate
        XAxisShape.transform = entity.transform;
        YAxisShape.transform.position = entity.transform.position;
        ZAxisShape.transform.position = entity.transform.position;
        sphereShape.transform.position = entity.transform.position;
        Engine::RenderEntity(XAxisShape,camera);
        Engine::RenderEntity(YAxisShape,camera);
        Engine::RenderEntity(ZAxisShape,camera);
        Engine::RenderEntity(sphereShape,camera);





    }

    void Gizmos::manipulateEntity(Engine::Entity &entity) {
        //


    }
}
