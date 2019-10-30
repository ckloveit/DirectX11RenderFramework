#include "WindowApplication.h"


WindowApplication::WindowApplication(int left, int top, int width, int height)
{
	mainFrameWnd = std::make_shared<MainFrameWindow>(left, top, width, height,
		"MainFrameWnd",
		WS_OVERLAPPEDWINDOW);
	
	mainDX11Wnd = std::make_shared<DX11Window>(0/*left*/, /*top + */0, width * 0.7f, height,
		"DX11Wnd", 
		WS_CHILD | WS_VISIBLE, 
		mainFrameWnd->GetHwnd());

	rightWnd = std::make_shared<Window>(width * 0.7f, 0, width * 0.3f, height,
		"RightWnd",
		WS_CHILD | WS_VISIBLE,
		mainFrameWnd->GetHwnd());
	//rightWnd->SetBackGroundColor(1.0f, 0.0f, 0.0f);

	containWindows.push_back(mainFrameWnd);
	containWindows.push_back(mainDX11Wnd);
	containWindows.push_back(rightWnd);
}

void WindowApplication::Run()
{
	MSG msg = {};
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			// TranslateMessage message
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			//// Idle
			//Update();
			//Render();
			float deltaTime = 0;

			for (auto& window : containWindows)
			{
				window->Update(deltaTime);
				window->Render(deltaTime);
			}
		}
	}
}