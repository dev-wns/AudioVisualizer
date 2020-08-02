Texture2D txDefault : register ( t0 ); 

SamplerState samLinear : register ( s0 );

cbuffer cb0 : register( b0 )
{
	matrix world: packoffset( c0 );
	matrix view	 : packoffset( c4 );
	matrix proj	 : packoffset( c8 );
	float4 color : packoffset( c12 );
};

struct VS_INPUT_INSTANCE
{
	float3 p : POSITION;
	float3 n : NORMAL;
	float4 c : COLOR;
	float2 t : TEXCOORD;
	float4x4 mTransform : TRANSFORM;
	float4 pc		: POSCOLOR;
	uint  id : SV_VertexID;
};
struct VS_OUTPUT_INSTANCE
{
	float4 p : SV_POSITION;
	float3 n : NORMAL;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
};

struct VS_INPUT
{
	float3 p  : POSITION;
	float3 n  : NORMAL;
	float4 c  : COLOR;
	float2 t  : TEXCOORD;
};

struct VS_OUTPUT
{
	float4 p  : SV_POSITION;
	float3 n  : NORMAL;
	float4 c  : COLOR0;
	float2 t  : TEXCOORD0;
};

VS_OUTPUT_INSTANCE VS_INSTANCE( VS_INPUT_INSTANCE vIn )
{
	VS_OUTPUT_INSTANCE output = (VS_OUTPUT_INSTANCE)0;
	output.p = mul( float4( vIn.p, 1.0f ), vIn.mTransform );
	//output.p = mul( vIn.p, vIn.mTransform );
	output.p = mul( output.p, world );
	output.p = mul( output.p, view );
	output.p = mul( output.p, proj );
	output.n = vIn.n;
	output.t = vIn.t;
	output.c = vIn.pc;
	return output;
}

float4 PS_INSTANCE( VS_OUTPUT_INSTANCE vIn ) : SV_TARGET
{
	float4 txColor = txDefault.Sample( samLinear, vIn.t );
	float2 tex = ( vIn.t * 2.0f ) - 1.0f;
	float fdist = ( tex.x * tex.x ) + ( tex.y * tex.y );
	if ( fdist < 1.0f )
	{
		if ( txColor.x == 0.0f && txColor.y == 0.0f && txColor.z == 0.0f && txColor.w == 0.0f )
			return vIn.c;
		else
			return txColor * vIn.c;
	}
	else
	{
		return  float4( 0,0,0,0 );
	}
}

float4 PS_INSTANCE_COLOR( VS_OUTPUT_INSTANCE vIn ) : SV_TARGET
{
	return vIn.c;
}

// Vertex Shader
VS_OUTPUT VS( VS_INPUT vIn )
{
	VS_OUTPUT output = ( VS_OUTPUT )0;
	output.p = mul( float4( vIn.p, 1.0f ), world );
	output.p = mul( output.p, view );
	output.p = mul( output.p, proj );
	output.n = vIn.n;
	output.t = vIn.t;
	output.c = color;

	return output;
}

// Pixel Shader
float4 PS_Sphere( VS_OUTPUT vIn ) : SV_Target
{ 
	float4 txColor = txDefault.Sample( samLinear, vIn.t );
	float2 tex = ( vIn.t * 2.0f ) - 1.0f;
	float fdist = ( tex.x * tex.x ) + ( tex.y * tex.y );
	if ( fdist < 1.0f )
	{
		if ( txColor.x == 0.0f && txColor.y == 0.0f && txColor.z == 0.0f && txColor.w == 0.0f )
			return vIn.c;
		else
			return txColor * vIn.c;
	}
	else
	{
		return  float4( 1,1,1,0 );
	}
}

float4 PixelShaderColor( VS_OUTPUT vIn ) : SV_Target
{
	return vIn.c;
}
float4 PixelShaderTexture( VS_OUTPUT vIn ) : SV_Target
{
	float4 txColor = txDefault.Sample( samLinear, vIn.t );
	//if ( txColor.x == 0.0f && txColor.y == 0.0f && txColor.z == 0.0f && txColor.w == 0.0f )
	//else
	return ( vIn.c * ( 1.0f - vIn.c.a ) + txColor * vIn.c.a );// *vIn.c;
}

float4 PS( VS_OUTPUT vIn ) : SV_Target
{
	return vIn.c;
	float4 txColor = txDefault.Sample( samLinear, vIn.t );
	//if ( txColor.x == 0.0f && txColor.y == 0.0f && txColor.z == 0.0f && txColor.w == 0.0f )
	//else
	return ( vIn.c * ( 1.0f - vIn.c.a ) + txColor * vIn.c.a );// *vIn.c;
}