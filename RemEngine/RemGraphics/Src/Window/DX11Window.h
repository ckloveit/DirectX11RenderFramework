#pragma once
#include "Window.h"
#include "Graphics/Graphics.h"

class DX11Window : public Window
{
	friend class WindowApplication;

public:
	DX11Window(int left, int top, int width, int height, const wchar_t* name, DWORD windowStyle, HWND wndParent = NULL);
	~DX11Window();
	void Update(float deltaTime) override;
	void Render(float deltaTime) override;
	virtual void RenderUI(float deltaTime);

	void SetBackGroundColor(float r, float g, float b);

private:
	void ImGUI_DrawMenuBar();
private:
	// Graphics
	std::unique_ptr<Graphics> pGfx;
	// 
	std::shared_ptr<Window> NoDx11Window;


	DirectX::XMFLOAT3 backgroundColor;
	bool show_demo_window = true;
	bool show_another_window = false;
};