#pragma once
#include "RemWin.h"

class WindowClass
{
public:
	static const char* GetName() noexcept;
	static HINSTANCE GetInstance() noexcept;
private:
	WindowClass() noexcept;
	~WindowClass();
	WindowClass(const WindowClass&) = delete;
	WindowClass& operator= (const WindowClass&) = delete;
	static constexpr const char* wndClassName = "Rem DX11 Engine Window";
	static WindowClass wndClass;
	HINSTANCE hInstance;

private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};