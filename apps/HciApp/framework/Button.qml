import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0

Item3D{
    signal pushed
    signal released

    property variant pistonBasePos: 0.0;

    Component.onCompleted: {
        pistonBasePos = piston.position.z;
    }

    function mtqContactUp(id,position){
        actuatorHide.stop();
        actuatorShow.start();
        released();
    }

    function mtqContactDown(id,position){
        actuatorShow.stop();
        actuatorHide.start();
        pushed();
    }

    mesh: Mesh { source: "qrc:/models/framework/buttonCase.3ds" }
    scale: 0.5
    effect: LightShader{
    }

    Item3D {
        id: piston
        mesh: Mesh { source: "qrc:/models/framework/buttonActuator.3ds" }

        effect: LightShader{
        }

        function mtqContactDown(id,position){
            parent.mtqContactDown(id,position);
        }
        function mtqContactUp(id,position){
            parent.mtqContactUp(id,position);
        }
    }

    NumberAnimation{
        id: actuatorHide
        property: "position.z"
        target: piston
        to: -0.3
        duration: 100
    }

    NumberAnimation{
        id: actuatorShow
        property: "position.z"
        target: piston
        to: 0.0
        duration: 100
    }
}
