import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import mtq.qml3d 1.0
import QtQuick.Window 2.1
import "../framework"
import "../widgets"

FlatButton {
    position: Qt.vector3d(0,0,0)

    // scale to small button size
    transform: [
        Scale3D {
            scale: Qt.vector3d(1,0.5,1)
        }
    ]

    Label {
        text: "Pentatonic"
        fontSize: 50
        fontColor: "black"
        position: Qt.vector3d(0.2, -0.6, 0)
        sceneWidth: 2.0

        transform: [
            Scale3D {
                scale: Qt.vector3d(1,2,1)
            }
        ]

        property var onTap
        onReleased: {
            console.info('Hallo');
            if (onTap) {
                onTap();
            }
        }
    }

    property var onTap
    onReleased: {
        if (onTap) {
            onTap();
        }
    }
}
