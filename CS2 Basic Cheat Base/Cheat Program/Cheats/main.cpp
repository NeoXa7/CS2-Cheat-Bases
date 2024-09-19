#include <Memory/hMemory.h>
#include <Maths/hColor.h>
#include <Globals/hGlobals.h>
#include <Functions/hConsole.h>

HANDLE Memory::processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, CS2::procID);

void INIT_Cheats()
{
    // your Cheat logic here; 
    while (true)
    {

    }
}

int main()
{
    vector<string> CheatTitle = {
        "   ___ ___ ___   _____  ___________ ___ _  _   _   _     ",
        "  / __/ __|_  ) | __\\ \\/ /_   _| __| _ \\ \\| | /_\\ | |    ",
        " | (__\\__ \\/ /  | _| >  <  | | | _||   / .` |/ _ \\| |__ ",
        "  \\___|___/___| |___/_/\\_\\ |_| |___|_|_\\_|\\_/_/ \\_\\____|",
        "                                                       ",
        "  ______   __  _   _          __  __    _____          ",
        " | __ ) \\ / / | \\ | | ___  ___\\ \\/ /__ |___  |         ",
        " |  _ \\\\ V /  |  \\| |/ _ \\/ _ \\\\  // _` | / /          ",
        " | |_)| | |   | |\\  |  __/ (_) /  \\ (_| |/ /           ",
        " |____/ |_|   |_| \\_|\\___|\\___/_/\\_\\__,_/_/            ",
        "                                                       "
    };

    for (const auto& line : CheatTitle) {
        SetConsoleTextColor(RED);
        std::cout << line << std::endl;
    }
    SetConsoleTextColor(YELLOW);
    cout << "   [+] CS2 Process ID : " << CS2::procID << '\n';
    cout << '\n';
    cout << "   [+] Retrieving Module Addresess\n";
    cout << '\n';
    Sleep(1000);
    cout << "    => ClientDll : " << CS2::ClientDll << '\n';
    cout << "    => Engine2Dll : " << CS2::Engine2Dll << '\n';
    cout << "    => InputsystemDll : " << CS2::InputsystemDll << '\n';
    cout << "    => MatchMakingDll : " << CS2::MatchMakingDll << '\n';
    cout << "    => SoundsystemDll : " << CS2::SoundsystemDll << '\n';
    cout << '\n';

    if (CS2::procID > 0)
    {
        cout << "   Cheat Succesfully Attached!\n";
        CreateLogNotification("Memory", "$CONNER"); // Creating an Log Notification
    }
    else
    {
        cout << "   Cheat Failed To Attach!\n";
        CreateLogNotification("Memory", "$CONNER"); // Creating an Log Notification
    }

    INIT_Cheats();
}
