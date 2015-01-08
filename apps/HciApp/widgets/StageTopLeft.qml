import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import mtq.qml3d 1.0
import QtQuick.Window 2.1
import "../framework"

Stage3D {
    mesh: Mesh { source: "qrc:/models/meshs/topleft.3ds" }
    effect: LightShader {
        //glow: Qt.vector3d(232,192,32)
    }


}
