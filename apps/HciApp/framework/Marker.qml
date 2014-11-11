import QtQuick 2.0
import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0

Item3D{
    id:marker
    mesh: Mesh { source: "qrc:/models/framework/marker.3ds" }

    effect: LightShader{
    }

    transform: [
        Rotation3D{
            axis: Qt.vector3d(1,0,0)
            angle: 180
        },
        Scale3D{
            scale: Qt.vector3d(0.001, 0.001, 0.001)
        }

    ]


}
