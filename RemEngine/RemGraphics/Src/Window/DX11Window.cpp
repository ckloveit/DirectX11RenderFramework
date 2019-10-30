#include "DX11Window.h"
#include "imgui/imgui_impl_win32.h"

DX11Window::DX11Window(int left, int top, int width, int height, const wchar_t* name, DWORD windowStyle, HWND wndParent /*= NULL*/)
	:Window(left,top,width,height,name,windowStyle,wndParent)
{
	// Init ImGui Win32 Impl
	ImGui_ImplWin32_Init(hWnd);
	// create graphics object
	pGfx = std::make_unique<Graphics>(hWnd, width, height);
	backgroundColor = DirectX::XMFLOAT3(0.07f, 0.0f, 0.12f);
}
DX11Window::~DX11Window()
{
	ImGui_ImplWin32_Shutdown();
}
void DX11Window::Update(float deltaTime)
{

}

void DX11Window::Render(float deltaTime)
{
	pGfx->BeginFrame(backgroundColor.x, backgroundColor.y, backgroundColor.z);

	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	//if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		ImGui::Checkbox("Another Window", &show_another_window);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)& backgroundColor); // Edit 3 floats representing a color

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	// 3. Show another simple window.
	//if (show_another_window)
	{
		ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			show_another_window = false;
		ImGui::End();
	}

	pGfx->EndFrame();
}

void DX11Window::SetBackGroundColor(float r, float g, float b)
{
	backgroundColor = DirectX::XMFLOAT3(r, g, b);
}