#include <Memory/hMemory.h>
#include <Maths/hColor.h>
#include <Globals/hGlobals.h>

HANDLE Memory::processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, CS2::procID);

void _cheat_InitProgram()
{
    if (Memory::processHandle == 0) {
        SetConsoleTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY); // red
        cerr << "processHandle not found Error: " << GetLastError() << endl;
        SetConsoleTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // white
    }

    // your Cheat logic here;
    
    
}

int main()
{
    ProcessManager::CheckProcess(CS2::procID, L"cs2.exe");
    ProcessManager::CheckBaseAddress(CS2::clientAddress);
    _cheat_InitProgram();
}
