import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import mtq.qml3d 1.0
import QtQuick.Window 2.1
import "../framework"

Item3D {
    id: instrumentButtons
    enabled: true

    position: Qt.vector3d(0.5, 0.5, 0)
    transform: Rotation3D {
        angle: 0
        axis: Qt.vector3d(0,0,1)
    }

    FlatButton {

        position: Qt.vector3d(-1, 0, 0)

        Label {
            text: "Floor"
            fontSize: 50
            fontColor: "black"
            position: Qt.vector3d(0.1, -0.2, 0)
        }

        Label {
            text: "Instrument"
            fontSize: 50
            fontColor: "black"
            position: Qt.vector3d(0.2, -0.5, 0)
            sceneWidth: 2
        }
    }

    FlatButton {

        position: Qt.vector3d(1, 0, 0)

        Label {
            text: "Own"
            fontSize: 50
            fontColor: "black"
            position: Qt.vector3d(0.1, -0.2, 0)
        }

        Label {
            text: "Instrument"
            fontSize: 50
            fontColor: "black"
            position: Qt.vector3d(0.2, -0.5, 0)
            sceneWidth: 2
        }

    }
}
