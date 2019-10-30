#include "Application/WindowApplication.h"
#include "Utils/Exception/HrException.h"
int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	try
	{
		WindowApplication(100, 20, 1600, 900).Run();
	}
	catch (const HrException& e)
	{
		MessageBoxA(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
	}
	return -1;
}