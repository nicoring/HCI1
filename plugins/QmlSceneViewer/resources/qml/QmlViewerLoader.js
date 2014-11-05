/*
* dynamically load a child QML into the panZoom
* taken from example code at http://qt-project.org/doc/qt-4.8/qdeclarativedynamicobjects.html
*/


var component;
var sprite;

function createChildObject(qmlPath) {
	console.log("[QML]: loading inner QML " + qmlPath);
	component = Qt.createComponent(qmlPath);
	if (component.status == Component.Ready) {
		finishCreation();
	}
	else {
		console.log("[QML]: Error creating inner QML: ");
		console.log(component.errorString());
		component.statusChanged.connect(finishCreation);
	}
}

function finishCreation() {
	if (component.status == Component.Ready) {
		sprite = component.createObject(contentToBeMoved);
		contentToBeMoved.width = sprite.width;
		contentToBeMoved.height = sprite.height;
		if (sprite == null) {
			console.log("[QML]: Error connecting inner QML to parent.");
		}
	}
}
