#pragma once
#define REM_HWND_EXCEPT(hr) HrException(__LINE__, __FILE__, (hr))
#define REM_HWND_LAST_EXCEPT() HrException(__LINE__, __FILE__, GetLastError())