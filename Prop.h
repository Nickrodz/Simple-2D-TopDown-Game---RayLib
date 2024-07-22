#include "raylib.h"

class Prop{

    public:
        Prop(Vector2 pop, Texture2D tex);
        void Render(Vector2 knightPos);
        Rectangle getCollsionRec(Vector2 KnightPos);
    private:
        Texture2D texture{};
        Vector2 worldPos{};
        float scale = 4.f;
};