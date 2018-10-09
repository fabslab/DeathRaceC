#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

// Output fragment color
out vec4 finalColor;

const float attenuation = 0.2;
const float linesFactor = 1800;

void main()
{
    vec4 color = texture(texture0, fragTexCoord);
	float scanline = sin(fragTexCoord.y * linesFactor) * attenuation;
	color.xyz -= scanline * (color.xyz);
    finalColor = color;
}
