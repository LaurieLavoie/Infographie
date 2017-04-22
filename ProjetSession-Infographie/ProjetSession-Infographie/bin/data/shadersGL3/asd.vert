#version 150

in vec3 position;
in vec3 normal;
in vec2 texCoord;
 
out VertexData {
    vec2 texCoord;
    vec3 normal;
} VertexOut;
 
void main()
{
    VertexOut.texCoord = texCoord;
    VertexOut.normal = normal;
    gl_Position = vec4(position, 1.0);
}