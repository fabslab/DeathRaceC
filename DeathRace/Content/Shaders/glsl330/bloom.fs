#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

uniform int renderWidth;
uniform int renderHeight;

// Output fragment color
out vec4 finalColor;

const int samples = 8; // pixels per axis; higher = bigger glow, worse performance
const float quality = 1.5; 	// lower = smaller glow, better quality

vec2 size = vec2(renderWidth, renderHeight);

void main()
{
    vec4 sum = vec4(0);
    vec2 sizeFactor = vec2(1) / size * quality;
    vec4 source = texture(texture0, fragTexCoord);
    int range = (samples - 1) / 2;

    for (int x = -range; x <= range; x++)
    {
        for (int y = -range; y <= range; y++)
        {
            sum += texture(texture0, fragTexCoord + vec2(x, y)*sizeFactor);
        }
    }

    vec4 bloom = (sum/(samples*samples))*colDiffuse;
    source *= (1 - clamp(bloom, 0.0, 1.0));

    // Calculate final fragment color
    finalColor = source + bloom;
}