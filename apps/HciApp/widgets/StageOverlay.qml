import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import mtq.qml3d 1.0
import QtQuick.Window 2.1
import "../framework"

HighResQuad {
    id: stageOverlay

    property int player_id
    property MidiInterface midiInterface
    property var onMtqContactDownOnce
    property var onContactDown

    transform: [
        Scale3D {
            scale: Qt.vector3d(4.4,2.2,1)
        }
    ]
    /*
    effect: LightShader {
        texture: "transparent.png"
    }
    */
    effect: LightShader {
        texture: "qrc:/models/transparent.png"
    }

    function mtqContactDown(id, position) {
        if (onContactDown) {
            onContactDown();
        }
    }
}
