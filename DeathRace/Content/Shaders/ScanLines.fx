// From SpriteBatch
sampler s0;

float Attenuation;
float LinesFactor;


float4 PixelShaderFunction(float2 texCoord : TEXCOORD0, in float2 screenPos : VPOS) : COLOR0
{
	float4 color = tex2D(s0, texCoord);
	float scanline = sin(texCoord.y * LinesFactor) * Attenuation;
	color.rgb -= scanline * (color.rgb);

	return color;
}


technique Scanlines
{
	pass P0
	{
		PixelShader = compile ps_3_0 PixelShaderFunction();
	}
};
