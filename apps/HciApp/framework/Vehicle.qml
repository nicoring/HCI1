import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import mtq.qml3d 1.0

Item3D{
    signal switchLeft;
    signal switchRight;

    property bool rightArrowEnabled: true;
    property bool leftArrowEnabled: true;

    onLeftArrowEnabledChanged: {
        if (!leftArrowEnabled){
            leftArrowDisableRotation.start();
            leftArrowDisableTranslation.start();
        } else {
            leftArrowEnableRotation.start();
            leftArrowEnableTranslation.start();
        }
    }

    onRightArrowEnabledChanged: {
        if (!rightArrowEnabled){
            rightArrowDisableRotation.start();
            rightArrowDisableTranslation.start();
        } else {
            rightArrowEnableRotation.start();
            rightArrowEnableTranslation.start();
        }
    }

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
        id: leftArrow
        position: Qt.vector3d(-0.9,0,0)
        scale: 0.65
        transform:[
            Rotation3D { angle:180; axis: Qt.vector3d(0, 0, 1)},
            Rotation3D { id: leftRotation; angle:0; axis: Qt.vector3d(0,1,0)}
        ]

        mesh: Mesh { source: "qrc:/models/framework/arrow.3ds" }
        effect: LightShader {}

        function mtqTap(id, position){
            parent.emitSwitchLeft();
        }
    }

    Item3D{
        id: rightArrow
        position: Qt.vector3d(0.9,0,0)
        scale: 0.65
        transform: [
            Rotation3D { id: rightRotation; angle:0; axis: Qt.vector3d(0,-1,0)}
        ]

        mesh: Mesh { source: "qrc:/models/framework/arrow.3ds" }
        effect: LightShader {}

        function mtqTap(id, position){
            parent.emitSwitchRight();
        }
    }

    NumberAnimation{
        id: leftArrowDisableRotation
        target: leftRotation
        properties: "angle"
        duration: 800
        to: -90
    }

    NumberAnimation{
        id: leftArrowEnableRotation
        target: leftRotation
        properties: "angle"
        duration: 800
        to: 0
    }

    NumberAnimation{
        id: rightArrowDisableRotation
        target: rightRotation
        properties: "angle"
        duration: 800
        to: -90
    }

    NumberAnimation{
        id: rightArrowEnableRotation
        target: rightRotation
        properties: "angle"
        duration: 800
        to: 0
    }

    Vector3dAnimation{
        id: leftArrowDisableTranslation
        target: leftArrow
        properties: "position"
        duration: 800
        to: Qt.vector3d(-0.6, 0.0, -0.2)
    }

    Vector3dAnimation{
        id: leftArrowEnableTranslation
        target: leftArrow
        properties: "position"
        duration: 800
        to: Qt.vector3d(-0.9, 0.0, 0.0)
    }

    Vector3dAnimation{
        id: rightArrowDisableTranslation
        target: rightArrow
        properties: "position"
        duration: 800
        to: Qt.vector3d(0.6, 0.0, -0.2)
    }

    Vector3dAnimation{
        id: rightArrowEnableTranslation
        target: rightArrow
        properties: "position"
        duration: 800
        to: Qt.vector3d(0.9, 0.0, 0.0)
    }
}
