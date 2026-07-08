#vertex
#version 330 core
uniform mat4 uView;
uniform mat4 uProj;
out vec3 NearPoint;
out vec3 FarPoint;
const vec3 Plane[6] = vec3[](vec3(1,1,0),vec3(-1,-1,0),vec3(-1,1,0),vec3(-1,-1,0),vec3(1,1,0),vec3(1,-1,0));
vec3 Unproject(float x, float y, float z, mat4 view, mat4 proj)
{
    mat4 inv = inverse(view) * inverse(proj);
    vec4 p = inv * vec4(x, y, z, 1.0);
    return p.xyz / p.w;
}
void main()
{
    vec3 p = Plane[gl_VertexID];
    NearPoint = Unproject(p.x, p.y, 0.0, uView, uProj);
    FarPoint = Unproject(p.x, p.y, 1.0, uView, uProj);
    gl_Position = vec4(p, 1.0);
}

#fragment
#version 330 core
in vec3 NearPoint;
in vec3 FarPoint;
uniform mat4 uView;
uniform mat4 uProj;
uniform vec3 uColor;
uniform float uScale;
uniform float uFade;
out vec4 FragColor;
vec4 GridColor(vec3 pos, float scale)
{
    vec2 coord = pos.xz * scale;
    vec2 d = fwidth(coord);
    vec2 grid = abs(fract(coord - 0.5) - 0.5) / d;
    float line = min(grid.x, grid.y);
    vec4 color = vec4(uColor, 1.0 - min(line, 1.0));
    if (pos.x > -0.1 * d.x && pos.x < 0.1 * d.x) color.z = 1.0;
    if (pos.z > -0.1 * d.y && pos.z < 0.1 * d.y) color.x = 1.0;
    return color;
}
float Depth(vec3 pos)
{
    vec4 clip = uProj * uView * vec4(pos, 1.0);
    return (clip.z / clip.w) * 0.5 + 0.5;
}
void main()
{
    float t = -NearPoint.y / (FarPoint.y - NearPoint.y);
    if (t <= 0.0) discard;
    vec3 pos = NearPoint + t * (FarPoint - NearPoint);
    gl_FragDepth = Depth(pos);
    vec4 c = GridColor(pos, uScale);
    c.a *= clamp(1.0 - length(pos.xz) / uFade, 0.0, 1.0);
    if (c.a <= 0.0) discard;
    FragColor = c;
}
