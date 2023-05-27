#include <iostream>
#include <Windows.h>
#include "globals/Globals.hpp"
#include "misc.hpp"
#include "kiero/kiero.h"
#include "../IL2CPP Scanner/GUI/gui.hpp"

DWORD WINAPI MainThread(LPVOID lpReserved)
{
	CreateConsole();

	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	Globals::Gui::hConsole = hCons;

	SetConsoleTextAttribute(Globals::Gui::hConsole, 15);
	printf("Initializing IL2CPP...\n");

	Globals::il2cppStatus = IL2CPP::Initialize(true);

	if (!Globals::il2cppStatus) {
		SetConsoleTextAttribute(Globals::Gui::hConsole, 4);
		printf("[-] Can't Initialize IL2CPP!\n\n");
		exit(1);
	}

	SetConsoleTextAttribute(Globals::Gui::hConsole, 2);
	printf("[+] IL2CPP Initialized!\n\n");

	bool init_hook = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
		{
			kiero::bind(8, (void**)&Globals::Gui::oPresent, hkPresent);
			init_hook = true;

			SetConsoleTextAttribute(Globals::Gui::hConsole, 2);
			printf("[+] IL2CPP Scanner loaded");
		}
	} while (!init_hook);
	return TRUE;
}


BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hMod);
		CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
}
