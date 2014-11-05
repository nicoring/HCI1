import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0

Item3D{
    signal enabled
    signal disabled

    id: sliderbody

    property variant sliderBasePos: 0.0
    property bool isEnabled: true;

    Component.onCompleted: {
        sliderBasePos = occluder.position.x
    }

    function mtqTap(id,position){
        if (isEnabled){
            moveToOff.start();
            isEnabled = false;
            disabled();
        } else {
            moveToOn.start();
            isEnabled = true;
            enabled();
        }
    }

    NumberAnimation {
        id: moveToOn
        target: occluder
        properties: "position.x"
        to: sliderBasePos
        duration: 500

        onRunningChanged: {
        }
   }

    NumberAnimation {
        id: moveToOff
        target: occluder
        properties: "position.x"
        to: sliderBasePos - 2
        duration: 500

        onRunningChanged: {
        }
   }

    mesh: Mesh { source: "sliderCasing.3ds" }
    effect: LightShader{}

    Item3D{
        id: occluder
        mesh: Mesh { source: "sliderSlider.3ds" }
        position: Qt.vector3d(1.9,0,0)
        effect: LightShader{}

        function mtqTap(id,position){
            parent.mtqTap(id,position);
        }
    }
}
