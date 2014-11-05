import QtQuick 2.0
import QtMultimedia 5.0
import mtq.layout 1.0
import mtq.core 1.0

QmlLayoutObject {

	property alias video: video
	property alias thumbnail: thumbnail

	width: 800
	height: 600

	Video {
		id: video
		width: 800
		height: 600
		source: "file:///Z://Video Prototypes/Task User Study/Gangnam.mp4"

		Image {
			id: thumbnail
			x: 0
			y: 0
			antialiasing: true
			height: parent.height
			width: parent.width
			fillMode: Image.PreserveAspectFit
			visible: true
			source:  "file:///Z://Video Prototypes/Task User Study/Gangnam_thumbnail.jpg";
		}

		volume: 0
		focus: true
		Keys.onSpacePressed: video.playbackState == MediaPlayer.PlayingState ? video.pause() : video.play()
		Keys.onLeftPressed: video.seek(video.position - 5000)
		Keys.onRightPressed: video.seek(video.position + 5000)
	}

	QmlEventDummy {
		id: eventDummy
		anchors.fill: parent

		onTap: {
			video.play();
			thumbnail.visible = false;
		}

	}

}

