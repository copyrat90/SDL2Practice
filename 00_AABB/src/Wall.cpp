#include "Wall.hpp"


Wall::Wall(float x, float y, float w, float h, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    : Rect(x, y, w, h, r, g, b, a, 99999)
{

}

void Wall::HandleEvent(const SDL_Event& e)
{

}

void Wall::Update(Uint32 deltaTime)
{

}
