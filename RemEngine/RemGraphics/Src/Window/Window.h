#pragma once
#include "RemWin.h"
#include "WindowClass.h"

struct FWindowRelativeRatio
{
	float leftRatio;
	float topRatio;
	float widthRatio;
	float heightRatio;
};



class Window
{
	friend class WindowClass;
	friend class WindowApplication;
public:
	Window(int left, int top, int width, int height, const wchar_t* name, DWORD windowStyle, HWND wndParent = NULL);
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	inline HWND GetHwnd() const
	{
		return hWnd;
	}

	virtual void Update(float deltaTime);
	virtual void Render(float deltaTime);

	RECT GetWindowRect();

protected:
	virtual LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
protected:
	const wchar_t* name;
	int width;
	int height;
	HWND hWnd;
	class MainFrameWindow* parentWindow;
	// in order to support window size scale
public:
	FWindowRelativeRatio WndRelativeRatio;
};