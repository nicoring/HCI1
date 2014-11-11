import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import QtQuick.Window 2.1
import mtq.qml3d 1.0

Item{
    property var mtqIntegrator: null;
    property int lastContactId: 1000;

    id: debuglayer

    function generateShoe(){
        var childComponent= Qt.createComponent("DebugShoe.qml");

         if (childComponent.status == Component.Ready){
             var shoe = childComponent.createObject(debuglayer, {contactId: lastContactId, x:shoeAddButton.x, y: shoeAddButton.y + 100});
             lastContactId++;

             if (lastContactId % 2 == 0){
                 shoe.isLeftShoe = true;
             } else {
                 shoe.isLeftShoe = false;
             }

             shoe.tap.connect(debugTap);
             shoe.contactDown.connect(contactDown);
             shoe.contactUp.connect(contactUp);                         

             contactDown(shoe.contactId, shoe.x, shoe.y);
         } else {
             console.log("Could not create shoe: " + childComponent.errorString());
         }
    }

    function debugTap(contactId, x, y){
        mtqIntegrator.setDebugContactTap(contactId, Qt.point(x,y));
    }

    function contactDown(contactId, x, y){
        mtqIntegrator.setDebugContactDown(contactId, Qt.point(x,y));
    }

    function contactUp(contactId, x, y){
        mtqIntegrator.setDebugContactUp(contactId, Qt.point(x,y));
    }

    Image{
        source: "buttonAddShoe.png"
        id: shoeAddButton

        MouseArea{
            anchors.fill: parent
            drag.target: shoeAddButton
            drag.axis: Drag.XandYAxis

            onClicked: {
                generateShoe();
            }
        }
    }
}
