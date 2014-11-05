import QtQuick 2.0
import mtq.core 1.0
import mtq.utils 1.0
import mtq.layout 1.0
import mtq.skeletons 1.0
import "../DebugView"

Item {
	objectName: "User"
	property string userName
	property string layoutKeySequence
	property string focusKeySequence
	anchors.fill: parent



		QmlPolygonViewer {
			id: sourcePolygonViewer
			objectName: "sourcePolygonViewer"
			color: "red"
			visible: false
		}

		QmlPolygonViewer {
			id: destinationPolygonViewer
			objectName: "destinationPolygonViewer"
			color: "green"
			visible: false
		}

		QmlTransformationViewer {
			id: transformationViewer
			objectName: "transformationViewer"
			scale: 2
			gridSize: 100/scale
			height: parent.height/scale
			width: parent.width/scale
			x: parent.width/(scale*2)
			y: parent.height/(scale*2)
			visible: false
		}

		QmlShortcut {
			key: "p"
			onActivated: {
				sourcePolygonViewer.visible = !(sourcePolygonViewer.visible);
				destinationPolygonViewer.visible = sourcePolygonViewer.visible;
			}
		}

		QmlShortcut {
			key: "m"
			onActivated: {
				transformationViewer.visible = !(transformationViewer.visible);
			}
		}

		QmlShortcut {
			key: layoutKeySequence
			blockRepetitions: true
			onActivated: {
				parent.setUserLayouting(true, userName);
			}
			onReleased: {
				parent.setUserLayouting(false, userName);
			}
		}

		QmlShortcut {
			key: focusKeySequence
			blockRepetitions: true
			onActivated: {
				parent.setUserFocusing(true, userName);
			}
			onReleased: {
				parent.setUserFocusing(false, userName);
			}
		}
}
