import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import mtq.qml3d 1.0
import QtQuick.Window 2.1
import "framework/GlobalLight.js" as GlobalLight
import "framework"

    MtqViewPort{
        id: mtqViewPort;
        //Show the circles around contacts and the user's position
        displayDebugInfo: true
        //Show the debug widget with shoes
        displayDebugLayer: true

        //projectionMode: "Orthographic"

        //for debug uses only
        saveShadowMapsToDisk: false

        //Disable shadows if they cause problems on your system (mainly in VMs)
        drawShadows: false // set to false on VM!!

        property var currentScene;

        Component.onCompleted: {
            mtqViewPort.getShadowMapEngine().shadowMapSize = 1024;

            currentScene = floorScene
            currentScene.showScene(true);

        }

        onMtqUserPositionChanged: {            
        }

        focus:true


        Scene{
            id: floorScene
            file: "../floorScene.qml"
        }
    }
