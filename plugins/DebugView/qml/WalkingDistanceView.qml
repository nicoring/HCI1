import QtQuick 2.0
import mtq.utils 1.0
import mtq.skeletons 1.0

BasicRealWorldShaderView {

	BoneAdapter {
	   id: footLeft
	   username: parent.username
	   type: BoneType.FOOT_LEFT
	}
	BoneAdapter {
	   id: footRight
	   username: parent.username
	   type: BoneType.FOOT_RIGHT
	}
	BoneAdapter {
	   id: thighLeft
	   username: parent.username
	   type: BoneType.THIGH_LEFT
	}
	QmlValueReceiver {
		id: receiver
		key: parent.parameterKey
	}

	property vector3d hipPos: thighLeft.startPosition; //no difference between thighLeft and thighRight startPos
	property vector3d footLeftPos: footLeft.endPosition;
	property vector3d footRightPos: footRight.endPosition;
	property string parameterKey: "wdView.parameterWalk"
	property real parameterWalk: receiver.value

	fragmentShader:
	"
		varying lowp vec2 coord;
		uniform lowp float qt_Opacity;
		uniform lowp vec3 hipPos;
		uniform lowp vec3 footLeftPos;
		uniform lowp vec3 footRightPos;
		uniform lowp float parameterWalk;

//		vec4 wdTextureCoord(){
//			float leftFootDistance = distance(coord,footLeftPos.xy)/2000;
//			float rightFootDistance = distance(coord,footRightPos.xy)/2000;
//			float footDistance = min(leftFootDistance, rightFootDistance);

//			float walkingCosts = clamp((1-footDistance)+0.5-min(0.5,max(0,(1-hipPos.z/1300)))-0.2,0.1,1);
//			return vec4(0,2*parameterWalk*walkingCosts,0, 1.0) * qt_Opacity;
//		}
		vec4 wdTextureCoord(){
			float footDistance = distance(coord,hipPos.xy)/2000;
			float walkingCosts = clamp((1-footDistance)+0.5*(0.4-min(0.4,max(0,(1-hipPos.z/1300)))-0.2),0.1,1);
			return vec4(0,2*parameterWalk*walkingCosts,0, 1.0) * qt_Opacity;
		}

		void main() {
			gl_FragColor = wdTextureCoord();
		}
	"
}
