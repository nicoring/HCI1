import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0

Item3D{
    id: checkBoxShell
    scale: 0.3

    property bool checked: false;
    onCheckedChanged: {
        if (checked){
            if (crossHide.running){
                crossHide.stop();
            }
            checkBoxCross.enabled = true;
            crossShow.start();
        } else {
            if (crossShow.running){
                crossShow.stop();
            }
            crossHide.start();
        }
    }

    mesh: Mesh { source: "checkboxCase.3ds" }
    effect: LightShader{
    }

    function mtqTap(id,position){
        checked = !checked;
    }

    Item3D{
        id: checkBoxCross
        enabled: false;
        position: Qt.vector3d(0.0,0.0,-0.2)
        mesh: Mesh { source: "checkboxCross.3ds" }
        effect: LightShader{
        }

        function mtqTap(id,position){
            parent.mtqTap(id,position);
        }
    }

    NumberAnimation{
        id: crossHide
        property: "position.z"
        target: checkBoxCross
        to: -0.2
        duration: 200
        onStopped: {
            checkBoxCross.enabled = false;
        }
    }

    NumberAnimation{
        id: crossShow
        property: "position.z"
        target: checkBoxCross
        to: 0.0
        duration: 200
    }
}
