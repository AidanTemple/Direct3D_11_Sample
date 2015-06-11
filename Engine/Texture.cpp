#include "Texture.h"

Texture::Texture()
{
	m_Texture = 0;
}

Texture::Texture(const Texture& other)
{

}

Texture::~Texture()
{

}

bool Texture::Initialize(ID3D11Device* device, WCHAR* filename)
{
	HRESULT result;

	// Load the texture in.
	result = D3DX11CreateShaderResourceViewFromFile(device, filename, NULL, NULL, &m_Texture, NULL);
	
	if(FAILED(result))
	{
		return false;
	}

	return true;
}

void Texture::Shutdown()
{
	// Release the texture resource.
	if(m_Texture)
	{
		m_Texture->Release();
		m_Texture = 0;
	}

	return;
}

ID3D11ShaderResourceView* Texture::GetTexture()
{
	return m_Texture;
}