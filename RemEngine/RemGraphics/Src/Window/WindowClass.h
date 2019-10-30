#pragma once
#include "RemWin.h"

class WindowClass
{
public:
	static const wchar_t* GetName() noexcept;
	static HINSTANCE GetInstance() noexcept;
private:
	WindowClass() noexcept;
	~WindowClass();
	WindowClass(const WindowClass&) = delete;
	WindowClass& operator= (const WindowClass&) = delete;
	static constexpr const wchar_t* wndClassName = L"Rem DX11 Engine Window";
	static WindowClass wndClass;
	HINSTANCE hInstance;

private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};