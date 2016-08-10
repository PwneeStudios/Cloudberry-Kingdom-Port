/*
 * Take screen-space coordinates and transform them into clip
 * space.  Pass the texture coordinates and the color to the
 * pixel shader.
 */
attribute vec2 a_position;
attribute vec2 a_texcoord;
attribute vec4 a_color;

varying vec2 v_position;
varying vec2 v_texcoord;
varying vec4 v_color;

uniform vec4 u_cameraPos;
uniform float u_cameraAspect;

uniform vec2 u_flipVector;
uniform vec2 u_flipCenter;
uniform float u_illumination;

void main()
{
	vec2 position = u_flipCenter - u_flipVector * ( a_position - u_flipCenter );
	
	gl_Position.x = ( position.x - u_cameraPos.x ) / u_cameraAspect * u_cameraPos.z;
	gl_Position.y = ( position.y - u_cameraPos.y ) * u_cameraPos.w;
	gl_Position.zw = vec2( 0, 1 );

	v_position = gl_Position.xy;
	v_texcoord = a_texcoord;
    v_color = a_color;
	v_color.rgb *= u_illumination;
}

