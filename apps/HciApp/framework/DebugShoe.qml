import QtQuick 2.0

Image{
    property int contactId: 1000
    property bool isDown: true;
    property bool isTapping: false;
    property bool isLeftShoe: true;

    signal contactMove(var contactId, var x, var y, var rotation);
    signal contactDown(var contactId, var x, var y, var rotation);
    signal contactUp(var contactId, var x, var y)
    signal tap(var contactId, var x, var y);
    signal doubleTap(var contactId, var x, var y);

    source: "shoe_s.png"
    id: shoe

    property int crosshairX: 38;
    property int crosshairY: 40;
    property real rotationResolution: 22.5;

    transform:[
        Rotation{id: shoeRotation; origin.x: crosshairX; origin.y: crosshairY; angle: 0}
    ]

    Component.onCompleted: {
        //rotate randomly
        shoeRotation.angle = randomAngle()
    }

    function randomAngle(){
        return Math.min(Math.round(Math.random() * 15) * rotationResolution,360);
    }

    //The position of the crosshair
    function displayedPosition(){
        return Qt.point(shoe.x + crosshairX, shoe.y + crosshairY);
    }

    onIsLeftShoeChanged: {
        if (isLeftShoe){
            shoe.mirror = false;
        } else {
            shoe.mirror = true;
        }
    }

    onIsDownChanged: {
        var pos = displayedPosition();

        if (!shoe.isDown){
            shoe.source = "shoe_s_hover.png";
            contactUp(contactId, pos.x, pos.y);
        } else {
            shoe.source = "shoe_s.png";
            contactDown(contactId, pos.x, pos.y, shoeRotation.angle)
        }
    }

    onIsTappingChanged: {
        if (shoe.isTapping){
            shoe.source = "shoe_s_tap.png"
        } else {
            shoe.source = "shoe_s.png"
        }
    }

    MouseArea{
        id: interactionArea
        x: 0
        y: 0
        width: parent.width
        height: parent.height / 2
        drag.target: shoe
        drag.axis: Drag.XandYAxis

        onClicked: {
            var pos = shoe.displayedPosition()
            if (mouse.modifiers == Qt.ShiftModifier){
                doubleTap(shoe.contactId, pos.x,pos.y)
            } else {
                tap(shoe.contactId, pos.x,pos.y)
            }
        }

        onPressed: {
            shoe.isTapping = true;
        }

        onReleased: {
            shoe.isTapping = false;
            shoe.isDown = false;
            shoe.isDown = true;
        }

        onWheel:{
            wheel.accepted = true;
            var pos = displayedPosition();

            if (wheel.angleDelta.y > 0){
                shoeRotation.angle += rotationResolution;
                contactMove(contactId, pos.x, pos.y, shoeRotation.angle)
            } else {
                shoeRotation.angle -= rotationResolution;
                contactMove(contactId, pos.x, pos.y, shoeRotation.angle)
            }
        }
    }

    MouseArea{
        id: dragArea
        x: 0
        y: parent.height / 2
        width: parent.width
        height: parent.height / 2
        drag.target: shoe
        drag.axis: Drag.XandYAxis

        onPressed: {
            shoe.isDown = false;

            if (mouse.modifiers == Qt.ControlModifier){
                shoe.destroy();
            }
        }

        onReleased: {
            shoe.isDown = true;
        }

        onWheel:{
            wheel.accepted = true;

            if (wheel.angleDelta.y > 0){
                shoeRotation.angle += rotationResolution;
            } else {
                shoeRotation.angle -= rotationResolution;
            }
        }
    }
}
