import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import mtq.qml3d 1.0
import QtQuick.Window 2.1
import "framework/GlobalLight.js" as GlobalLight
import "framework"

Item3D{
    mesh: Mesh { source: "qrc:/models/framework/zgBase.3ds" }
    position: Qt.vector3d(-3.8,-2.5,-0.2)
    scale: 0.7
    effect: LightShader{}

    Item3D{
        mesh: Mesh { source: "qrc:/models/framework/zgLight.3ds" }
        position: Qt.vector3d(0,-0.2,0)
        effect: LightShader{
            id: lightBulbShader
            glow: Qt.vector3d(1.0,1.0,1.0)
        }
    }

    Component.onCompleted: {
        parent.sceneEnabled.connect(enableLight);
    }

    function enableLight(){
        //Enable light 0 and light 1 for the zen garden
        var spotLight = GlobalLight.GlobalLightDefinition.lightEntries[1];
        spotLight.enabled = true;
        spotLight.type = 2;
        spotLight.spotAngle = 110;
        spotLight.position = Qt.vector3d(0.51,-2.4,1.5);
        spotLight.color = Qt.vector3d(1,1,1)
        spotLight.attenuation = true;
        spotLight.createsShadows = true;

        var ambientLight = GlobalLight.GlobalLightDefinition.lightEntries[0];
        ambientLight.enabled = true;
        ambientLight.type = 1;
        ambientLight.color = Qt.vector3d(0.60,0.57, 0.57);
        ambientLight.position = Qt.vector3d(0,0,4);
        ambientLight.createsShadows = false;

        GlobalLight.GlobalLightDefinition.lightEntries[2].enabled = false;
        GlobalLight.GlobalLightDefinition.lightEntries[3].enabled = false;
    }

    ColorChangeStone{
        changeColor: Qt.vector3d(1.0,0.3,0.3)
        modelFileName: "qrc:/models/framework/zgStone0.3ds"

        onActivate: {
            lightBulbShader.glow = changeColor;
        }
    }

    ColorChangeStone{
        changeColor: Qt.vector3d(0.3,1.0,0.3)
        modelFileName: "qrc:/models/framework/zgStone1.3ds"

        onActivate: {
            lightBulbShader.glow = changeColor;
        }
    }

    ColorChangeStone{
        changeColor: Qt.vector3d(0.3,0.3,1.0)
        modelFileName: "qrc:/models/framework/zgStone2.3ds"

        onActivate: {
            lightBulbShader.glow = changeColor;
        }
    }

    ColorChangeStone{
        changeColor: Qt.vector3d(1,1,1)
        modelFileName: "qrc:/models/framework/zgStone3.3ds"

        onActivate: {
            lightBulbShader.glow = changeColor;
        }
    }
}
