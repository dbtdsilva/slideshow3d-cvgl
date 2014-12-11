#version 120

attribute vec3 v_coord3d;
attribute vec2 texcoord;

uniform mat4x4 matrizProj;
uniform mat4x4 matrizModelView;

varying vec2 f_texcoord;

void main( void )
{
    gl_Position = matrizProj * matrizModelView * vec4(v_coord3d, 1.0);
    f_texcoord = texcoord;
}
