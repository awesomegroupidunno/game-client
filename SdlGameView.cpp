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

void SdlGameView::drawVehicle(SDL_Rect *vehicle, double angle, int teamColor){
	glTranslatef(vehicle->x, vehicle->y, 0);
	glRotatef(angle, 0, 0, 1);
	glScalef(vehicle->h/2, vehicle->w/2, 1);
	if(teamColor == 0) {
		glColor3f(1.0, 0.0, 0.0);
	}else if(teamColor == 1){
		glColor3f(0.0, 0.0, 1.0);
	}
	drawSquare();
}

void SdlGameView::drawBase(SDL_Rect *base, int teamColor){
	glTranslatef(base->x, base->y, 0);
	glScalef(base->h/2, base->w/2, 1);
	if(teamColor == 0) {
		glColor3f(1.0, 0.0, 0.0);
	}else if(teamColor == 1){
		glColor3f(0.0, 0.0, 1.0);
	}
	drawSquare();
}

int SdlGameView::drawView(){
	if(!init()){
		return 0;
	}

	// Rendering loop
	bool gameRunning = true;
	while (gameRunning) {

		// Listen for user input
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
			{
				// The user pressed a key
				inputAdapter->key_down(event);
			}
			if (event.type == SDL_KEYUP)
			{
				// The user released a key
				inputAdapter->key_up(event);
			}
			if (event.type == SDL_QUIT)
			{
				// The application was quit (clicked X or pressed alt+f4)
				gameRunning = false;
			}
		}

		// React to any keys that are currently being held down
		inputAdapter->check_keys();

		//initialize queue of vehicles to be drawn
		std::vector<Vehicle*>* vehicles = gameViewAdapter->getVehicles();
		int numCars = (int) vehicles->size();
		SDL_Rect* cars = new SDL_Rect[numCars];
		for (unsigned long i = 0; i < numCars; i++){
			cars[i].x = vehicles->at(i)->x;
			cars[i].y = vehicles->at(i)->y;
			cars[i].w = vehicles->at(i)->width;
			cars[i].h = vehicles->at(i)->height;
		}

		//initialize queue of bases to be drawn
		std::vector<Base*>* bases = gameViewAdapter->getBases();
		int numBases = (int) bases->size();
		SDL_Rect* baseRects = new SDL_Rect[numBases];
		for (unsigned long i = 0; i < numBases; i++){
			baseRects[i].x = bases->at(i)->x;
			baseRects[i].y = bases->at(i)->y;
			baseRects[i].w = bases->at(i)->width;
			baseRects[i].h = bases->at(i)->height;
		}

		// Make background white and clear renderer
		glClear(GL_COLOR_BUFFER_BIT);

		//draw vehicles
		for (int j = 0; j < numCars; j++) {
			glPushMatrix();
				drawVehicle(&cars[j], vehicles->at(j)->frontAngle, vehicles->at(j)->team);
			glPopMatrix();
		}

		//draw bases
		for (int j = 0; j < numBases; j++) {
			glPushMatrix();
				drawBase(&baseRects[j], bases->at(j)->team);
			glPopMatrix();
		}

		// Update the screen
		glFlush();
		SDL_GL_SwapWindow(window);

		// Add a 20 ms delay to reduce render load
		SDL_Delay(20);
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