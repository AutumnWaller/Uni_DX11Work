Texture2D txDiffuse : register(t0);
SamplerState samLinear : register(s0);


cbuffer ConstantBuffer : register(b0)
{
	matrix World;

	matrix View;

	matrix Projection;

	float pad;
	float3 LightVecW;

	float4 DiffuseMtrl;
	float4 DiffuseLight;
	float3 AmbientMtrl;
	float a = 0;

	float3 AmbientLight;
	float specularPower;

	float4 cameraEye;
	float3 specularMtrl;
	float padding;
	float3 specularLight;
	float morePadding;
}


//--------------------------------------------------------------------------------------
struct VS_INPUT
{
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD0;

};

struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD0;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS(VS_INPUT input)
{
    PS_INPUT output = (PS_INPUT) 0;
    output.Pos = mul(input.Pos, World);
    output.Pos = mul(output.Pos, View);
    output.Pos = mul(output.Pos, Projection);
    float3 vertexPos = mul(input.Pos, World);
	
    float2 tex = input.Tex;


    output.Tex = tex;
	return output;

}



//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(PS_INPUT input) : SV_Target
{
    float4 textureColour =  txDiffuse.Sample(samLinear, input.Tex);
    clip(textureColour.a - 0.95f);
    return float4(1, 0, 0, 0);
}
