import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import mtq.qml3d 1.0
import QtQuick.Window 2.1
import "../framework"

HighResQuad {
    id: chord
    property int rid // Property id isn't accessible for any reason (?)
    effect : LightShader {
        texture: "../guitar chords/G-Dur.jpg"
    }

    transform: [
        Scale3D {
            scale: Qt.vector3d(0.7,1,1)
        }

    ]
}
