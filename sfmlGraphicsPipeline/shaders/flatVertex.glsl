#version 400

uniform mat4 projMat, viewMat, modelMat;

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec4 vColor;
out vec4 surfel_color;

void main()
{
    // Transform coordinates from local space to clipped space
    gl_Position = projMat*viewMat*modelMat*vec4(vPosition, 1.0f);
    // surfel_color = vec4(1, 0, 0, 1); // RGBA color defined in [0,1]
    surfel_color = vColor;
}
