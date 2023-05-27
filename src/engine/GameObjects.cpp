#include "engine.h"

void GameObjectsEngine()
{
	ImGui::BeginChild("GameObject List", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), true, ImGuiWindowFlags_NoResize);
	
	if (Globals::Gui::GameObjectTypeSearch_Current == 0) // Defined GameObject
	{
		if (Globals::GameObject != nullptr) // Safety check
		{
			Globals::GameObjectName = Globals::GameObject->GetName(); // Get GameObject Name

			if (ImGui::Button(Globals::GameObjectName->ToString().c_str(), ImVec2(ImGui::GetContentRegionAvail().x, NULL))) // Find Components + children in the GameObject
			{
				Globals::Gui::right_column = "component";
				Globals::Gui::DisplayComponents = true;

				// Cleanup for imminent search
				Globals::ComponentsName.clear();
				Globals::ChildrenComponentsName.clear();
				Globals::Components.clear();
				Globals::ChildrenComponents.clear();

				if (Globals::Gui::ModuleNamespaceTypeSearch_Current == 1) // Namespace defined
				{
					FindChildrenComponents();
				}
				else // Default or All namespaces
				{
					FindComponents();
					//FindChildren();
				}
			}
		}
		else {
			ImGui::SetCursorPos(ImVec2(70, ImGui::GetContentRegionAvail().y / 2));
			ImGui::Text("No GameObject to show at the moment");
		}
	}
	
	// ------------------------------------------------------------------------------------------------------------------------------- \\

	if (Globals::Gui::GameObjectTypeSearch_Current == 1) // All GameObjects
	{
		if (Globals::GameObjects.size() > 0)
		{
			for (uintptr_t u{}; Globals::GameObjects.size() > u; ++u)
			{
				if (Globals::GameObjects.at(u) != nullptr) // Safety check
				{
					Globals::GameObjectsName.push_back(Globals::GameObjects.at(u)->GetName());

					if (ImGui::Button(Globals::GameObjectsName.at(u)->ToString().c_str(), ImVec2(ImGui::GetContentRegionAvail().x, NULL)))
					{
						Globals::Gui::right_column = "component";
						Globals::Gui::DisplayComponents = true;

						// Cleanup for imminent search
						Globals::ComponentsName.clear();
						Globals::ChildrenComponentsName.clear();
						Globals::Components.clear();
						Globals::ChildrenComponents.clear();

						Globals::GameObject = Globals::GameObjects.at(u); // Store the selected GameObject
						Globals::GameObjectName = Globals::GameObjectsName.at(u); // Store the selected GameObject name

						std::vector<Unity::il2cppClass*> classesBackup = Globals::m_vClasses; // Backup the number of found classes in all namespaces
						Globals::m_vClasses.clear();

						// Makes so FindComponents doesn't get invalid children components 
						IL2CPP::Class::FetchClasses(&Globals::m_vClasses, Globals::Temp::ModuleNameSearch.c_str(), ""); // Only blank namespace components are supported in GameObject multi-search for now

						FindComponents();

						Globals::m_vClasses = classesBackup; // Restore the number of found classes in all namespaces
					}
				}
			}
			Globals::GameObjectsName.clear(); // Cleanup after every for loop to not go outbound
		}
		else {
			ImGui::SetCursorPos(ImVec2(70, ImGui::GetContentRegionAvail().y / 2));
			ImGui::Text("No GameObject to show at the moment");
		}
	}
	
	ImGui::EndChild();
}