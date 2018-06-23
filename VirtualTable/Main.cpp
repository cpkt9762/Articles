#include <iostream>
#include "windows.h"

class Behavior
{
public:
    virtual void Awake	()  { std::cout << "Behavior Awake"  << std::endl; }
    virtual void Start	()  { std::cout << "Behavior Start"  << std::endl; }
    virtual void Update	()	{ std::cout << "Behavior Update" << std::endl; }
    virtual void Hack	()	{ std::cout << "Your vtable has been hacked" << std::endl; }
};

class GameScript : public Behavior
{
public:

    void Awake	() final { std::cout << "GameScript Awake"  << std::endl; }
    void Start	() final { std::cout << "GameScript Start"  << std::endl; }
    void Update	() final { std::cout << "GameScript Update" << std::endl; }
};

void HackVTable(uintptr_t** vtable)
{
    HANDLE process       = GetCurrentProcess();
    DWORD  protection    = PAGE_READWRITE;
    DWORD  oldProtection = 0;

    if(VirtualProtectEx(process, (void *)*vtable, sizeof(uintptr_t), protection, &oldProtection) == 0)
    {
        std::cout << "Unable to changes vtable memory state" << std::endl;
        return;
    }
    else
    {
        (*vtable)[0] = (*vtable)[3];
        (*vtable)[1] = (*vtable)[3];
        (*vtable)[2] = (*vtable)[3];
    }
}

int main(int argc, char ** argv)
{
    GameScript game_script;
    Behavior* p_base = &game_script;
    auto** vptr = (uintptr_t**)p_base;

    p_base->Awake();
    p_base->Start();
    p_base->Update();

    HackVTable(vptr);

    p_base->Awake();
    p_base->Start();
    p_base->Update();

    return 0;
}