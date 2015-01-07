#include "midiinterface.h"

MTQ_QML_REGISTER_PLUGIN(MidiInterface)

/*MidiInterface::MidiInterface(QObject *parent) :
    QObject(parent)
{
}
*/
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
    qDebug() << "Player " << player_id << " triggered button " << button_id;
    emit playerRequestsMidiForButton(player_id, button_id);
}
