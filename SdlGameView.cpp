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

void SdlGameView::drawTriangle() {
	glBegin(GL_POLYGON);
		glVertex2f(tri[0][0], tri[0][1]);
		glVertex2f(tri[1][0], tri[1][1]);
		glVertex2f(tri[2][0], tri[2][1]);
	glEnd();
}

void SdlGameView::drawVehicle(SDL_Rect *vehicle, double angle, int teamColor){
	glTranslatef(vehicle->x, vehicle->y, 0);
	glRotatef(angle, 0, 0, 1);
	glScalef(vehicle->h, vehicle->w, 1);
	if(teamColor == 0) {
		glColor3f(1.0, 0.0, 0.0);
	}else if(teamColor == 1){
		glColor3f(0.0, 0.0, 1.0);
	}
	drawSquare();
}

void SdlGameView::drawBase(SDL_Rect *base, int teamColor){
	glTranslatef(base->x, base->y, 0);
	glScalef(base->h, base->w, 1);
	if(teamColor == 0) {
		glColor3f(1.0, 0.0, 0.0);
	}else if(teamColor == 1){
		glColor3f(0.0, 0.0, 1.0);
	}
	drawSquare();
}

void SdlGameView::drawGenerator(Generator *generator)
{
	glTranslatef(generator->x, generator->y, 0.0);
	glScalef(generator->height, generator->width, 1);
	if(generator->team == 0) {
		glColor3f(1.0, 0.0, 0.0);
	}else if(generator->team == 1) {
		glColor3f(0.0, 0.0, 1.0);
	}
	drawTriangle();
}

void SdlGameView::drawShield(SDL_Rect *shield, int teamColor)
{
	glTranslatef(shield->x, shield->y, 0);
	glScalef(shield->h, shield->w, 1);
	if(teamColor == 0) {
		glColor3f(0.5, 0.0, 0.0);
	}else if(teamColor == 1){
		glColor3f(0.0, 0.0, 0.5);
	}
	drawSquare();
}

void SdlGameView::drawBullet(SDL_Rect* bullet)
{
	glTranslatef(bullet->x, bullet->y, 0);
	glScalef(bullet->h, bullet->w, 1.0f);
	glColor3f(0.8f, 0.6f, 0.6f);
	drawSquare();
}

void SdlGameView::drawHealthBar(int curHealth, int maxHealth, float x, float y){
	glTranslatef(x, y, 0.0);
	float healthPercent = (((float)curHealth/(float)maxHealth)*100)/2;
	glPushMatrix();
		glScalef(50, 5, 1.0);		//scales from the center, scales Y by 50 (100%)
		glColor3f(0.0, 0.0, 0.0);	//black background bar based on max health
		drawSquare();
	glPopMatrix();
	glPushMatrix();
		glScalef(healthPercent, 5, 1.0);	//scales from the left, scales Y by the percentage of curHealth
		glColor3f(0.0, 1.0, 0.0);	//green foreground bar based on current health
		drawSquare();
	glPopMatrix();
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
		int numVehicles = (int) vehicles->size();
		SDL_Rect*vehicleRects = new SDL_Rect[numVehicles];
		for (unsigned long i = 0; i < numVehicles; i++){
			vehicleRects[i].x = vehicles->at(i)->x;
			vehicleRects[i].y = vehicles->at(i)->y;
			vehicleRects[i].w = vehicles->at(i)->width;
			vehicleRects[i].h = vehicles->at(i)->height;
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

		// initialize queue of shields to be drawn
		std::vector<Shield*>* shields = gameViewAdapter->getShields();
		int numShields = (int) shields->size();
		SDL_Rect* shieldRects = new SDL_Rect[numShields];
		for (unsigned long i = 0; i < numShields; i++)
		{
			shieldRects[i].x = shields->at(i)->x;
			shieldRects[i].y = shields->at(i)->y;
			shieldRects[i].w = shields->at(i)->width;
			shieldRects[i].h = shields->at(i)->height;
		}

		// initialize vector of generators to be drawn
		std::vector<Generator*>* generators = gameViewAdapter->getGenerators();

		// Init bullets to be drawn
		std::vector<Bullet*>* bullets = gameViewAdapter->getBullets();
		int numBullets = (int) bullets->size();
		SDL_Rect* bulletRects = new SDL_Rect[numBullets];
		for (unsigned long i = 0; i < numBullets; i++)
		{
			bulletRects[i].x = bullets->at(i)->x;
			bulletRects[i].y = bullets->at(i)->y;
			bulletRects[i].w = bullets->at(i)->radius;
			bulletRects[i].h = bullets->at(i)->radius;
		}

		// Make background white and clear renderer
		glClear(GL_COLOR_BUFFER_BIT);

		//draw vehicles and their health bars
		for (int j = 0; j < numVehicles; j++) {
			glPushMatrix();
				drawVehicle(&vehicleRects[j], vehicles->at(j)->frontAngle, vehicles->at(j)->team);
			glPopMatrix();
			glPushMatrix();
				drawHealthBar(vehicles->at(j)->curHealth, vehicles->at(j)->maxHealth, vehicles->at(j)->x, vehicles->at(j)->y + vehicles->at(j)->height);
			glPopMatrix();
		}

		//draw bases and their health bars
		for (int j = 0; j < numBases; j++) {
			glPushMatrix();
				drawBase(&baseRects[j], bases->at(j)->team);
			glPopMatrix();
			glPushMatrix();
				drawHealthBar(bases->at(j)->curHealth, bases->at(j)->maxHealth, bases->at(j)->x, bases->at(j)->y + bases->at(j)->height);
			glPopMatrix();
		}

		//draw shields
		for (int j = 0; j < numShields; j++){
			glPushMatrix();
				drawShield(&shieldRects[j], shields->at(j)->team);
			glPopMatrix();
		}

		//draw generators
		for (int j = 0; j < generators->size(); j++){
			glPushMatrix();
				drawGenerator(generators->at(j));
			glPopMatrix();
			glPushMatrix();
				drawHealthBar(generators->at(j)->curHealth, generators->at(j)->maxHealth, generators->at(j)->x, generators->at(j)->y + generators->at(j)->height);
			glPopMatrix();
		}

		// Draw bullets
		for (int j = 0; j < numBullets; j++)
		{
			glPushMatrix();
				drawBullet(&bulletRects[j]);
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