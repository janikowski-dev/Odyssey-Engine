#vertex
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;

out vec3 vNormal;

void main()
{
    vNormal = mat3(transpose(inverse(uModel))) * aNormal;
    gl_Position = uProj * uView * uModel * vec4(aPos, 1.0);
}

#fragment
#version 330 core
in vec3 vNormal;
uniform vec3 uColor;
out vec4 FragColor;

void main()
{
    vec3 N = normalize(vNormal);
    vec3 L = normalize(vec3(0.4, 1.0, 0.6));
    float diff = max(dot(N, L), 0.0);
    vec3 c = uColor * (0.25 + 0.75 * diff);
    FragColor = vec4(c, 1.0);
}