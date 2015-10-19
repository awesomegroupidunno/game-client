//
// Created by austin4e on 9/26/15.
//
#include "SdlGameView.h"

SdlGameView::SdlGameView(SdlGameViewAdapter* gva, SdlInputAdapter* ia){
        gameViewAdapter = gva;
        inputAdapter = ia;
    }

int SdlGameView::init(){
    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 0;
    }

    // Create SDL window with OpenGL
    window = SDL_CreateWindow("Car Combat", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
    if (window == NULL) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 0;
    }

    if(!initGL()){
        std::cout << "Error: OpenGL with SDL failed to initialize" << std::endl;
    }

    return 1;
}

int SdlGameView::initGL(){
    // Set our OpenGL attributes.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    // DO NOT CHANGE!! -- Rendering relies on this version of OpenGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // Create GL context buffer for window
    context = SDL_GL_CreateContext(window);
    SDL_GL_SetSwapInterval(1);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    glewInit();

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
    glViewport( 0, 0, 640, 480 );
    glClear( GL_COLOR_BUFFER_BIT );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    glOrtho(0.0f, 640, 480, 0.0f, -1.0f, 1.0f);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    SDL_GL_SwapWindow(window);
}

void SdlGameView::drawSquare(){
    glBegin(GL_QUADS);
        glVertex2f(sqr[0][0], sqr[0][1]);
        glVertex2f(sqr[1][0], sqr[1][1]);
        glVertex2f(sqr[2][0], sqr[2][1]);
        glVertex2f(sqr[3][0], sqr[3][1]);
    glEnd();
}

void SdlGameView::drawVehicle(SDL_Rect *vehicle, double angle){
    // TODO: switch to OpenGL, delete SDL renderer code remnants
    // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
    // SDL_RenderFillRect(renderer, vehicle);
    glTranslatef(vehicle->x, vehicle->y, 0);
    glRotatef(angle, 0, 0, 1);
    glScalef(vehicle->h/2, vehicle->w/2, 1);
    glColor3f(1.0, 0.0, 0.0);
    drawSquare();
}

int SdlGameView::drawView(){
    if(!init()){
        return 0;
    }

    // Rendering loop
    bool gameRunning = true;
    int tick = 0;
    while (gameRunning) {

        // Listen for user input
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN) {
                // Listen for new user input
                inputAdapter->inputListener(event);
            }
            if (event.type == SDL_QUIT)
                gameRunning = false;
        }

        int numCars = gameViewAdapter->getVehicles().size();
        printf("number of cars = %i\n", numCars);
        SDL_Rect* cars = new SDL_Rect[numCars];
        double angle;
        // Take the vehicles from the vehicle vector
        // Use their values to begin drawing
        printf("SETTING CARS FROM VEHICLE VECTOR\n");
        for (int i = 0; i < numCars; i++){
            cars[i].x = gameViewAdapter->getVehicles().at(i)->x;
            cars[i].y = gameViewAdapter->getVehicles().at(i)->y;
            cars[i].w = carWidth;
            cars[i].h = carHeight;
            angle = gameViewAdapter->getVehicles().at(i)->frontAngle;
        }

        // Make background white and clear renderer
        // TODO: switch to OpenGL, delete SDL renderer code remnants
        //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        //SDL_RenderClear(renderer);
        glClear(GL_COLOR_BUFFER_BIT);

        printf("DRAWING: tick %i\n", tick);

        for (int j = 0; j < numCars; j++) {
            glPushMatrix();
                drawVehicle(&cars[j], angle);
            glPopMatrix();
        }

        // Update the screen
        //SDL_RenderPresent(renderer);
        glFlush();
        SDL_GL_SwapWindow(window);

        // Take a quick break after all that hard work
        SDL_Delay(40);

        // Next tick
        tick++;
    }
        // Clean up
        exit();

        return 0;
}

void SdlGameView::exit(){
    // Delete OpenGL context
    SDL_GL_DeleteContext(context);

    // Destroy window
    SDL_DestroyWindow(window);

    // Shutdown SDL2
    SDL_Quit();
}