#include "DX11Window.h"
#include "imgui/imgui_impl_win32.h"
#include "Window/MainFrameWindow.h"

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
	if (show_demo_window)
		/*ImGui::SetNextWindowPos(ImVec2(200, 0));
		ImGui::SetNextWindowSize(ImVec2(100, 100));*/
		ImGui::ShowDemoWindow(&show_demo_window);

	

	RenderUI(deltaTime);
	pGfx->EndFrame();
}


void DX11Window::RenderUI(float deltaTime)
{
	ImGUI_DrawMenuBar();

	RECT rcWnd = parentWindow->GetWindowRect();
	// draw Hierachy window
	int curPosX = (rcWnd.right - rcWnd.left) * NoDx11Window->WndRelativeRatio.leftRatio;
	int curPosY = 0;
	int curWidth = (rcWnd.right - rcWnd.left) * NoDx11Window->WndRelativeRatio.widthRatio * 0.5f;
	int curHeight = rcWnd.bottom - rcWnd.top;
	ImVec2 main_viewport_pos = ImGui::GetMainViewport()->Pos;
	ImGui::SetNextWindowPos(ImVec2(main_viewport_pos.x + curPosX, main_viewport_pos.y + curPosY));
	ImGui::SetNextWindowSize(ImVec2(curWidth, curHeight));
	{
		ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			show_another_window = false;
		ImGui::End();
	}

	// draw property window
	curPosX = (rcWnd.right - rcWnd.left) * NoDx11Window->WndRelativeRatio.leftRatio + curWidth;
	ImGui::SetNextWindowPos(ImVec2(main_viewport_pos.x + curPosX, main_viewport_pos.y + curPosY));
	ImGui::SetNextWindowSize(ImVec2(curWidth, curHeight));
	ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

	ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
	ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
	ImGui::Checkbox("Another Window", &show_another_window);

	ImGui::ColorEdit3("clear color", (float*)& backgroundColor); // Edit 3 floats representing a color

	ImGui::SameLine();

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();


}


void DX11Window::ImGUI_DrawMenuBar()
{
	// Menu
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New")) { MessageBox(NULL, TEXT("Click New"), TEXT("Imgui Message"), MB_OK); }
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
			if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
			ImGui::Separator();
			if (ImGui::MenuItem("Cut", "CTRL+X")) {}
			if (ImGui::MenuItem("Copy", "CTRL+C")) {}
			if (ImGui::MenuItem("Paste", "CTRL+V")) {}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("Show ImGUI Demo")) { show_demo_window = true; }
			if (ImGui::MenuItem("hide ImGUI Demo")) { show_demo_window = false; }
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}


void DX11Window::SetBackGroundColor(float r, float g, float b)
{
	backgroundColor = DirectX::XMFLOAT3(r, g, b);
}