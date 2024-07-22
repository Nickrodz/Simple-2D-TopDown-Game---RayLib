#include "raylib.h"
#include "BaseCharacter.h"

#ifndef CHARACTER_H
#define CHARACTER_H


class Character : public BaseCharacter
{
public:
    Character(int winWidth, int winHeight);
    virtual void tick(float deltaTime) override;
    virtual Vector2 getscreenPos() override;
    Rectangle GetWeaponCollisionRec() { return weaponCollisionRec; }
    float GetHealth() const { return health; }
    void takeDamage(float damage);

private:
   int windowWidth = 0;
   int windowHeight = 0;
   Texture2D weapon{LoadTexture("Characters/weapon_sword.png")};
   Rectangle weaponCollisionRec{};
   float health = 100.f;
    
};


#endif