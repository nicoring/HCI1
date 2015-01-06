import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import mtq.qml3d 1.0
import QtQuick.Window 2.1
import "../framework"
Item3D {
    id: testscene
    mesh: Mesh { source: "qrc:/models/floorscene-2.3ds" }
    effect: LightShader {
     //   texture: "../framework/componentBase.png"
    }
}
