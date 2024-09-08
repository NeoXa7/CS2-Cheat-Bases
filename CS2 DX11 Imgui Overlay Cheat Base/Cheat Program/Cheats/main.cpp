
// Libs 
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_dx11.h>
#include <ImGui/imgui_impl_win32.h>
#include <d3d11.h>
#include <dwmapi.h>

// Internals
#include <Memory/hMemory.h>
#include <Memory/hProcess.h>
#include <Globals/hGlobals.h>
#include <Menu/ImGuiResourceLoader.h>
#include <Menu/Interfaces.h>
#include <Readers/Game.h>
#include <Readers/Player.h>

Game game;
LocalPlayer player;
Entities entities;

HANDLE Memory::processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, CS2::procID);

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void CreateConsoleWindow()
{
	AllocConsole();
	FILE* file;
	freopen_s(&file, "CONOUT$", "w", stdout);  // Redirect stdout
	freopen_s(&file, "CONIN$", "r", stdin);   // Redirect stdin
	freopen_s(&file, "CONERR$", "w", stderr); // Redirect stderr

	// Set console title
	SetConsoleTitle(L"Debug Console");

	// Optional: Move console window to a specific position
	HWND consoleWindow = GetConsoleWindow();
	if (consoleWindow != NULL)
	{
		MoveWindow(consoleWindow, 100, 100, 800, 600, TRUE); // Position and size
	}

	std::cout << "Console initialized!" << std::endl; // Test message
}


LRESULT CALLBACK window_procedure(HWND window, UINT message, WPARAM w_param, LPARAM l_param)
{
	if (ImGui_ImplWin32_WndProcHandler(window, message, w_param, l_param))
	{
		return 0L;
	}

	if (message == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0L;
	}

	return DefWindowProc(window, message, w_param, l_param);
}

INT APIENTRY WinMain(HINSTANCE instance, HINSTANCE, PSTR, INT cmd_show)
{
	CreateConsoleWindow();
	cout << "Process ID : " << CS2::procID << '\n';
	cout << "Base Address : " << CS2::clientAddress << '\n';

	WNDCLASSEXW wc{};
	wc.cbSize = sizeof(WNDCLASSEXW);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = window_procedure;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = instance;
	wc.hIcon = 0;
	wc.hCursor = 0;
	wc.hbrBackground = 0;
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"External Overlay Class";
	wc.hIconSm = 0;

	RegisterClassExW(&wc);

	int Screen_WIDTH = GetSystemMetrics(SM_CXSCREEN);
	int Screen_HEIGHT = GetSystemMetrics(SM_CYSCREEN);

	const HWND window = CreateWindowExW(
		WS_EX_TOPMOST | WS_EX_LAYERED,
		wc.lpszClassName,
		L"External Overlay",
		WS_POPUP,
		0,
		0,
		Screen_WIDTH,
		Screen_HEIGHT,
		nullptr,
		nullptr,
		wc.hInstance,
		nullptr
	);


	SetLayeredWindowAttributes(window, RGB(0, 0, 0), 255, LWA_COLORKEY);


	{
		RECT client_area{};
		GetClientRect(window, &client_area);

		RECT window_area{};
		GetWindowRect(window, &window_area);

		POINT diff{};
		ClientToScreen(window, &diff);

		const MARGINS margins{
			window_area.left + (diff.x - window_area.left),
			window_area.top + (diff.y - window_area.top),
			client_area.right,
			client_area.bottom

		};

		DwmExtendFrameIntoClientArea(window, &margins);

	}

	DXGI_SWAP_CHAIN_DESC sd{};
	sd.BufferDesc.RefreshRate.Numerator = 60U;
	sd.BufferDesc.RefreshRate.Denominator = 1U;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.SampleDesc.Count = 1U;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 2U;
	sd.OutputWindow = window;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	constexpr D3D_FEATURE_LEVEL levels[2]
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_0
	};

	ID3D11Device* device{ nullptr };
	ID3D11DeviceContext* device_context{ nullptr };
	IDXGISwapChain* swap_chain{ nullptr };
	ID3D11RenderTargetView* render_target_view{ nullptr };
	D3D_FEATURE_LEVEL level{};

	D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0U,
		levels,
		2U,
		D3D11_SDK_VERSION,
		&sd,
		&swap_chain,
		&device,
		&level,
		&device_context
	);

	ID3D11Texture2D* back_buffer{ nullptr };
	swap_chain->GetBuffer(0U, IID_PPV_ARGS(&back_buffer));

	if (back_buffer)
	{
		device->CreateRenderTargetView(back_buffer, nullptr, &render_target_view);
		back_buffer->Release();
	}
	else
	{
		return 1;
	}

	ShowWindow(window, cmd_show);
	UpdateWindow(window);

	
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(device, device_context);
	ImGui_Resource_Loader::LoadStyles();
	
	while (Flags::isRunning)
	{
		player.UpdateLocalPlayer();
		entities.UpdateEntities();
		game.UpdateGameVars();

		MSG msg;
		while (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
			{
				Flags::isRunning = false;
			}
		}

		if (!Flags::isRunning)
		{
			break;
		}

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	
		RenderMenu();
		
		ImGui::Render();
		constexpr float color[4]{ 0.f, 0.f, 0.f, 0.f };
		device_context->OMSetRenderTargets(1U, &render_target_view, nullptr);
		device_context->ClearRenderTargetView(render_target_view, color);

		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		swap_chain->Present(1U, 0U);
	}

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	if (swap_chain)
	{
		swap_chain->Release();
	}

	if (device_context)
	{
		device_context->Release();
	}

	if (device)
	{
		device->Release();
	}

	if (render_target_view)
	{
		render_target_view->Release();
	}

	DestroyWindow(window);
	UnregisterClassW(wc.lpszClassName, wc.hInstance);

	return 0;
}
