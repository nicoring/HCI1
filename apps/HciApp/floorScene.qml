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


    /** each player needs a controlled menu flow **/

    property var settings1
    property var settings2
    property var settings3
    property var settings4

    Component.onCompleted: {
        parent.sceneEnabled.connect(setupLight);

        // init settings
        settings1 = Settings.createSettings(topLeftOverlay, label_player1, resume_player1, instrument_player1, player1, showChordsBtn_player1, chorddis_player1, showPentatonicBtn_player1, pentscreen_player1);
        settings2 = Settings.createSettings(topRightOverlay, label_player2, resume_player2, instrument_player2, player2, showChordsBtn_player2, chorddis_player2, showPentatonicBtn_player2, pentscreen_player2);
        settings3 = Settings.createSettings(bottomLeftOverlay, label_player3, resume_player3, instrument_player3, player3, showChordsBtn_player3, chorddis_player3, showPentatonicBtn_player3, pentscreen_player3);
        settings4 = Settings.createSettings(bottomRightOverlay, label_player4, resume_player4, instrument_player4, player4, showChordsBtn_player4, chorddis_player4, showPentatonicBtn_player4, pentscreen_player4);

        // Initialize harmony section
        MusicControl.useKey("C"); // Generate a cardence and load the pentatonic image -> TODO: Key sent by the MIDI interface
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


    /** create start labels for each player **/

    StartLabel {
        id: label_player1
        position: Qt.vector3d(-3,1.8,0.2)
        transform: Rotation3D {
            angle: 225
            axis: Qt.vector3d(0,0,1)
        }
    }

    StartLabel {
        id: label_player2
        position: Qt.vector3d(3,1.6,0.2)
        transform: Rotation3D {
            angle: 135
            axis: Qt.vector3d(0,0,1)
        }
    }

    StartLabel {
        id: label_player3
        position: Qt.vector3d(-3,-1.8,0.2)
        transform: Rotation3D {
            angle: 315
            axis: Qt.vector3d(0,0,1)
        }
    }

    StartLabel {
        id: label_player4
        position: Qt.vector3d(2.8,-2,0.2)
        transform: Rotation3D {
            angle: 45
            axis: Qt.vector3d(0,0,1)
        }
    }

    /** create resume/ restart buttons for each player **/

    // TODO: build actual elements
    Item3D {
        id: resume_player1
    }

    Item3D {
        id: resume_player2
    }

    Item3D {
        id: resume_player3
    }

    Item3D {
        id: resume_player4
    }

    /** create instrument menu buttons for each player **/

    InstrumentButton {
        id: instrument_player1
        position: Qt.vector3d(-2.2,1.4,0.5)
        scale: 0.8
        enabled: false

        transform: Rotation3D {
            angle: -120
            axis: Qt.vector3d(0,0,1)
        }
    }

    InstrumentButton {
        id: instrument_player2
        position: Qt.vector3d(2.2,1.4,0.5)
        scale: 0.8
        enabled: false

        transform: Rotation3D {
            angle: 120
            axis: Qt.vector3d(0,0,1)
        }
    }

    InstrumentButton {
        id: instrument_player3
        position: Qt.vector3d(-2.2,-1.4,0.5)
        scale: 0.8
        enabled: false

        transform: Rotation3D {
            angle: -40
            axis: Qt.vector3d(0,0,1)
        }
    }

    InstrumentButton {
        id: instrument_player4
        position: Qt.vector3d(2.2,-1.4,0.5)
        scale: 0.8
        enabled: false

        transform: Rotation3D {
            angle: 40
            axis: Qt.vector3d(0,0,1)
        }
    }

    /** buttons to switch to the pentatonic screen **/

    ChordButton {
        id: showChordsBtn_player1

        position: Qt.vector3d(-3,0.45,0.5)
        enabled: false

        transform: [
            Rotation3D {
                angle: -180
                axis: Qt.vector3d(0,0,1)
            }
        ]
    }

    ChordButton {
        id: showChordsBtn_player2

        position: Qt.vector3d(3,0.45,0.5)
        enabled: false

        transform: [
            Rotation3D {
                angle: -180
                axis: Qt.vector3d(0,0,1)
            }
        ]
    }

    ChordButton {
        id: showChordsBtn_player3

        position: Qt.vector3d(-3,-0.55,0.5)
        enabled: true
    }

    ChordButton {
        id: showChordsBtn_player4

        position: Qt.vector3d(3,-0.55,0.5)
        enabled: false
    }

    /** create chords display for each player **/

    // Global timer which controlls all chord displays
    Timer {
        id: slidingTimer
        interval: 2000
        running: false
        repeat: true
        onTriggered: {
            MusicControl.doOneSlidingStep();
        }
    }

    ChordDisplay {
        id: chorddis_player1
        position: Qt.vector3d(-1.55,1.3,0.5)
        scale: 0.85
        enabled: false

        transform: Rotation3D {
            angle: -120
            axis: Qt.vector3d(0,0,1)
        }
    }

    ChordDisplay {
        id: chorddis_player2
        position: Qt.vector3d(1.55,1.3,0.5)
        scale: 0.85
        enabled: false

        transform: Rotation3D {
            angle: 120
            axis: Qt.vector3d(0,0,1)
        }
    }

    ChordDisplay {
        id: chorddis_player3
        position: Qt.vector3d(-1.5,-1.4,0.5)
        scale: 0.95
        enabled: false

        transform: Rotation3D {
            angle: -60
            axis: Qt.vector3d(0,0,1)
        }
    }

    ChordDisplay {
        id: chorddis_player4
        position: Qt.vector3d(1.5,-1.4,0.5)
        scale: 0.95
        enabled: false

        transform: Rotation3D {
            angle: 60
            axis: Qt.vector3d(0,0,1)
        }
    }

    /** buttons to switch to the pentatonic screen **/

    PentatonicButton {
        id: showPentatonicBtn_player1

        position: Qt.vector3d(-3,0.45,0.5)
        enabled: false

        transform: [
            Rotation3D {
                angle: -180
                axis: Qt.vector3d(0,0,1)
            }
        ]
    }

    PentatonicButton {
        id: showPentatonicBtn_player2

        position: Qt.vector3d(3,0.45,0.5)
        enabled: false

        transform: [
            Rotation3D {
                angle: -180
                axis: Qt.vector3d(0,0,1)
            }
        ]
    }

    PentatonicButton {
        id: showPentatonicBtn_player3

        position: Qt.vector3d(-3,-0.55,0.5)
        enabled: false
    }

    PentatonicButton {
        id: showPentatonicBtn_player4

        position: Qt.vector3d(3,-0.55,0.5)
        enabled: false
    }

    /** create pentatonic screen **/
    PentatonicScreen {
        id: pentscreen_player1
        position: Qt.vector3d(-1.55,1.3,0.2)
        scale: 0.75
        enabled: false

        transform: Rotation3D {
            angle: -120
            axis: Qt.vector3d(0,0,1)
        }
    }

    PentatonicScreen {
        id: pentscreen_player2
        position: Qt.vector3d(1.55,1.3,0.2)
        scale: 0.75
        enabled: false

        transform: Rotation3D {
            angle: 120
            axis: Qt.vector3d(0,0,1)
        }
    }

    PentatonicScreen {
        id: pentscreen_player3
        position: Qt.vector3d(-1.5,-1.4,0.2)
        scale: 0.75
        enabled: false

        transform: Rotation3D {
            angle: -60
            axis: Qt.vector3d(0,0,1)
        }
    }

    PentatonicScreen {
        id: pentscreen_player4
        position: Qt.vector3d(1.5,-1.4,0.2)
        scale: 0.75
        enabled: false

        transform: Rotation3D {
            angle: 60
            axis: Qt.vector3d(0,0,1)
        }
    }

    /** create midi button sets for each player **/
    MidiButtonSet {
        id: player1
        player_id: 1
        midiInterface: midiInterface
        position: Qt.vector3d(-3.5,0.8,0.2)
        enabled: false
    }

    MidiButtonSet {
        id: player2
        player_id: 2
        midiInterface: midiInterface
        position: Qt.vector3d(2.2,0.8,0.2)
        enabled: false
    }

    MidiButtonSet {
        id: player3
        player_id: 3
        midiInterface: midiInterface
        position: Qt.vector3d(-3.5,-2,0.2)
        enabled: false
    }

    MidiButtonSet {
        id: player4
        player_id: 4
        midiInterface: midiInterface
        position: Qt.vector3d(2.2,-2,0.2)
        enabled: false
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
            id: bottomrightStage
            mesh: Mesh { source: "qrc:/models/meshs/topleft.3ds" }
        }

        Stage3D {
            id: bottomleftStage
            mesh: Mesh { source: "qrc:/models/meshs/topright.3ds" }
        }

        Stage3D {
            id: toprightStage
            mesh: Mesh { source: "qrc:/models/meshs/bottomleft.3ds" }
        }

        Stage3D {
            id: topleftStage
            mesh: Mesh { source: "qrc:/models/meshs/bottomright.3ds" }
        }
    }

    Item3D {
        CupBoard {
            id: cupBoardTopLeft
            position: Qt.vector3d(-4,1.3,0.5)
        }
        CupBoard {
            id: cupBoardTopRight
            position: Qt.vector3d(4,1.3,0.5)
        }
        CupBoard {
            id: cupBoardBottomLeft
            position: Qt.vector3d(-4,-1.3,0.5)
        }
        CupBoard {
            id: cupBoardBottomRight
            position: Qt.vector3d(4,-1.3,0.5)
        }
    }


    StageOverlay {
        id: topLeftOverlay
        position: Qt.vector3d(-2.4, 1.4, 0.1)
    }

    StageOverlay {
        id: topRightOverlay
        position: Qt.vector3d(2.4, 1.4, 0.1)
    }

    StageOverlay {
        id: bottomLeftOverlay
        position: Qt.vector3d(-2.4, -1.5, 0.1)
    }

    StageOverlay {
        id: bottomRightOverlay
        position: Qt.vector3d(2.4, -1.5, 0.1)
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



    // create midi interface only once
    MidiInterface {
        id: midiInterface

        function showBeat() {
            circle.beat();
        }
    }


}
