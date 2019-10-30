#include "DX11Window.h"
#include "imgui/imgui_impl_win32.h"

DX11Window::DX11Window(int left, int top, int width, int height, const char* name, DWORD windowStyle, HWND wndParent /*= NULL*/)
	:Window(left,top,width,height,name,windowStyle,wndParent)
{
	// Init ImGui Win32 Impl
	ImGui_ImplWin32_Init(hWnd);
	// create graphics object
	pGfx = std::make_unique<Graphics>(hWnd, width, height);
	backgroundColor = DirectX::XMFLOAT3(0.07f, 0.0f, 0.12f);
}
DX11Window::~DX11Window()
{
	ImGui_ImplWin32_Shutdown();
}
void DX11Window::Update(float deltaTime)
{

}

void DX11Window::Render(float deltaTime)
{
	pGfx->BeginFrame(backgroundColor.x, backgroundColor.y, backgroundColor.z);

	ImGui::ShowDemoWindow();

	pGfx->EndFrame();
}

void DX11Window::SetBackGroundColor(float r, float g, float b)
{
	backgroundColor = DirectX::XMFLOAT3(r, g, b);
}