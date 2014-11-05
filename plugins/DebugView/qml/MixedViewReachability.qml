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

	QmlValueReceiver {
		id: receiverReachMixed
		key: parent.thresholdReachMixedKey
	}
	QmlValueReceiver {
		id: receiverWeightWdReachMixed
		key: parent.weightWdReachMixedKey
	}
	QmlValueReceiver {
		id: receiverWeightFrReachMixed
		key: parent.weightFrReachMixedKey
	}
	QmlValueReceiver {
		id: receiverWeightHrReachMixed
		key: parent.weightHrReachMixedKey
	}
	QmlValueReceiver {
		id: receiverWd
		key: parent.parameterWalkKey
	}
	QmlValueReceiver {
		id: receiverHr
		key: parent.parameterHandKey
	}
	QmlValueReceiver {
		id: receiverFr
		key: parent.parameterFeetKey
	}

	property string weightWdReachMixedKey: "mixShaderReach.weightWd"
	property real weightWdReachMixed: receiverWeightWdReachMixed.value

	property string weightFrReachMixedKey: "mixShaderReach.weightFr"
	property real weightFrReachMixed: receiverWeightFrReachMixed.value

	property string weightHrReachMixedKey: "mixShaderReach.weightHr"
	property real weightHrReachMixed: receiverWeightHrReachMixed.value

	property string thresholdReachMixedKey: "mixShaderReach.threshold"
	property real thresholdReachMixed: receiverReachMixed.value

	//wd
	property vector3d headPos: head.endPosition;
	property string parameterWalkKey: "wdView.parameterWalk"
	property real parameterWalk: receiverWd.value

	//hr
	property vector3d shoulderLeftPos: shoulderLeft.endPosition;
	property vector3d shoulderRightPos: shoulderRight.endPosition;
	property vector3d midShoulderPos: shoulderLeft.startPosition;
	property vector3d thighAxis: thighLeft.endPosition.minus(thighRight.endPosition).normalized();//normalized!
	property string parameterHandKey: "hrView.parameterHand"
	property real parameterHand: receiverHr.value

	//fr
	property vector3d footLeftPos: footLeft.endPosition;
	property vector3d hipPos: thighLeft.startPosition; //no difference between thighLeft and thighRight startPos
	property vector3d footRightPos: footRight.endPosition;
	property vector3d thighLeftEndPos: thighLeft.endPosition;
	property vector3d thighRightEndPos: thighRight.endPosition;
	//property vector3d thighAxis: thighLeft.endPosition.minus(thighRight.endPosition).normalized();
	property string parameterFeetKey: "frView.parameterFeet"
	property real parameterFeet: receiverFr.value

	fragmentShader: "
		varying lowp vec2 coord;
		uniform lowp float qt_Opacity;

		//wd
		uniform lowp vec3 headPos;
		uniform lowp float parameterWalk;

		//hr
		uniform lowp vec3 shoulderLeftPos;
		uniform lowp vec3 shoulderRightPos;
		uniform lowp vec3 midShoulderPos;
		uniform lowp vec3 thighAxis;
		uniform lowp float parameterHand;

		//fr
		uniform lowp float parameterFeet;
		uniform lowp vec3 footLeftPos;
		uniform lowp vec3 footRightPos;
		uniform lowp vec3 thighLeftEndPos;
		uniform lowp vec3 thighRightEndPos;
		uniform lowp vec3 hipPos;
		//uniform lowp vec3 thighAxis;


		uniform lowp float thresholdReachMixed;
		uniform lowp float weightWdReachMixed;
		uniform lowp float weightFrReachMixed;
		uniform lowp float weightHrReachMixed;

		//wd
		vec4 wdTextureCoord(){
			float footDistance = distance(coord,hipPos.xy)/2000;
			float walkingCosts = clamp((1-footDistance)+0.5*(0.4-min(0.4,max(0,(1-hipPos.z/1300)))-0.2),0.1,1);
			return vec4(0,2*parameterWalk*walkingCosts,0, 1.0) * qt_Opacity;
		}

		//hr
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

		//fd
		float DistToLine(vec2 pt1, vec2 pt2, vec2 testPt){
			vec2 lineDir = pt2 - pt1;
			vec2 perpDir = vec2(lineDir.y, -lineDir.x);
			vec2 dirToPt1 = pt1 - testPt;
			return dot(normalize(perpDir), dirToPt1);
			//  return abs(dot(normalize(perpDir), dirToPt1));
		}
		float isLeft(vec2 a, vec2 b, vec2 c){
			return step(0.1,(b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x));
		}
		vec4 frTextureCoord(){
			float floorHeight = 300;
			float hipContact = 1-step(floorHeight,hipPos.z);
			float kneeRightContact = 1-step(floorHeight,thighRightEndPos.z);
			float kneeLeftContact = 1-step(floorHeight,thighLeftEndPos.z);
			float kneeAnyContact = max(kneeLeftContact,kneeRightContact);
			float footLeftContact = 1-step(floorHeight,footLeftPos.z);
			float footRightContact = 1-step(floorHeight,footRightPos.z);
			float footAnyContact = max(footLeftContact,footRightContact);

			float leftFootDistance = distance(coord,footLeftPos.xy)/2000;
			float rightFootDistance = distance(coord,footRightPos.xy)/2000;
			float footCosts = mix(0,max(1-leftFootDistance, 1-rightFootDistance),step(parameterFeet,max(1-leftFootDistance, 1-rightFootDistance)));
			footCosts = (footCosts+(0.6-min(0.6,max(0,(1-hipPos.z/1200))))*0.5)-0.1;
			footCosts = footCosts*footCosts-0.1;
			float kneelingReachability = mix(0,footCosts,step(0.3,footCosts));
			float standingReachability = footCosts;
			float sittingReachability =  (degrees(acos(dot(normalize(coord-hipPos.xy),-normalize(-thighAxis.yx))))/180);
			sittingReachability = (clamp(sittingReachability,0.0,0.9)-0.33) * 1.5;
			sittingReachability = mix(0,sittingReachability,step(0.6,sittingReachability));
			sittingReachability = sittingReachability*step(distance(coord,hipPos.xy)/2000,0.5)*step(0.1,distance(coord,hipPos.xy)/2000);

			float standing = footAnyContact * (1-kneeAnyContact) * (1-hipContact);
			float kneeling = kneeAnyContact * footAnyContact;
			float sitting = kneeAnyContact * footAnyContact * hipContact;

			float allReachabilities = mix(mix(kneelingReachability,standingReachability,standing),sittingReachability,sitting);
			//return vec4(kneeAnyContact,footAnyContact,hipContact, 1.0) * qt_Opacity;
			return vec4(0,allReachabilities*allReachabilities,0, 1.0) * qt_Opacity;
		}
		vec4 mixedReachTextureCoord(){
			lowp float first = (0.5+weightWdReachMixed) * wdTextureCoord().g;
			lowp float second = 0;//(0.5+weightHrReachMixed) * hrTextureCoord().g;
			lowp float third = 0;//(1.1+weightFrReachMixed) * frTextureCoord().g;
			lowp float combined = max(first,max(second,third));
			return vec4(0.0,step(thresholdReachMixed, combined), 0.0, 1.0) * qt_Opacity;
		}
		void main() {
			gl_FragColor = mixedReachTextureCoord();
		}"

}
