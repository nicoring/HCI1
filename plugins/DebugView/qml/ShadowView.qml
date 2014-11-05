import QtQuick 2.0

Image {
	Timer {
		interval: 70; running: parent.visible; repeat: true
		onTriggered: {
		   var oP;
		   oP = parent.source;
		   parent.source = "";
		   parent.source = oP;
		}
	}
	source: "../../PaperApp/tempCapturedShadowFrame_0.jpg"
	cache: false
	x: -6
	y: -9
	opacity: 1.0
	transform: Scale { origin.x: 0; origin.y: 100; xScale: 6.5; yScale: 6.5}
}
