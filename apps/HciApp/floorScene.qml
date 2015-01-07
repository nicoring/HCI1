import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import mtq.qml3d 1.0
import QtQuick.Window 2.1
import "framework/GlobalLight.js" as GlobalLight
import "framework"
import "widgets"

Item3D {

    Component.onCompleted: {
        parent.sceneEnabled.connect(setupLight);
    }

    function setupLight(){
        for (var i=0; i < 4; i++){
            var l = GlobalLight.GlobalLightDefinition.lightEntries[i];
            l.enabled = false;
        }

        var l0 = l = GlobalLight.GlobalLightDefinition.lightEntries[0];
        l.position = Qt.vector3d(-2, 0, 3)
        l.center = Qt.vector3d(0,0,0);
        l.type = 1;
        l.color = Qt.vector3d(4.8,4.8,4.8)
        l.createsShadows = true;
        l.enabled = true;
    }

    // create midi interface only once
    MidiInterface {
        id: midiInterface
    }

    /** create a test midi button set for each player **/

    Player {
        id: player1
        player_id: 1
        midiInterface: midiInterface
        position: Qt.vector3d(-2,1,0)
    }

    Player {
        id: player2
        player_id: 2
        midiInterface: midiInterface
        position: Qt.vector3d(2,1,0)
    }

    Player {
        id: player3
        player_id: 3
        midiInterface: midiInterface
        position: Qt.vector3d(-2,-1.5,0)
    }

    Player {
        id: player4
        player_id: 4
        midiInterface: midiInterface
        position: Qt.vector3d(2,-1.5,0)
    }

}

