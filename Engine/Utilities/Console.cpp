#include "Console.h"

Console::Console()
{
    const BOOL _ = AllocConsole(); // Open new Console
    
    // FILE* traceConsoleStream; // Open file stream of console for trace log;
    // errno_t error = freopen_s(&traceConsoleStream, "CONOUT$", "w", stdout);
    // if (error != 0) std::cerr << "Failed to open trace log console stream!" << std::endl;
    // FILE* errorConsoleStream; // Open file stream of console for error log;
    // error = freopen_s(&errorConsoleStream, "CONOUT$", "w", stderr);
    // if (error != 0) std::cerr << "Failed to open error log console stream!" << std::endl;
}

Console::~Console()
{
    FreeConsole();
}

void Console::SetForegroundColor(const WORD color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
