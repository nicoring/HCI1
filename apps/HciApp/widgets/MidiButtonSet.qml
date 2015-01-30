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
    property int instrument_id
    property MidiInterface midiInterface

    /*********************
     * --> instrument_id depends on the chosen instrument. So if another
     *     is chosen, the instrument_id has to be updated on each button.
     */

    /** keyboard buttons **/

    Item3D {
        id: midibuttons
        enabled: true

        MidiButton {
            id: btn1

            button_id: 1
            player_id: buttonset.player_id
            instrument_id: buttonset.instrument_id
            midiInterface: buttonset.midiInterface

            position: Qt.vector3d(0,0,0)
            transform {
                Rotation3D {
                    angle: 0
                    axis: Qt.vector3d(0,0,1)
                }
            }
        }

        MidiButton {
            id: btn2

            button_id: 2
            player_id: buttonset.player_id
            instrument_id: buttonset.instrument_id
            midiInterface: buttonset.midiInterface

            transform {
                Rotation3D {
                    angle: 90
                    axis: Qt.vector3d(0,0,1)
                }
            }

            position: Qt.vector3d(1.1, 0, 0)
        }

        MidiButton {
            id: btn3

            button_id: 3
            player_id: buttonset.player_id
            instrument_id: buttonset.instrument_id
            midiInterface: buttonset.midiInterface

            transform {
                Rotation3D {
                    angle: 270
                    axis: Qt.vector3d(0,0,1)
                }
            }

            position: Qt.vector3d(0, 1.1, 0)
        }

        MidiButton {
            id: btn4

            button_id: 4
            player_id: buttonset.player_id
            instrument_id: buttonset.instrument_id
            midiInterface: buttonset.midiInterface

            transform {
                Rotation3D {
                    angle: 180
                    axis: Qt.vector3d(0,0,1)
                }
            }

            position: Qt.vector3d(1.1, 1.1, 0)
        }

        function mtqContactDown(id, position) {
            if (parent.mtqContactDown) {
                parent.mtqContactDown(id, position);
            }
        }

        function mtqContactUp(id, position) {
            if (parent.mtqContactDown) {
                parent.mtqContactDown(id, position);
            }
        }
    }

    function mtqContactDown(id, position) {
        if (parent.mtqContactDown) {
            parent.mtqContactDown(id, position);
        }
    }

    function mtqContactUp(id, position) {
        if (parent.mtqContactDown) {
            parent.mtqContactDown(id, position);
        }
    }
}
