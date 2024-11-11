#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <Driver/Process.hpp>
#include <Globals/Globals.hpp>
#include <Driver/UM_Driver.hpp>
#include <Interface/Interfaces.hpp>
#include <Overlay/Overlay.hpp>
#include <Functions/Console.hpp>
#include <Overlay/Message.hpp>
#include <Readers/Entities.hpp>
#include <Readers/Game.hpp>
#include <Readers/Player.hpp>


#define Success 0;
#define Failed 1;

INT APIENTRY WinMain(HINSTANCE instance, HINSTANCE, PSTR, INT cmd_show) {
    CreateConsoleWindow(L"Console");
    if (CS2::ProcID <= 0)
    {
        std::cout << " [+] Failed to find designated Process (cs2.exe)\n";
        ShowErrorBox(L"Failed to find designated Process (cs2.exe)\n", L"Driver Error");
        return Failed;
    }

    Driver::driver_handle = CreateFile(L"\\\\.\\Synapse", GENERIC_READ, 0, nullptr, OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL, nullptr);

    if (Driver::driver_handle == INVALID_HANDLE_VALUE)
    {
        std::cout << "Failed to create our driver handle\n";
        std::cin.get();
        return Failed;
    }

    if (Driver::attach_to_process(Driver::driver_handle, CS2::ProcID) == true)
    {
        ShowMessage(L"Cheat Attached to Driver Successfully");
        CS2::ClientDll = PM.GetModuleBaseAddress(CS2::ProcID, L"client.dll");
        CS2::Engine2Dll = PM.GetModuleBaseAddress(CS2::ProcID, L"engine2.dll");
        CS2::MatchMakingDll = PM.GetModuleBaseAddress(CS2::ProcID, L"matchmaking.dll");
        CS2::ServerDll = PM.GetModuleBaseAddress(CS2::ProcID, L"server.dll");
        ShowTitle();

        HWND window = InitializeWindow(instance, cmd_show);
        ID3D11Device* device = nullptr;
        ID3D11DeviceContext* device_context = nullptr;
        IDXGISwapChain* swap_chain = nullptr;
        ID3D11RenderTargetView* render_target_view = nullptr;

        if (!InitializeDirectX(window, &device, &device_context, &swap_chain, &render_target_view))
            return 1;

        InitializeImGui(window, device, device_context);
        MSG msg{};


        if (CS2::ProcID > 0 && CS2::ClientDll > 0)
        {
            while (Flags::IsRunning)
            {
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

                // Updating Local Player and Game Variables Before Running Cheats;
                player.UpdateLocalPlayer();
                game.UpdateGameVars();

                // Rendering Starts Here;
                RenderMenu__(); // Rendering the Menu;

                // Closing Cheat Process When Cs2 is Closed;
                if (!PM.IsProcessRunning(CS2::ProcID))
                {
                    Flags::IsRunning = false;
                }

                ImGui::Render(); // Rendering Stops Here;
                const float color[4]{ 0.f, 0.f, 0.f, 0.f };
                device_context->OMSetRenderTargets(1U, &render_target_view, nullptr);
                device_context->ClearRenderTargetView(render_target_view, color);
                ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

                swap_chain->Present(0U, 0U);
            }

            CleanUp(swap_chain, device, device_context, render_target_view, window, {});
        }
        
    }

    CloseHandle(Driver::driver_handle);
    std::cin.get();
    return 0;
}
