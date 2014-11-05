import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import mtq.qml3d 1.0

Cube {
    id:cube
    scale: 1

    NumberAnimation {
        id: animateHeight2
        target: cube
        properties: "position.z"
        to: -3.0
        duration: 5000
   }

    NumberAnimation {
        id: animateHeightback2
        target: cube
        properties: "position.z"
        to: -0.5
        duration: 5000
   }

    function mtqTap(id,position){
        effect.texture = "componentHighlight.png";
    }

    function mtqContactUp(id,position){
        effect.texture = "componentBase.png"
        animateHeight2.stop();
        animateHeightback2.start();
    }

    function mtqContactMove(id,position){
    }

    function mtqContactDown(id,position){
        effect.texture = "componentHighlight.png"
        animateHeightback2.stop();
        animateHeight2.start();
    }

    //Eigenes Gebastel mit light
    effect: LightShader{
        texture: "componentBase.png"
    }
}
