import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import mtq.qml3d 1.0
import QtQuick.Window 2.1
import "GlobalLight.js" as GlobalLight

Item3D{
    property string modelFileName: "zgStone0.3ds"
    property vector3d changeColor: Qt.vector3d(1,1,1)

    id: stone
    mesh: Mesh { source: modelFileName }
    effect: LightShader{}

    function mtqContactDown(id,position){
        GlobalLight.GlobalLightDefinition.lightEntries[1].color = changeColor;
        animateHeightBack.stop();
        animateHeight.start();

        //add a little glow
        effect.glow = Qt.vector3d(0.2,0.2,0.2);
    }

    function mtqContactUp(id, position){
        animateHeight.stop();
        animateHeightBack.start();

        //reset glow
        effect.glow = Qt.vector3d(0.0,0.0,0.0);
    }

    NumberAnimation {
        id: animateHeight
        target: stone
        properties: "position.z"
        to: -0.18;
        duration: 1500
   }

   NumberAnimation {
        id: animateHeightBack
        target: stone
        properties: "position.z"
        to: 0.00;
        duration: 1000
   }

}
