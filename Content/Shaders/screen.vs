/*
 * Take screen-space coordinates and transform them into clip
 * space.  Pass the texture coordinates and the color to the
 * pixel shader.
 */
attribute vec2 a_position;
attribute vec2 a_texcoord;
attribute vec4 a_color;

varying vec2 v_texcoord;
varying vec4 v_color;

void main()
{
	vec2 clipSpace = 2.0f * a_position / vec2( 1280.0f, 720.0f ) - 1.0f;
	clipSpace.y = -clipSpace.y;
    gl_Position = vec4( clipSpace, 0, 1 );
	
	v_texcoord = a_texcoord;
    v_color = a_color;
}

