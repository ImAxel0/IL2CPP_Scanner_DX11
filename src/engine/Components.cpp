#include "engine.h"

void ComponentsEngine()
{
	if (Globals::Gui::right_column == "component")
	{
		if (Globals::Gui::DisplayComponents)
		{
			if (Globals::GameObject != nullptr) // Safety check
			{
				for (uintptr_t u{}; Globals::Components.size() > u; ++u) // Components Buttons
				{
					if (Globals::Components.at(u) != nullptr) // Safety check
					{
						if (ImGui::Button(Globals::ComponentsName.at(u), ImVec2(ImGui::GetContentRegionAvail().x, NULL)))
						{
							// Cleaning for imminent search
							Globals::m_vFields.clear();
							Globals::fieldType.clear();
							Globals::m_vProperties.clear();

							// Field vectors get emptied when a component is selected before filling them with new values
							Config::Values::floatFields.clear();
							Config::Values::intFields.clear();
							Config::Values::booleanFields.clear();

							Globals::Gui::CurrentComponentString = Globals::ComponentsName.at(u); // Store the selected component name
							Globals::CurrentComponent = Globals::Components.at(u); // Store the selected component
							Globals::Gui::right_column = "inside_component";

							FindFields();
							FindProperties();
						}
					}
				}

				// ----------------------------------------------------------------------------------------------------------- \\

				for (uintptr_t u{}; Globals::ChildrenComponents.size() > u; ++u) // Children Components Buttons
				{
					if (Globals::ChildrenComponents.at(u) != nullptr) // Safety check
					{
						ImGui::Text(ICON_FA_CHILD);
						ImGui::SameLine();
						if (ImGui::Button(Globals::ChildrenComponentsName.at(u), ImVec2(ImGui::GetContentRegionAvail().x, NULL)))
						{
							// Cleaning for imminent search
							Globals::m_vFields.clear();
							Globals::fieldType.clear();
							Globals::m_vProperties.clear();

							// Field vectors get emptied when a component is selected before filling them with new values
							Config::Values::floatFields.clear();
							Config::Values::intFields.clear();
							Config::Values::booleanFields.clear();

							Globals::Gui::CurrentComponentString = Globals::ChildrenComponentsName.at(u); // Store the selected component name
							Globals::CurrentComponent = Globals::ChildrenComponents.at(u); // Store the selected component
							Globals::Gui::right_column = "inside_component";

							FindFields();
							FindProperties();
						}
					}
				}
			}
		}
		else {
			ImGui::SetCursorPos(ImVec2((ImGui::GetContentRegionAvail().x / 2) - 90, ImGui::GetContentRegionAvail().y / 2));
			ImGui::Text("Nothing to show here at the moment");
		}
	}
}