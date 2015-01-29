import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import mtq.qml3d 1.0
import QtQuick.Window 2.1
import "../framework/GlobalLight.js" as GlobalLight
import "../framework"
import "."


Item3D {

    property string normalTexture: "qrc:/models/images/purple.png"
    property string highlightTexture: "qrc:/models/images/purple-highlight.png"

    mesh: Mesh { source: "qrc:/models/meshs/instrumentButton.3ds" }
    effect: LightShader {
        id: lightShader
        texture: normalTexture
    }
    scale: 1

    transform: [
        Rotation3D {
            angle: 90
            axis: Qt.vector3d(1,0,0)
        }
    ]

    function highlight() {
        lightShader.texture = highlightTexture
    }

    function unhighlight() {
        lightShader.texture = normalTexture
    }
}
