import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import mtq.qml3d 1.0

Item3D{
    id: keybase

    property string character: "a";

    signal pressed(string c)

    function mtqTap(id,position){
        if (upperCase){
            keybase.pressed(keybase.character.toUpperCase());
        } else {
            keybase.pressed(keybase.character.toLowerCase());
        }

        keyshader.texture = "componentHighlight.png"
        textureResetTimer.start();
        tapAnimation.start();
    }

    property bool upperCase: false
    onUpperCaseChanged: {
        if (upperCase){
            lowerCaseLabel.enabled = false;
            upperCaseLabel.enabled = true;
        } else {
            lowerCaseLabel.enabled = true;
            upperCaseLabel.enabled = false;
        }
    }

    Cube{
        id: keycube

        effect: LightShader{
            id: keyshader
            texture: "componentBase.png"
        }

        function mtqTap(id,position){
            parent.mtqTap(id,position);
        }

        Timer{
            id:textureResetTimer
            interval: 250
            running: false
            repeat: false
            onTriggered: keyshader.texture = "componentBase.png"
        }

        NumberAnimation{
            id: tapAnimation
            to:-0.2
            target: keybase
            properties: "position.z"
            duration: 100;
            onStopped: {
                tapBack.start();
            }
        }

        NumberAnimation{
            id: tapBack
            to: 0.0;
            target: keybase
            duration: 150;
            properties: "position.z"
        }

    }

    Label{
        id:lowerCaseLabel
        text: keybase.character.toLowerCase();
        sceneWidth: 1.0
        sceneHeight: 1.0
        fontSize: 100
        fontColor: "black"
        position: Qt.vector3d(0.35,-0.25,0.51);

        function mtqTap(id,position){
            parent.mtqTap(id,position);
        }
    }

    Label{
        id:upperCaseLabel
        enabled: false
        text: keybase.character.toUpperCase();
        sceneWidth: 1.0
        sceneHeight: 1.0
        fontSize: 100
        fontColor: "black"
        position: Qt.vector3d(0.35,-0.25,0.51);

        function mtqTap(id,position){
            parent.mtqTap(id,position);
        }
    }
}
