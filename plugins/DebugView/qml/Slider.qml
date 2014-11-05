import QtQuick 2.0
import mtq.utils 1.0

Rectangle {
	id: slider
	width: 1000; height: 40
	property real value
	property alias notifierKey: notifier.key
	color: "grey"
	x: parent.width/2 - width/2
	y: parent.height - height
	Component.onCompleted: {value =  root.globalConfig["DefaultValues"][notifierKey];}

	Text {
		text: notifierKey
		color: "white"
		font.pixelSize: 20
	}

	Rectangle {
		id: handle
		width: 40; height: 40
		color: "black"
		x: slider.value * (slider.width-handle.width)
		onXChanged: {slider.value = Math.round(handle.x/(slider.width-handle.width)*100)/100;}

		Text {
			text: slider.value
			color: "white"
			font.pixelSize: 20
		 }

		MouseArea {
			anchors.fill: parent
			drag.target: parent; drag.axis: "XAxis"
			drag.minimumX: 0; drag.maximumX: slider.width-handle.width
		}
	}

	QmlValueNotifier {
		id: notifier
		value: slider.value
	}
}
