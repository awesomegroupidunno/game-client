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

void SdlGameView::drawVehicle(Vehicle *vehicle){
	glTranslatef(vehicle->x, vehicle->y, 0);
	glRotatef((GLfloat)vehicle->frontAngle, 0, 0, 1);
	glScalef(vehicle->height, vehicle->width, 1);
	if(vehicle->team == 0) {
		glColor3f(1.0, 0.0, 0.0);
	}else if(vehicle->team == 1){
		glColor3f(0.0, 0.0, 1.0);
	}
	drawSquare();
}

void SdlGameView::drawBase(Base *base){
	glTranslatef(base->x, base->y, 0);
	glScalef(base->height, base->width, 1);
	if(base->team == 0) {
		glColor3f(1.0, 0.0, 0.0);
	}else if(base->team == 1){
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

void SdlGameView::drawShield(Shield *shield)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glTranslatef(shield->x, shield->y, 0);
	glScalef(shield->height, shield->width, 1);
	if(shield->team == 0) {
		glColor4f(0.5, 0.0, 0.0, 0.5);
	}else if(shield->team == 1){
		glColor4f(0.0, 0.0, 0.5, 0.5);
	}
	drawSquare();

	glDisable(GL_BLEND);
}

void SdlGameView::drawBullet(Bullet *bullet)
{
	glTranslatef(bullet->x, bullet->y, 0);
	glScalef(bullet->radius, bullet->radius, 1.0f);
	glColor3f(0.8f, 0.6f, 0.6f);
	drawSquare();
}

void SdlGameView::drawPowerup(Powerup *powerup)
{
	glTranslatef(powerup->x, powerup->y, 0);
	glScalef(powerup->radius, powerup->radius, 1.0f);
	//change colors to differentiate types of powerups
	if(powerup->type == 0)
	{
		glColor3f(0.0f, 1.0f, 0.0f);
	}else if(powerup->type == 1)
	{
		glColor3f(1.0f, 1.0f, 0.0f);
	}else if(powerup->type == 2)
	{
		glColor3f(0.0f, 1.0f, 1.0f);
	}
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

/*
 * MAIN DRAWING LOOP
 */
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

		//initialize vector lists (queue) of objects to be drawn, and get their sizes
		std::vector<Vehicle*>* vehicles = gameViewAdapter->getVehicles();
		int numVehicles = (int) vehicles->size();
		std::vector<Base*>* bases = gameViewAdapter->getBases();
		int numBases = (int) bases->size();
		std::vector<Shield*>* shields = gameViewAdapter->getShields();
		int numShields = (int) shields->size();
		std::vector<Generator*>* generators = gameViewAdapter->getGenerators();
		int numGenerators = (int) generators->size();
		std::vector<Bullet*>* bullets = gameViewAdapter->getBullets();
		int numBullets = (int) bullets->size();
		std::vector<Powerup*>* powerups = gameViewAdapter->getPowerups();
		int numPowerups = (int) powerups->size();

		// Make background white and clear renderer
		glClear(GL_COLOR_BUFFER_BIT);

		//draw vehicles and their health bars
		for (unsigned long j = 0; j < numVehicles; j++) {
			glPushMatrix();
				drawVehicle(vehicles->at(j));
			glPopMatrix();
			glPushMatrix();
				drawHealthBar(vehicles->at(j)->curHealth, vehicles->at(j)->maxHealth, vehicles->at(j)->x, vehicles->at(j)->y + vehicles->at(j)->height);
			glPopMatrix();
		}

		//draw bases and their health bars
		for (unsigned long j = 0; j < numBases; j++) {
			glPushMatrix();
				drawBase(bases->at(j));
			glPopMatrix();
			glPushMatrix();
				drawHealthBar(bases->at(j)->curHealth, bases->at(j)->maxHealth, bases->at(j)->x, bases->at(j)->y + bases->at(j)->height);
			glPopMatrix();
		}

		//draw shields
		for (unsigned long j = 0; j < numShields; j++){
			if (shields->at(j)->isEnabled) {
				glPushMatrix();
					drawShield(shields->at(j));
				glPopMatrix();
			}
		}

		//draw generators
		for (unsigned long j = 0; j < numGenerators; j++){
			glPushMatrix();
				drawGenerator(generators->at(j));
			glPopMatrix();
			glPushMatrix();
				drawHealthBar(generators->at(j)->curHealth, generators->at(j)->maxHealth, generators->at(j)->x, generators->at(j)->y + generators->at(j)->height);
			glPopMatrix();
		}

		// Draw bullets
		for (unsigned long j = 0; j < numBullets; j++)
		{
			glPushMatrix();
				drawBullet(bullets->at(j));
			glPopMatrix();
		}

		// Draw powerups
		for (unsigned long j = 0; j < numPowerups; j++)
		{
			glPushMatrix();
				drawPowerup(powerups->at(j));
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