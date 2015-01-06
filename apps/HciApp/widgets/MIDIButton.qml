import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import mtq.qml3d 1.0
import QtQuick.Window 2.1
import "../framework/GlobalLight.js" as GlobalLight
import "../framework"
import "."

CubeQuad {
    id: midiButton

    property int button_id
    property int player_id

    // class does not compile correctly
    // check against TravelingSalesmanCalculator form inClassHacking branch
    MidiInterface {
        id: midiInterface
    }

    /**
     * when button was tapped, signal the midi interface
     */
    function mtqTap(id, position) {
        console.info(id, position);
        midiInterface.buttonTapped(button_id, player_id)
    }

}
