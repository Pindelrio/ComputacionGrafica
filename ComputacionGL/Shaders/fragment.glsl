#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 texCoord;
uniform sampler2D u_texture;
void main()
{
   FragColor = vec4(ourColor, 1.0f);
   FragColor = texture(u_texture, texCoord);
}