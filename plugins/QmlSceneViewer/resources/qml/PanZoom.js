var panStep = 40,
	zoomInFactor = 1.2,
	zoomOutFactor = 1 / zoomInFactor;

function panContentLeft() {
	viewTranslate.x -= panStep;
}

function panContentRight() {
	viewTranslate.x += panStep;
}

function panContentUp() {
	viewTranslate.y -= panStep;
}

function panContentDown() {
	viewTranslate.y += panStep;
}

function zoomOut() {
	zoomToPixelsPerMillimeter(viewScale.xScale * zoomOutFactor, viewScale.yScale * zoomOutFactor)
}

function zoomIn() {
	zoomToPixelsPerMillimeter(viewScale.xScale * zoomInFactor, viewScale.yScale * zoomInFactor)
}

function zoomToPixelsPerMillimeter(newPixelsPerMillimeterX, newPixelsPerMillimeterY) {

	var oldXDistance =  (background.width/2 - (viewTranslate.x * viewScale.xScale));
	var oldYDistance =  (background.height/2 - (viewTranslate.y * viewScale.yScale));

	var scaleFactorX = newPixelsPerMillimeterX / viewScale.xScale;
	var scaleFactorY = newPixelsPerMillimeterY / viewScale.yScale;

	viewScale.xScale = newPixelsPerMillimeterX;
	viewScale.yScale = newPixelsPerMillimeterY;

	viewTranslate.x = (background.width/2 - oldXDistance * scaleFactorX) / viewScale.xScale;
	viewTranslate.y = (background.height/2 - oldYDistance * scaleFactorY) / viewScale.yScale;
}

function fitToScreen() {
	var yScale = background.height / contentToBeMoved.height;
	var xScale = background.width / contentToBeMoved.width;

	var scale;
	if (yScale < xScale)
		scale = yScale;
	else
		scale = xScale;

	var pixelDensityRatio = 1;
	if(background.height == 2400 && background.width == 4096) {
		pixelDensityRatio = 1.017730496453901;
	}

	viewScale.xScale = scale * pixelDensityRatio;
	viewScale.yScale = scale;
}

function alignTopLeft() {
	viewTranslate.x=0;
	viewTranslate.y=0;
}
