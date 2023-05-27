#include "engine.h"

void ChildrenEngine()
{
	if (Globals::Gui::right_column == "children")
	{
		if (Globals::childCount != 0 && Globals::GameObject) // Safety check
		{
			for (uintptr_t u{}; Globals::childCount > u; ++u)
			{
				ImGui::InputScalar("##", ImGuiDataType_U64, &Globals::Childs.at(u), NULL, NULL, NULL, ImGuiInputTextFlags_ReadOnly);
			}
		}
		else {
			ImGui::SetCursorPos(ImVec2((ImGui::GetContentRegionAvail().x / 2) - 90, ImGui::GetContentRegionAvail().y / 2));
			ImGui::Text("Nothing to show here at the moment");
		}
	}
}