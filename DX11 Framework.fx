//--------------------------------------------------------------------------------------
// File: DX11 Framework.fx
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------

Texture2D txDiffuse : register(t0);
SamplerState samLinear : register(s0);


cbuffer ConstantBuffer : register( b0 )
{
	matrix World;
	matrix View;
	matrix Projection;
	float gTime;
	float3 LightVecW;
	float4 DiffuseMtrl;
	float4 DiffuseLight;

	float3 AmbientMtrl;
	float a = 0;
	float3 AmbientLight;
	float b = 0;
}


//--------------------------------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR0;
	float2 Tex : TEXCOORD0;
};

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
VS_OUTPUT VS(float4 Pos : POSITION, float3 NormalL : NORMAL, float2 Tex : TEXCOORD0)
{
VS_OUTPUT output = (VS_OUTPUT)0;
    output.Pos = mul( Pos, World );
    output.Pos = mul( output.Pos, View );
	output.Pos = mul( output.Pos, Projection);
	output.Tex = Tex;
    // Convert from local space to world space 
    // W component of vector is 0 as vectors cannot be translated
    float3 normalW = mul(float4(NormalL, 0.0f), World).xyz;
    normalW = normalize(normalW);

    float diffuseAmount = max(dot(LightVecW, normalW), 0.0f);
    
	float3 diffuse = diffuseAmount * (DiffuseMtrl * DiffuseLight);
	float3 ambient = AmbientMtrl * AmbientLight;
	
	output.Color.rgb = diffuse + ambient;
    output.Color.a = DiffuseMtrl.a;

    return output;

}



//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS( VS_OUTPUT input ) : SV_Target
{ 
	float4 textureColour = input.Color + txDiffuse.Sample(samLinear, input.Tex);
	clip(textureColour.a - 0.95f);
	return textureColour;
}
