import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0

Item3D{
    id: sliderbody

    signal enabled
    signal disabled
    property bool isEnabled: true;

    mesh: Mesh { source: "qrc:/models/framework/sliderCasing.3ds" }
    effect: LightShader{}

    Component.onCompleted: updateSlider()

    function mtqTap(id,position){
        isEnabled = !isEnabled
    }

    onIsEnabledChanged: updateSlider()

    function updateSlider(){
        if (isEnabled){
            moveToOn.start()
            enabled()
        } else {
            moveToOff.start()
            disabled()
        }
    }

    NumberAnimation {
        id: moveToOn
        target: occluder
        properties: "position.x"
        to: 1.9
        duration: 500
   }

   NumberAnimation {
        id: moveToOff
        target: occluder
        properties: "position.x"
        to: -0.1
        duration: 500
   }

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
