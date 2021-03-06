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

	// Initialize GLUT -- use dummy values since args aren't needed
	int argc = 1;
	char *argv[1] = {(char*)"init"};
	glutInit(&argc, argv);

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

	return 1;
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
	if(vehicle->team == RED_TEAM) {
		glColor3f(1.0, 0.0, 0.0);
	}else if(vehicle->team == BLUE_TEAM){
		glColor3f(0.0, 0.0, 1.0);
	}
	drawSquare();
	glTranslatef(0.3, 0, 0);
	glScalef(0.3, 0.3, 1);
	glColor3f(0.0, 0.0, 0.0);
	drawSquare();
}

void SdlGameView::pointToVehicle(Vehicle *vehicle){
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// create an arrow that points to clients vehicle
	glTranslatef(vehicle->x, (GLfloat) (vehicle->y - (vehicle->height / 1.1) ), -1.0f);
	glScalef(15, 15, 1);
	glColor4f(0.0f, 0.0f, 0.0f, highlight);
	drawTriangle();

	glDisable(GL_BLEND);
}

void SdlGameView::drawBase(Base *base){
	glTranslatef(base->x, base->y, 0);
	glScalef(base->height, base->width, 1);
	if(base->team == RED_TEAM) {
		glColor3f(1.0, 0.0, 0.0);
	}else if(base->team == BLUE_TEAM){
		glColor3f(0.0, 0.0, 1.0);
	}
	drawSquare();
}

void SdlGameView::drawGenerator(Generator *generator)
{
	glTranslatef(generator->x, generator->y, 0.0);
	glScalef(generator->height, generator->width, 1);
	if(generator->team == RED_TEAM) {
		glColor3f(1.0, 0.0, 0.0);
	}else if(generator->team == BLUE_TEAM) {
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
	if(shield->team == RED_TEAM) {
		glColor4f(0.5, 0.0, 0.0, highlight);
	}else if(shield->team == BLUE_TEAM){
		glColor4f(0.0, 0.0, 0.5, highlight);
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
	glScalef(powerup->width, powerup->height, 1.0f);
	//change colors to differentiate types of powerups
    switch (powerup->type)
    {
        case HEAL:
            glColor3f(0.0f, 1.0f, 0.0f);
            break;
        case SPEEDUP:
            glColor3f(1.0f, 1.0f, 0.0f);
            break;
        case ROCKET:
            glColor3f(0.0f, 1.0f, 1.0f);
            break;
		case GRAVWELL:
			glColor3f(0.0f, 0.0f, 0.0f);
			break;
        default:
            glColor3f(0.5f, 0.5f, 0.5f);
    }
	drawSquare();
}

void SdlGameView::drawRocket(Rocket *rocket){
	glTranslatef(rocket->x, rocket->y, 0);
	glRotatef((GLfloat)rocket->angle, 0, 0, 1);
	glScalef(rocket->width, rocket->height, 1.0f);
	glColor3f(0.8f, 0.6f, 0.6f);
	drawSquare();
}

void SdlGameView::drawGravityWell(GravityWell *gravityWell){
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (int i = 0; i < 360; i++) {
		glLoadIdentity();
		glTranslatef(gravityWell->x, gravityWell->y, 0);
		glRotatef(i, 0.0, 0.0, 1.0);
		glScalef(gravityWell->radius, 50.0, 1.0);
		glBegin(GL_POLYGON);
			glColor4f(0.0, 0.0, 0.0, 0.8);
			glVertex2f(triFan[0][0], triFan[0][1]);
			glColor4f(0.0, 0.0, 0.0, 0.0);
			glVertex2f(triFan[1][0], triFan[1][1]);
			glVertex2f(triFan[2][0], triFan[2][1]);
		glEnd();
	}

	glDisable(GL_BLEND);
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

void SdlGameView::drawHUD(Vehicle* client){
	glColor3f(0.0f,0.0f,0.0f);

	// Power up
	switch (client->storedPower)
	{
		case NO_POWERUP:
			sprintf(strPowerup, "Powerup: NONE");
			break;
		case HEAL:
			sprintf(strPowerup, "Powerup: HEAL");
			break;
		case SPEEDUP:
			sprintf(strPowerup, "Powerup: SPEED BOOST");
			break;
		case ROCKET:
			sprintf(strPowerup, "Powerup: HOMING ROCKET");
			break;
		case GRAVWELL:
			sprintf(strPowerup, "Powerup: GRAVITY WELL");
			break;
		default:
			sprintf(strPowerup, "Powerup: NONE");
	}
	drawText(10.0f, 20.0f, strPowerup, GLUT_BITMAP_HELVETICA_18);

	// Health
	sprintf(strHealth, "Health: %i / %i", client->curHealth, client->maxHealth);
	drawText(300.0f, 20.0f, strHealth, GLUT_BITMAP_HELVETICA_18);
}

void SdlGameView::drawText(float x, float y, char *text, void *font)
{
	glRasterPos2f(x, y);
	for (unsigned int i = 0; i < strlen(text); i++)
	{
		glutBitmapCharacter(font, text[i]);
	}
}

/*
 * MAIN DRAWING LOOP
 */
int SdlGameView::drawView(){
	if(!init()){
		return 0;
	}

	// initialize variables used for pulsating effect
	highlight = 0.5;
	delta = -0.01f;

	// Rendering loop
	bool gameRunning = true;
	int gameOver;
	while (gameRunning) {

		// Detect game over state
		gameOver =  gameViewAdapter->getGameOver();

		if (gameOver == -1)
		{
			gameRunning = drawPlayScreen();
		}
		else
		{
			inputAdapter->clear_keys();
			gameRunning = drawEndScreen(gameOver);
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

bool SdlGameView::drawPlayScreen()
{
	// Listen for user input
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			// The user pressed a key
			inputAdapter->key_down(event);

			// The user pressed escape
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				return false;
			}
		}
		if (event.type == SDL_KEYUP)
		{
			// The user released a key
			inputAdapter->key_up(event);
		}
		if (event.type == SDL_QUIT)
		{
			// The application was quit (clicked X or pressed alt+f4)
			return false;
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
	std::vector<Rocket*>* rockets = gameViewAdapter->getRockets();
	int numRockets = (int) rockets->size();
	std::vector<GravityWell*>* gravityWells = gameViewAdapter->getGravityWells();
	int numGravityWells = (int) gravityWells->size();

	// Make background white and clear renderer
	glClear(GL_COLOR_BUFFER_BIT);

	//draw rockets and gravity wells
	for (unsigned long j = 0; j < numGravityWells; j++) {
		glPushMatrix();
			drawGravityWell(gravityWells->at(j));
		glPopMatrix();
	}

	for (unsigned long j = 0; j < numRockets; j++) {
		glPushMatrix();
			drawRocket(rockets->at(j));
		glPopMatrix();
	}

	//draw bases and their health bars
	for (unsigned long j = 0; j < numBases; j++) {
		glPushMatrix();
		drawBase(bases->at(j));
		glPopMatrix();
		glPushMatrix();
		drawHealthBar(bases->at(j)->curHealth, bases->at(j)->maxHealth, bases->at(j)->x, (float) (bases->at(j)->y + bases->at(j)->height / 1.1) );
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

	// pulsating effect for shields / vehicle arrow
	highlight += delta;
	if(highlight >= 0.5){
		delta = -0.01f;
	}else if(highlight <=0.2){
		delta = 0.01f;
	}

	//draw generators
	for (unsigned long j = 0; j < numGenerators; j++){
		glPushMatrix();
		drawGenerator(generators->at(j));
		glPopMatrix();
		glPushMatrix();
		drawHealthBar(generators->at(j)->curHealth, generators->at(j)->maxHealth, generators->at(j)->x, (float) (generators->at(j)->y + generators->at(j)->height / 1.1) );
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

	//draw vehicles and their health bars
	Vehicle *tempVehicle = NULL;
	for (unsigned long j = 0; j < numVehicles; j++) {
		glPushMatrix();
		drawVehicle(vehicles->at(j));
		glPopMatrix();
		glPushMatrix();
		drawHealthBar(vehicles->at(j)->curHealth, vehicles->at(j)->maxHealth, vehicles->at(j)->x, (float) (vehicles->at(j)->y + vehicles->at(j)->height / 1.3) );
		glPopMatrix();
		if(vehicles->at(j)->isMe){
			tempVehicle = vehicles->at(j);
			glPushMatrix();
			pointToVehicle(vehicles->at(j));
			glPopMatrix();
		}
	}
	if (tempVehicle != NULL)
	{
		glPushMatrix();
		drawHUD(tempVehicle);
		glPopMatrix();
	}

	return true;
}

bool SdlGameView::drawEndScreen(int losingTeam)
{
	// Listen for user input
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			// The user pressed escape
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				return false;
			}
		}
		if (event.type == SDL_QUIT)
		{
			// The application was quit (clicked X or pressed alt+f4)
			return false;
		}
	}

	glClear(GL_COLOR_BUFFER_BIT);

	// Set color and text based on winning team
	char gameOverText[50];
	int secToRestart = gameViewAdapter->getSecToRestart();
	if (losingTeam == RED_TEAM)
	{
		glColor3f(0.0f, 0.0f, 1.0f);
		sprintf(gameOverText, "BLUE TEAM WON! Press ESC to quit. Restart in %i...", secToRestart);
	}
	if (losingTeam == BLUE_TEAM)
	{
		glColor3f(1.0f, 0.0f, 0.0f);
		sprintf(gameOverText, "RED TEAM WON! Press ESC to quit. Restart in %i...", secToRestart);
	}

	// Draw text
	drawText(100.0f, 200.0f, gameOverText, GLUT_BITMAP_HELVETICA_18);

	return true;
}

void SdlGameView::exit(){
	// Delete OpenGL context
	SDL_GL_DeleteContext(context);

	// Destroy window
	SDL_DestroyWindow(window);

	// Shutdown SDL2
	SDL_Quit();
}