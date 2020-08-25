//precision mediump float;
//uniform samplerCube u_samplerCubeMap;
//varying vec4 v_pos;

//void main(void)
//{
//	gl_FragColor = textureCube(u_samplerCubeMap, v_pos.xyz);
//}

precision mediump float;
varying vec4 v_color;
uniform sampler2D u_texture;
varying vec2 v_uv;

void main()
{
	//v_uv += vec2(0.333096, 0.0);
	//gl_FragColor = vec4(1.0, 0.5, 1.0, 1.0);
	gl_FragColor =  texture2D(u_texture, v_uv);
}