import QtQuick 2.0
import mtq.utils 1.0
import mtq.skeletons 1.0

BasicRealWorldShaderView {

	BoneAdapter {
	   id: head
	   username: parent.username
	   type: BoneType.HEAD
	}
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

	QmlValueReceiver {
		id: receiverVisMixed
		key: parent.thresholdVisMixedKey
	}

	QmlValueReceiver {
		id: receiverVis
		key: parent.parameterVisKey
	}

	//lb
	property vector3d headPos: head.endPosition;

	//vis
	property vector3d midShoulderPos: shoulderLeft.startPosition;
	property vector3d shoulderAxis: shoulderLeft.endPosition.minus(shoulderRight.endPosition).normalized().minus(Qt.vector3d(0,0, shoulderLeft.endPosition.minus(shoulderRight.endPosition).normalized().z));
	property vector3d shoulderDir: head.rotateVectorAxisAngle(shoulderAxis, Qt.vector3d(0.0,0.0,1.0), 90); //rotate shoudlerAxis around z-axis, so the vector points to the front
	property string parameterVisKey: "visView.parameterShoulder"
	property real parameterShoulder: receiverVis.value //higher value -> smaller field

	property string thresholdVisMixedKey: "mixShaderVis.threshold"
	property real thresholdVisMixed: receiverVisMixed.value

	fragmentShader: "
		varying lowp vec2 coord;
		uniform lowp float qt_Opacity;
		uniform lowp float thresholdVisMixed;

		//lb
		uniform lowp vec3 headPos;

		//vis
		uniform lowp vec3 midShoulderPos;
		uniform lowp vec3 shoulderDir;
		uniform lowp float parameterShoulder;

		//lb
		vec4 lbTextureCoord(){
			float legibility = 1-((distance(vec3(coord,0),headPos)-1000)/2000);
			return vec4(pow(legibility,2.),0,0, 1.0) * qt_Opacity;
		}

		//vis
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
		vec4 mixedVisTextureCoord(){
			lowp float vis = visTextureCoord().r;
			lowp float lb = lbTextureCoord().r;
			lowp float combined = vis * lb;
			return vec4(step(thresholdVisMixed, combined), 0.0, 0.0, 1.0) * qt_Opacity;
			//return vec4( combined, 0.0, 0.0, 1.0) * qt_Opacity;
		}
		void main() {
			gl_FragColor = mixedVisTextureCoord();
		}"

}

