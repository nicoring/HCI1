import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import mtq.qml3d 1.0
import QtQuick.Window 2.1
import "framework/GlobalLight.js" as GlobalLight
import "framework"

Item3D{    
    Component.onCompleted: {
        parent.sceneEnabled.connect(setupLight);
    }

    function setupLight(){
        //set up 4 directional lights from each side

        //###2###
        //#     #
        //1     3
        //#     #
        //###4###

        var lightHeight = 3.0;
        var positions = [
                    //standard dimensions are (8.5,5)
                    Qt.vector3d(-4,0,lightHeight),
                    Qt.vector3d(0,2.5,lightHeight),
                    Qt.vector3d(4,0,lightHeight),
                    Qt.vector3d(0,-2.5,lightHeight)
                ]

        var colors = [
                   Qt.vector3d(0.8,0.2,0.2),
                   Qt.vector3d(0.2,0.8,0.2),
                   Qt.vector3d(0.2,0.2,0.8),
                   Qt.vector3d(0.8,0.8,0.2)
                ]

        for (var i=0; i < 4; i++){
            var l = GlobalLight.GlobalLightDefinition.lightEntries[i];

            l.center = Qt.vector3d(0,0,0);
            l.type = 1;
            //l.attenuation = true;
            l.spotAngle = 110;
            l.createsShadows = true;
            l.enabled = true;

            l.position = positions[i];
            l.color = colors[i];
        }
    }

    HighResQuad {
        scale: 12
        position: Qt.vector3d(0,0,-1)
        effect: LightShader {
            texture: "framework/componentBase.png"
        }
    }

    MovingCube{
        id: firstCube
        position: Qt.vector3d(-2,0.0,-0.5)

        onContactDown: {
            GlobalLight.GlobalLightDefinition.lightEntries[0].enabled = false;
        }
        onContactUp: {
            GlobalLight.GlobalLightDefinition.lightEntries[0].enabled = true;
        }
    }

    MovingCube{
        id: cube0
        position: Qt.vector3d(2,0.0,-0.5)

        onContactDown: {
            GlobalLight.GlobalLightDefinition.lightEntries[2].enabled = false;
        }
        onContactUp: {
            GlobalLight.GlobalLightDefinition.lightEntries[2].enabled = true;
        }
    }

    MovingCube{
        id: cube1
        position: Qt.vector3d(2,2,-0.5)
    }

    MovingCube{
        id: cube2
        position: Qt.vector3d(2,-2,-0.5)
    }

    MovingCube{
        id: cube3
        position: Qt.vector3d(-2,2,-0.5)
    }

    MovingCube{
        id: cube6
        position: Qt.vector3d(-2,-2,-0.5)
    }

    MovingCube{
        id: cube4
        position: Qt.vector3d(0,2,-0.5)

        onContactDown: {
            GlobalLight.GlobalLightDefinition.lightEntries[1].enabled = false;
        }
        onContactUp: {
            GlobalLight.GlobalLightDefinition.lightEntries[1].enabled = true;
        }
    }

    MovingCube{
        id: cube5
        position: Qt.vector3d(0,-2,-0.5)

        onContactDown: {
            GlobalLight.GlobalLightDefinition.lightEntries[3].enabled = false;
        }
        onContactUp: {
            GlobalLight.GlobalLightDefinition.lightEntries[3].enabled = true;
        }
    }
}
