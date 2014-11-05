import QtQuick 2.0
import mtq.skeletons 1.0

BasicRealWorldShaderView {

	BoneAdapter {
		id: head
		username: parent.username
		type: BoneType.HEAD
	}

	property vector3d headPos: head.endPosition

	fragmentShader:
		"
		varying lowp vec2 coord;
		uniform lowp float qt_Opacity;
		uniform lowp vec3 headPos;
		vec4 lbTextureCoord(){
			float legibility = 1-((distance(vec3(coord,0),headPos)-1000)/2000);
			return vec4(pow(legibility,2.),0,0, 1.0) * qt_Opacity;
		}
		void main() {

			gl_FragColor = lbTextureCoord();
		}
		"
}

