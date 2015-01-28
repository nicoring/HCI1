import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import mtq.qml3d 1.0
import QtQuick.Window 2.1
import "../framework"
import "../widgets"

Item3D{
    id: label
    property string text: "Text"
    property string fontFamily: "Helvetica"
    property int fontSize: 30
    property color fontColor: "cyan"

    //width an height in 3d-length-units
    property real sceneWidth: 1.0
    property real sceneHeight: 1.0

    //pixel per 3d-length-unit
    property real imageResolution: 200.0

    TextDrawer{
        id: textdrawer
        text: label.text
        fontFamily: label.fontFamily
        fontSize: label.fontSize
        fontColor: label.fontColor
        imageWidth: Math.round(label.sceneWidth * label.imageResolution)
        imageHeight: Math.round(label.sceneHeight * label.imageResolution)
    }

    // ImageCanvas
    Item3D {
        id: paintCanvas
        property var textureQImage: textdrawer.paintedImage;
        onTextureQImageChanged: {
            shaderEffect.textureImage = textureQImage;
        }

        property real sceneWidth: label.sceneWidth;
        property real sceneHeight: label.sceneHeight;

        Quad {
            effect: LightShader{
                id: shaderEffect;
                blending: true;
                textureImage: textureQImage;
                onTextureImageChanged: gc();
            }

            transform:[
                Scale3D{ scale: Qt.vector3d(sceneWidth, 1.0,  sceneHeight) },
                Rotation3D { angle: 90; axis: Qt.vector3d(1, 0, 0)}
            ]

// --- Label Code: End --------------------------------------------------------- //
// ----------------------------------------------------------------------------- //
// --- Pass through contact events --------------------------------------------- //

            function mtqContactUp(id,position){
                parent.mtqContactUp(id,position);
            }

            function mtqContactDown(id,position){
                parent.mtqContactDown(id,position);
            }

            function mtqTap(id,position){
                parent.mtqTap(id,position);
            }
        }

        function mtqContactUp(id,position){
            parent.mtqContactUp(id,position);
        }

        function mtqContactDown(id,position){
            parent.mtqContactDown(id,position);
        }

        function mtqTap(id,position){
            parent.mtqTap(id,position);
        }
    }

    function mtqContactUp(id,position){
        if (parent.mtqContactUp) {
            parent.mtqContactUp(id,position);
        }
    }

    function mtqContactDown(id,position){
        if (parent.mtqContactDown) {
            parent.mtqContactDown(id,position);
        }
    }

    function mtqTap(id,position){
        if (parent.mtqTap) {
            parent.mtqTap(id,position);
        }
    }
}
