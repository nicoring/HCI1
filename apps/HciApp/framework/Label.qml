import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import mtq.qml3d 1.0

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

    ImageCanvas{
        id: paintCanvas
        textureQImage: textdrawer.paintedImage;
        sceneWidth: label.sceneWidth
        sceneHeight: label.sceneHeight

        function mtqTap(id,position){
            if (parent.mtqTap) {
                parent.mtqTap(id,position);
            }
        }
    }
}

