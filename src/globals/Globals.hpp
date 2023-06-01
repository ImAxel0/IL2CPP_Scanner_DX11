#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include <d3d11.h>
#include <dxgi.h>
#include "../il2cppresolver/Il2CppResolver.hpp"

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_dx11.h"
#include "../imgui/imgui_impl_win32.h"

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;

namespace Globals
{
	// GameObjects related
	inline Unity::CGameObject* GameObject;
	inline Unity::System_String* GameObjectName;
	inline std::vector<Unity::CGameObject*> GameObjects;
	inline std::vector< Unity::System_String*> GameObjectsName;
	inline uintptr_t rangeStart{ 0 };
	inline uintptr_t rangeEnd{ 100 };
	inline bool gotClasses = false;

	// Components
	inline std::vector<Unity::CComponent*> Components = {};
	inline std::vector<const char*> ComponentsName = {};

	// Components of children
	inline std::vector<Unity::CComponent*> ChildrenComponents = {};
	inline std::vector<const char*> ChildrenComponentsName = {};

	inline std::string Namespace; // Namespace text backup for for loops

	// Current active/selected component
	inline Unity::CComponent* CurrentComponent;

	// Vector of module classes
	inline std::vector<Unity::il2cppClass*> m_vClasses;

	// Vector of Namespaces
	inline std::vector<std::string> ClassesNamespaces = {};

	// Vector of properties
	inline std::vector<Unity::il2cppPropertyInfo*> m_vProperties;
	inline std::string propertyName;

	// Fields
	inline std::vector<Unity::il2cppFieldInfo*> m_vFields;
	inline std::vector<unsigned int> fieldType = {};

	// Children
	inline int childCount{};
	inline std::vector<Unity::CTransform*> Childs = {};

	namespace Temp // Search strings
	{
		inline std::string ModuleNameSearch;
		inline std::string NameSpaceSearch;
		inline std::string GameObjectSearch;
		inline std::string ComponentSearch;
	}
	namespace Gui
	{
		inline Present oPresent;
		inline ImGuiStyle* style;
		inline HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		inline bool showMenu = false;
		inline bool isOpen = true;
		inline bool DisplayComponents = false;

		inline const char* ModuleNamespaceTypeSearch[] = { "Default (no namespace)", "Defined"};
		inline int ModuleNamespaceTypeSearch_Current = 0;

		inline const char* GameObjectTypeSearch[] = { "Defined", "All" };
		inline int GameObjectTypeSearch_Current = 0;

		inline std::string right_column = "component";
		inline std::string LogContent = "";
		inline std::string CurrentComponentString = ""; // The selected component text
	}

	inline bool il2cppStatus = false;
}
