import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import mtq.qml3d 1.0
import QtQuick.Window 2.1
import "../framework"
Item3D {
    id: testscene
    mesh: Mesh { source: "qrc:/models/meshs/circle.3ds" }
    effect: LightShader {
     //texture: "../framework/componentBase.png"
    }

    scale: 0.022
    transform {

        Rotation3D {
            id: oneRoundRotation
            angle: 0
            axis: Qt.vector3d(0,0,1)
        }
    }

    NumberAnimation{
        id: oneRoundRotationAnimation
        target: oneRoundRotation
        properties: "angle"
        duration: 800
        to: 360
    }

    function rotateOneRound () {
        oneRoundRotationAnimation.start()
    }
}
