#include "raylib.h"


#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

class BaseCharacter{
public:
    BaseCharacter();
    Vector2 GetWorldPos() { return worldPos; }
    void undoMovement();
    virtual void tick(float deltaTime);
    Rectangle getCollisionRec();
    virtual Vector2 getscreenPos() = 0;
    bool getAlive() {return alive;}
    void setAlive(bool isAlive) {alive = isAlive;}
private:
    bool alive = true;
protected:
    Texture2D texture = LoadTexture("Characters/knight_idle_spritesheet.png");
    Texture2D idle = LoadTexture("Characters/knight_idle_spritesheet.png");
    Texture2D run = LoadTexture("Characters/knight_run_spritesheet.png");
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};
    // 1 = face right -1 = face left
    float rightLeft = 1.f;
    // animation variables
    float runningTime = 0.0;
    float updateTime = 1.f / 12.f;
    int frame = 0;
    int maxFrames = 6;
    float speed = 4.f;
    float width = 0.0;
    float height = 0.0;
    float scale = 4.0f;
    Vector2 velocity{};
};

#endif