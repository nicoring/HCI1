import QtQuick 2.0

//use directly as a child of an QmlLayoutObject
Item {

	anchors.fill: parent
	opacity: 0.5
	Rectangle {
		id: visBar
		color: "red"
		anchors.left: parent.left
		anchors.right: parent.horizontalCenter
		height: parent.height *Math.max(0,parent.parent.visibility)
		anchors.bottom: parent.bottom
	}

	Rectangle {
		id: reachBar
		color: "green"
		anchors.left: parent.horizontalCenter
		anchors.right: parent.right
		height: parent.height *Math.max(0,parent.parent.reachability)
		anchors.bottom: parent.bottom
	}
}
