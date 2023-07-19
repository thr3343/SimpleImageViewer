#version 460
#pragma shader_stage(fragment)

//Not My Shader!: All credit to Silexars : https://www.shadertoy.com/view/XsXXDn

layout(push_constant) uniform i_Time { vec2 iResolution; float iTime; float sTime; };
layout(location = 0) out vec4 fragColor;
mat4 a={vec4(1,0,1,0),vec4(1,1,0,0),vec4(0,0,1,0),vec4(0,0,0,1)};
vec2 fragCoord = vec2(gl_FragCoord.x,(iResolution.y-gl_FragCoord.y));
const vec4 iMouse = vec4(0.,0.,0.,0.);













void main(){
	vec3 c;
	float t = iTime;
	float l,z=t;
	for(int i=0;i<3;i++) {
		vec2 uv,p=gl_FragCoord.xy/iResolution;
		uv=p;
		p-=.5;
		p.x*=iResolution.x/iResolution.y;
		z+=.07;
		l=length(p);
		uv+=p/l*(sin(z)+1.)*abs(sin(l*9.-z-z));
		c[i]=.01/length(mod(uv,1.)-.5);
	}
	fragColor=vec4(c/l,t);
}