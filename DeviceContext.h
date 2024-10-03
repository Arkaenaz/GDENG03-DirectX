#pragma once

#include <d3d11.h>
#include "Viewport.h"

namespace engine
{
	namespace graphics
	{
		class SwapChain;
		class VertexBuffer;
		class ConstantBuffer;
		class VertexShader;
		class PixelShader;
		class Viewport;

		class DeviceContext
		{
		private:
			ID3D11DeviceContext* m_device_context;

		private:
			friend class ConstantBuffer;

		public:
			DeviceContext(ID3D11DeviceContext* device_context);
			~DeviceContext();

		public:
			void clearRenderTargetColor(SwapChain* swap_chain, float red, float green, float blue, float alpha);
			void setVertexBuffer(VertexBuffer* vertex_buffer);
			void drawTriangleList(UINT vertex_count, UINT start_vertex_index);
			void drawTriangleStrip(UINT vertex_count, UINT start_vertex_index);

			//void setViewportSize(UINT width, UINT height, int index);
			void setViewport(Viewport* vp);

			void setVertexShader(VertexShader* vertex_shader);
			void setPixelShader(PixelShader* pixel_shader);

			void setConstantBuffer(VertexShader* vertex_shader, ConstantBuffer* buffer);
			void setConstantBuffer(PixelShader* pixel_shader, ConstantBuffer* buffer);
			void setRasterizerState(Rasterizer* rasterizer);


			bool release();
		};
	}
}


