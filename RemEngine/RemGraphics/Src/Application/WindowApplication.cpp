#include "WindowApplication.h"


WindowApplication::WindowApplication(int left, int top, int width, int height)
{
	mainFrameWnd = std::make_shared<MainFrameWindow>(left, top, width, height,
		L"MainFrameWnd",
		WS_OVERLAPPEDWINDOW);
	
	mainDX11Wnd = std::make_shared<DX11Window>(0/*left*/, /*top + */0, width * 0.6f, height,
		L"DX11Wnd", 
		WS_CHILD | WS_VISIBLE, 
		mainFrameWnd->GetHwnd());
	mainDX11Wnd->WndRelativeRatio.leftRatio = 0.0f;
	mainDX11Wnd->WndRelativeRatio.topRatio = 0.0f;
	mainDX11Wnd->WndRelativeRatio.widthRatio = 0.6f;
	mainDX11Wnd->WndRelativeRatio.heightRatio = 1.0f;
	mainDX11Wnd->parentWindow = mainFrameWnd.get();

	rightWnd = std::make_shared<Window>(width * 0.6f, 0, width * 0.4f, height,
		L"RightWnd",
		WS_CHILD | WS_VISIBLE,
		mainFrameWnd->GetHwnd());

	rightWnd->WndRelativeRatio.leftRatio = 0.6f;
	rightWnd->WndRelativeRatio.topRatio = 0.0f;
	rightWnd->WndRelativeRatio.widthRatio = 0.4f;
	rightWnd->WndRelativeRatio.heightRatio = 1.0f;
	rightWnd->parentWindow = mainFrameWnd.get();

	//rightWnd->SetBackGroundColor(1.0f, 0.0f, 0.0f);

	containWindows.push_back(mainFrameWnd);
	containWindows.push_back(mainDX11Wnd);
	containWindows.push_back(rightWnd);

	mainDX11Wnd->NoDx11Window = rightWnd;

	mainFrameWnd->childWindows.push_back(mainDX11Wnd.get());
	mainFrameWnd->childWindows.push_back(rightWnd.get());

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