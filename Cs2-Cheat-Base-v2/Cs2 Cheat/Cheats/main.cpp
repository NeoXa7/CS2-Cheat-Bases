#include <Windows.h>
#include <string>
#include <iostream>
#include <TlHelp32.h>
#include <d3d11.h>
#include <Overlay/Overlay.hpp>
#include <Functions/Console.hpp>
#include <Memory/Memory.hpp>
#include <Esp.hpp>

HANDLE Memory::ProcessHandle = NULL;

INT APIENTRY WinMain(HINSTANCE instance, HINSTANCE, PSTR, INT cmd_show)
{
    CreateConsoleWindow(L"Console");
    ShowTitle();

    if (CS2::ProcID <= 0)
    {
        ShowErrorBox(L"Process cs2.exe not found!");
    }

    Memory::ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, CS2::ProcID);
    if (!Memory::ProcessHandle)
        return 1;

    HWND window = InitializeWindow(instance, cmd_show);
    ID3D11Device* device = nullptr;
    ID3D11DeviceContext* device_context = nullptr;
    IDXGISwapChain* swap_chain = nullptr;
    ID3D11RenderTargetView* render_target_view = nullptr;

    if (!InitializeDirectX(window, &device, &device_context, &swap_chain, &render_target_view))
        return 1;

    InitializeImGui(window, device, device_context);

    MSG msg{};
    while (Flags::IsRunning)
    {
        //  std::this_thread::sleep_for(std::chrono::milliseconds(1));
        while (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT) Flags::IsRunning = false;
        }

        if (!Flags::IsRunning) break;

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        // Rendering Starts Here;
        if (CS2::ProcID > 0)
        {
            // Updating Local Player and Game Variables Before Running Cheats;
            player.UpdateLocalPlayer();
            game.UpdateGameVars();

            
            ANTIFLASH();
            RenderMenu(); // Rendering the Menu;
            std::this_thread::sleep_for(std::chrono::milliseconds(1)); // Sleep for 1 ms		

            // Closing Cheat Process When Cs2 is Closed;
            if (!PM.IsProcessRunning(CS2::ProcID))
            {
                Flags::IsRunning = false;
            }
        }

        ImGui::Render(); // Rendering Stops Here;
        const float color[4]{ 0.f, 0.f, 0.f, 0.f };
        device_context->OMSetRenderTargets(1U, &render_target_view, nullptr);
        device_context->ClearRenderTargetView(render_target_view, color);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        swap_chain->Present(0U, 0U);
    }

    CleanUp(swap_chain, device, device_context, render_target_view, window, {});

    return 0;
}