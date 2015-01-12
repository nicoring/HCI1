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
        //set up 4 directional lights from each side

        //###2###
        //#     #
        //1     3
        //#     #
        //###4###

        var lightHeight = 2.5;
        var positions = [
                    //standard dimensions are (8.5,5)
                    Qt.vector3d(-4,0,lightHeight),
                    Qt.vector3d(0,2.5,lightHeight),
                    Qt.vector3d(4,0,lightHeight),
                    Qt.vector3d(0,-2.5,lightHeight)
                ]

        var colors = [
                   Qt.vector3d(0.8,0.2,0.2),
                   Qt.vector3d(0.2,0.8,0.2),
                   Qt.vector3d(0.2,0.2,0.8),
                   Qt.vector3d(0.8,0.8,0.2)
                ]

        for (var i=0; i < 4; i++){
            var l = GlobalLight.GlobalLightDefinition.lightEntries[i];

            l.center = Qt.vector3d(0,0,0);
            l.type = 1;
            //l.attenuation = true;
            l.spotAngle = 110;
            l.createsShadows = true;
            l.enabled = true;

            l.position = positions[i];
            l.color = colors[i];
        }
    }

    HighResQuad {
        scale: 12
        position: Qt.vector3d(0,0,-0.1)
        effect: LightShader {
            texture: "framework/componentBase.png"
        }
    }

    //If you need global acces to Floor events, use the floorEventWidget in your scene / component
    FloorEventWidget{
        onMtqTap: {
            console.log("Tap with id " + contactId + " at position " + position)
        }
        onMtqDoubleTap: {
            console.log("DoubleTap with id " + contactId + " at position " + position)
        }
        onMtqContactDown: {
            console.log("ContactDown with id " + contactId + " at position " + position)
        }

        /*
        onMtqContactMove: {
            console.log("ContactMove with id " + contactId + " at position " + position)

            //more functions you can use to get detailed information for a contact
            //(can be used at any time, but some information might not be available directly at the
            // moment of contactDown or Tap - user recognition takes some time)
            var user = getContactUser(contactId)
            var tilting = getContactTilting(contactId)
            var direction = getContactDirection(contactId)

            console.log("user=" + user + " tilting=" + tilting + " direction=" + direction)
        }
        */

        onMtqContactUp: {
            console.log("ContactUp with id " + contactId + " at position " + position)
        }
    }

    ClickThroughMenu{
        id:ctmenu
        position: Qt.vector3d(-1.5,-1.5,0)
        transform:[
            Rotation3D{axis: Qt.vector3d(0,0,1); angle:15}
        ]
        spaceInBetweenArrows: 1.3
        menuItems: [
            //It is important that all items have the 'parent' entry
            Cube { scale: 0.5; parent:ctmenu; effect: LightShader{texture: "framework/componentBase.png"}},
            Cube {
                scale: 0.5
                transform: Rotation3D{ angle: 45; axis: Qt.vector3d(0,0,1)}
                effect: LightShader{texture: "framework/componentBase.png"}
                parent:ctmenu
            },
            Cube { scale: 0.5; effect: LightShader{texture: "framework/componentBase.png"} transform: Rotation3D{ angle: 10; axis: Qt.vector3d(0,1,1)} parent:ctmenu}
        ]

        onSelectionChanged: {
            console.log("Selected Item: " + selectedItem);
        }
    }

    Item3D{
        position:Qt.vector3d(1.5,1.0,0.0)
        transform:[
            Rotation3D{angle: 110; axis:Qt.vector3d(0,0,1)}
        ]

        Slider{
            scale: 0.4
            isEnabled: true;

            Component.onCompleted: {
                var p = paintCanvas.painter;
                paintImage1();
            }

            onEnabled: {
                //do something
                paintImage1();
            }

            onDisabled: {
                //do something
                paintImage2();
            }

            function paintImage1(){
                var p = paintCanvas.painter;

                p.penWidth = 1;
                p.clear("transparent");
                p.penColor = "black";
                p.paintLine(0,0,50,50);
                p.paintLine(0,50,50,0);

                p.penWidth = 3;
                p.penColor = "blue";
                p.paintEllipse(25,25,10,10);
            }

            function paintImage2(){
                var p = paintCanvas.painter;

                p.penWidth = 1;
                p.clear("transparent");
                p.penColor = "black";
                p.paintEllipse(25,25,20,20);

                p.penWidth = 3;
                p.penColor = "blue";
                p.paintEllipse(25,25,10,10);
            }
        }

        PaintedCanvas{
            id: paintCanvas
            position: Qt.vector3d(0,-1.3,0.0)
            sceneWidth: 1.0
            sceneHeight: 1.0
            imageWidth: 50
            imageHeight: 50
            showFrame: true
        }
    }

    Slider{
        id: lightSlider
        scale: 0.3
        position: Qt.vector3d(1.6,-1.0,0.0)
        transform: [
            Rotation3D {angle: 45; axis: Qt.vector3d(0,0,1)}
        ]
        isEnabled: false

        property var light3: GlobalLight.GlobalLightDefinition.lightEntries[3];

        onEnabled: {
            //do something
            raiseLight.start();
        }

        onDisabled: {
            //do something
            lowerLight.start();
        }

        NumberAnimation{
            id: raiseLight
            target: lightSlider.light3
            property: "position.z"
            to: 4
        }

        NumberAnimation{
            id: lowerLight
            target: lightSlider.light3
            property: "position.z"
            to: 1
        }
    }

    Item3D{
        position: Qt.vector3d(-2.5,0.5,0.1)
        scale:0.8
        transform: [
            Rotation3D{axis: Qt.vector3d(0,0,1); angle: -45 }
        ]

        FlatButton{
            scale: 0.4
            position: Qt.vector3d(0.0,-0.55,0.0);

            onPushed: {
                naEnabled.start()
            }

            onReleased: {
                naDisabled.start()
            }
        }

        Label {
            sceneWidth: 0.8
            sceneHeight: 0.2
            id:buttonlabel
            text: "Button"
            fontColor: "black"
            position: Qt.vector3d(0.15,0.0,0.0)
        }

        NumberAnimation{
            id: naEnabled
            target: buttonlabel
            property: "position.z"
            to: 0.5;
        }

        NumberAnimation{
            id: naDisabled
            target: buttonlabel
            property: "position.z"
            to: 0.0;
        }
    }
}
