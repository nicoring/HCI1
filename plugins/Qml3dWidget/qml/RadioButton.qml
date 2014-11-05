import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0

Item3D{
    id: radioShell
    scale: 0.3

    property bool radioActive: false
    onRadioActiveChanged: {
        if (radioActive){
            radioPoint.enabled = true;
            show.start();
        } else {
            hide.start();
        }
    }

    signal contact(var item)

    mesh: Mesh { source: "radioCase.3ds" }
    effect: LightShader{
    }

    function mtqTap(id,position){
        if (!radioActive){
            contact(radioShell);
        }
    }

    Item3D{
        id: radioPoint
        enabled: false;
        position: Qt.vector3d(0,0,-0.2)
        mesh: Mesh { source: "radioCirc.3ds" }
        effect: LightShader{
        }

        function mtqTap(id,position){
            //Don't do anything: if it is activated, it should stay activated
        }
    }

    NumberAnimation{
        id: hide
        property: "position.z"
        target: radioPoint
        to: -0.2
        duration: 200
        onStopped: {
            radioPoint.enabled = false;
        }
    }

    NumberAnimation{
        id: show
        property: "position.z"
        target: radioPoint
        to: 0.0
        duration: 200
    }
}
