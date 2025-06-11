#include <Windows.h>
#include <iostream>
#include <cmath>
extern "C" NTSTATUS NTAPI RtlAdjustPrivilege(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
extern "C" NTSTATUS NTAPI NtRaiseHardError(LONG, ULONG, ULONG, PULONG_PTR, ULONG, PULONG);