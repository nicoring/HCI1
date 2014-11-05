import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0

Item3D{
    signal enabled
    signal disabled

    id: sliderbody

    property bool isEnabled: true;

    Component.onCompleted: {
        updateSlider();
    }

    function mtqTap(id,position){
        if (isEnabled){
            isEnabled = false;
            disabled();
        } else {
            isEnabled = true;
            enabled();
        }
    }

    function updateSlider(){
        if (isEnabled){
            moveToOn.start();
        } else {
            moveToOff.start();
        }
    }

    onIsEnabledChanged: {
        updateSlider();
    }

    NumberAnimation {
        id: moveToOn
        target: occluder
        properties: "position.x"
        to: 1.9
        duration: 500

        onRunningChanged: {
        }
   }

    NumberAnimation {
        id: moveToOff
        target: occluder
        properties: "position.x"
        to: -0.1
        duration: 500

        onRunningChanged: {
        }
   }

    mesh: Mesh { source: "qrc:/models/framework/sliderCasing.3ds" }
    effect: LightShader{}

    Item3D{
        id: occluder
        mesh: Mesh { source: "qrc:/models/framework/sliderSlider.3ds" }
        position: Qt.vector3d(1.9,0,0)
        effect: LightShader{}

        function mtqTap(id,position){
            parent.mtqTap(id,position);
        }
    }
}
