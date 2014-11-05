import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import mtq.qml3d 1.0

Item3D{
    id: paintedCanvas;
    property var painter: painter;

    property real sceneWidth: 1.0;
    property real sceneHeight: 1.0;

    property int imageWidth: 100
    property int imageHeight: 100

    property bool showFrame: true

    Item3D{
        id: frame
        enabled: paintedCanvas.showFrame

        mesh: Mesh{
            source: "qrc:/models/framework/canvascase.3ds"
        }
        transform:[
            Scale3D{
                scale: Qt.vector3d(sceneWidth, sceneHeight, 1.0)
            }
        ]
    }

    effect: LightShader{
    }

    SimplePainter{
        id: painter
        imageWidth: paintedCanvas.imageWidth
        imageHeight: paintedCanvas.imageHeight
    }

    ImageCanvas{
        id:canvas
        textureQImage: painter.paintedImage;
        sceneWidth: paintedCanvas.sceneWidth;
        sceneHeight: paintedCanvas.sceneHeight;

        function mtqTap(id,position){
            parent.mtqTap(id,position);
        }
    }
}
