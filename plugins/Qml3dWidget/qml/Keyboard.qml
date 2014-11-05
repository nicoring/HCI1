import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import mtq.qml3d 1.0
import "KeyCache.js" as Cache

Item3D{
    id: keyboard

    property real horizontalKeySpacing: 0.6
    property real verticalKeySpacing: -0.6
    property real oddRowOffset: 0.25

    signal key(string c)

    Item{
        id: internalData
        property variant keyRows: ["0123456789", "qwertzuiop", "asdfghjkl", "yxcvbnm^"]
        property bool currentlyUpperCase: false
    }

    Component.onCompleted: {
        //Create Keys
        var keycomp = Qt.createComponent("KeyboardKey.qml");
        if (keycomp.status != Component.Ready){
            console.log("Error: KeyboardKey.qml component not ready");
            return;
        }

        Cache.initCache();

        for (var row = 0; row < internalData.keyRows.length; row++){
            var currentRow = internalData.keyRows[row];

            var startOffset = 0.0;
            if (row % 2 == 1){
                startOffset = keyboard.oddRowOffset;
            }

            for (var i=0; i<currentRow.length;i++){
                var key = keycomp.createObject(keyboard, {});
                key.position = Qt.vector3d(startOffset + i*horizontalKeySpacing,row*verticalKeySpacing,0.0);
                key.scale = 0.5;
                key.character = currentRow[i];
                key.pressed.connect(keyPressed);
                Cache.addKey(key);
            }
        }
    }

    function keyPressed(c){
        if (c == "^"){
            if (internalData.currentlyUpperCase){
                internalData.currentlyUpperCase = false;
                Cache.setUpperCase(false);
            } else {
                internalData.currentlyUpperCase = true;
                Cache.setUpperCase(true);
            }
        } else {
            //Disable upper cases after one keystroke
            if (internalData.currentlyUpperCase){
                internalData.currentlyUpperCase = false;
                Cache.setUpperCase(false);
            }

            key(c)
        }
    }   
}
