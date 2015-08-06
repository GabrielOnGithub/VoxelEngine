#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include "sdlglutils.h"

void Dessiner();
void stop();

int main(int argc, char *argv[])
{
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);
    atexit(stop);
    SDL_WM_SetCaption("Planete Terre", NULL);

    SDL_SetVideoMode(640, 480, 32, SDL_OPENGL);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(70,(double)640/480,0.001,1000);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    Uint32 last_time,current_time,elapsed_time; //for time animation
    const Uint32 time_per_frame = 1000/50;
    Uint32 start_time,stop_time; //for frame limit
    last_time = SDL_GetTicks();
    Dessiner();
    SDL_EnableKeyRepeat(10, 10);

    for (;;)
    {

        start_time = SDL_GetTicks();

        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                exit(0);
                break;

            }
        }

        current_time = SDL_GetTicks();
        elapsed_time = current_time - last_time;
        last_time = current_time;

        Dessiner();

        stop_time = SDL_GetTicks();
        if ((stop_time - last_time) < time_per_frame)
        {
            //SDL_Delay(time_per_frame - (stop_time - last_time));
        }

    }

    return 0;
}
void Dessiner()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );

    gluLookAt(3,4,0,0,0,0,0,0,1);

    GLUquadric* params=gluNewQuadric();
    gluSphere(params,1,50,50);
    gluDeleteQuadric(params);

    glFlush();
    SDL_GL_SwapBuffers();
}
void stop()
{

    SDL_Quit();
}
