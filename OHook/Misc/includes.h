#pragma once
#include <windows.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <map>
#include <TlHelp32.h>
#include <bitset>

#define IsKeyPressed(key) GetAsyncKeyState(key) & 1 && GetAsyncKeyState(key) & 0x8000
#define IsKeyHeld(key) (GetAsyncKeyState(key) & 0x8000)
/*
*  Hooks
*/
static __int64 (*M1org)(void* ViewportClient, void* DebugCanvas) = NULL;

/*
*  Signatures
*/
struct sigmod {
	uintptr_t dwBase, dwSize;
};