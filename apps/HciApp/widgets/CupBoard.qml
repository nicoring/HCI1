import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import mtq.qml3d 1.0
import QtQuick.Window 2.1
import "../framework"

Item3D {
    scale: 0.9
    Item3D {
        id: cupboard
        mesh: Mesh { source: "qrc:/models/meshs/cupboard.3ds" }

        scale: 2.5
        transform: [
            Rotation3D {
                angle: 90
                axis: Qt.vector3d(0,1,0)
            },
            Rotation3D {
                angle: 90
                axis: Qt.vector3d(1,0,0)
            }
        ]
    }

    signal changedInstrument
    signal selectedVirtualInstrument (int instrumentIndex)
    signal selectedOwnInstrument

    HighResQuad {
        scale: 0.45
        position: Qt.vector3d(-1,0,0.301)
        effect : LightShader {
            texture: "qrc:/models/images/drum.png"
        }
        function mtqTap(id, position) {
            changedInstrument();
            selectedVirtualInstrument(1);

            if (parent.mtqTap) {
                parent.mtqTap(id, position);
            }
        }
    }

    HighResQuad {
        scale: 0.45
        position: Qt.vector3d(-0.5,0,0.301)
        effect : LightShader {
            texture: "qrc:/models/images/bass.png"
        }
        function mtqTap(id, position) {
            changedInstrument();
            selectedVirtualInstrument(2);

            if (parent.mtqTap) {
                parent.mtqTap(id, position);
            }
        }
    }

    HighResQuad {
        scale: 0.45
        position: Qt.vector3d(0,0,0.301)
        effect : LightShader {
            texture: "qrc:/models/images/samplesounds.png"
        }
        function mtqTap(id, position) {
            changedInstrument();
            selectedVirtualInstrument(3);

            if (parent.mtqTap) {
                parent.mtqTap(id, position);
            }
        }
    }

    HighResQuad {
        scale: 0.45
        position: Qt.vector3d(0.5,0,0.301)
        effect : LightShader {
            texture: "qrc:/models/images/pad.png"
        }
        function mtqTap(id, position) {
            changedInstrument();
            selectedVirtualInstrument(4);

            if (parent.mtqTap) {
                parent.mtqTap(id, position);
            }
        }
    }

    HighResQuad {
        scale: 0.45
        position: Qt.vector3d(1,0,0.301)
        effect : LightShader {
            texture: "qrc:/models/images/guitar.png"
        }
        function mtqTap(id, position) {
            changedInstrument();
            selectedOwnInstrument();

            if (parent.mtqTap) {
                parent.mtqTap(id, position);
            }
        }
    }
}
