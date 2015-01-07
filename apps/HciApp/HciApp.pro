TARGET = HciApp
TO_BASE_DIR = ../..
APP_DIR = $${PWD}

Qt += 3dquick 3d quick gui opengl

CONFIG(debug, debug|release) { #debug
} else { #release
        #MTQ_POST_HOOKS += Floor
}

include($${TO_BASE_DIR}/buildsystem/app.pri)

OTHER_FILES += \
    config.json \
    firstScene.qml \
    secondScene.qml \
    fourthScene.qml \
    framework/GlobalLight.js \
    framework/KeyCache.js \
    framework/arrow.3ds \
    framework/buttonActuator.3ds \
    framework/buttonCase.3ds \
    framework/buttontop.3ds \
    framework/checkboxCase.3ds \
    framework/checkboxCross.3ds \
    framework/cube.obj \
    framework/HighResQuad.3ds \
    framework/newTextures.psd \
    framework/radioCase.3ds \
    framework/radioCirc.3ds \
    framework/sliderCasing.3ds \
    framework/sliderSlider.3ds \
    framework/zgBase.3ds \
    framework/zgStone0.3ds \
    framework/zgStone1.3ds \
    framework/zgStone2.3ds \
    framework/zgStone3.3ds \
    framework/Button.qml \
    framework/Checkbox.qml \
    framework/ClickThroughMenu.qml \
    framework/ColorChangeStone.qml \
    framework/HighResQuad.qml \
    framework/Keyboard.qml \
    framework/KeyboardKey.qml \
    framework/Label.qml \
    framework/LightDefinition.qml \
    framework/LightDefinitionEntry.qml \
    framework/LightShader.qml \
    framework/MovingCube.qml \
    framework/MtqViewPort.qml \
    framework/RadioButton.qml \
    framework/RadioGroup.qml \
    framework/Scene.qml \
    framework/Slider.qml \
    framework/Vehicle.qml \
    framework/zgBase.jpg \
    framework/zgStones.jpg \
    framework/arrow.png \
    framework/butact.png \
    framework/butcase.png \
    framework/cbcase.png \
    framework/cbcross.png \
    framework/componentBase.png \
    framework/componentHighlight.png \
    framework/radcase.png \
    framework/radcirc.png \
    framework/sliderCa.png \
    framework/sliderSl.png \
    framework/LightShader.frag \
    framework/LightShader.vert \
    ZenGardenScene.qml \
    App.qml \
    framework/ObjectArray.qml \
    framework/LightShaderHardShadows.frag \
    framework/FlatButton.qml \
    framework/DebugLayer.qml \
    framework/DebugShoe.qml \
    framework/PaintedCanvas.qml \
    framework/ImageCanvas.qml \
    framework/Marker.qml \
    floorScene.qml \
    widgets/Slice.qml \
    widgets/MainMenu.qml \
    widgets/CubeQuad.qml \
    framework/floorscene.3ds \
    widgets/TestScene.qml \
    floorscene-2.3ds \
    surf.jpeg \
    meshs/circle.3ds \
    meshs/middle_c.jpg \
    meshs/ring.3ds \
    meshs/notifica.jpg \
    meshs/topleft.3ds \
    meshs/top_left.jpg \
    meshs/topright.3ds \
    meshs/top_righ.jpg \
    meshs/bottomleft.3ds \
    meshs/left_bot.jpg \
    meshs/bottomright.3ds \
    meshs/right_bo.jpg \
    widgets/Circle3D.qml \
    widgets/Ring3D.qml \
    widgets/Stage3D.qml \
    widgets/StageTopLeft.qml \
    widgets/StageTopRight.qml \
    widgets/StageBottomLeft.qml \
    widgets/StageBottomRight.qml

RESOURCES += \
    frameworkResources.qrc

