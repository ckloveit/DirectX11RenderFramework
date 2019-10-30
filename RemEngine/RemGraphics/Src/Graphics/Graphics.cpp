#include "Graphics.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"
#include "Utils/Macro/WindowThrowMacro.h"

namespace wrl = Microsoft::WRL;
namespace dx = DirectX;

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"D3DCompiler.lib") // compile shader

Graphics::Graphics(HWND hWnd, int width, int height)
{
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hWnd;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	UINT swapCreateFlags = 0;
#ifndef NDEBUG
	swapCreateFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	// for checking results of d3d functions
	HRESULT hr;
	REM_HWND_EXCEPT(D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		swapCreateFlags,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&pSwapChain,
		&pDevice,
		nullptr,
		&pImmediateContext
	));

	// gain access to texture subresource in swap chain (back buffer)
	wrl::ComPtr<ID3D11Resource> pBackBuffer;
	(pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer));
	(pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &pRTV));

	// create depth stensil state
	D3D11_DEPTH_STENCIL_DESC dsDesc = {};
	dsDesc.DepthEnable = TRUE;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	wrl::ComPtr<ID3D11DepthStencilState> pDSState;
	(pDevice->CreateDepthStencilState(&dsDesc, &pDSState));

	// bind depth state
	pImmediateContext->OMSetDepthStencilState(pDSState.Get(), 1u);

	// create depth stencil texture
	wrl::ComPtr<ID3D11Texture2D> pDepthStencil;
	D3D11_TEXTURE2D_DESC descDepth = {};
	descDepth.Width = width;
	descDepth.Height = height;
	descDepth.MipLevels = 1u;
	descDepth.ArraySize = 1u;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1u;
	descDepth.SampleDesc.Quality = 0u;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	(pDevice->CreateTexture2D(&descDepth, nullptr, &pDepthStencil));

	// create view of depth stensil texture
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
	descDSV.Format = DXGI_FORMAT_D32_FLOAT;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0u;
	(pDevice->CreateDepthStencilView(
		pDepthStencil.Get(), &descDSV, &pDSV
	));

	// bind depth stensil view to OM
	pImmediateContext->OMSetRenderTargets(1u, pRTV.GetAddressOf(), pDSV.Get());

	// configure viewport
	D3D11_VIEWPORT vp;
	vp.Width = width;
	vp.Height = height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	pImmediateContext->RSSetViewports(1u, &vp);

	// init imgui d3d impl
	ImGui_ImplDX11_Init(pDevice.Get(), pImmediateContext.Get());

}
Graphics::~Graphics()
{
	ImGui_ImplDX11_Shutdown();
}

void Graphics::BeginFrame(float red, float green, float blue) noexcept
{
	// imgui stuff
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	const float color[] = { red,green,blue,1.0f };
	pImmediateContext->ClearRenderTargetView(pRTV.Get(), color);
	pImmediateContext->ClearDepthStencilView(pDSV.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
}


void Graphics::EndFrame()
{
	// imgui frame end
	if (true/*imguiEnabled*/)
	{
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

	HRESULT hr;

	if (FAILED(hr = pSwapChain->Present(1u, 0u)))
	{
		if (hr == DXGI_ERROR_DEVICE_REMOVED)
		{
			throw REM_HWND_EXCEPT(pDevice->GetDeviceRemovedReason());
		}
		else
		{
			throw REM_HWND_EXCEPT(hr);
		}
	}
}
