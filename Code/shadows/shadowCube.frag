#version 330
uniform vec3 in_LightPos;
uniform float in_FarPlane;

in vec4 ex_FragPos;

void main()
{
    // get distance between fragment and light source
    float lightDistance = length(ex_FragPos.xyz - in_LightPos);
    
    // map to [0;1] range by dividing by far_plane
    lightDistance = lightDistance / in_FarPlane;
    
    // write this as modified depth
    gl_FragDepth = lightDistance;
}  