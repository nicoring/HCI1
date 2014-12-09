import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import mtq.qml3d 1.0
import "../framework"

Item3D {

    FlatButton {
        position: Qt.vector3d(-1,2,0)
    }

    Button {
        position: Qt.vector3d(1,2,0)
    }

}
