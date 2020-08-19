//precision mediump float;
//varying vec4 v_color;
//uniform sampler2D u_texture;
//varying vec2 v_uv;



//void main()
//{
	//gl_FragColor = texture2D(u_texture, v_uv);
//}


precision mediump float;
uniform samplerCube u_samplerCubeMap;
varying vec4 v_pos;

void main(void)
{
	gl_FragColor = textureCube(u_samplerCubeMap, v_pos.xyz);
}
