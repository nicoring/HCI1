import QtQuick 2.0
import QtGraphicalEffects 1.0
import mtq.layout 1.0
import mtq.core 1.0
//import mtq.laser 1.0

QmlDocument {
	property string filepath;
	property point lastTapPosition
	property point tapOffset
	property var layoutScene

	id: document
	//TODO: get this from environment somehow
	debugInfoFor: "Jonathan"
	z: 0
	transformOrigin: Item.Center

//	Behavior on x { SmoothedAnimation { velocity:1000 } }
//	Behavior on y { SmoothedAnimation { velocity: 1000 } }

	onTap: {
		lastTapPosition.x = position.x;
		lastTapPosition.y = position.y;
	}

	onTapDown: {
		parent.lastDocPosition.x = position.x;
		parent.lastDocPosition.y = position.y;
		tapOffset.x = position.x - x;
		tapOffset.y = position.y - y;
		z = parent.upperLayer++;
	}

	onDoubleTap: {
		lastTapPosition.x = position.x;
		lastTapPosition.y = position.y;
		z = parent.upperLayer+parent.children.length-parent.stackCounter;
		parent.stackCounter++;
	}

	onDwell: {
		magnifierProxy.visible = true;

		var newX = width/2 - magnifierProxy.width/2;
		var newY = - 10 + position.y - magnifierProxy.height;

		magnifierProxy.y = newY;
		magnifierProxy.x = newX;
	}

	onTapUp: {
		magnifierProxy.visible = false;
	}

	Image {
		id: image
		property bool imageSizeInitialized: false;
		x: 0
		y: 0
		antialiasing: true
		width: parent.width
		fillMode: Image.PreserveAspectFit
		source: parent.filepath
		Component.onCompleted: {
			parent.height = height;
			imageSizeInitialized = true;
		}
	}

	Image {
		id: magnifierProxy
		source: image.source;
		antialiasing: true
		fillMode: Image.PreserveAspectFit
		visible: false
		transformOrigin: Item.Bottom;

		Component.onCompleted: {
			width = Math.min(width, 600);
		}

		RectangularGlow {
			z: -1
			anchors.fill: parent
			glowRadius: 3
			color: "black"
			visible: parent.visible
		}
	}

	Binding {
		target: image
		property: "height";
		value: document.height
		when: image.imageSizeInitialized
	}

	RectangularGlow {
		z: -1
		anchors.fill: parent
		glowRadius: 30
		spread: 0.1
		color: "white"
		visible: parent.selected
	}

	RectangularGlow {
		id: focusAndLayoutGlow
		z: -1
		anchors.fill: parent
		glowRadius: 15
		spread: 0.3
		color: "green"
		visible: false
	}

	Binding {
		target: focusAndLayoutGlow
		property: "visible"
		value: selectedByUser != ""
			   || layoutScene.focusingUsers.indexOf(belongingToUser) != -1
		when: typeof layoutScene != 'undefined'
	}

	RectangularGlow {
		z: -1
		anchors.fill: parent
		glowRadius: 3
		color: "black"
	}

	MouseArea {
		anchors.fill: parent
		hoverEnabled: true

		onWheel: {
			document.rotation += wheel.angleDelta.y/10;
		}

	}


	/* ENABLE WITH CARE. If you are in the same local network as the etherdream box,
	   this will control the laser.
	   Also, laser stuff is not yet in separate thread which may cause performance issues.
	*/

	//QmlLaserRectangle {screenVisible: true}


	//enable to get visibility/reachability bars on documents
	//uses DebugInfoFor:
	/*DebugInfoExtender {

	}*/
}
