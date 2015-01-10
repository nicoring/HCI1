import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import mtq.qml3d 1.0
import QtQuick.Window 2.1
import "framework/GlobalLight.js" as GlobalLight
import "framework"
import "widgets"

Item3D {

    /**
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


    CubeQuad {
        id: underground
        position: Qt.vector3d(0,0,-1)
        transform: [
            Scale3D {
                scale: Qt.vector3d(100,100,0)
            }
        ]
    }

    // create midi interface only once
    MidiInterface {
        id: midiInterface
    }

    // group stage elements
    Item3D {
        id: floorElems
        scale: 2.3

        Ring3D {
            id: ring
        }

        Circle3D {
            id: circle
        }

        Stage3D {
            id: topleftStage
            midiInterface: midiInterface
            player_id: 1
            mesh: Mesh { source: "qrc:/models/meshs/topleft.3ds" }
        }

        Stage3D {
            id: toprightStage
            midiInterface: midiInterface
            player_id: 2
            mesh: Mesh { source: "qrc:/models/meshs/topright.3ds" }
        }

        Stage3D {
            id: bottomleftStage
            midiInterface: midiInterface
            player_id: 3
            mesh: Mesh { source: "qrc:/models/meshs/bottomleft.3ds" }
        }

        Stage3D {
            id: bottomrightStage
            midiInterface: midiInterface
            player_id: 4
            mesh: Mesh { source: "qrc:/models/meshs/bottomright.3ds" }
        }
    }

    CircleController {
        id: circleController

        onDoBeat: {
            circle.beat();
        }

        onDoRotateToPlayer: {
            // playerNum is defined in circlecontroller.h should work:
            // playerNum is emitted by doRotateToPlayer
            // http://qt-project.org/forums/viewthread/3502
            circle.rotateToPlayer(playerNum);
        }
    }

}

