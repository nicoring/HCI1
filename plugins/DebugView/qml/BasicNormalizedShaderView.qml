import QtQuick 2.0

ShaderEffect {

	property string username: "";

	anchors.fill: parent;
	//property variant src: imgx
	vertexShader: "
				uniform lowp mat4 qt_Matrix;
				attribute lowp vec4 qt_Vertex;
				attribute lowp vec2 qt_MultiTexCoord0;
				varying lowp vec2 coord;
				void main() {
					coord = qt_MultiTexCoord0;
					gl_Position =  qt_Matrix * qt_Vertex;
				}"
	fragmentShader: "
				varying lowp vec2 coord;
				//uniform sampler2D src;
				uniform lowp float qt_Opacity;
				void main() {
					//lowp vec4 tex = texture2D(src, coord);
					gl_FragColor = vec4(coord,0.0, 1.0) * qt_Opacity;
				}"
}
