import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0

Item3D {
    property real menuWidth: 0.3
    property list<Item3D> menuItems
    property int selectedIndex: 0
    property real spaceInBetweenArrows: 1.3

    signal selectionChanged(Item3D selectedItem)

    Item{
        id: internalData
        property int selectedIndex:0

        function moveRight(){
            if (selectedIndex == parent.menuItems.length-1){
                return;
            }

            if (outToLeft.running){
                outToLeft.complete();
                inFromRight.complete();
            }

            var currentItem = parent.menuItems[selectedIndex];
            var nextItem = parent.menuItems[selectedIndex+1]

            //make both visible and trigger animation
            currentItem.enabled = true;
            nextItem.enabled = true;

            inFromRight.target = nextItem;
            outToLeft.target = currentItem;

            inFromRight.start();
            outToLeft.start();

            selectedIndex++;
            parent.selectedIndex++;
        }

        function moveLeft(){
            if (selectedIndex <= 0){
                return;
            }

            if (inFromLeft.running){
                inFromLeft.complete();
                outToRight.complete();
            }

            //make both visible and trigger animation
            var currentItem = parent.menuItems[selectedIndex];
            var prevItem = parent.menuItems[selectedIndex-1]

            currentItem.enabled = true;
            prevItem.enabled = true;

            inFromLeft.target = prevItem;
            outToRight.target = currentItem;

            inFromLeft.start();
            outToRight.start();

            selectedIndex--;
            parent.selectedIndex--;
        }
    }

    Vector3dAnimation{
        id: inFromRight
        property: "position"
        duration: 300
        from: Qt.vector3d(1.5,0,-1.5)
        to: Qt.vector3d(0,0,0)
    }

    Vector3dAnimation{
        id: inFromLeft
        property: "position"
        duration: 300
        from: Qt.vector3d(-1.5,0,-1.5)
        to: Qt.vector3d(0,0,0)
    }

    Vector3dAnimation{
        id: outToLeft
        property: "position"
        duration:300
        from: Qt.vector3d(0,0,0)
        to: Qt.vector3d(-1.5,0,-1.5)

        onRunningChanged:{
            //Hide target when animation finished
            if (running == false){
                target.enabled = false;
            }
        }
    }

    Vector3dAnimation{
        id: outToRight
        property: "position"
        duration: 300
        from: Qt.vector3d(0,0,0)
        to: Qt.vector3d(1.5,0,-1.5)

        onRunningChanged:{
            //Hide target when animation finished
            if (running == false){
                target.enabled = false;
            }
        }
    }

    id: mainItem

    function clickLeft(){
        console.log("ClickThroughMenu clicked left");
        internalData.moveLeft();
        selectionChanged(menuItems[internalData.selectedIndex]);
    }

    function clickRight(){
        console.log("ClickThroughMenu clicked right");
        internalData.moveRight();
        selectionChanged(menuItems[internalData.selectedIndex]);
    }

    Component.onCompleted: {
        //make all menuItems childs of this item and invisible
        for (var i=0; i < menuItems.length; i++){
            var obj = menuItems[i];
            obj.enabled = false;
        }

        //except first item
        if (menuItems.length > 0){
            menuItems[0].enabled = true;
        }
    }

    onSelectedIndexChanged:{
        var newIndex = selectedIndex;
        if (newIndex < 0)
            newIndex = 0;
        if (newIndex > menuItems.length)
            newIndex = menuItems.length - 1;

        while(newIndex > internalData.selectedIndex){
            internalData.moveRight();
        }
        while(newIndex < internalData.selectedIndex){
            internalData.moveLeft();
        }
        selectedIndex = newIndex;
    }

    Item3D{
        id: buttonRight
        scale: 0.5
        position: Qt.vector3d((spaceInBetweenArrows/2.0),0,0)
        mesh: Mesh { source: "qrc:/models/framework/arrow.3ds" }
        effect: LightShader{}
        function mtqTap(id,position){
            parent.clickRight();
        }
    }

    Item3D{
        id: buttonLeft
        scale: 0.5
        position: Qt.vector3d(-1.0 * (spaceInBetweenArrows/2.0),0,0.0)
        transform:Rotation3D{
            angle: 180
            axis: Qt.vector3d(0,1,0)
        }

        mesh: Mesh { source: "qrc:/models/framework/arrow.3ds" }
        effect: LightShader{}
        function mtqTap(id,position){
            parent.clickLeft();
        }
    }
}
