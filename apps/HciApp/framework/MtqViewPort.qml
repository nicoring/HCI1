import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import QtQuick.Window 2.1
import mtq.qml3d 1.0
import "GlobalLight.js" as GlobalLight

Viewport {
    //----- Properties -----

    //if set to true, all current contacts and the average user position are drawn as an overlay
    property bool displayDebugInfo: false
    //display the debug layer (shoes etc)
    property bool displayDebugLayer: true
    //slightly randomizes the input of the mouse (good for simulating the incurracy of feet on floor)
    property bool fuzzyInput: true

    //enable shadowmapping at all?
    property bool drawShadows: true

    //debug: if set to true, all shadowmaps are saved to disk
    property bool saveShadowMapsToDisk: false

    //if set to true, the camera height will adjust itself to the height of the object below the user
    property bool adjustCameraHeightToScene: true

    // "OffCenter" for perspective 3d
    // "Orthographic" for flat surfaces
    property string projectionMode: "OffCenter" //or use "Orthographic" when you want a flat UI

    //---- Signals ----
    signal mtqUserPositionChanged(point userPosition);

    //---- Functions -----
    //Increase / Decrease the height of the camera. This only modifies the projection (e.g. for a taller/smaller user)
    //increaseCameraHeight();
    //decreaseCameraHeight();

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
    enableShadows: drawShadows
    shadowMapEngineStartOffset: 1

    onHeightChanged: {
        adjustCameraViewSize();
    }

    onDrawShadowsChanged: {
        GlobalLight.EnableShadowsAtAll = drawShadows;
    }

    onWidthChanged: {
        adjustCameraViewSize();
    }

    onDisplayDebugInfoChanged: {
        mtqIntegrator.paintDebugInfo = displayDebugInfo;
    }

    onDisplayDebugLayerChanged: {
        if (displayDebugLayer){
            debugLayer.enabled = true;
            debugLayer.visible = true;
        } else {
            debugLayer.enabled = false;
            debugLayer.visible = false;
        }
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
                    GlobalLight.GlobalLightDefinition.lightEntries[i].biasedMvpMatrix = mtqViewPort.getShadowMapEngine().getLight(i).getBiasedMvpMatrix();
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

        GlobalLight.EnableShadowsAtAll = drawShadows;

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
            if (Qt.ControlModifier == mouse.modifiers){
                mtqIntegrator.mouseClicked(p);
            } else if (mouse.modifiers == Qt.ShiftModifier){
                mtqIntegrator.mouseDoubleClick(p);
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
        fuzzyInput: parent.fuzzyInput
        printDebugOutput: false
        onUserPositionChanged:{
            mtqUserPositionChanged(qmlUserPosition);
        }

        //You can use these signals to react globally to all tap/contact down/... events.
        //remember that the corresponding mtqXYZ(...) methods are called on each
        //Object that ist actually touched by the user
        onMtqContactDown: {
        }

        onMtqContactUp:{
        }

        onMtqContactMove: {
            /*
            //All events supply contactId and position
            var user = mtqIntegrator.getContactUser(contactId);
            var tilting = mtqIntegrator.getContactTilting(contactId);

            console.log("JS Event: contact move for " + user + " tilting " + tilting);
            */
        }

        onMtqTap:{
        }

        onMtqDoubleTap:{
        }
    }

    DebugLayer{
        id: debugLayer
        mtqIntegrator:  mtqIntegrator
        anchors.fill: parent
    }
}

