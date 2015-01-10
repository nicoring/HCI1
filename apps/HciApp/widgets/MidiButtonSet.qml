import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import mtq.qml3d 1.0
import QtQuick.Window 2.1
import "../framework/GlobalLight.js" as GlobalLight
import "../framework"
import "."

Item3D {
    id: player

    property int player_id
    property MidiInterface midiInterface

    MidiButton {
        id: btn1

        button_id: 1
        player_id: player.player_id
        midiInterface: player.midiInterface

        position: Qt.vector3d(0,0,0)
    }

    MidiButton {
        id: btn2

        button_id: 2
        player_id: player.player_id
        midiInterface: player.midiInterface

        position: Qt.vector3d(1.1, 0, 0)
    }

    MidiButton {
        id: btn3

        button_id: 3
        player_id: player.player_id
        midiInterface: player.midiInterface

        position: Qt.vector3d(0, 1.1, 0)
    }

    MidiButton {
        id: btn4

        button_id: 4
        player_id: player.player_id
        midiInterface: player.midiInterface

        position: Qt.vector3d(1.1, 1.1, 0)
    }
}
