import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import mtq.qml3d 1.0
import QtQuick.Window 2.1
import "../framework"

HighResQuad {
    id: chord
    property int rid // Property id isn't accessible -> Workaround
    effect : LightShader {
        texture: "../guitar chords/G.png"
    }

    transform: [
        Scale3D {
            scale: Qt.vector3d(0.7,1,1)
        }

    ]
}
