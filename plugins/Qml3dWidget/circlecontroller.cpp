#include "circlecontroller.h"
using namespace mtq;

MTQ_QML_REGISTER_PLUGIN(CircleController)

CircleController::CircleController(QQuickItem *parent) :
    QQuickItem(parent)
{
}

// inherited from abstract method, but unused
void CircleController::paint(QPainter *painter){
    painter; // hacky -- but removes a compiler warning
}

/**
 * Lets the Circle pulse once
 *
 * @brief CircleController::beat
 */
void CircleController::beat() {
    emit doBeat();
}

/**
 * Rotates the spinner three times and then stops by the given playerNumber
 *
 * @brief CircleController::rotateToPlayer
 * @param num number of the player
 *
 *
      *******************************
      *             *               *
      *  player 1   *    player 2   *
      *             *               *
      *******************************
      *             *               *
      *  player 3   *    player 4   *
      *             *               *
      *******************************

 */
void CircleController::rotateToPlayer(int playerNum) {
    emit doRotateToPlayer(playerNum);
}

// TODO: should be implemented in a main controller class
void CircleController::chooseRandomSoloPlayer() {
    int playerNum;

    // get a random player number between 1 and 4
    playerNum = rand() % 4 + 1;
    this->rotateToPlayer(playerNum);
}
