import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0

Item3D{
    property list<Item3D> radioButtons
    signal selectionChanged(var item)

    Component.onCompleted:{
        for (var i=0; i<radioButtons.length; i++){
            radioButtons[i].contact.connect(function(item){
                enableRadioButton(item);
                selectionChanged(item);
            });
        }
    }

    function enableRadioButton(item){
        //disable all but this item
        for (var i=0; i<radioButtons.length; i++){
            radioButtons[i].radioActive = false;
        }
        item.radioActive = true;
    }
}
