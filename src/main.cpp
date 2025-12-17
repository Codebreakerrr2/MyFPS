#include "engine/Renderer.h"
#include "game/Player.h"
#include "world/Map.h"


int main(){

    Engine::InitRenderer();
    Engine::InitInput();
    World::LoadMap("assets");
    Game::InitPlayer();

    while(true){
        
        //time
        float dt = 0.016;

        Game::UpdatePlayer(dt);
        World::UpdateMap(dt);
        Engine::ClearScreen();
        World::RenderMap();
        Game::RenderPlayer();
        Engine::SwapBuffers();
    }

    return 0;    
}