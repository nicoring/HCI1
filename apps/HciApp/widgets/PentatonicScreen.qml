import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import mtq.qml3d 1.0
import QtQuick.Window 2.1
import "../framework"
import "../widgets"

HighResQuad {
    id: pentScreen
    effect : LightShader {
        texture: "../pentatonics/Am-1.png"
    }

    transform: [
        Scale3D {
            scale: Qt.vector3d(2.8,1.4,1)
        }
    ]

    /** Load a pentatonic image to the current key*/
    function loadImage(nextPent) {
        pentScreen.effect.texture = "../pentatonics/" + nextPent + "-1.png"; // '1' for Pattern 1
    }
}
