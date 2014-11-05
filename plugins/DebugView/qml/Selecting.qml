import QtQuick 2.0
import mtq.utils 1.0
import mtq.skeletons 1.0

BasicRealWorldShaderView {

	BoneAdapter {
		id: head
		username: parent.username
		type: BoneType.HEAD
	}

	QmlValueReceiver {
		id: receiverOffset
		key: parent.parameterHeadKey
	}

	QmlValueReceiver {
		id: receiverAngle
		key: parent.parameterAngleKey
	}

	property vector3d headPos: head.endPosition
	property vector3d viewDir: head.rotateVectorQuaternion(Qt.vector3d(1.0,0.0,0.0), head.rotation)

	property string parameterHeadKey: "select.parameterHead"
	property real parameterHead: receiverOffset.value

	property string parameterAngleKey: "select.parameterAngle"
	property real parameterAngle: receiverAngle.value

	fragmentShader:
				"
				uniform lowp vec3 headPos;
				uniform lowp vec3 viewDir;
				varying lowp vec2 coord;
				uniform lowp float parameterHead;
				uniform lowp float parameterAngle;

				void main() {
					lowp float dotproduct;
					lowp float alpha;
					lowp vec3 Coords3D = vec3(coord, 0.0);
					lowp vec3 viewDirNormalized = normalize(viewDir);
					lowp vec2 headPos2D = vec2(headPos.x, headPos.y);
					lowp vec2 headToPoint = normalize(coord - headPos2D);
					lowp vec2 lookingAt = headPos2D + (headPos.z/ viewDir.z) * vec2(viewDir.x, viewDir.y);	//point on the floor, user is looking at

					//eyes
					dotproduct = (dot(vec2(viewDirNormalized.x, viewDirNormalized.y), headToPoint));		// cos(alpha), alpha = angle between viewDirNormalized, headToPoint
					alpha = (degrees(acos(dotproduct)) / 180) * -1 + 1;										//inverted
					lowp float distanceToUser = distance(headPos2D,coord);
					lowp float radius = distance(lookingAt, headPos2D) + 500 * parameterHead;				//offset up to 500mm adjustable

					lowp float viewField = step(parameterAngle, alpha);
					lowp float nearDistanceviewField = step(distanceToUser, radius * viewField);
					gl_FragColor = vec4(nearDistanceviewField, 0., 0., 1.);
				}"


}

