#version 330 core
in vec4 FragPos;
in vec3 GeoNormal;
uniform vec3 lightPos;
uniform float far_plane;
out vec4 FragColor;
void main()
{
    float lightDistance = length(FragPos.xyz - lightPos);

    // map to [0;1] range by dividing by far_plane
    lightDistance = lightDistance / far_plane;

    // write this as modified depth
    gl_FragDepth = lightDistance;
    FragColor = vec4(GeoNormal, lightDistance);
}