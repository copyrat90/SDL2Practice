#pragma once

#include "Rect.hpp"


class Player final : public Rect
{
public:
    Player(float x, float y, float w, float h, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void HandleEvent(const SDL_Event& e) override;
    void Update(Uint32 deltaTime) override;

private:
    static constexpr float AXIS_MOVE_SPEED = 0.5f;
};
