#pragma once

#include <SDL.h>


class GameObject
{
public:
    virtual void HandleEvent(const SDL_Event&) = 0;
    virtual void Update(Uint32 deltaTime) = 0;
    virtual void Render(SDL_Renderer*) const = 0;
};
