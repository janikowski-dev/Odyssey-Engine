#vertex
#version 330 core
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;
uniform float uThickness;

void main()
{
    mat3 normalMatrix = transpose(inverse(mat3(uModel)));
    vec3 worldNormal = normalize(normalMatrix * aNormal);
    vec3 worldPos = vec3(uModel * vec4(aPosition, 1.0)) + worldNormal * uThickness;
    gl_Position = uProj * uView * vec4(worldPos, 1.0);
}

#fragment
#version 330 core
uniform vec3 uColor;
out vec4 FragColor;

void main()
{
    FragColor = vec4(uColor, 1.0);
}