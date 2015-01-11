import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import mtq.qml3d 1.0
import QtQuick.Window 2.1
import "../framework/GlobalLight.js" as GlobalLight
import "../framework"
import "."

Item3D {
    id: buttonset

    property int player_id
    property MidiInterface midiInterface

    /*********************
     * initialize buttonset
     * --> show 'come here' label
     * --> on over, tag as active
     *     -> show menu buttons
     * --> on out and longer than time threshold
     *     -> show 'come here' label
     *     -> resume button which loads previous settings
     */

    /** keyboard buttons **/

    Item3D {
        id: midibuttons
        enabled: true

        MidiButton {
            id: btn1

            button_id: 1
            player_id: buttonset.player_id
            midiInterface: buttonset.midiInterface

            position: Qt.vector3d(0,0,0)
        }

        MidiButton {
            id: btn2

            button_id: 2
            player_id: buttonset.player_id
            midiInterface: buttonset.midiInterface

            position: Qt.vector3d(1.1, 0, 0)
        }

        MidiButton {
            id: btn3

            button_id: 3
            player_id: buttonset.player_id
            midiInterface: buttonset.midiInterface

            position: Qt.vector3d(0, 1.1, 0)
        }

        MidiButton {
            id: btn4

            button_id: 4
            player_id: buttonset.player_id
            midiInterface: buttonset.midiInterface

            position: Qt.vector3d(1.1, 1.1, 0)
        }
    }
}
