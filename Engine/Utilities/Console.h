#pragma once
#include "../Framework.h"

class Console
{
public:
    Console();
    ~Console();

    static void SetForegroundColor(WORD color);
};
