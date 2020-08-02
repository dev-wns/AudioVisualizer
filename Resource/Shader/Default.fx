Texture2D txDefault : register ( t0 );

SamplerState samLinear : register ( s0 );

cbuffer cb0 : register( b0 )
{
	matrix world : packoffset( c0 );
	matrix view	 : packoffset( c4 );
	matrix proj	 : packoffset( c8 );
	float4 color : packoffset( c12 );
};

struct VS_INPUT
{
	float4 p  : POSITION;
	float3 n  : NORMAL;
	float4 c  : COLOR;
	float2 t  : TEXCOORD;
	float4x4 mTransform : TRANS;
	uint id : SV_InstanceID;
};
struct VS_OUTPUT
{
	float4 p  : SV_POSITION;
	float3 n  : NORMAL;
	float4 c  : COLOR0;
	float2 t  : TEXCOORD0;
	//uint   i : INDEX;
};

VS_OUTPUT VS_INSTANCE( VS_INPUT vIn )
{
	VS_OUTPUT output = ( VS_OUTPUT )0;
	output.p = mul( vIn.p, vIn.mTransform  );
	//output.p = mul( output.p, world );
	output.p = mul( output.p, view );
	output.p = mul( output.p, proj );
	output.n = vIn.n;
	output.t = vIn.t;
	output.c = vIn.c;
	//output.i = id;

	return output;
}

float4 PS_INSTANCE( VS_OUTPUT vIn ) : SV_Target
{
	return vIn.c;
}
