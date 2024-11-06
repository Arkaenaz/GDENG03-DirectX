#include "SwapChain.h"

#include <exception>

#include "RenderSystem.h"
#include "Logger.h"

using namespace graphics;

SwapChain::SwapChain(RenderSystem* system, HWND hwnd, UINT width, UINT height) : system(system)
{
	ID3D11Device* device = this->system->m_d3d_device;

	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.BufferCount = 1;
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = hwnd;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = TRUE;

	// Create the swap chain for the window indicated by HWND parameter
	HRESULT hr = this->system->m_dxgi_factory->CreateSwapChain(device, &desc, &m_swap_chain);

	if (!debug::Logger::log(this, hr))
		throw std::exception("SwapChain not created successfully");

	ID3D11Texture2D* buffer = NULL;
	hr = m_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);

	if (!debug::Logger::log(this, hr))
		throw std::exception("SwapChain not created successfully");

	hr = device->CreateRenderTargetView(buffer, NULL, &m_rtv);
	buffer->Release();

	if (!debug::Logger::log(this, hr))
		throw std::exception("Render Target View not created successfully");

	D3D11_TEXTURE2D_DESC texDesc = {};
	texDesc.Width = width;
	texDesc.Height = height;
	texDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	texDesc.MipLevels = 1;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.MiscFlags = 0;
	texDesc.ArraySize = 1;
	texDesc.CPUAccessFlags = 0;

	hr = device->CreateTexture2D(&texDesc, NULL, &buffer);

	if (!debug::Logger::log(this, hr))
		throw std::exception("Texture2D not created successfully");

	hr = device->CreateDepthStencilView(buffer, NULL, &m_dsv);
	buffer->Release();

	if (!debug::Logger::log(this, hr))
		throw std::exception("Depth Stencil View not created successfully");

}

SwapChain::~SwapChain()
{
	m_dsv->Release();
	m_rtv->Release();
	m_swap_chain->Release();
}

void SwapChain::cleanRenderTarget()
{
	if (m_rtv)
	{
		m_rtv->Release();
		m_rtv = nullptr;
	}
}

void SwapChain::resizeBuffers(UINT bufferCount, UINT width, UINT height)
{
	m_swap_chain->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0);
}

void SwapChain::createRenderTarget()
{
	ID3D11Texture2D* buffer = NULL;
	HRESULT result = m_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);

	if (!debug::Logger::log(this, result))
		throw std::exception("Swap Chain Fail");

	result = this->system->m_d3d_device->CreateRenderTargetView(buffer, NULL, &m_rtv);
	if (!debug::Logger::log(this, result))
		throw std::exception("Render Target View not created successfully.");

	buffer->Release();
}

bool SwapChain::present(bool vsync)
{
	m_swap_chain->Present(vsync, NULL);
	return true;
}
