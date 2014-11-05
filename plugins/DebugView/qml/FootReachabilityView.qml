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

	BoneAdapter {
		id: thighRight
		username: parent.username
		type: BoneType.THIGH_RIGHT
	}

	QmlValueReceiver {
		id: receiver
		key: parent.parameterKey
	}

	//1. find out which body parts are approximately on the floor/near the feets z-value
	//2. switch statement simulated with step() or mix of reachabilities for all 3 poses


	property vector3d footLeftPos: footLeft.endPosition
	property vector3d hipPos: thighLeft.startPosition //no difference between thighLeft and thighRight startPos
	property vector3d footRightPos: footRight.endPosition
	property vector3d thighLeftEndPos: thighLeft.endPosition
	property vector3d thighRightEndPos: thighRight.endPosition
	property vector3d thighAxis: thighLeft.endPosition.minus(thighRight.endPosition).normalized()

	property string parameterKey: "frView.parameterFeet"
	property real parameterFeet: receiver.value

	fragmentShader:
		"
			varying lowp vec2 coord;
			uniform lowp float qt_Opacity;
			uniform lowp float parameterFeet;
			uniform lowp vec3 footLeftPos;
			uniform lowp vec3 footRightPos;
			uniform lowp vec3 thighLeftEndPos;
			uniform lowp vec3 thighRightEndPos;
			uniform lowp vec3 hipPos;
			uniform lowp vec3 thighAxis;

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
			void main() {
				gl_FragColor = frTextureCoord();
			}
		 "
}
