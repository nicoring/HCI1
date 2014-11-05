import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import mtq.qml3d 1.0
import QtQuick.Window 2.1
import "framework/GlobalLight.js" as GlobalLight
import "framework"

Item3D{
    Component.onCompleted: {
        parent.sceneEnabled.connect(setupLight);
    }
    function setupLight(){
        for (var i=0; i < 4; i++){
            var l = GlobalLight.GlobalLightDefinition.lightEntries[i];
            l.enabled = false;
        }

        var l0 = l = GlobalLight.GlobalLightDefinition.lightEntries[0];
        l.position = Qt.vector3d(-2, 0, 3)
        l.center = Qt.vector3d(0,0,0);
        l.type = 1;
        l.color = Qt.vector3d(0.8,0.8,0.8)
        l.createsShadows = true;
        l.enabled = true;
    }


    HighResQuad {
        scale: 12
        position: Qt.vector3d(0,0,-0.05)
        effect: LightShader {
            texture: "framework/componentBase.png"
        }
    }

    RadioGroup{
        id: radioGroup

        scale: 0.5
        position: Qt.vector3d(2,2,0);
        transform:[
            Rotation3D{axis: Qt.vector3d(0,0,1); angle: 80}
        ]

        radioButtons: [
            RadioButton{ parent: radioGroup; position: Qt.vector3d(0.0,-0.5,0)},
            RadioButton{ parent: radioGroup; position: Qt.vector3d(0.0,-1.5,0)},
            RadioButton{ parent: radioGroup; position: Qt.vector3d(0.0,-2.5,0)}
        ]

        Label {
            sceneWidth: 1.2
            sceneHeight: 0.2
            id:buttonlabel
            text: "Radio Group"
            fontColor: "black"
            position: Qt.vector3d(0.0,0.0,0.0)
        }
    }

    Checkbox{
        position: Qt.vector3d(2,-1,0)
        transform:[
            Rotation3D{axis: Qt.vector3d(0,0,1); angle: 15}
        ]

        Label {
            scale:2
            sceneWidth: 1.2
            sceneHeight: 0.2
            id:cblabel
            text: "Checkbox"
            fontColor: "black"
            position: Qt.vector3d(0.45,1.5,0.0)
        }
    }

    Item3D{
        position: Qt.vector3d(-2.5,0.5,0.1)
        transform:[
            Rotation3D{
                axis: Qt.vector3d(0,0,1)
                angle: 20
            }
        ]

        Label {
            scale:1
            sceneWidth: 2.2
            sceneHeight: 0.2
            id:blabel
            text: "Buttons (many of them)"
            fontColor: "black"
            position: Qt.vector3d(0.3,0.6,-0.1)
        }

        ObjectArray{
            position: Qt.vector3d(0.0,0.0,0.0)
            repetitions: 4
            translationPerRepetition: Qt.vector3d(0.5,0,0)

            qmlCode:
                "
                 import Qt3D 2.0
                 ObjectArray{
                    position: Qt.vector3d(0,0,0)
                    repetitions: 5
                    translationPerRepetition: Qt.vector3d(0,-0.5,0)

                    transform:[
                        Rotation3D{axis: Qt.vector3d(0,0,1); angle:10}
                    ]

                    function arraygen(i){
                        transform[0].angle = i * 10;
                    }

                    qmlCode: \"
                        import Qt3D 2.0
                        FlatButton{
                            transform:[
                                Scale3D{scale:0.4}
                            ]
                        }
                    \"
                }"
        }
    }

    Keyboard{
        position: Qt.vector3d(-3,0,0)
        scale: 0.5

        transform: [
            Rotation3D {axis: Qt.vector3d(0,0,1); angle: -100}
        ]
        onKey: {
            console.log("Keyboard key pressed: " + c);
        }
    }
}
