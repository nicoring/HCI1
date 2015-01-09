import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import mtq.qml3d 1.0
import QtQuick.Window 2.1
import "../framework"

Item3D {
    id: middleCircle
    mesh: Mesh { source: "qrc:/models/meshs/circle3.3ds" }
    effect: LightShader {
     //texture: "../framework/componentBase.png"
    }

    transform {
        Rotation3D {
            angle: 90
            axis: Qt.vector3d(1,0,0)
        }

        Rotation3D {
            id: zAxisRotation
            angle: 0
            axis: Qt.vector3d(0,0,1)
        }

        Scale3D {
            id: radiusScale
            scale: Qt.vector3d(1.1,1.1,1)
        }
    }

    SequentialAnimation {
        id: beatAnimation
        Vector3dAnimation {
            id: circleBigAnimation
            target: radiusScale
            properties: "scale"
            duration: 50
            to: Qt.vector3d(1.5,1.5,1)
        }
        Vector3dAnimation {
            id: circleLittleAnimation
            target: radiusScale
            properties: "scale"
            duration: 100
            to: Qt.vector3d(1.1,1.1,1)
        }
    }

    SequentialAnimation {
        id: arrowRotationAnimation
        NumberAnimation {
            id: zAxisFullRotationAnimation
            target: zAxisRotation
            properties: "angle"
            duration: 1400
            from: 0
            to: 360
            loops: 3
        }

        NumberAnimation {
            id: zAxisAngleRotationAnimation
            target: zAxisRotation
            properties: "angle"
            duration: 500
            from: 0
            to: 0
        }
    }

    function mtqTap(position, id) {
        rotateToPlayer(3)
        //beat()
    }

    function beat() {
        beatAnimation.start()
    }


    /**
      *******************************
      *             *               *
      *  player 1   *    player 2   *
      *             *               *
      *******************************
      *             *               *
      *  player 3   *    player 4   *
      *             *               *
      *******************************
      */
    function rotateToPlayer(player) {
        var angle, duration
        var fullDurationSlow = 2000
        switch (player) {
            case 1:
                angle = 135
                break;
            case 2:
                angle = 45
                break;
            case 3:
                angle = 225
                break;
            case 4:
                angle = 315
                break;
        }

        // adapt rotation speed to the angle of the rotation
        duration = fullDurationSlow * (angle / 360)

        zAxisAngleRotationAnimation.to = angle
        zAxisAngleRotationAnimation.duration = duration
        arrowRotationAnimation.start()

    }
}
