import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import mtq.qml3d 1.0

Item3D{
    signal switchLeft;
    signal switchRight;

    function emitSwitchLeft(){
        switchLeft();
    }

    function emitSwitchRight(){
        switchRight();
    }

    Cube{
        transform:[
            Scale3D {scale: Qt.vector3d(1,1,0.3)}
        ]
        effect: LightShader {
            texture: "componentBase.png"
        }
    }

    Item3D{
        position: Qt.vector3d(-0.9,0,0)
        scale: 0.65
        transform:[
            Rotation3D { angle:180; axis: Qt.vector3d(0, 0, 1)}
        ]

        mesh: Mesh { source: "qrc:/models/arrow.3ds" }
        effect: LightShader {}

        function mtqTap(id, position){
            parent.emitSwitchLeft();
        }
    }

    Item3D{
        position: Qt.vector3d(0.9,0,0)
        scale: 0.65
        mesh: Mesh { source: "qrc:/models/arrow.3ds" }
        effect: LightShader {}
        function mtqTap(id, position){
            parent.emitSwitchRight();
        }
    }
}
