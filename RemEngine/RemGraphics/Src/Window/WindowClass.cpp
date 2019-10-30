#include "WindowClass.h"
#include "Window.h"
#include "../../resource.h"

// window class stuff
WindowClass WindowClass::wndClass;

WindowClass::WindowClass() noexcept
	:
	hInstance(GetModuleHandle(nullptr))
{
	// register windowclass
	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(wcex);
	wcex.style = CS_OWNDC;
	wcex.lpfnWndProc = HandleMsgSetup;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = GetInstance();
	wcex.hIcon = static_cast<HICON>(LoadImage(
		GetInstance(), MAKEINTRESOURCE(IDB_BITMAP1),
		IMAGE_ICON, 32, 32, 0
	));
	wcex.hCursor = ::LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = GetName();
	wcex.hIconSm = static_cast<HICON>(LoadImage(
		GetInstance(), MAKEINTRESOURCE(IDB_BITMAP1),
		IMAGE_ICON, 16, 16, 0
	));
	RegisterClassEx(&wcex);
}


WindowClass::~WindowClass()
{
	UnregisterClass(wndClassName, GetInstance());
}

const char* WindowClass::GetName() noexcept
{
	return wndClassName;
}

HINSTANCE WindowClass::GetInstance() noexcept
{
	return wndClass.hInstance;
}


// -- Window Message Dispatch --//
// dispatch message to every window
LRESULT CALLBACK WindowClass::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// URL : https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-nccreate
	// Sent prior to the WM_CREATE message when a window is first created.
	// use create parameter passed in from CreateWindow() to store window class pointer at WinAPI side
	if (msg == WM_NCCREATE)
	{
		// extract ptr to window class from creation data
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
		// set WinAPI-managed user data to store ptr to window instance
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		// set message proc to normal (non-setup) handler now that setup is finished
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&WindowClass::HandleMsgThunk));
		// forward message to window instance handler
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}
	// if we get a message before the WM_NCCREATE message, handle with default handler
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK WindowClass::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// retrieve ptr to window instance
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	// forward message to window instance handler
	return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}