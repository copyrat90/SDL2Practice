#pragma once

#include <SDL.h>
#include <vector>
#include <memory>

#include "Rect.hpp"


class Game
{
public:
    ~Game() { Destroy(); }

    bool Init();
    void Destroy();

    void Run();

private:
    bool InitSDL();
    bool InitGame();

    void HandleEvents();
    void Update(Uint32 deltaTime);
    void Render() const;

    static constexpr Uint32 FPS = 60;
    static constexpr Uint32 MS_PER_FRAME = 1000 / FPS;

    bool isReady_ = false;
    bool isRunning_ = false;

    std::vector<std::unique_ptr<Rect>> rectObjects_;

    SDL_Window* window_ = nullptr;
    SDL_Renderer* renderer_ = nullptr;
};
