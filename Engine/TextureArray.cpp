#include "TextureArray.h"

TextureArray::TextureArray()
{
	m_Textures[0] = 0;
	m_Textures[1] = 0;
	m_Textures[2] = 0;
}

TextureArray::TextureArray(const TextureArray& other)
{

}

TextureArray::~TextureArray()
{

}

bool TextureArray::Initialize(ID3D11Device* device, WCHAR* filename1, WCHAR* filename2)
{
	HRESULT result;

	// Load the first texture in.
	result = D3DX11CreateShaderResourceViewFromFile(device, filename1, NULL, NULL, &m_Textures[0], NULL);
	
	if (FAILED(result))
	{
		return false;
	}

	// Load the second texture in.
	result = D3DX11CreateShaderResourceViewFromFile(device, filename2, NULL, NULL, &m_Textures[1], NULL);
	
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

bool TextureArray::Initialize(ID3D11Device* device, WCHAR* filename1, WCHAR* filename2, WCHAR* filename3)
{
	HRESULT result;

	// Load the first texture in.
	result = D3DX11CreateShaderResourceViewFromFile(device, filename1, NULL, NULL, &m_Textures[0], NULL);
	
	if (FAILED(result))
	{
		return false;
	}

	// Load the second texture in.
	result = D3DX11CreateShaderResourceViewFromFile(device, filename2, NULL, NULL, &m_Textures[1], NULL);
	
	if (FAILED(result))
	{
		return false;
	}

	result = D3DX11CreateShaderResourceViewFromFile(device, filename3, NULL, NULL, &m_Textures[2], NULL);
	
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void TextureArray::Shutdown()
{
	// Release the texture resources.
	if (m_Textures[0])
	{
		m_Textures[0]->Release();
		m_Textures[0] = 0;
	}

	if (m_Textures[1])
	{
		m_Textures[1]->Release();
		m_Textures[1] = 0;
	}

	if (m_Textures[2])
	{
		m_Textures[2]->Release();
		m_Textures[2] = 0;
	}

	return;
}

ID3D11ShaderResourceView** TextureArray::GetTextureArray()
{
	return m_Textures;
}