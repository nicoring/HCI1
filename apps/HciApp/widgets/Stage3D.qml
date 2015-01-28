import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import mtq.qml3d 1.0
import QtQuick.Window 2.1
import "../framework"

Item3D {
    id: stage

    /*
    property int player_id
    property MidiInterface midiInterface
    property var onMtqContactDownOnce
    */

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

}
