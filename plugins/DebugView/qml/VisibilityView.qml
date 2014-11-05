import QtQuick 2.0
import mtq.utils 1.0
import mtq.skeletons 1.0

BasicRealWorldShaderView {

	BoneAdapter {
		id: shoulderLeft
		username: parent.username
		type: BoneType.SHOULDER_LEFT
	}

	BoneAdapter {
		id: shoulderRight
		username: parent.username
		type: BoneType.SHOULDER_RIGHT
	}

	BoneAdapter {
		id: head
		username: parent.username
		type: BoneType.HEAD
	}

	QmlValueReceiver {
		id: receiver
		key: parent.parameterKey
	}

	property vector3d midShoulderPos: shoulderLeft.startPosition
	property vector3d shoulderAxis: shoulderLeft.endPosition.minus(Qt.vector3d(midShoulderPos.normalized().x, midShoulderPos.normalized().y, 0))
	property vector3d shoulderDir: head.rotateVectorAxisAngle(shoulderAxis, Qt.vector3d(0.0,0.0,1.0), 90) //rotate shoudlerAxis around z-axis, so the vector points to the front

	property string parameterKey: "visView.parameterShoulder"
	property real parameterShoulder: receiver.value //higher value -> smaller field

	fragmentShader:
				"
				uniform lowp vec3 midShoulderPos;
				uniform lowp vec3 shoulderDir;
				varying lowp vec2 coord;
				uniform lowp float parameterShoulder;

				vec4 visTextureCoord(){
					lowp float dotproduct;
					lowp float alphaShoulders;

					lowp vec3 Coords3D = vec3(coord, 0.0);
					lowp vec3 shoulderDirNormalized = normalize(shoulderDir);
					lowp vec3 shouldersToPoint = normalize(Coords3D-midShoulderPos);

					dotproduct = (dot(shouldersToPoint, shoulderDirNormalized));
					alphaShoulders = (degrees(acos(dotproduct))/180)*-1+1;		//inverted

					lowp float shoulderField = smoothstep(parameterShoulder-0.5, 1.0, alphaShoulders);
					return vec4(shoulderField, 0., 0., 1.);
				}
				void main() {
					gl_FragColor = visTextureCoord();
				}"


}

