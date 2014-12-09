import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import mtq.qml3d 1.0
import QtQuick.Window 2.1
import "framework/GlobalLight.js" as GlobalLight
import "framework"

Item3D {
    Component.onCompleted: {
        parent.sceneEnabled.connect(setupLight);
    }
    function setupLight(){
        for (var i=0; i < 4; i++){
            var l = GlobalLight.GlobalLightDefinition.lightEntries[i];
            l.enabled = false;
        }

        var l0 = l = GlobalLight.GlobalLightDefinition.lightEntries[0];
        l.position = Qt.vector3d(-2, 0, 3)
        l.center = Qt.vector3d(0,0,0);
        l.type = 1;
        l.color = Qt.vector3d(0.8,0.8,0.8)
        l.createsShadows = true;
        l.enabled = true;
    }

    HighResQuad {
        scale: 3
        position: Qt.vector3d(1.5,1.5,0)
        effect: LightShader {
            texture: "framework/componentBase.png"
        }
    }

    FlatButton{
        scale: 0.4
        position: Qt.vector3d(0.0,0,0.1);

        onPushed: {
            naEnabled.start()
        }

        onReleased: {
            naDisabled.start()
        }
    }

    MovingCube{
        id: cube4
        position: Qt.vector3d(0,2,0.1)

        onContactDown: {
            GlobalLight.GlobalLightDefinition.lightEntries[1].enabled = false;
        }
        onContactUp: {
            GlobalLight.GlobalLightDefinition.lightEntries[1].enabled = true;
        }
    }

    HighResQuad {
        scale: 3
        position: Qt.vector3d(-1.5,-1.5,0)
        effect: LightShader {
            texture: "framework/componentBase.png"
        }
    }
    HighResQuad {
        scale: 3
        position: Qt.vector3d(-1.5,1.5,0)
        effect: LightShader {
            texture: "framework/componentBase.png"
        }
    }
    HighResQuad {
        scale: 3
        position: Qt.vector3d(1.5,-1.5,0)
        effect: LightShader {
            texture: "framework/componentBase.png"
        }
    }

}
