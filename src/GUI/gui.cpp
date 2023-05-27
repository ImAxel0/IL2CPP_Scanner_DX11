#include <iostream>
#include <Windows.h>
#include <chrono>
#include <thread>
#include "memory.h"
#include "font-icons/font.hpp"
#include "GUIdefines.hpp"
#include "../engine/engine.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;

namespace Colors
{
	ImColor black(0, 0, 0);
	ImColor white(255, 255, 255);
	ImColor mainTheme(183, 64, 64);
	ImColor* color = &mainTheme;
}

void InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantTextInput || ImGui::GetIO().WantCaptureKeyboard;
	io.Fonts->AddFontFromMemoryTTF(&OpenSans_Regular_ttf, 1, 18.0);
	float baseFontSize = 10.0f;
	float iconFontSize = baseFontSize * 2.0f / 3.0f;
	static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };
	ImFontConfig config;
	config.MergeMode = true;
	config.GlyphMinAdvanceX = 10.0f;
	static const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
	io.Fonts->AddFontFromMemoryTTF(&icon_font_ttf, sizeof icon_font_ttf, 10.0f, &config, icon_ranges);	

	Globals::Gui::LogContent.append("Start searching for a ModuleName and a GameObject\nA ModuleName is always required!\nOnly active GameObjects can be found.\nYou can also find all active GameObjects in a specified ModuleName but you won't get the children components of the selected\nGameObject\nTo get them search the desidered GameObject individually specifying the namespace containing the children components\n\n");

	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (Globals::Gui::showMenu) {
		ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
		return true;
	}

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

bool init = false;
HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();
			init = true;
		}

		else
			return Globals::Gui::oPresent(pSwapChain, SyncInterval, Flags);
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::GetMouseCursor();
	ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
	ImGui::GetIO().WantCaptureMouse = Globals::Gui::showMenu;
	ImGui::GetIO().MouseDrawCursor = Globals::Gui::showMenu;

	if (GetAsyncKeyState(VK_INSERT) & 1)
	{
		Globals::Gui::showMenu = !Globals::Gui::showMenu;
	}

	if (Globals::Gui::showMenu)
	{
		Globals::Gui::style = &ImGui::GetStyle();

		Globals::Gui::style->WindowTitleAlign = ImVec2(0.5, 0.5);
		Globals::Gui::style->WindowBorderSize = 3.0f;
		Globals::Gui::style->Colors[ImGuiCol_Border] = *Colors::color;
		Globals::Gui::style->Colors[ImGuiCol_TitleBg] = *Colors::color;
		Globals::Gui::style->Colors[ImGuiCol_TitleBgActive] = *Colors::color;
		Globals::Gui::style->Colors[ImGuiCol_FrameBg] = ImColor(36, 36, 36);
		Globals::Gui::style->Colors[ImGuiCol_FrameBgActive] = ImColor(36, 36, 36);
		Globals::Gui::style->Colors[ImGuiCol_FrameBgHovered] = ImColor(45, 45, 45);
		Globals::Gui::style->Colors[ImGuiCol_Button] = ImColor(32, 32, 32);
		Globals::Gui::style->Colors[ImGuiCol_ButtonHovered] = ImColor(45, 45, 45);
		Globals::Gui::style->Colors[ImGuiCol_ChildBg] = ImColor(36, 36, 36);

		ImGui::SetNextWindowSize(ImVec2(1280, 720), ImGuiCond_Once);
		ImGui::Begin("IL2CPP SCANNER " ICON_FA_MAGNIFYING_GLASS, &Globals::Gui::isOpen, ImGuiWindowFlags_NoResize);

		ImGui::Columns(2, nullptr, true);
		ImGui::SetColumnOffset(1, 400);
		{
			// Left panel GUI from here
			SearchEngine(); // Search panel GUI

			Globals::Gui::style->Colors[ImGuiCol_Border] = ImColor(45, 45, 45);
			Globals::Gui::style->Colors[ImGuiCol_FrameBg] = ImColor(24, 24, 24);
			Globals::Gui::style->Colors[ImGuiCol_FrameBgActive] = ImColor(24, 24, 24);
			Globals::Gui::style->Colors[ImGuiCol_FrameBgHovered] = ImColor(45, 45, 45);
			
			GameObjectsEngine(); // GameObjects panel GUI

			ImGui::NextColumn(); // Right Column from here

			// Current right panel view check
			if (Globals::Gui::right_column == "component") {
				ImGui::Text(Globals::GameObjectName->ToString().c_str());
				ImGui::SameLine(),
				ImGui::Text("Component List (Instantiated Only)");
			}
			else if (Globals::Gui::right_column == "children") {
				ImGui::Text("Children List");
			}
			else if (Globals::Gui::right_column == "inside_component") {
				ImGui::Text(Globals::Gui::CurrentComponentString.c_str());
			}

			// Right panel GUI from here
			ImGui::BeginChild("right_panel", ImVec2(ImGui::GetContentRegionAvail().x, 438), true, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_MenuBar);

			Globals::Gui::style->Colors[ImGuiCol_MenuBarBg] = ImColor(50, 50, 50);

			ImGui::BeginMenuBar();
			/* Disabled at the moment
			if (ImGui::SmallButton("Components View"))
			{
				Globals::Gui::right_column = "component";
			}
			ImGui::SameLine();
			if (ImGui::SmallButton("Children View"))
			{
				Globals::Gui::right_column = "children";
			}
			
			if (Globals::Gui::right_column != "inside_component")
			{
				ImGui::SetCursorPosX(800);
				if (ImGui::SmallButton("Refresh"))
				{
					if (Globals::Gui::right_column == "component")
					{
						// Cleanup for imminent search
						Globals::Components.clear();
						Globals::ChildrenComponents.clear();
						Globals::ComponentsName.clear();
						Globals::ChildrenComponentsName.clear();

						if (Globals::Gui::GameObjectTypeSearch_Current == 0) // Defined GameObject
						{
							if (Globals::Gui::ModuleNamespaceTypeSearch_Current == 1) // Defined Namespace
							{
								FindChildrenComponents();
							}
						}
						else // Default namespace
						{
							FindComponents();
						}
					}

					if (Globals::Gui::right_column == "children")
					{
						Globals::Childs.clear();
						FindChildren();
					}
				}
			}
			*/
			ImGui::EndMenuBar();

			ComponentsEngine(); // Components view
			
			FieldsEngine(); // Fields view

			ChildrenEngine(); // Children view

			ImGui::EndChild();
			
			ImGui::SetCursorPos(ImVec2(NULL, 500));
			Globals::Gui::style->Colors[ImGuiCol_Separator] = ImColor(0, 0, 0, 0);
			Globals::Gui::style->Colors[ImGuiCol_SeparatorActive] = ImColor(0, 0, 0, 0);
			Globals::Gui::style->Colors[ImGuiCol_SeparatorHovered] = ImColor(0, 0, 0, 0);
			ImGui::Separator();

			// Log panel GUI from here
			ImGui::Text("Log");
			ImGui::SameLine(), ImGui::SetCursorPosX(800);
			if (ImGui::SmallButton("Clear"))
			{
				Globals::Gui::LogContent.clear();
			}
			Globals::Gui::style->Colors[ImGuiCol_FrameBg] = ImColor(36, 36, 36);
			Globals::Gui::style->Colors[ImGuiCol_FrameBgActive] = ImColor(36, 36, 36);
			Globals::Gui::style->Colors[ImGuiCol_FrameBgHovered] = ImColor(45, 45, 45);
			ImGui::BeginChild("log", ImGui::GetContentRegionAvail(), true, ImGuiWindowFlags_NoResize);
			ImGui::InputTextMultiline("##", &Globals::Gui::LogContent, ImGui::GetContentRegionAvail(), ImGuiInputTextFlags_ReadOnly);
			ImGui::EndChild();
		}

		if (!Globals::Gui::isOpen)
		{
			Globals::Gui::showMenu = false;
			Globals::Gui::isOpen = true;
		}
		ImGui::End();
	}
	ImGui::Render();

	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return Globals::Gui::oPresent(pSwapChain, SyncInterval, Flags);
}
