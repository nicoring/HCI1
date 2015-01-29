import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import mtq.qml3d 1.0
import QtQuick.Window 2.1
import "framework/GlobalLight.js" as GlobalLight
import "framework"
import "widgets"
import "widgets/settings.js" as Settings
import "widgets/musicControl.js" as MusicControl

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

        // Initialize harmony section
        MusicControl.useKey("C"); // Generate a cadence and load the pentatonic image -> TODO: Key sent by the MIDI interface
        MusicControl.useBeat(120 / 4); // 120 bpm -> TODO: Sent by MIDI interface [:4 for more speed while debugging]
        // useBeat also starts the Timer -> TODO: Wait for first instrument selection

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
        l.color = Qt.vector3d(2,2,2)
        l.createsShadows = true;
        l.enabled = true;
    }

    /** load background **/

    HighResQuad {
        id: underground
        scale:6
        position: Qt.vector3d(0,0,-0.5)

        transform:[
            Scale3D {
                scale: Qt.vector3d(2,1.3,1)
            }
        ]

        effect: LightShader {
            texture: "floorPanelsquad.jpg"
        }
    }

    /** controller widget for "beat-button" **/

    CircleController {
        id: circleController
        objectName: "circle"

        onDoRotateToPlayer: {
            // playerNum is defined in circlecontroller.h should work:
            // http://qt-project.org/forums/viewthread/3502
            // playerNum is emitted by doRotateToPlayer
            circle.rotateToPlayer(playerNum);
        }
    }

    /** midi interface which connects ableton to the virtual instrument **/

    MidiInterface {
        id: midiInterface

        function showBeat() {
            circle.beat();
        }
    }

    /** Global timer which controlls all chord displays **/

    Timer {
        id: slidingTimer
        interval: 2000
        running: false
        repeat: true
        onTriggered: {
            MusicControl.doOneSlidingStep();
        }
    }

    /** stage environment **/

    // group stage elements
    // exported from cinema4d
    // 3ds meshes have their own positions and scaling
    Item3D {
        id: floorElems3D
        scale: 2.3
        position: Qt.vector3d(0,0,-0.1)

        Ring3D {
            id: ring
        }

        Circle3D {
            id: circle
        }

        Stage3D {
            id: topleftStage
            mesh: Mesh { source: "qrc:/models/meshs/bottomright.3ds" }

            player_id: 1
            midiInterface: midiInterface

            Component.onCompleted: {

                labelPosition = Qt.vector3d(0.9,1.25,0.2);
                labelRotation = 135;

                cupboardPosition = Qt.vector3d(0.55,1.8,0.1);
                cupboardRotation = 0;

                midiPosition = Qt.vector3d(0.32,0.87,0.2);

                ownInstrument.chordsPosition = Qt.vector3d(1.30,1.55,0.2);
                ownInstrument.chordsRotation = 135;

                ownInstrument.pentatonicsPosition = Qt.vector3d(1.35,1.65,0.2);
                ownInstrument.pentatonicsRotation = 135;

                ownInstrument.switchPosition = Qt.vector3d(0.4,2.8,0.2);
                ownInstrument.switchRotation = 90;

            }

        }

        Stage3D {
            id: toprightStage
            mesh: Mesh { source: "qrc:/models/meshs/bottomleft.3ds" }

            player_id: 2
            midiInterface: midiInterface

            Component.onCompleted: {

                labelPosition = Qt.vector3d(0.65,-1.4,0.2);
                labelRotation = 45;

                cupboardPosition = Qt.vector3d(0.55,-1.8,0.1);
                cupboardRotation = 180;

                midiPosition = Qt.vector3d(0.32,-1.37,0.2);

                ownInstrument.chordsPosition = Qt.vector3d(1.30,-1.55,0.2);
                ownInstrument.chordsRotation = 45;

                ownInstrument.pentatonicsPosition = Qt.vector3d(1.35,-1.65,0.2);
                ownInstrument.pentatonicsRotation = 45;

                ownInstrument.switchPosition = Qt.vector3d(0.4,-2.85,0.2);
                ownInstrument.switchRotation = 90;

            }
        }

        Stage3D {
            id: bottomrightStage
            mesh: Mesh { source: "qrc:/models/meshs/topleft.3ds" }

            player_id: 3
            midiInterface: midiInterface

            Component.onCompleted: {

                labelPosition = Qt.vector3d(-1,-1.2,0.2);
                labelRotation = -45;

                cupboardPosition = Qt.vector3d(-0.60,-1.8,0.1);
                cupboardRotation = 180;

                midiPosition = Qt.vector3d(-0.85,-1.37,0.2);

                ownInstrument.chordsPosition = Qt.vector3d(-1.3,-1.55,0.2);
                ownInstrument.chordsRotation = -45;

                ownInstrument.pentatonicsPosition = Qt.vector3d(-1.4,-1.60,0.2);
                ownInstrument.pentatonicsRotation = -45;

                ownInstrument.switchPosition = Qt.vector3d(-0.5,-2.85,0.2);
                ownInstrument.switchRotation = 270;

            }
        }

        Stage3D {
            id: bottomleftStage
            mesh: Mesh { source: "qrc:/models/meshs/topright.3ds" }

            player_id: 3
            midiInterface: midiInterface

            Component.onCompleted: {

                labelPosition = Qt.vector3d(-0.7,1.35,0.2);
                labelRotation = -135;

                cupboardPosition = Qt.vector3d(-0.60,1.8,0.1);
                cupboardRotation = 0;

                midiPosition = Qt.vector3d(-0.85,0.87,0.2);

                ownInstrument.chordsPosition = Qt.vector3d(-1.3,1.55,0.2);
                ownInstrument.chordsRotation = -135;

                ownInstrument.pentatonicsPosition = Qt.vector3d(-1.4,1.60,0.2);
                ownInstrument.pentatonicsRotation = -135;

                ownInstrument.switchPosition = Qt.vector3d(-0.5,2.85,0.2);
                ownInstrument.switchRotation = 270;

            }
        }

    }

}
