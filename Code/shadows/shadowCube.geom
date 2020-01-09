#version 330
layout (triangles) in;
layout (triangle_strip, max_vertices=18) out;

uniform mat4 in_LightSpace[6];

out vec4 ex_FragPos;

void main()
{
    for(int face = 0; face < 6; ++face)
    {
        gl_Layer = face; // built-in variable that specifies to which face we render.
        for(int i = 0; i < 3; ++i) // for each triangle's vertices
        {
            ex_FragPos = gl_in[i].gl_Position;
            gl_Position = in_LightSpace[face] * ex_FragPos;
            EmitVertex();
        }    
        EndPrimitive();
    }
}  