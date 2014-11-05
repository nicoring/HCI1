import QtQuick 2.0
import QtMultimedia 5.0
import mtq.layout 1.0
import mtq.core 1.0

QmlLayoutObject {

	property variant videoStream

	id: controlElements
	width: 800
	height: 60

	Rectangle {
		width: 130
		height: 40
		x: 0
		y: 25
		border.color: "grey"
		radius: 8
		color: "transparent"

		signal buttonClick()
		onButtonClick: videoStream.video.seek(videoStream.video.position - 5000)

		Text {
			anchors.centerIn: parent
			font.family: "webdings"
			font.pointSize: 30
			text: "7"
		}

		 QmlEventDummy {
			anchors.fill: parent
			onTap: parent.buttonClick()
		 }
	}

	Rectangle {
		property string playLabel: "4"
		property string pauseLabel: ";"

		id: playButton
		width: 130
		height: 40
		x: 140
		y: 25
		border.color: "grey"
		radius: 8
		color: "transparent"

		signal buttonClick()
		onButtonClick: {
			videoStream.thumbnail.visible = false;
			if (videoStream.video.playbackState == MediaPlayer.PlayingState)
				playButtonLabel.text = playLabel;
			else
				playButtonLabel.text = pauseLabel;

			if (videoStream.video.playbackState == MediaPlayer.PlayingState)
				videoStream.video.pause();
			else
				videoStream.video.play();
		}

		Text {
			id: playButtonLabel
			anchors.centerIn: parent
			font.family: "webdings"
			font.pointSize: 30
			text: parent.playLabel
		}

		 QmlEventDummy {
			anchors.fill: parent
			onTap: parent.buttonClick()
		 }
	}



	Rectangle {
		width: 130
		height: 40
		x: 280
		y: 25
		border.color: "grey"
		radius: 8
		color: "transparent"

		signal buttonClick()
		onButtonClick: {
			videoStream.video.seek(videoStream.video.position + 5000)
		}

		Text {
			anchors.centerIn: parent
			font.family: "webdings"
			font.pointSize: 30
			text: "8"
		}

		 QmlEventDummy {
			anchors.fill: parent
			onTap: parent.buttonClick()
		 }
	}

	Rectangle {
		width: parent.width
		height: 20
		radius: 6
		border.color: "grey"
		border.width: 6
		color: "transparent"

		Rectangle {
			id: progressBar
			y: 3
			color: "royalblue"
			radius: 6
			width: parent.width * videoStream.video.position/videoStream.video.duration
			height: parent.height - 6
		}

		QmlEventDummy {
			anchors.fill: parent
			onTap: {
				videoStream.video.seek(videoStream.video.duration * position.x/parent.width);
				progressBar.width = position.x
			}
		}

	}

	Rectangle {
		width: parent.width * 0.4
		height: 40
		x: parent.width *0.6
		y: 25
		radius: 6
		border.color: "grey"
		color: "transparent"

		Text {
			x: -35
//			anchors.centerIn: parent
			font.family: "webdings"
			font.pointSize: 30
			text: "X"
		}

		Rectangle {
			id: volumeBar
			y: 3
			x: 2
			anchors.verticalCenter: parent.verticalCenter
			color: "royalblue"
			radius: 6
			width: parent.width * videoStream.video.volume/parent.width
			height: 15
		}

		QmlEventDummy {
			anchors.fill: parent
			onTap: {
				videoStream.video.volume = position.x/parent.width;
				volumeBar.width = position.x
			}
		}
	}
}

