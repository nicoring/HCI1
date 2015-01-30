import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import mtq.qml3d 1.0
import QtQuick.Window 2.1
import "../framework/GlobalLight.js" as GlobalLight
import "../framework"
import "."

MidiButtonMesh {
    id: midiButton

    property int button_id
    property int player_id
    property int instrument_id

    // load midi interface qml widget
    property MidiInterface midiInterface

    // 3d elements --> push into floor to be visible
    position: Qt.vector3d(0,0,1)

    // scale to small button size
    transform: [
        Scale3D {
            scale: Qt.vector3d(2.5,2.5,1)
        }
    ]

   /**
    * when foot is on button, signal the midi interface
    */

    function mtqContactDown(id, position) {
        highlight()
        console.info('contact down', id, position)
        console.info('button id', button_id, 'player id', player_id, 'instrument id', instrument_id);
        console.info('--- contact down ---');
        midiInterface.buttonDown(player_id, button_id, instrument_id);

        if (parent.mtqContactDown) {
            parent.mtqContactDown(id, position);
        }
    }


    function mtqContactUp(id, position) {
        unhighlight()
        console.info('contact up', id, position)
        console.info('button id', button_id, 'player id',  player_id, 'instrument id', instrument_id);
        console.info('--- contact up ---');

        midiInterface.buttonUp(player_id, button_id, instrument_id);

        if (parent.mtqContactDown) {
            parent.mtqContactDown(id, position);
        }
    }

}
