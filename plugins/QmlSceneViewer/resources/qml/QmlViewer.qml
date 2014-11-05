import QtQuick 2.0
import "QmlViewerLoader.js" as QmlViewerLoader
import "PanZoom.js" as PanZoom

import mtq.core 1.0

Rectangle {
	id: background
    color: "transparent" //otherwise other widgets can't draw using OpenGL, since OpenGL is drawn before all widgets
	x: 0
	y: 0

	Timer {
		id: fitToScreenTimer
        interval: 100
		running: false
		repeat: false
        onTriggered: {
            /*PanZoom.fitToScreen(); PanZoom.alignTopLeft();*/
            contentToBeMoved.width = background.width; contentToBeMoved.height = background.height
        }
	}
	Component.onCompleted: {fitToScreenTimer.start()}

	QmlRootItem {
		id: root
		objectName: "RootItem"
		x: 0
		y: 0
		onReady: {
			var qmlPath = "file:///"+root.currentDirectory+"/"+root.localConfig["qmlFile"];
			QmlViewerLoader.createChildObject(qmlPath);
		}

		QmlPanZoomRootItem {

			/*  Do not be alarmed;
			 *	you are looking for the QML filename, which was called statically here.
			 *	It has been raised; it is not here. Look, there is the place we laid it.
			 *	But go, tell the disciples and Jakob that it is going ahead of you to a
			 *	config file parameter. There you will see it, just as we told you.
			 */

			id: contentToBeMoved
            /*Scale {
				id: viewScale;
				xScale: 1;
				yScale: 1;
				origin.x: 0
				origin.y: 0
			}
            Translate {id: viewTranslate; x: 0; y: 0}
            transform: [viewTranslate, viewScale ]*/
		}
	}

    /*FramerateDisplay {
		id: framerateDisplay
	}

	//Minimap

	Rectangle {
		id: minimapFrame
		height: contentToBeMoved.height * 0.03
		width: contentToBeMoved.width * 0.03
		x: background.width - 10 - (contentToBeMoved.width * 0.03)
		y: 10
		color: "#50aaaaaa"
		border.color: "#80ffffff"
		border.width: 2
	}

	Rectangle {
		id: minimapScreen
		height: (background.height * 0.03) / viewScale.yScale
		width: background.width * 0.03 / viewScale.xScale
		color: "#50303030"
		border.color: "#80ffffff"
		border.width: 2
		x: background.width - 10 - (contentToBeMoved.width * 0.03)
			- (viewTranslate.x * 0.03)
		y: 10
			- (viewTranslate.y * 0.03)
    }*/

    /*QmlShortcut {key: "Alt++"; onActivated: {PanZoom.zoomIn()} }
	QmlShortcut {key: "Alt+-"; onActivated: {PanZoom.zoomOut()} }
	QmlShortcut {key: "Alt+e"; onActivated: {PanZoom.zoomIn()} }
	QmlShortcut {key: "Alt+q"; onActivated: {PanZoom.zoomOut()} }
	QmlShortcut {key: "Alt+w"; onActivated: {PanZoom.panContentUp()} }
	QmlShortcut {key: "Alt+s"; onActivated: {PanZoom.panContentDown()} }
	QmlShortcut {key: "Alt+a"; onActivated: {PanZoom.panContentLeft()} }
	QmlShortcut {key: "Alt+d"; onActivated: {PanZoom.panContentRight()} }

	QmlShortcut {key: "Alt+0"; onActivated: {PanZoom.fitToScreen(); PanZoom.alignTopLeft()} }
	QmlShortcut {key: "Alt+1"; onActivated: {PanZoom.zoomToPixelsPerMillimeter(1,1); PanZoom.alignTopLeft()} }
	QmlShortcut {key: "Alt+f"; onActivated: {PanZoom.zoomToPixelsPerMillimeter(1.148, 1.13); PanZoom.alignTopLeft()} } //Floor
	QmlShortcut {key: "Alt+2"; onActivated: {PanZoom.zoomToPixelsPerMillimeter(3.61, 3.61); PanZoom.alignTopLeft()} } //Office dell p2411h screen
	QmlShortcut {key: "Alt+3"; onActivated: {PanZoom.zoomToPixelsPerMillimeter(3.87, 3.87); PanZoom.alignTopLeft()} } //Office fujitsu p20-1 screen
	QmlShortcut {key: "Alt+o"; onActivated: {PanZoom.alignTopLeft()} }

	QmlShortcut {key: "Alt+m"; onActivated: {minimapFrame.visible = !minimapFrame.visible; minimapScreen.visible = minimapFrame.visible} }

    QmlShortcut {key: "Alt+r"; onActivated: {framerateDisplay.visible = !framerateDisplay.visible} }*/
}
