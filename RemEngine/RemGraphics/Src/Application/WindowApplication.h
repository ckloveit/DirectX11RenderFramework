#pragma once
#include "Window/Window.h"
#include "Window/DX11Window.h"
#include "Window/MainFrameWindow.h"
#include <memory>
#include <vector>
#include "Manager/ImguiManager.h"

// 包含最基本的Window Application 功能，不包含渲染相关

class WindowApplication
{
public:
	WindowApplication(int left, int top, int width, int height);

	void Run();

	virtual void Update() {};
	virtual void Render() {};

private:
	ImguiManager imgui;

	std::shared_ptr<MainFrameWindow> mainFrameWnd;
	std::shared_ptr<DX11Window> mainDX11Wnd;
	std::shared_ptr<Window> rightWnd;

	std::vector<std::shared_ptr<Window>> containWindows;
};

