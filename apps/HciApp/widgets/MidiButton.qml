import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import mtq.qml3d 1.0
import QtQuick.Window 2.1
import "../framework/GlobalLight.js" as GlobalLight
import "../framework"
import "."

FlatButton {
    id: midiButton

    property int button_id
    property int player_id

    // load midi interface qml widget
    property MidiInterface midiInterface

    // 3d elements --> push into floor to be visible
    position: Qt.vector3d(0,0,-1)

    // scale to small button size
    transform: [
        Scale3D {
            scale: Qt.vector3d(1,1,0.1)
        }
    ]

    /**
     * when button was tapped, signal the midi interface
     */
    function mtqTap(id, position) {
        console.info(id, position, button_id, player_id);
        midiInterface.buttonTapped(button_id, player_id)
    }

   /**
    * when foot is on button, signal the midi interface
    */
    function mtqContactDown(id, position) {
        console.info('contact down', id, position, button_id, player_id);
        midiInterface.buttonDown(button_id, player_id);
    }

   /**
    * when foot is on button, signal the midi interface
    */
    function mtqContactUp(id, position) {
        console.info('contact up', id, position, button_id, player_id);
        midiInterface.buttonUp(button_id, player_id);
    }
}
