#pragma once



enum class ERasterizer	 : char { Wire = 0, Back, Front, None, };
enum class EDepthStencil : char { Enable = 0, Disable, };
enum class ESampler		 : char { Default = 0, Clamp, };
enum class EBlend		 : char { Color = 0, Alpha, NoAlpha, };


struct DxState
{
	std::map<ERasterizer, ID3D11RasterizerState*> raster;
	std::map<EDepthStencil, ID3D11DepthStencilState*> depth;
	std::map<ESampler, ID3D11SamplerState*> sampler;
	std::map<EBlend, ID3D11BlendState*> blend;

	HRESULT Init( ID3D11Device* pd3dDevice )
	{
		HRESULT hr( S_OK );
		//===========================================================
		//=======================AlphaBlend==========================
		//===========================================================
		ID3D11SamplerState* samDefault = nullptr;
		ID3D11SamplerState* samClampLinear = nullptr;

		D3D11_SAMPLER_DESC samplerDesc;
		ZeroMemory( &samplerDesc, sizeof( samplerDesc ) );
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.BorderColor[0] = 1.0f;
		samplerDesc.BorderColor[1] = 0.0f;
		samplerDesc.BorderColor[2] = 0.0f;
		samplerDesc.BorderColor[3] = 1.0f;
		samplerDesc.MaxAnisotropy = 16;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		samplerDesc.MaxLOD = FLT_MAX;
		samplerDesc.MipLODBias = 0.0f;
		samplerDesc.MinLOD = FLT_MIN;
		if ( FAILED( hr = pd3dDevice->CreateSamplerState( &samplerDesc, &samDefault ) ) )
		{
			return hr;
		}
		sampler.insert( std::make_pair( ESampler::Default, samDefault ) );

		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		if ( FAILED( hr = pd3dDevice->CreateSamplerState( &samplerDesc, &samClampLinear ) ) )
		{
			return hr;
		}
		sampler.insert( std::make_pair( ESampler::Clamp , samClampLinear ) );

		//===========================================================
		//=======================AlphaBlend==========================
		//===========================================================
		ID3D11BlendState* blendColor = nullptr;
		ID3D11BlendState* blendAlpha = nullptr;
		ID3D11BlendState* blendNoAlpha = nullptr;

		D3D11_BLEND_DESC blendDesc;
		ZeroMemory( &blendDesc, sizeof( D3D11_BLEND_DESC ) );
		blendDesc.AlphaToCoverageEnable = FALSE;
		blendDesc.RenderTarget[0].BlendEnable = TRUE;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		pd3dDevice->CreateBlendState( &blendDesc, &blendAlpha );
		blend.insert( std::make_pair( EBlend::Alpha, blendAlpha ) );

		blendDesc.RenderTarget[0].BlendEnable = FALSE;
		pd3dDevice->CreateBlendState( &blendDesc, &blendNoAlpha );
		blend.insert( std::make_pair( EBlend::NoAlpha, blendNoAlpha ) );

		blendDesc.RenderTarget[0].BlendEnable = TRUE;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_COLOR;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		pd3dDevice->CreateBlendState( &blendDesc, &blendColor );
		blend.insert( std::make_pair( EBlend::Color, blendColor ) );

		//===========================================================
		//=======================DepthState==========================
		//===========================================================
		ID3D11DepthStencilState* dsEnable = nullptr;
		ID3D11DepthStencilState* dsDisable = nullptr;

		D3D11_DEPTH_STENCIL_DESC dsd;
		ZeroMemory( &dsd, sizeof( D3D11_DEPTH_STENCIL_DESC ) );
		dsd.DepthEnable = TRUE;
		dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		dsd.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
		dsd.StencilEnable = FALSE;

		pd3dDevice->CreateDepthStencilState( &dsd, &dsEnable );
		depth.insert( std::make_pair( EDepthStencil::Enable, dsEnable ) );

		dsd.DepthEnable = FALSE;
		pd3dDevice->CreateDepthStencilState( &dsd, &dsDisable );
		depth.insert( std::make_pair( EDepthStencil::Disable, dsDisable ) );

		//=============================================================
		//=======================RasterizeState========================
		//=============================================================
		ID3D11RasterizerState* rsWire = nullptr;
		ID3D11RasterizerState* rsNone = nullptr;
		ID3D11RasterizerState* rsBack = nullptr;
		ID3D11RasterizerState* rsFront = nullptr;
		

		D3D11_RASTERIZER_DESC rsDesc;
		ZeroMemory( &rsDesc, sizeof( rsDesc ) );
		rsDesc.DepthClipEnable = TRUE;
		rsDesc.FillMode = D3D11_FILL_WIREFRAME;
		rsDesc.CullMode = D3D11_CULL_BACK;
		rsDesc.MultisampleEnable = TRUE;
		rsDesc.AntialiasedLineEnable = FALSE;
		if ( FAILED( hr = pd3dDevice->CreateRasterizerState( &rsDesc, &rsWire ) ) )
		{
			return hr;
		}
		raster.insert( std::make_pair( ERasterizer::Wire, rsWire ) );

		rsDesc.FillMode = D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_BACK;
		if ( FAILED( hr = pd3dDevice->CreateRasterizerState( &rsDesc, &rsBack ) ) )
		{
			return hr;
		}
		raster.insert( std::make_pair( ERasterizer::Back, rsBack ) );

		rsDesc.FillMode = D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_NONE;
		if ( FAILED( hr = pd3dDevice->CreateRasterizerState( &rsDesc, &rsNone ) ) )
		{
			return hr;
		}
		raster.insert( std::make_pair( ERasterizer::None, rsNone ) );

		rsDesc.FillMode = D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_FRONT;
		if ( FAILED( hr = pd3dDevice->CreateRasterizerState( &rsDesc, &rsFront ) ) )
		{
			return hr;
		}
		raster.insert( std::make_pair( ERasterizer::Front, rsFront ) );

		return hr;
	}
	void Release()
	{
		for ( std::pair<ERasterizer, ID3D11RasterizerState*> oneRaster : raster )
		{
			SafeRelease( oneRaster.second );
		}

		for ( std::pair<EDepthStencil, ID3D11DepthStencilState*> oneDepth : depth )
		{
			SafeRelease( oneDepth.second );
		}

		for ( std::pair<ESampler, ID3D11SamplerState*> oneSampler : sampler )
		{
			SafeRelease( oneSampler.second );
		}

		for ( std::pair<EBlend, ID3D11BlendState*> oneBlend : blend )
		{
			SafeRelease( oneBlend.second );
		}

		raster.clear();
		depth.clear();
		sampler.clear();
		blend.clear();
	}
};