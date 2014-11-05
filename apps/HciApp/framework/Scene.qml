import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import mtq.qml3d 1.0
import QtQuick.Window 2.1

Item3D{
    id: mainObject

    property Item3D nextScene: null
    property Item3D previousScene: null

    property string file: ""

    signal sceneEnabled
    signal sceneDisabled    

    enabled: false

    Component.onCompleted: {
        if (file == "")
            return;

        var childStuff = Qt.createComponent(file);
         if (childStuff.status == Component.Ready)
             childStuff.createObject(mainObject, {});
         else{
            console.log("Warning: Scene '" + file + "' is not ready and therefore not loaded");
            console.log("(Error: " + childStuff.errorString() + ")");
         }
    }

    function showScene(overridePosition){
        enabled = true;
        sceneEnabled();
    }

    function hideScene(){
        enabled = false;
        sceneDisabled();
    }

    function switchToNextScene(){
        if (nextScene != null){
            afadeOutLeft.start();
            nextScene.fadeInRight();
            return nextScene;
        } else {
            return this;
        }
    }

    function switchToPreviousScene(){
        if (previousScene != null){
            afadeOutRight.start();
            previousScene.fadeInLeft();
            return previousScene;
        } else {
            return this;
        }
    }

    function fadeInLeft(){
        showScene(false);
        afadeInLeft.start();
    }

    function fadeInRight(){
        showScene(false);
        afadeInRight.start();
    }

    Vector3dAnimation{
        id: afadeOutLeft
        easing.type: Easing.InOutQuad
        from: Qt.vector3d(0,0,0)
        to: Qt.vector3d(-10,0,0)
        duration: 1000
        property: "position"
        onRunningChanged: {
            if (running == false){
                target.hideScene();
            }
        }
        target: mainObject
    }

    Vector3dAnimation{
        id: afadeOutRight
        easing.type: Easing.InOutQuad
        from: Qt.vector3d(0,0,0)
        to: Qt.vector3d(10,0,0)
        duration: 1000
        property: "position"
        onRunningChanged: {
            if (running == false){
                target.hideScene();
            }
        }
        target: mainObject
    }

    Vector3dAnimation{
        id: afadeInRight
        easing.type: Easing.InOutQuad
        from: Qt.vector3d(10,0,0)
        to: Qt.vector3d(0,0,0)
        duration: 1000
        property: "position"
        target: mainObject
    }

    Vector3dAnimation{
        id: afadeInLeft
        easing.type: Easing.InOutQuad
        from: Qt.vector3d(-10,0,0)
        to: Qt.vector3d(0,0,0)
        duration: 1000
        property: "position"
        target: mainObject
    }
}
