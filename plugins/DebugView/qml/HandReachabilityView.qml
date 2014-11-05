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
		id: thighLeft
		username: parent.username
		type: BoneType.THIGH_LEFT
	}

	BoneAdapter {
		id: thighRight
		username: parent.username
		type: BoneType.THIGH_RIGHT
	}

	QmlValueReceiver {
		id: receiver
		key: parent.parameterKey
	}

	property vector3d shoulderLeftPos: shoulderLeft.endPosition
	property vector3d shoulderRightPos: shoulderRight.endPosition
	property vector3d midShoulderPos: shoulderLeft.startPosition
	property vector3d thighAxis: thighLeft.endPosition.minus(thighRight.endPosition)

	property string parameterKey: "hrView.parameterHand"
	property real parameterHand: receiver.value

	fragmentShader:
	"		   varying lowp vec2 coord;
				uniform lowp float qt_Opacity;
				uniform lowp vec3 shoulderLeftPos;
				uniform lowp vec3 shoulderRightPos;
				uniform lowp vec3 midShoulderPos;
				uniform lowp vec3 thighAxis;
				uniform lowp float parameterHand;
				vec4 hrTextureCoord(){
					float leftShoulderDistance = clamp(distance(vec3(coord,0),vec3(shoulderLeftPos.xy,midShoulderPos.z))/1800,0,1.1);
					float rightShoulderDistance = clamp(distance(vec3(coord,0),vec3(shoulderRightPos.xy,midShoulderPos.z))/1800,0,1.1);
					float handReachabilityWithZ = mix(0,max(1-leftShoulderDistance, 1-rightShoulderDistance),step(parameterHand,max(1-leftShoulderDistance, 1-rightShoulderDistance)));
					handReachabilityWithZ = 1.7*handReachabilityWithZ*handReachabilityWithZ;
					float leftShoulderDistanceXY = distance(coord,shoulderLeftPos.xy)/1800;
					float rightShoulderDistanceXY = distance(coord,shoulderRightPos.xy)/1800;
					float handReachabilityWithoutZ = 0.5 * mix(0,max(1-leftShoulderDistanceXY, 1-rightShoulderDistanceXY),step(parameterHand+0.1,max(1-leftShoulderDistanceXY, 1-rightShoulderDistanceXY)));
					float handReachabilityMixed = max(handReachabilityWithZ,handReachabilityWithoutZ);
					return vec4(0,handReachabilityMixed*handReachabilityMixed,0, 1.0) * qt_Opacity;
				}
				void main() {
					gl_FragColor = hrTextureCoord();
				}
	 "
}
