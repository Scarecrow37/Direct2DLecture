#include "pch.h"
#include "ConsoleLogger.h"

ConsoleLogger::ConsoleLogger()
{
    AllocConsole(); // Open new Console
    FILE* traceConsoleStream; // Open file stream of console for trace log;
    freopen_s(&traceConsoleStream, "CONOUT$", "w", stdout);
    FILE* errorConsoleStream; // Open file stream of console for error log;
    freopen_s(&errorConsoleStream, "CONOUT$", "w", stderr);
}

ConsoleLogger::~ConsoleLogger()
{
    FreeConsole();
}