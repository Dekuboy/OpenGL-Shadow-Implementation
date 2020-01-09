#version 330
attribute vec3 in_Position;

uniform mat4 in_Model;

void main()
{
    gl_Position = in_Model * vec4(in_Position, 1.0);
}