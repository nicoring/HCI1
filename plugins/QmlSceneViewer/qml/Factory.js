var components = {};

function init(componentName)
{
	var component = Qt.createComponent(componentName + ".qml");
	if (component.status != Component.Ready) {
		console.log("[QmlFactory]: Error loading " + componentName + ": " +
					component.errorString());
	}
	components[componentName] = component;
}

function createObject(componentName, parent_, properties)
{
	if(!components[componentName]) {
		init(componentName);
	}

	if(components[componentName].status == Component.Ready) {
		var object = components[componentName].createObject(parent_, properties);
		if (object == null) {
			console.log("[QmlFactory]: Error creating " + componentName + ".");
		}
		return object;
	} else {
		console.log("[QmlFactory]: Component for " + componentName + " not ready: ",
					components[componentName].errorString());
	}
}
