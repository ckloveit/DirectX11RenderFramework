#pragma once
#include "Window.h"
#include "DX11Window.h"
#include <memory>

class MainFrameWindow : public Window
{
	using Window::Window;
public:
	void Update(float deltaTime) override
	{}

	void Render(float deltaTime) override
	{}
protected:
	virtual LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept override;

};