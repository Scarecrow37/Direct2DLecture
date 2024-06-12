
#include "../Engine/Logger/Logger.h"

int main(int argc, char* argv[])
{
    Logger::Initialize();
    Logger::Log(Logger::Level::Trace, "Trace");
    Logger::Log(Logger::Level::Debug, "Debug");
    Logger::Log(Logger::Level::Info, "Information");
    Logger::Log(Logger::Level::Warning, "Warning");
    Logger::Log(Logger::Level::Error, "Error");
    Logger::Log(Logger::Level::Fatal, "Fatal");
    return 0;
}
