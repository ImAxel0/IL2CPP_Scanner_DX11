#include "engine.h"

void AskRange()
{
	ImGui::SetNextWindowSize(ImVec2(800, 240));
	ImGui::Begin("Range Input", NULL, ImGuiWindowFlags_NoResize);

	int classesSize = static_cast<int>(Globals::m_vClasses.size());

	ImGui::Text(std::to_string(classesSize).c_str());
	ImGui::SameLine(), ImGui::Text("classes has been found in the specified ModuleName");
	ImGui::Text("Please input a range to search. If the range is too large the game may crash, recommended max range is 1000.\nDo not exceed the number of found classes\nActive found GameObjects will be listed on the left panel");

	ImGui::InputScalar("From", ImGuiDataType_U64, &Globals::rangeStart, NULL, NULL, NULL, ImGuiInputTextFlags_EnterReturnsTrue);
	ImGui::InputScalar("To", ImGuiDataType_U64, &Globals::rangeEnd, NULL, NULL, NULL, ImGuiInputTextFlags_EnterReturnsTrue);

	ImGui::End();
}

void SearchEngine()
{
	if (Globals::Gui::GameObjectTypeSearch_Current == 0)
	{
		ImGui::Combo("Module Namespace", &Globals::Gui::ModuleNamespaceTypeSearch_Current, Globals::Gui::ModuleNamespaceTypeSearch, 2); // Choose to include or not a Namespace in the search
	}

	ImGui::InputText("ModuleName", &Globals::Temp::ModuleNameSearch);

	if (Globals::Gui::GameObjectTypeSearch_Current == 0)
	{
		if (Globals::Gui::ModuleNamespaceTypeSearch_Current == 1) // Namespace Specified
		{
			ImGui::InputText("Namespace", &Globals::Temp::NameSpaceSearch, ImGuiInputTextFlags_EnterReturnsTrue);
		}
		else
		{
			Globals::Temp::NameSpaceSearch = "";
		}
	}

	ImGui::Combo("GameObject Search", &Globals::Gui::GameObjectTypeSearch_Current, Globals::Gui::GameObjectTypeSearch, 2); // Choose to search a defined GameObject or all

	if (Globals::Gui::GameObjectTypeSearch_Current == 0) // Defined GameObject
	{
		ImGui::InputText("GameObject", &Globals::Temp::GameObjectSearch);
	}

	// Search buttons
	if (Globals::Gui::GameObjectTypeSearch_Current == 0) // Defined GameObject
	{
		Globals::gotClasses = false;

		if (ImGui::SmallButton("Search GameObject"))
		{
			if (Globals::Temp::ModuleNameSearch == "")
			{
				Globals::Gui::LogContent.append("ModuleName field can't be empty\n\n");
				DU_MessageBoxTimeout(NULL, L"ModuleName field can't be empty", L"Warning", MB_ICONINFORMATION, 3000);
			}
			else
			{
				Globals::m_vClasses.clear();
				Globals::GameObjects.clear();
				Globals::GameObjectsName.clear();
				FindGameObject();
				FindModule();
			}
		}
	}
	else if (Globals::Gui::GameObjectTypeSearch_Current == 1) // Search all GameObjects
	{
		if (!Globals::gotClasses) {

			if (Globals::Temp::ModuleNameSearch == "")
			{
				Globals::Gui::GameObjectTypeSearch_Current = 0;
				Globals::Gui::LogContent.append("ModuleName field can't be empty\n\n");
				DU_MessageBoxTimeout(NULL, L"ModuleName field can't be empty", L"Warning", MB_ICONINFORMATION, 3000);
				Globals::gotClasses = false;
				return;
			}
			else
			{
				IL2CPP::Class::FetchClasses(&Globals::m_vClasses, Globals::Temp::ModuleNameSearch.c_str(), nullptr);

				if (Globals::m_vClasses.size() == 0)
				{
					Globals::Gui::GameObjectTypeSearch_Current = 0;
					Globals::Gui::LogContent.append("Specified ModuleName doesn't exist or is empty\nCheck for spelling mistakes\n\n");
					DU_MessageBoxTimeout(NULL, L"Specified ModuleName doesn't exist or is empty\nCheck for spelling mistakes", L"Warning", MB_ICONINFORMATION, 3000);
					Globals::gotClasses = false;
					return;
				}
				else
				{
					Globals::rangeEnd = static_cast<uintptr_t>(Globals::m_vClasses.size()); // Auto set the End range number to the number of found classes
				}
				Globals::gotClasses = true;
			}
		}

		AskRange();

		if (ImGui::SmallButton("Search all GameObjects in range (can be slow)"))
		{
			Globals::m_vClasses.clear();
			Globals::GameObjects.clear();
			Globals::GameObjectsName.clear();
			FindAllGameObjects();
		}
	}
}