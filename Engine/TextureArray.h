#pragma once

#include <d3d11.h>
#include <d3dx11tex.h>

class TextureArray
{
public:
	TextureArray();
	TextureArray(const TextureArray&);
	~TextureArray();

	bool Initialize(ID3D11Device*, WCHAR*, WCHAR*);
	bool Initialize(ID3D11Device*, WCHAR*, WCHAR*, WCHAR*);
	void Shutdown();

	ID3D11ShaderResourceView** GetTextureArray();

private:
	ID3D11ShaderResourceView* m_Textures[3];
};