 Qt.include("../QmlSceneViewer/Factory.js")

function createDocuments(number, numberOffset,
						 width, height, offsetX, offsetY,
						 style, filetype, parent_, layoutScene)
{
	for(var i = 1; i <= number; i++) {
		var document = createObject("Document", parent_, {
			"width": 200,
			"filepath": "file:///Z:/assets/documents/" + style +
						"/" + (i + numberOffset) + "." + filetype,
			"rotation": Math.random()*360,
			"layoutScene": layoutScene
		});
		document.z = i;
		document.centerX = Math.random()*(width-document.width) + offsetX;
		document.centerY = Math.random()*(height-document.height) + offsetY;
	}
}

//http://stackoverflow.com/questions/6274339/how-can-i-shuffle-an-array-in-javascript

function shuffleArray(o)
{
	for(var j, x, i = o.length; i; j = Math.floor(Math.random() * i), x = o[--i], o[i] = o[j], o[j] = x);
	return o;
}

function createPileOfDocuments(prefix, styles, filetype, x, y, width, baseRotation, parent_, layoutScene)
{
	var filenames = []

	for(var style in styles) {
		for(var i = 1; i <= styles[style]; i++) {
			filenames.push("file:///Z:/assets/documents/"
						   + prefix + "/" + style + "/" + style + i
						   + "." + filetype);
		}
	}

	var shuffledFilenames = shuffleArray(filenames);

	for (var z = 0; z < shuffledFilenames.length; z++) {
		var document = createObject("Document", parent_, {

			"width": width,
			"filepath": shuffledFilenames[z],
			"rotation": baseRotation - 10 + Math.random()*20,
			"layoutScene": layoutScene
		});
		document.z = z;
		document.centerX = x - 25 + Math.random()*50;
		document.centerY = x - 25 + Math.random()*50;
	}
}

function createDocumentByKnownProperties(parent_, filepath, rotation,
										 z, x, y, layoutScene) {
	var document = createObject("Document", parent_, {
		"width": 200,
		"filepath": filepath,
		"rotation": rotation,
		"layoutScene": layoutScene

	});
	document.z = z;
	document.centerX = x;
	document.centerY = y;
}

function createDocumentCluster(numberCluster, numberDocuments,
							   width, height, widthCluster, heightCluster,
							   style, filetype, parent_, layoutScene)
{
	for(var i = 0; i < numberCluster; i++) {
		var offsetX = Math.random()*(width-widthCluster);
		var offsetY = Math.random()*(height-heightCluster);
		createDocuments(numberDocuments, i*numberDocuments,
						widthCluster, heightCluster,
						offsetX, offsetY,
						style, filetype, parent_, layoutScene);
	}
}
