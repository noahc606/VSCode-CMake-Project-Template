#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_net.h>
#include <SDL2/SDL_ttf.h>

int main()
{
    printf("hello\n");

    SDL_Init(0);
    SDL_CreateWindow("My Window", 0, 0, 640, 480, SDL_WINDOW_OPENGL);

    bool running = true;
    while(running) {
        SDL_Event e;
        SDL_PollEvent(&e);
        if(e.type==SDL_QUIT) {
            running = false;
        }
    }

    printf("Quitting\n");
    SDL_Quit();

    return 0;
}

int WinMain()
{
    return main();
}