#include <Windows.h>
#include <iostream>

void CreateConsole()
{
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
}

int DU_MessageBoxTimeout(HWND hWnd, const WCHAR* sText, const WCHAR* sCaption, UINT uType, DWORD dwMilliseconds)
{
    // Displays a message box, and dismisses it after the specified timeout.
    typedef int(__stdcall* MSGBOXWAPI)(IN HWND hWnd, IN LPCWSTR lpText, IN LPCWSTR lpCaption, IN UINT uType, IN WORD wLanguageId, IN DWORD dwMilliseconds);

    int iResult;

    HMODULE hUser32 = LoadLibraryA("user32.dll");
    if (hUser32)
    {
        auto MessageBoxTimeoutW = (MSGBOXWAPI)GetProcAddress(hUser32, "MessageBoxTimeoutW");

        iResult = MessageBoxTimeoutW(hWnd, sText, sCaption, uType, 0, dwMilliseconds);

        FreeLibrary(hUser32);
    }
    else
        iResult = MessageBoxW(hWnd, sText, sCaption, uType); // fallback to the standard function

    return iResult;
}