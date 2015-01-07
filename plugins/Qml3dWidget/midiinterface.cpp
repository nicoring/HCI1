 #include "midiinterface.h"
using namespace mtq;

MTQ_QML_REGISTER_PLUGIN(MidiInterface)

MidiInterface::MidiInterface(QQuickItem *parent) :
    QQuickPaintedItem(parent)
{
}

// inherited from abstract method, but unused
void MidiInterface::paint(QPainter *painter){
    painter; // hacky -- but removes a compiler warning
}

/**
 * Triggered when button was tapped by player.
 * This should notify the ableton project to start midi signal transmission.
 *
 * @brief MidiInterface::buttonTapped
 * @param player_id
 * @param button_id
 */
void MidiInterface::buttonTapped(int player_id, int button_id)
{
    qDebug() << "Player " << player_id << " tapped button " << button_id;
}

/**
 * Triggered when player is on button.
 * This should notify the ableton project to start midi signal transmission.
 *
 * @brief MidiInterface::buttonTapped
 * @param player_id
 * @param button_id
 */
void MidiInterface::buttonDown(int player_id, int button_id)
{
    qDebug() << "Player " << player_id << " on button " << button_id;
}

/**
 * Triggered when player releases button.
 * This should notify the ableton project to start midi signal transmission.
 *
 * @brief MidiInterface::buttonTapped
 * @param player_id
 * @param button_id
 */
void MidiInterface::buttonUp(int player_id, int button_id)
{
    qDebug() << "Player " << player_id << " released button " << button_id;
}
