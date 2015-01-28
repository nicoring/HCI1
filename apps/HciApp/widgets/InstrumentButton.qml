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

    property alias floorInstrument: btn1
    FlatButton {
        id: btn1

        position: Qt.vector3d(-0.6, 0, 0)

        TapLabel {
            text: "Floor"
            fontSize: 50
            fontColor: "black"
            position: Qt.vector3d(0.1, -0.2, 0)
        }

        TapLabel {
            text: "Instrument"
            fontSize: 50
            fontColor: "black"
            position: Qt.vector3d(0.2, -0.5, 0)
            sceneWidth: 2
        }

        property var onTap
        onReleased: {
            if (onTap) {
                onTap();
            }
        }
    }

    property alias ownInstrument: btn2
    FlatButton {
        id: btn2

        position: Qt.vector3d(0.6, 0, 0)

        TapLabel {
            text: "Own"
            fontSize: 50
            fontColor: "black"
            position: Qt.vector3d(0.1, -0.2, 0)
        }

        TapLabel {
            text: "Instrument"
            fontSize: 50
            fontColor: "black"
            position: Qt.vector3d(0.2, -0.5, 0)
            sceneWidth: 2
        }

        property var onTap
        onReleased: {
            if (onTap) {
                onTap();
            }
        }
    }
}
