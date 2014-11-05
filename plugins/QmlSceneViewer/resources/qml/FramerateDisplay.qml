import QtQuick 2.0

Rectangle {
	id: framerate
	color: "navy"
	x: 0
	y: 0
	width: 200
	height: 100
	property var lines: []

	Text {
		id: frameRateText
		x: 0
		y: 0
		width: parent.width - 3
		height: 12
		horizontalAlignment: Text.AlignRight
		verticalAlignment: Text.AlignVCenter
		text: "FPS"
		font.pointSize: 7
		color: "cyan"
	}

	Text {
		id: frameTimeText
		x: 0
		y: 12
		width: parent.width - 3
		height: 12
		horizontalAlignment: Text.AlignRight
		verticalAlignment: Text.AlignVCenter
		text: "ms"
		font.pointSize: 7
		color: "cyan"
	}

	Text {
		id: renderTimeText
		x: 0
		y: 24
		width: parent.width - 3
		height: 12
		horizontalAlignment: Text.AlignRight
		verticalAlignment: Text.AlignVCenter
		text: "ms"
		font.pointSize: 7
		color: "cyan"
	}

	Component.onCompleted: {
		for(var i = 0; i < width; i++) {
			lines.push(Qt.createQmlObject('import QtQuick 2.0; Rectangle { x: ' + i + '; y: 100; height: 0; width: 1; transformOrigin: Item.TopRight; rotation: 180; color: "cyan" }', framerate, 'line' + i));
		}
	}

	Timer {
		interval: 1000
		repeat: true
		running: true
		onTriggered: {
			for(var i = 0; i < width-1; i++) {
				lines[i].height = lines[i+1].height
			}
			lines[width-1].height = root.framerate;
			frameRateText.text = root.frameRate + " FPS";
			frameTimeText.text = root.frameTime + " ms";
			renderTimeText.text = root.renderTime + " ms";
		}
	}
}
