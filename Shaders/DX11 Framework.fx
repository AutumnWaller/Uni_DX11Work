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
    float3 Normal : NORMAL;
    float2 Tex : TEXCOORD0;

};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float3 Normal : NORMAL;
    float2 Tex : TEXCOORD0;
    float3 PosW : POSITION;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS(VS_INPUT input)
{
    PS_INPUT output = (PS_INPUT) 0;
    float4 posW = mul(input.Pos, World);
    output.PosW = posW.xyz;

    output.Pos = mul(posW, View);
    output.Pos = mul(output.Pos, Projection);
    output.Tex = input.Tex;
    float3 normalW = mul(float4(input.Normal, 0.0f), World).xyz;
    normalW = normalize(normalW);
    output.Normal = normalW;

    return output;

}



//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(PS_INPUT input) : SV_Target
{
    float3 normalW = normalize(input.Normal);
    float3 toEye = normalize(cameraEye.xyz - input.PosW);
    
    float4 textureColour = txDiffuse.Sample(samLinear, input.Tex);

    float3 lightVecNorm = normalize(LightVecW);
    
    float3 r = reflect(-lightVecNorm, normalW);
    float specularAmount = pow(max(dot(r, toEye), 0), specularPower);
    float diffuseAmount = max(dot(lightVecNorm, normalW), 0);

    if (diffuseAmount <= 0)
    {
        specularAmount = 0;
    }

    float3 diffuse = diffuseAmount * (DiffuseMtrl * DiffuseLight).rgb;
    float3 ambient = (AmbientMtrl * AmbientLight).rgb;
    float3 specular = specularAmount * (specularMtrl * specularLight).rgb;
    float4 colour;
    colour.rgb = textureColour.rgb * (ambient + diffuse) + specular;
    colour.a = DiffuseMtrl.a;
    clip(textureColour.a - 0.95f);
    return colour;
}
