import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import mtq.qml3d 1.0
import QtQuick.Window 2.1
import "../framework"

Item3D {
    id: startLabel
    enabled: true

    TapLabel {
        text: "Come here"
        fontSize: 60
        sceneWidth: 3
        sceneHeight: 3
        fontColor: "black"
        position: Qt.vector3d(0.7,-0.5,0)
    }

    TapLabel {
        text: "\nto start!"
        fontSize: 60
        sceneWidth: 3
        sceneHeight: 3
        fontColor: "black"
        position: Qt.vector3d(1,-0.5,0)
    }

    property var onContactDown
    function mtqContactDown(id, position) {
        if (onContactDown) {
            onContactDown();
        }
    }
}
