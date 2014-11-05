import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import "GlobalLight.js" as GlobalLight

ShaderProgram{
    blending: true
    id: localShaderProgramId

    property variant lightPositions: [
        3.0, 3.0, 5.0, 0.0, // xyz and type (0: light disabled, 1: directional w/ shadows, 2:spot light w/shadows, 3: point light w/ shadows, 4: directional w/o shadows, 5: spot w/o shadows, 6: point light w/o shadows)
        3.0, 3.0, 5.0, 0.0,
        3.0, 3.0, 5.0, 0.0,
        3.0, 3.0, 5.0, 0.0
    ]

    property variant lightColors: [
        1.0, 1.0, 1.0, 1.0, // rgb and attenuation (0= disabled, 1=enabled)
        1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0
    ]

    //biased mvp matrix for each light (also usee as the 0-cubemap matrix)
    property variant light0ShadowBiasMvp:
        [0, 0, 0, 0,
         0, 0, 0, 0,
         0, 0, 0, 0,
         0, 0, 0, 0]

    property variant light1ShadowBiasMvp:
        [0, 0, 0, 0,
         0, 0, 0, 0,
         0, 0, 0, 0,
         0, 0, 0, 0]

    property variant light2ShadowBiasMvp:
        [0, 0, 0, 0,
         0, 0, 0, 0,
         0, 0, 0, 0,
         0, 0, 0, 0]

    property variant light3ShadowBiasMvp:
        [0, 0, 0, 0,
         0, 0, 0, 0,
         0, 0, 0, 0,
         0, 0, 0, 0]

    property bool useGlobalLightDefinition: true

    property vector2d textureScaling: Qt.vector2d(1.0,1.0)

    //does the object emit light itself?
    property vector3d glow: Qt.vector3d(0,0,0)

    Component.onCompleted: {
        if (useGlobalLightDefinition){
            if (GlobalLight.GlobalLightDefinition == 0){
                var component = Qt.createComponent("LightDefinition.qml");
                GlobalLight.GlobalLightDefinition = component.createObject(parent);
                if (component.errorString().length > 0){
                    console.log("LightDefinition.qml component error: " + component.errorString());
                }
            }

            GlobalLight.GlobalLightDefinition.onLightDefinitionChange.connect(updateShader);
        }
    }

    function updateShader(){
        GlobalLight.GlobalLightDefinition.updateLightShader(localShaderProgramId);
    }

    vertexShader:"LightShader.vert"
    fragmentShader: "LightShader.frag"
}
