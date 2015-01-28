import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import mtq.qml3d 1.0
import QtQuick.Window 2.1
import "../framework"
import "../widgets"

Item3D{
    id: displayswitch
    position: Qt.vector3d(0, 0, 0)

    Slider{
        position: Qt.vector3d(0, 0, 0.3)
        id: sliderbody
        scale: 0.2
        enabled: true
    }

    Label{
        text: "Pentatonic    Chords"
        sceneWidth: 2.0
        fontSize: 22
        fontColor: "black"
        position: Qt.vector3d(0.3, -0.22, 0.1)
    }
}
