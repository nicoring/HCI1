import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import mtq.qml3d 1.0
import QtQuick.Window 2.1
import "../framework/GlobalLight.js" as GlobalLight
import "../framework"

Cube {
    id: flatCube
    position: Qt.vector3d(0,0,-1)
    transform: [
        Scale3D {
            scale: Qt.vector3d(2.7,2.7,0.1)
        }
    ]
    effect : LightShader {
        texture: "../framework/componentBase.png"
    }
}
