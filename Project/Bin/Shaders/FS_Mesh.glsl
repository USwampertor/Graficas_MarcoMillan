uniform highp mat4 WVP;
uniform highp mat4 World;
uniform highp mat4 WorldView;

varying highp vec2 vecUVCoords;
varying highp vec3 Norm;
varying highp vec4 Pos;

void main(){
	gl_FragColor = vec4(Norm, 1.0f);
}

