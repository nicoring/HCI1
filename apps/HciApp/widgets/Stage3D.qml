import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import mtq.qml3d 1.0
import QtQuick.Window 2.1
import "../framework"

Item3D {
    id: stage

    property int player_id
    property MidiInterface midiInterface

    effect: LightShader {
        texture: "../framework/componentBase.png"
    }

    Translation3D {
        translate: Qt.vector3d(0,0,-1)
    }

    transform {
        Rotation3D {
            angle: 90
            axis: Qt.vector3d(0,0,1)
        }
    }

    property var onContactDown
    function mtqContactDown(id, position) {
        if (onContactDown) {
            onContactDown();
        }
    }

    Component.onCompleted: {
        // hide start label as soon as an instrument was selected
        cupboard.changedInstrument.connect(hideStartLabel);

        // show midi buttons set and configure its interface
        cupboard.selectedVirtualInstrument.connect(selectVirtualInstrument);

        // show own instrument and chord hints
        cupboard.selectedOwnInstrument.connect(selectOwnInstrument);
    }

    function hideStartLabel() {
       label.enabled = false;
    }

    property alias labelPosition: label.position
    property alias labelRotation: label_rotation.angle
    StartLabel {
        id: label
        scale: 1 / floorElems3D.scale
        transform: Rotation3D {
            id: label_rotation
            axis: Qt.vector3d(0,0,1)
        }
    }

    property alias cupboardPosition: cupboard.position
    property alias cupboardRotation: cupboard_rotation.angle
    CupBoard {
        id: cupboard
        scale: 1 / floorElems3D.scale

        transform: Rotation3D {
            id: cupboard_rotation
            axis: Qt.vector3d(0,0,1)
        }
    }

    function selectVirtualInstrument(index) {
        console.log('select vi ', index);

        hideOwnInstrument();
        midi.enabled = true;
        midi.offset = index;
    }

    function hideVirtualInstrument() {
        midi.enabled = false;
    }

    property alias midiPosition: midi.position
    MidiButtonSet {
        id: midi
        scale: 1 / floorElems3D.scale
        player_id: player_id
        offset: 0
        midiInterface: midiInterface
        enabled: false
    }

    function hideOwnInstrument() {
        ownInstrumentSet.enabled = false;
    }

    function selectOwnInstrument() {
        console.log('select oi');

        hideVirtualInstrument();
        ownInstrumentSet.enabled = true;
    }

    property alias ownInstrument: ownInstrumentSet
    property alias chords: chords
    property alias pentatonics: pentatonics
    Item3D {
        scale: 1 / floorElems3D.scale
        id: ownInstrumentSet
        enabled: false

        Component.onCompleted: {
            // switch between chords and pentatonic
            switchBtn.slider.disabled.connect(showPentatonics);
            switchBtn.slider.enabled.connect(showChords);
        }

        function showPentatonics() {
            pentatonics.enabled = true;
            chords.enabled = false;
        }

        property alias pentatonicsPosition: pentatonics.position
        property alias pentatonicsRotation: pentatonics_rotation.angle
        PentatonicScreen {
            id: pentatonics
            scale: 0.75
            enabled: false // hide by default

            transform: Rotation3D {
                id: pentatonics_rotation
                axis: Qt.vector3d(0,0,1)
            }
        }

        function showChords() {
            pentatonics.enabled = false;
            chords.enabled = true;
        }

        property alias chordsPosition: chords.position
        property alias chordsRotation: chords_rotation.angle
        ChordDisplay {
            id: chords
            scale: 0.85
            enabled: true // show by default

            transform: Rotation3D {
                id: chords_rotation
                axis: Qt.vector3d(0,0,1)
            }
        }

        property alias switchPosition: switchBtn.position
        property alias switchRotation: switch_rotation.angle
        MusicDisplaySwitch {
            id: switchBtn
            scale: 0.75

            transform: [
                Rotation3D {
                    id: switch_rotation
                    axis: Qt.vector3d(0,0,1)
                }
            ]
        }

    }

}
