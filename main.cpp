#include <SDL/SDL.h>
#include "SDL/SDL_image.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include "sdlglutils.h"

#include "freeflycamera.h"
void Dessiner();

double MangleZ = 0, VangleZ = 0, NangleZ = 0, UangleZ = 0, SangleZ = 0, JangleZ = 0, MAangleZ = 0, TangleZ = 0;
double MangleX = 0, VangleX = 0, NangleX = 0, UangleX = 0, SangleX = 0, JangleX = 0, MAangleX = 0, TangleX = 0;
FreeFlyCamera * camera;

int main(int argc, char *argv[])
{
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);
    atexit(SDL_Quit);
    SDL_WM_SetCaption("SDL GL Application", NULL);
    SDL_SetVideoMode(640, 480, 32, SDL_OPENGL);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(70,(double)640/480,1,1000);

    glEnable(GL_DEPTH_TEST);

    //Dessiner();

    Uint32 last_time = SDL_GetTicks();
    Uint32 current_time,ellapsed_time;
    Uint32 start_time;
    
    camera = new FreeFlyCamera(Vector3D(0,0,2));
    
    for (;;)
    {
        start_time = SDL_GetTicks();
        while (SDL_PollEvent(&event))
        {

            switch(event.type)
            {
                case SDL_QUIT:
                exit(0);
                break;
                case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                    exit(0);
                    break;
                    default : //on a utilisé la touche P et la touche ECHAP, le reste (en keydown) est donné à la caméra
                    camera->OnKeyboard(event.key);
                }
                break;
                case SDL_KEYUP: //on n'utilise pas de keyup, on donne donc tout à la caméra
                camera->OnKeyboard(event.key);
                break;
                case SDL_MOUSEMOTION: //la souris est bougée, ça n'intéresse que la caméra
                camera->OnMouseMotion(event.motion);
                break;
                case SDL_MOUSEBUTTONUP:
                case SDL_MOUSEBUTTONDOWN: //tous les évenements boutons (up ou down) sont donnés à la caméra
                camera->OnMouseButton(event.button);
                break;
            }
        }

        current_time = SDL_GetTicks();
        ellapsed_time = current_time - last_time;
        last_time = current_time;
        
        NangleZ += 0.00015 * ellapsed_time;
        NangleX += 0.00015 * ellapsed_time;
        UangleZ += 0.00029 * ellapsed_time;
        UangleX += 0.00029 * ellapsed_time;
        SangleZ += 0.00082 * ellapsed_time;
        SangleX += 0.00082 * ellapsed_time;
        JangleZ += 0.002 * ellapsed_time;
        JangleX += 0.002 * ellapsed_time;
        MAangleZ += 0.013 * ellapsed_time;
        MAangleX += 0.013 * ellapsed_time;
        TangleZ += 0.024 * ellapsed_time;
        TangleX += 0.024 * ellapsed_time;
        VangleZ += 0.039 * ellapsed_time;
        VangleX += 0.039 * ellapsed_time;
        MangleZ += 0.1 * ellapsed_time;
        MangleX += 0.1 * ellapsed_time;
        
        camera->animate(ellapsed_time);
        Dessiner();
        ellapsed_time = SDL_GetTicks() - start_time;
        if (ellapsed_time < 10)
        {
            SDL_Delay(10 - ellapsed_time);
        }

    }

    return 0;
}

void Dessiner()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );

    camera->look();

    GLUquadric* params;
    params = gluNewQuadric();
    
    //soleil
    gluQuadricTexture(params,GL_TRUE);
    gluSphere(params,3,25,25);
    
    //neptune
    glPushMatrix();
    glRotated(NangleZ,0,0,1);
    glRotated(NangleX,1,0,0);
    glTranslated(-311.2,0,0);
    glRotated(NangleZ,0,0,1);
    glRotated(NangleX,1,0,0);
    gluSphere(params,0.108,25,25);
    glPopMatrix();
    
    //Uranus
    glPushMatrix();
    glRotated(UangleZ,0,0,1);
    glRotated(UangleX,1,0,0);
    glTranslated(-198.6,0,0);
    glRotated(UangleZ,0,0,1);
    glRotated(UangleX,1,0,0);
    gluSphere(params,0.1101,25,25);
    glPopMatrix();
    
    //Saturne
    glPushMatrix();
    glRotated(SangleZ,0,0,1);
    glRotated(SangleX,1,0,0);
    glTranslated(-98.8,0,0);
    glRotated(SangleZ,0,0,1);
    glRotated(SangleX,1,0,0);
    gluSphere(params,0.261,25,25);
    glPopMatrix();
    
    //jupiter
    glPushMatrix();
    glRotated(JangleZ,0,0,1);
    glRotated(JangleX,1,0,0);
    glTranslated(-53.8,0,0);
    glRotated(JangleZ,0,0,1);
    glRotated(JangleX,1,0,0);
    gluSphere(params,0.309,25,25);
    glPopMatrix();
    
    //mars
    glPushMatrix();
    glRotated(MAangleZ,0,0,1);
    glRotated(MAangleX,1,0,0);
    glTranslated(-15.7,0,0);
    glRotated(MAangleZ,0,0,1);
    glRotated(MAangleX,1,0,0);
    gluSphere(params,0.015,25,25);
    glPopMatrix();
    
    //terre
    glPushMatrix();
    glRotated(TangleZ,0,0,1);
    glRotated(TangleX,1,0,0);
    glTranslated(-10.3,0,0);
    glRotated(TangleZ,0,0,1);
    glRotated(TangleX,1,0,0);
    gluSphere(params,0.0276,25,25);
    glPopMatrix();
        //lune
            glPushMatrix();
            glTranslated(-10.3,0,0);
            glRotated(TangleZ,0,0,1);
            glRotated(TangleX,1,0,0);
            glTranslated(-0.05,0,0);
            glRotated(TangleZ,0,0,1);
            glRotated(TangleX,1,0,0);
            gluSphere(params,0.0075,25,25);
            glPopMatrix();
    //venus
    glPushMatrix();
    glRotated(VangleZ,0,0,1);
    glRotated(VangleX,1,0,0);
    glTranslated(-7.57,0,0);
    glRotated(VangleZ,0,0,1);
    glRotated(VangleX,1,0,0);
    gluSphere(params,0.0261 ,25,25);
    glPopMatrix();

    //mercure
    glPushMatrix();
    glRotated(MangleZ,0,0,1);
    glRotated(MangleX,1,0,0);
    glTranslated(-4,0,0);
    glRotated(MangleZ,0,0,1);
    glRotated(MangleX,1,0,0);
    gluSphere(params,0.0105,25,25);
    glPopMatrix();
    
    gluDeleteQuadric(params);
    
    glFlush();
    SDL_GL_SwapBuffers();
}
