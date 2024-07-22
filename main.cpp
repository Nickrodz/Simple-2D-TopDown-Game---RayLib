#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

using namespace std;

int main()
{

    const int windowHeight = 1500;
    const int windowWidth = 1500;
    InitWindow(windowWidth, windowHeight, "GAME");
    InitAudioDevice();
    Texture2D MainMap = LoadTexture("C:/Users/nick_/Desktop/Project Game 3/nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos({0.0, 0.0});
    const float mapScale = 3.5f;
    Character knight {windowWidth, windowHeight};
    

    Prop props[3]{
        Prop{Vector2{600.f, 2300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/log.png")},
        Prop{Vector2{800.f, 800.f}, LoadTexture("nature_tileset/Tree.png")}
    };
    
    Enemy goblin {Vector2{800.f, 300.f}, LoadTexture("Characters/goblin_idle_spritesheet.png"), LoadTexture("Characters/goblin_run_spritesheet.png")};
    
    Enemy slime{
        Vector2{500.f, 1700.f}, LoadTexture("Characters/slime_idle_spritesheet.png"), LoadTexture("Characters/slime_run_spritesheet.png")
    };
    Enemy* enemies[]{
        &goblin, &slime
    };
    for(auto enemy : enemies){
        enemy->SetTarget(&knight);
    }
    
    
    Music m = LoadMusicStream("C:/Users/nick_/Desktop/Project Game 3/Jumper - Castle Crashers.mp3");
    SetMusicVolume(m, 0.1f);
    PlayMusicStream(m);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        
        BeginDrawing();
        ClearBackground(WHITE);
        UpdateMusicStream(m);
        mapPos = Vector2Scale(knight.GetWorldPos(), -1);
        // draw map
        DrawTextureEx(MainMap, mapPos, 0.0, mapScale, WHITE);

        //draw the props
        for(auto prop : props){
            prop.Render(knight.GetWorldPos());
        }


        if(!knight.getAlive()){
            DrawText("Game Over!", 55.f, 45.f, 40 , RED);
            EndDrawing();
            continue;
        } else { // character is alive
            string knightsHealth = "Health: ";
            string KnighPosX = "X: ";
            string KnighPosY = "Y: ";
            knightsHealth.append(to_string(knight.GetHealth()), 0, 5);
            KnighPosX.append(to_string(knight.GetWorldPos().x), 0, 5);
            KnighPosY.append(to_string(knight.GetWorldPos().y), 0, 5);
            DrawText(knightsHealth.c_str(), 55.f, 45.f ,40, RED);
            DrawText(KnighPosX.c_str(), 55.f, 85.f ,40, RED);
            DrawText(KnighPosY.c_str(), 55.f, 125.f ,40, RED);
        }

        knight.tick(GetFrameTime());
        //check map bounds
        if (static_cast<int>(knight.GetWorldPos().x) < 0 || static_cast<int>(knight.GetWorldPos().y) < 0 || static_cast<int>(knight.GetWorldPos().x) + windowWidth > MainMap.width * mapScale || static_cast<int>(knight.GetWorldPos().y) + windowHeight > MainMap.height * mapScale){
            //knight.undoMovement();
        }
        //check for prop collisions
        for(auto prop : props){
            if(CheckCollisionRecs(prop.getCollsionRec(knight.GetWorldPos()), knight.getCollisionRec())){
                knight.undoMovement();
            }
        }
        for(auto enemy : enemies){
            enemy->tick(GetFrameTime());


            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionRecs(enemy->getCollisionRec(), knight.GetWeaponCollisionRec())){
                 enemy->setAlive(false);
            }
        }
        
        

        EndDrawing();
    }
    StopMusicStream(m);
    CloseWindow();
    UnloadMusicStream(m);
    UnloadTexture(MainMap);
}