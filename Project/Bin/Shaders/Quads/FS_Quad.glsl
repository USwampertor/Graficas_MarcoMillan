uniform highp mat4 WVP;
uniform highp mat4 World;
uniform highp mat4 WorldView;

varying highp vec2 vecUVCoords;
varying highp vec4 Pos;

uniform mediump sampler2D tex0;

void main(){
	gl_FragColor = texture2D(tex0,vecUVCoords);
}




