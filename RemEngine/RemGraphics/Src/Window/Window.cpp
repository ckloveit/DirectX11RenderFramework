#include "Window.h"
#include "Utils/Exception/HrException.h"
#include "Utils/Macro/WindowThrowMacro.h"
#include "imgui/imgui_impl_win32.h"

Window::Window(int left,int top,int width, int height, const char* name, DWORD windowStyle, HWND wndParent /* = NULL*/)
	: width(width), height(height), name(name)
{
	// calculate window size based on desired client region size
	RECT wr;
	wr.left = left;
	wr.right = width + wr.left;
	wr.top = top;
	wr.bottom = height + wr.top;
	if (AdjustWindowRect(&wr, windowStyle/*WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU | WS_THICKFRAME*/, FALSE) == 0)
	{
		throw REM_HWND_LAST_EXCEPT();
	}
	// create window & get hWnd
	hWnd = CreateWindow(
		WindowClass::GetName(), name,
		windowStyle/*WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU | WS_THICKFRAME*/,
		left, top, wr.right - wr.left, wr.bottom - wr.top,
		wndParent, nullptr, GetModuleHandle(nullptr), this
	);
	if (hWnd == nullptr)
	{
		throw REM_HWND_LAST_EXCEPT();
	}
	// newly created windows start off as hidden
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);

}
Window::~Window()
{
	DestroyWindow(hWnd);
}

void Window::Update(float deltaTime)
{
	
}

void Window::Render(float deltaTime)
{


}




LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	// if Imgui need process,just process it
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
	{
		return true;
	}

	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	case WM_SIZE:
	{
		//MoveWindow(hWnd, left, top, width, height, true);
		return 0;
	}

	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

