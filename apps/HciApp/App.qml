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
        drawShadows: true

        property var currentScene;

        Component.onCompleted: {
            mtqViewPort.getShadowMapEngine().shadowMapSize = 1024;

            currentScene = firstScene
            vehicle.updateArrows();
            currentScene.showScene(true);
        }

        onMtqUserPositionChanged: {            
        }

        focus:true

        function switchToPreviousScene(){
            currentScene = currentScene.switchToPreviousScene();
        }
        function switchToNextScene(){
            currentScene = currentScene.switchToNextScene();
        }

        Scene{
            id:firstScene
            file:"../firstScene.qml"
            nextScene: secondScene
        }

        Scene{
            id:secondScene
            file:"../secondScene.qml"
            previousScene: firstScene
            nextScene: zenGardenScene
        }

        Scene{
            id:zenGardenScene
            file:"../ZenGardenScene.qml"
            previousScene: secondScene
            nextScene: fourthScene
        }

        Scene{
            id:fourthScene
            file:"../fourthScene.qml"
            previousScene: zenGardenScene
        }

        Keys.onDigit0Pressed: worldMapScene.content.toggleRoute();

        Vehicle{
            id: vehicle

            onSwitchLeft: {
                switchToPreviousScene();
                updateArrows();
            }

            onSwitchRight: {
                switchToNextScene();
                updateArrows();
            }

            function updateArrows(){
                if (currentScene.previousScene == null){
                    vehicle.leftArrowEnabled = false;
                } else {
                    vehicle.leftArrowEnabled = true;
                }

                if (currentScene.nextScene == null){
                    vehicle.rightArrowEnabled = false;
                } else {
                    vehicle.rightArrowEnabled = true;
                }
            }

            position: Qt.vector3d(-3.6,2.1,0)
            scale: 0.8
            transform:[
                Rotation3D { angle:45; axis: Qt.vector3d(0, 0, 1)}
            ]
        }
    }
