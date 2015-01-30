import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import mtq.qml3d 1.0
import QtQuick.Window 2.1
import "../framework"

Item3D {
    id: middleRing
    mesh: Mesh { source: "qrc:/models/meshs/ring.3ds" }
    effect: LightShader {
     texture: "../framework/componentBase.png"
    }
    HighResQuad {
        position: Qt.vector3d(0,0,1)
        scale: 1.8
        transform: [
            Rotation3D {
                angle: 90
                axis: Qt.vector3d(0,0,1)
            }
        ]
        effect: LightShader {
            texture: "qrc:/models/images/warmUp.png"
        }
    }
}
