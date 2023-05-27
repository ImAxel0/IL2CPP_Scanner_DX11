#include "engine.h"

void FieldsEngine()
{
	if (Globals::Gui::right_column == "inside_component")
	{
		for (uintptr_t u{}; Globals::fieldType.size() > u; ++u)
		{
			if (Globals::fieldType.at(u) == 12) // type float
			{
				Config::Values::floatFields.push_back(Globals::CurrentComponent->GetMemberValue<float>(Globals::m_vFields.at(u)->m_pName));

				Globals::Gui::style->Colors[ImGuiCol_Text] = ImColor(48, 167, 24);
				ImGui::Text("Float");
				Globals::Gui::style->Colors[ImGuiCol_Text] = ImColor(255, 255, 255);

				ImGui::SameLine();

				if (ImGui::InputFloat(Globals::m_vFields.at(u)->m_pName, &Config::Values::floatFields.at(u), NULL, NULL, "%.3f", ImGuiInputTextFlags_EnterReturnsTrue))
				{
					Globals::CurrentComponent->SetMemberValue<float>(Globals::m_vFields.at(u)->m_pName, Config::Values::floatFields.at(u));
				}
			}
			else {
				Config::Values::floatFields.push_back(NULL); // To fill other types as a dummy value of 0
			}

			if (Globals::fieldType.at(u) == 8) // type integer
			{
				Config::Values::intFields.push_back(Globals::CurrentComponent->GetMemberValue<int>(Globals::m_vFields.at(u)->m_pName));

				Globals::Gui::style->Colors[ImGuiCol_Text] = ImColor(0, 120, 212);
				ImGui::Text("Int");
				Globals::Gui::style->Colors[ImGuiCol_Text] = ImColor(255, 255, 255);

				ImGui::SameLine();

				if (ImGui::InputInt(Globals::m_vFields.at(u)->m_pName, &Config::Values::intFields.at(u), NULL, NULL, ImGuiInputTextFlags_EnterReturnsTrue))
				{
					Globals::CurrentComponent->SetMemberValue<int>(Globals::m_vFields.at(u)->m_pName, Config::Values::intFields.at(u));
				}
			}
			else {
				Config::Values::intFields.push_back(NULL); // To fill other types as a dummy value of 0
			}
			
			if (Globals::fieldType.at(u) == 2) // type boolean
			{
				Config::Values::booleanFields.push_back(Globals::CurrentComponent->GetMemberValue<bool>(Globals::m_vFields.at(u)->m_pName));

				Globals::Gui::style->Colors[ImGuiCol_Text] = ImColor(183, 64, 64);
				ImGui::Text("Bool");
				Globals::Gui::style->Colors[ImGuiCol_Text] = ImColor(255, 255, 255);

				ImGui::SameLine();

				if (ImGui::Checkbox(Globals::m_vFields.at(u)->m_pName, (bool*)&Config::Values::booleanFields.at(u)))
				{
					bool state;
					state = Globals::CurrentComponent->GetMemberValue<bool>(Globals::m_vFields.at(u)->m_pName);

					if (state)
					{
						Globals::CurrentComponent->SetMemberValue<bool>(Globals::m_vFields.at(u)->m_pName, false);
					}
					else 
					{
						Globals::CurrentComponent->SetMemberValue<bool>(Globals::m_vFields.at(u)->m_pName, true);
					}
				}
			}
			else {
				Config::Values::booleanFields.push_back(NULL); // To fill other types as a dummy value of 0
			}

			/* // Disabled as unstable
			if (Globals::fieldType.at(u) == 14) // type string
			{
				Config::Values::stringFields.push_back(Globals::CurrentComponent->GetMemberValue<Unity::System_String>(Globals::m_vFields.at(u)->m_pName));

				Globals::Gui::style->Colors[ImGuiCol_Text] = ImColor(244, 202, 33);
				ImGui::Text("String");
				Globals::Gui::style->Colors[ImGuiCol_Text] = ImColor(255, 255, 255);

				ImGui::SameLine();

				ImGui::InputText(Globals::m_vFields.at(u)->m_pName, &Config::Values::stringFields.at(u).ToString());
			}
			else {
				Unity::System_String dummy{};
				Config::Values::stringFields.push_back(dummy); // To fill other types as a dummy value
			}
			*/
		}

		// Vectors need to be cleared after every for loop otherwise it goes above the current number of fields
		Config::Values::floatFields.clear();
		Config::Values::intFields.clear();
		Config::Values::booleanFields.clear();
		//Config::Values::stringFields.clear();

		// Properties list
		for (uintptr_t u{}; Globals::m_vProperties.size() > u; ++u)
		{
			Globals::Gui::style->Colors[ImGuiCol_Text] = ImColor(244, 202, 33);
			ImGui::Text("Property");
			Globals::Gui::style->Colors[ImGuiCol_Text] = ImColor(255, 255, 255);

			ImGui::SameLine();

			Globals::propertyName = Globals::m_vProperties.at(u)->m_pName;

			ImGui::InputText("##", &Globals::propertyName, ImGuiInputTextFlags_ReadOnly);
		}
	}
}