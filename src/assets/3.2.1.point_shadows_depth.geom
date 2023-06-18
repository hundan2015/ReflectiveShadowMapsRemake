#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 18) out;

uniform mat4 shadowMatrices[6];
in vec3 Normal[];
out vec4 FragPos; // FragPos from GS (output per emitvertex)
out vec3 GeoNormal;
void main()
{
    for (int face = 0; face < 6; ++face)
    {
        gl_Layer = face; // built-in variable that specifies to which face we render.
        for (int i = 0; i < 3; ++i) // for each triangle's vertices
        {
            FragPos = gl_in[i].gl_Position;
            gl_Position = shadowMatrices[face] * FragPos;
            GeoNormal = (shadowMatrices[face] * vec4(Normal[i], 1)).xyz;
            EmitVertex();
        }
        EndPrimitive();
    }
} 