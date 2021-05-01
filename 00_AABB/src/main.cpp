#include "Game.hpp"


int SDL_main(int argc, char** argv)
{
    Game game;

    if (game.Init())
        game.Run();
    game.Destroy();

    return 0;
}
