import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0

Item3D {
    property var textureQImage;
    onTextureQImageChanged: {
        shaderEffect.textureImage = textureQImage;
    }

    property real sceneWidth: 1.0;
    property real sceneHeight: 1.0;

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

        function mtqTap(id,position){
            parent.mtqTap(id,position);
        }
    }
}
