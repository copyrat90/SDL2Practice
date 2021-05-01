#include "Game.hpp"

#include "Player.hpp"
#include "PushableBox.hpp"
#include "Wall.hpp"


bool Game::Init()
{
    isReady_ = InitSDL() && InitGame();
    return isReady_;
}


bool Game::InitSDL()
{
    if (0 > SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_LogError(0, "SDL_Init() failed!\n%s", SDL_GetError());
        return false;
    }

    window_ = SDL_CreateWindow(
        "AABB Collision Resolution",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 640, 480, 0
    );
    if (!window_)
    {
        SDL_LogError(0, "SDL_CreateWindow() failed!\n%s", SDL_GetError());
        return false;
    }
    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer_)
    {
        SDL_LogError(0, "SDL_CreateRenderer() failed!\n%s", SDL_GetError());
        return false;
    }

    return true;
}

bool Game::InitGame()
{
    rectObjects_.push_back(std::make_unique<Player>(100, 200, 60, 60, 255, 255, 255, 255));

    rectObjects_.push_back(std::make_unique<Wall>(300, 200, 60, 60, 255, 0, 0, 255));
    rectObjects_.push_back(std::make_unique<Wall>(400, 300, 60, 60, 255, 0, 0, 255));

    rectObjects_.push_back(std::make_unique<PushableBox>(100, 100, 60, 60, 0, 0, 255, 255));
    rectObjects_.push_back(std::make_unique<PushableBox>(200, 200, 60, 60, 0, 0, 255, 255));
    rectObjects_.push_back(std::make_unique<PushableBox>(300, 300, 60, 60, 0, 0, 255, 255));

    return true;
}

void Game::Destroy()
{
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

void Game::Run()
{
    if (!isReady_ && !Init())
        return;

    isRunning_ = true;
    Uint32 prevTimePoint = SDL_GetTicks();
    while (isRunning_)
    {
        HandleEvents();

        // capping frame rate
        if (SDL_GetTicks() - prevTimePoint < MS_PER_FRAME)
        {
            const Uint32 waitTime = MS_PER_FRAME - (SDL_GetTicks() - prevTimePoint);
            SDL_Delay(waitTime);
        }

        const Uint32 deltaTime = SDL_GetTicks() - prevTimePoint;
        prevTimePoint = SDL_GetTicks();

        Update(deltaTime);
        Render();
    }
}

void Game::HandleEvents()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_EventType::SDL_QUIT)
        {
            isRunning_ = false;
            break;
        }
        else
        {
            for (const auto& obj : rectObjects_)
                obj->HandleEvent(e);
        }
    }
}

void Game::Update(Uint32 deltaTime)
{
    for (const auto& obj : rectObjects_)
        obj->Update(deltaTime);

    // collision resolution
    // limit is here to prevent infinite collision cycle
    for (int limit = 0; limit < 100; ++limit)
    {
        bool isCollisionDetected = false;

        for (int i = 0; i < rectObjects_.size() - 1; ++i)
        {
            for (int j = i + 1; j < rectObjects_.size(); ++j)
            {
                Rect& obj1 = *rectObjects_[i];
                Rect& obj2 = *rectObjects_[j];

                if (obj1.CheckCollision(obj2))
                {
                    isCollisionDetected = true;
                    obj1.ResolveCollision(obj2);
                }
            }
        }

        if (!isCollisionDetected)
            break;

        if (limit == 99)
            SDL_LogWarn(0, "100 loop limit reached!");
    }

    for (const auto& obj : rectObjects_)
        obj->Rect::Update(deltaTime);
}

void Game::Render() const
{
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderClear(renderer_);

    for (const auto& obj : rectObjects_)
        obj->Render(renderer_);

    SDL_RenderPresent(renderer_);
}
