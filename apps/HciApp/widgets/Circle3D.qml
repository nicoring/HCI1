import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import mtq.qml3d 1.0
import QtQuick.Window 2.1
import "../framework"

Item3D {
    id: circleComponent

    signal spinningStopped()
    signal rotationStopped()

    property int fullDurationSlow: 2000
    property int warmUpSoloTime: 1000
    property int soloTime: 1000

    Component.onCompleted: {
    }

    Item3D {
        id: middleCircle
        mesh: Mesh { source: "qrc:/models/meshs/circle3.3ds" }
        effect: LightShader {
         texture: "../framework/componentBase.png"
        }

        transform {
            Rotation3D {
                angle: 90
                axis: Qt.vector3d(1,0,0)
            }

            Rotation3D {
                id: zAxisRotationCircle
                angle: 0
                axis: Qt.vector3d(0,0,1)
            }

            Scale3D {
                id: radiusScale
                scale: Qt.vector3d(1.1,1.1,1)
            }
        }

        function mtqTap(position, id) {
            parent.mtqTap(position, id)
        }
    }

    HighResQuad {
        id: arrow
        scale: 0.4
        enabled: false
        position: Qt.vector3d(0,0,0.2)
        effect : LightShader {
            texture: "qrc:/models/images/arrow.png"
        }
        transform {
            Rotation3D {
                id: zAxisRotationArrow
                angle: 0
                axis: Qt.vector3d(0,0,1)

            }
        }

        function mtqTap(position, id) {
            parent.mtqTap(position, id)
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
        PauseAnimation { duration: 200 }
        loops: Animation.Infinite
    }

    SequentialAnimation {
        id: arrowRotationAnimation
        NumberAnimation {
            id: zAxisFullRotationAnimation
            target: zAxisRotationArrow
            properties: "angle"
            duration: 1400
            from: 0
            to: 360
            loops: 3
        }

        NumberAnimation {
            id: zAxisAngleRotationAnimation
            target: zAxisRotationArrow
            properties: "angle"
            duration: 500
            from: 0
            to: 0
        }
        PauseAnimation { duration: soloTime }
        onRunningChanged: {
            if (!arrowRotationAnimation.running) {
                spinningStopped()
            }
        }
    }

    SequentialAnimation {
        id: fromToAnimation
        NumberAnimation {
            id: zAxisFromToAnimation
            target: zAxisRotationArrow
            properties: "angle"
            duration: 500
            from: 0
            to: 0
        }
        PauseAnimation { duration: warmUpSoloTime }
        onRunningChanged: {
            if (!fromToAnimation.running) {
                rotationStopped()
            }
        }
     }

    function mtqTap(position, id) {
        //enableSpinner()
        //rotateToPlayer(1)
        //rotateFromToPlayer(2,4)
    }

    function beat() {
        if (!beatAnimation.running) {
            beatAnimation.start();
        }
    }

    function enableSpinner() {
        arrow.enabled = true
    }

    function disableSpinner() {
        arrow.enabled = false
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

    function getAngleForPlayer(player) {
        var angle
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
        return angle
    }

    // adapt rotation speed to the angle of the rotation
    function getDurationForRotation(rotationAngle) {
        return fullDurationSlow * (rotationAngle / 360)
    }

    function rotateFromToPlayer(player1, player2) {
        var angle1 = getAngleForPlayer(player1)
        var angle2 = getAngleForPlayer(player2)
        var rotationAngle = Math.abs(angle1 - angle2)
        var duration = getDurationForRotation(rotationAngle)

        zAxisFromToAnimation.from = angle1
        zAxisFromToAnimation.to = angle2
        zAxisFromToAnimation.duration = duration
        fromToAnimation.start()
    }

    function rotateToPlayer(player) {
        var angle = getAngleForPlayer(player)
        var duration = getDurationForRotation(angle)

        zAxisFromToAnimation.from = 0
        zAxisFromToAnimation.to = angle
        zAxisFromToAnimation.duration = duration
        fromToAnimation.start()
    }

    function spinToPlayer(player) {
        var angle = getAngleForPlayer(player)
        var duration = getDurationForRotation(angle)

        zAxisAngleRotationAnimation.from = 0
        zAxisAngleRotationAnimation.to = angle
        zAxisAngleRotationAnimation.duration = duration
        arrowRotationAnimation.start()

    }
}
