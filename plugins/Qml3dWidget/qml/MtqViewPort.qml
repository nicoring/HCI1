import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import QtQuick.Window 2.1
import mtq.qml3d 1.0
import "GlobalLight.js" as GlobalLight

Viewport {
    //Properties
    property bool displayDebugInfo: false
    property bool drawShadows: true
    property bool saveShadowMapsToDisk: false
    property bool adjustCameraHeightToScene: true
    property string projectionMode: "OffCenter" //or use "Orthographic" when you want a flat UI

    //Signals
    signal mtqUserPositionChanged(point userPosition);

    //Internal properties and settings
    id: quickViewPort
    x:0; y:0
    width: parent.width
    height: parent.height
    picking: true
    navigation: false
    showSceneGraph: false
    showPicking: false
    blending: true
    renderDepthMap: true
    enableShadows: true

    onDrawShadowsChanged: {
        enableShadows = drawShadows;
    }

    onHeightChanged: {
        adjustCameraViewSize();
    }

    onWidthChanged: {
        adjustCameraViewSize();
    }

    onDisplayDebugInfoChanged: {
        mtqIntegrator.paintDebugInfo = displayDebugInfo;
    }

    onSaveShadowMapsToDiskChanged: {
        quickViewPort.shadowMapEngine.debugMode = saveShadowMapsToDisk;
    }

    onProjectionModeChanged: {
        if (projectionMode == "OffCenter"){
            viewportCamera.projectionType = "OffCenterProjection"
            mtqIntegrator.moveCamera = true;
        } else if (projectionMode == "Orthographic"){
            mtqIntegrator.moveCamera = false;
            viewportCamera.eye = Qt.vector3d(0,0,8)
            viewportCamera.center = Qt.vector3d(0,0,0)
            viewportCamera.projectionType = "Orthographic";
        } else {
            console.log("Invalid Projection Mode '" + projectionMode + "'(MtqViewPort)");
        }
    }

    Component.onCompleted: {
        initShadowMapEngine();        
    }

    function getShadowMapEngine(){
        return quickViewPort.shadowMapEngine;
    }

    function updateShadowMatrices(){
        if (GlobalLight != 0){
            //Update MVP Matrices (C++ ---> QML)
            for (var i=0; i<4; i++){
                if (GlobalLight.GlobalLightDefinition.lightEntries[i].enabled){
                    if (GlobalLight.GlobalLightDefinition.lightEntries[i].type == 1 || GlobalLight.GlobalLightDefinition.lightEntries[i].type == 2){
                        //Directional and Spotlight
                        GlobalLight.GlobalLightDefinition.lightEntries[i].biasedMvpMatrix = mtqViewPort.getShadowMapEngine().getLight(i).getBiasedMvpMatrix();
                    } else {
                        //Point is removed
                    }
                }
            }
        }
    }

    function initShadowMapEngine(){
        if (GlobalLight.GlobalLightDefinition == 0){
            var component = Qt.createComponent("LightDefinition.qml");
            GlobalLight.GlobalLightDefinition = component.createObject(parent);
            console.log("LightDefinition.qml component error: " + component.errorString());
        }

        GlobalLight.GlobalLightDefinition.onLightDefinitionChange.connect(updateShadowEngine);

        quickViewPort.onShadowMapRenderingComplete.connect(updateShadowMatrices);
    }

    //transfers QML light settings to the C++ ShadowMapEngine
    function updateShadowEngine(){
        for (var i=0; i<4; i++){
            var cppLight = mtqViewPort.getShadowMapEngine().getLight(i);
            var lightEntry = GlobalLight.GlobalLightDefinition.lightEntries[i];

            cppLight.enabled = lightEntry.enabled;          
            if (!lightEntry.createsShadows){
                cppLight.enabled = false;
            }

            cppLight.eye = lightEntry.position;
            cppLight.center = lightEntry.center;
            if (lightEntry.type == 1){
                cppLight.lightType = "Directional";
            } else if (lightEntry.type == 2){
                cppLight.lightType = "Spot";
                cppLight.spotAngle = lightEntry.spotAngle;
            } else {
                cppLight.lightType = "Point";
            }
        }
    }

    MouseArea {
       anchors.fill: parent
       width:Screen.width;
       height: Screen.height;
       onDoubleClicked: {
           var p = Qt.point(mouse.x,mouse.y);
           if (mouse.modifiers == Qt.ShiftModifier){
               mtqIntegrator.mouseDoubleClick(p);
           }
       }
       onPressed: {
           var p = Qt.point(mouse.x,mouse.y);
           mtqIntegrator.mousePress(p);
       }
       onPositionChanged: {
           var p = Qt.point(mouse.x,mouse.y);
           mtqIntegrator.mouseMove(p);
       }
       onReleased: {
           var p = Qt.point(mouse.x,mouse.y);
           mtqIntegrator.mouseRelease(p);
       }
       onClicked: {
            var p = Qt.point(mouse.x,mouse.y);
            if (mouse.modifiers == Qt.ShiftModifier || Qt.ControlModifier == mouse.modifiers){
                mtqIntegrator.mouseClicked(p);
            }
       }
    }

    camera: Camera {
        id: viewportCamera
        center: Qt.vector3d(0,0,0)
        eye: Qt.vector3d(0,0,8)
        nearPlane: 5.0
        farPlane: 150.0
        viewSize: Qt.size(8.5,5)
        projectionType: "OffCenterProjection"
        offCenterHeightAdjustment: 0.0
        adjustForAspectRatio: false
    }

    function adjustCameraViewSize(){
        //Adjust the cameras view size to a constant 8.5 in length and varying height
        var aspectRatio = width/height;
        var viewHeight = viewportCamera.viewSize.width * (1.0 / aspectRatio);
        viewportCamera.viewSize = Qt.size(viewportCamera.viewSize.width, viewHeight);
    }

    function increaseCameraHeight(){
        viewportCamera.eye.z += 0.25;
    }

    function decreaseCameraHeight(){
        viewportCamera.eye.z -= 0.25;
    }

    MtqIntegratorWidget{
        id: mtqIntegrator
        anchors.fill: parent
        smoothCamera: true
        moveCamera: true
        adjustCameraHeightToScene: quickViewPort.adjustCameraHeightToScene
        paintDebugInfo: displayDebugInfo
        onUserPositionChanged:{
            mtqUserPositionChanged(qmlUserPosition);
        }               
    }
}

