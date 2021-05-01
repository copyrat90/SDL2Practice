#include "Player.hpp"


Player::Player(float x, float y, float w, float h, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    : Rect(x, y, w, h, r, g, b, a, 100)
{

}

void Player::HandleEvent(const SDL_Event& e)
{

}

void Player::Update(Uint32 deltaTime)
{
    const bool* keyStates = (const bool*)SDL_GetKeyboardState(nullptr);
    if (keyStates[SDL_SCANCODE_UP])
        rect_.y -= AXIS_MOVE_SPEED * deltaTime;
    if (keyStates[SDL_SCANCODE_DOWN])
        rect_.y += AXIS_MOVE_SPEED * deltaTime;
    if (keyStates[SDL_SCANCODE_LEFT])
        rect_.x -= AXIS_MOVE_SPEED * deltaTime;
    if (keyStates[SDL_SCANCODE_RIGHT])
        rect_.x += AXIS_MOVE_SPEED * deltaTime;
}
