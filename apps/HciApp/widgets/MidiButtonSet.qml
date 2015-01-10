import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import mtq.qml3d 1.0
import QtQuick.Window 2.1
import "../framework/GlobalLight.js" as GlobalLight
import "../framework"
import "."
import "buttonset.js" as ButtonSettings

Item3D {
    id: buttonset

    property int player_id
    property MidiInterface midiInterface
//    property var settings

    /*********************
     * initialize buttonset
     * --> show 'come here' label
     * --> on over, tag as active
     *     -> show menu buttons
     * --> on out and longer than time threshold
     *     -> show 'come here' label
     *     -> resume button which loads previous settings
     */

//    function showResumeStartScreen() {

//    }

    /**
     * rotate oriented items towards scene center
     */
//    function rotateObjectTowardsCenter(object, parent) {
//        console.log(floorScene.position);
//        var globalObjectCoords = floorScene.mapToItem(object, object.position.x, object.position.y);
//        var globalObjectVector = Qt.vector3d(globalObjectCoords.x, globalObjectCoords.y, 0);


//        var vectorToCenter = Qt.vector3d(0,0,0).minus(globalObjectVector);
//        console.log(player_id, vectorToCenter);
//        var vectorObjectOrienation = Qt.vector3d(0,1,0); // TODO: apply rotation of object

//        var dot = vectorToCenter.dotProduct(vectorObjectOrienation);
//        var rad = Math.acos( dot / (vectorToCenter.length() * vectorObjectOrienation.length()) );
//        var deg = rad / Math.PI * 360;

//        object.transform[0].angle = deg;
//    }

//    Component.onCompleted: {
//        rotateObjectTowardsCenter(menubuttons, buttonset);

//       settings = new ButtonSettings.ButtonsetSettings(buttonset);
//       settings.showStartScreen();
//    }

    /** labels **/

//    property alias startLabel: startLabel
//    Item3D {
//        id: startLabel
//        enabled: true

//        Label {
//            text: "Come here"
//            fontSize: 60
//            sceneWidth: 3
//            sceneHeight: 3
//            fontColor: "black"
//            position: Qt.vector3d(0.7,-0.5,0)
//        }

//        Label {
//            text: "\nto start!"
//            fontSize: 60
//            sceneWidth: 3
//            sceneHeight: 3
//            fontColor: "black"
//            position: Qt.vector3d(1,-0.5,0)
//        }
//    }

    /** menu buttons **/

//    property alias instrumentButtons: menubuttons
//    Item3D {
//        id: menubuttons
//        enabled: true

//        position: Qt.vector3d(0.5, 0.5, 0)
//        transform: Rotation3D {
//            angle: 0
//            axis: Qt.vector3d(0,0,1)
//        }


//        FlatButton {

//            Label {
//                text: "Floor"
//                fontSize: 50
//                fontColor: "black"
//                position: Qt.vector3d(0.1, -0.2, 0)
//            }

//            Label {
//                text: "Instrument"
//                fontSize: 50
//                fontColor: "black"
//                position: Qt.vector3d(0.2, -0.5, 0)
//                sceneWidth: 2
//            }
//        }
//    }

    /** keyboard buttons **/

    Item3D {
        id: midibuttons
        enabled: true

        MidiButton {
            id: btn1

            button_id: 1
            player_id: buttonset.player_id
            midiInterface: buttonset.midiInterface

            position: Qt.vector3d(0,0,0)
        }

        MidiButton {
            id: btn2

            button_id: 2
            player_id: buttonset.player_id
            midiInterface: buttonset.midiInterface

            position: Qt.vector3d(1.1, 0, 0)
        }

        MidiButton {
            id: btn3

            button_id: 3
            player_id: buttonset.player_id
            midiInterface: buttonset.midiInterface

            position: Qt.vector3d(0, 1.1, 0)
        }

        MidiButton {
            id: btn4

            button_id: 4
            player_id: buttonset.player_id
            midiInterface: buttonset.midiInterface

            position: Qt.vector3d(1.1, 1.1, 0)
        }
    }
}
