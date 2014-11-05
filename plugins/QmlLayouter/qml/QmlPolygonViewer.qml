import QtQuick 2.0
import "../QmlSceneViewer/Factory.js" as Factory


Item {

	property var lines: []
	property var circles: []
	property int usedLines: 0
	property color color: "black"
	property int lineThickness: 7
	property int cornerMarkerDiameter: 30

	property variant polygon

	onPolygonChanged: {
		//A lot of testing happens in case the number of lines of a polygon changes

		function setLine(i) {
			lines[i].x1 = polygon[i].x;
			lines[i].y1 = polygon[i].y;
			lines[i].x2 = polygon[(i+1) % (polygon.length)].x;
			lines[i].y2 = polygon[(i+1) % (polygon.length)].y;
			lines[i].height = lineThickness;
			lines[i].color = color;
			lines[i].visible = true;
		}

		function setCircle(i) {
			circles[i].x = polygon[i].x-cornerMarkerDiameter/2;
			circles[i].y = polygon[i].y-cornerMarkerDiameter/2;
			circles[i].height = cornerMarkerDiameter;
			circles[i].width = cornerMarkerDiameter;
			circles[i].color = color;
			circles[i].z = polygon.length + i;
			circles[i].visible = true;
		}

		for(var i = 0; i < polygon.length; i++) {

			//First part: create Objects we don’t have stored yet
			if (typeof lines[i] == 'undefined' || lines[i] == null) {
				lines[i] = Factory.createObject("../QmlLayouter/Line", this, {});
				circles[i] = Factory.createObject("../QmlLayouter/Circle", this, {});
			}
			//Second part: change properties of lines we already have, and are still used in the new polygon
			setLine(i);
			setCircle(i);
		}
		if(polygon.length > 1) {
			circles[0].color = "#777";
			circles[1].color = "white";
		}

		//discard old lines beyond the now used ones
		usedLines = polygon.length;
		for(var i = usedLines; i < lines.length; i++) {
			lines[i].visible = false;
			circles[i].visible = false;
		}


	}
}
