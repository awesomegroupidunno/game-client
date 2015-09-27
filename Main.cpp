#include "SdlGameView.cpp"
/*
 * NOTE: GameState.cpp and Vehicle.h usually would NOT be here.
 *      GameState would usually be set by the server.
 *      For the sake of testing, main has been hardcoded
 *      to initialize GameState and Vehicles.
 */
#include "GameState.cpp"
#include "Vehicle.h"
#include "GameController.h"

int main()
{
    // TODO: The following is an idea of how Main.cpp should look
    // Draw window / game screen
    // Initialize game loop / GameController.cpp
    // Handle exiting game
    /*
     * THE FOLLOWING IS ONLY A TEST OF WHAT THE STRUCTURE SHOULD LOOK LIKE
     */
    GameState state;
    GameController gc;
    Vehicle* player = new Vehicle(50, 50, 100, 0, 0);
    state.addPlayers(player);
    gc.replaceGameState(state);
    SdlGameView screen;
    screen.drawView();
    return 0;
}