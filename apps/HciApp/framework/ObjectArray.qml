import QtQuick 2.0
import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0

Item3D{
    id: arrayGenerator
    property string qmlCode: ""
    property string qmlFile: ""
    property int repetitions: 0

    property string mode: "incremental"

    //if mode is incremental, use this
    property vector3d translationPerRepetition: Qt.vector3d(0,0,0)
    //if mode is list, use this
    //property list<var> positionList
    //if mode is random, be random
    //ToDo

    Component.onCompleted: {
        var objects = [];

        for (var i = 0; i < repetitions; i++){
            var obj = generateObject();

            if (mode == "incremental"){
                assignIncremental(i, obj);
            } else if (mode == "list"){
                assignList(i, obj);
            } else if (mode == "random") {
                assignRandom(i,obj);
            } else {
                console.log("Illegal ObjectArray mode '" + mode + "'");
                return;
            }

            objects[i] = obj;
        }

        //call the function arraygen if it exists, to let the object do further refinements
        for (var i=0; i < repetitions; i++){
            if (objects[i].arraygen){
                objects[i].arraygen(i);
            }
        }

    }

    function assignIncremental(i, obj){
        var addTranslation = translationPerRepetition.times(i);
        obj.position = obj.position.plus(addTranslation);
    }

    function assignList(i, obj){

    }

    function assignRandom(i, obj){

    }

    function generateObject(){
        if (qmlCode.length > 0){
            return Qt.createQmlObject(qmlCode,arrayGenerator,"dynamicSnippet");
        } else {
            var component = Qt.createComponent(qmlFile);
            if (component.status == Component.Ready)  {
                return component.createObject(arrayGenerator);
            } else {
                console.log("Error creating the QML Component (ObjectArray): " + component.errorString());
                return null;
            }
        }
    }
}
