#pragma once
#include "Window.h"
#include "Graphics/Graphics.h"

class DX11Window : public Window
{
	friend class WindowApplication;

public:
	DX11Window(int left, int top, int width, int height, const char* name, DWORD windowStyle, HWND wndParent = NULL);
	~DX11Window();
	void Update(float deltaTime) override;
	void Render(float deltaTime) override;

	void SetBackGroundColor(float r, float g, float b);


private:
	DirectX::XMFLOAT3 backgroundColor;

	std::unique_ptr<Graphics> pGfx;
};