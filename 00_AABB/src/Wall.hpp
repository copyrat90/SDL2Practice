#pragma once

#include "Rect.hpp"


class Wall : public Rect
{
public:
    Wall(float x, float y, float w, float h, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    void HandleEvent(const SDL_Event& e) override;
    void Update(Uint32 deltaTime) override;
};
