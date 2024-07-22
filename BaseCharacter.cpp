#include "BaseCharacter.h"
#include "raymath.h"
BaseCharacter::BaseCharacter(){

}


void BaseCharacter::tick(float deltaTime){
    worldPosLastFrame = worldPos;

     // update animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrames)
            frame = 0;
    }

    if (Vector2Length(velocity) != 0.0)
    {
        // set worldpos = worldpos + direction
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        velocity.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }
    velocity = {};
    // draw character
    Rectangle source{width * frame, 0.f, rightLeft * width, height};
    Rectangle dest{getscreenPos().x, getscreenPos().y, scale * width, scale * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);

}


void BaseCharacter::undoMovement(){
    worldPos = worldPosLastFrame;
}



Rectangle BaseCharacter::getCollisionRec(){
    return Rectangle{
        getscreenPos().x,
        getscreenPos().y,
        width * scale,
        height * scale
    };

 }