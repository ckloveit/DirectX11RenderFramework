#include "MainFrameWindow.h"

LRESULT MainFrameWindow::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	case WM_SIZE:
	{
		//MoveWindow(mainDX11Wnd->GetHwnd(), mainDX11Wnd->left, mainDX11Wnd->top, mainDX11Wnd->width, mainDX11Wnd->height, true);
		return 0;
	}

	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}