#pragma once

#include <d3d11.h>
#include "Prerequisites.h"

namespace graphics
{
	class SwapChain
	{
	private:
		RenderSystem* system = nullptr;

		IDXGISwapChain* m_swap_chain;
		ID3D11RenderTargetView* m_rtv;
		ID3D11DepthStencilView* m_dsv;

	private:
		friend class DeviceContext;

	public:
		SwapChain(RenderSystem* system, HWND hwnd, UINT width, UINT height);
		~SwapChain();

	public:
		void cleanRenderTarget();
		void resizeBuffers(UINT bufferCount, UINT width, UINT height);
		void createRenderTarget();
		bool present(bool vsync);
	};
}