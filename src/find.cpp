#include "globals/Globals.hpp"
#include "../IL2CPP Scanner/GUI/GUIdefines.hpp"

void FindModule()
{
	Globals::Gui::LogContent.append("Fetching Classes...\n\n");

	IL2CPP::Class::FetchClasses(&Globals::m_vClasses, Globals::Temp::ModuleNameSearch.c_str(), Globals::Temp::NameSpaceSearch.c_str());

	for (uintptr_t u{}; Globals::m_vClasses.size() > u; ++u)
	{
		Globals::Gui::LogContent.append(Globals::m_vClasses.at(u)->m_pName).append("\n");
	}

	if (Globals::m_vClasses.size() == 0)
	{
		Globals::Gui::LogContent.append("[-] Couldn't find ").append(Globals::Temp::ModuleNameSearch).append(" Module\n\n");
	}
}

void FindGameObject()
{
	Globals::Gui::LogContent.append("Searching ").append(Globals::Temp::GameObjectSearch).append(" GameObject...\n\n");

	Globals::GameObject = Unity::GameObject::Find(Globals::Temp::GameObjectSearch.c_str());

	if (Globals::GameObject != nullptr)
	{
		Globals::Gui::LogContent.append("[+] ").append(Globals::Temp::GameObjectSearch).append(" GameObject Found\n");
	}

	else {
		Globals::Gui::LogContent.append("[-] ").append(Globals::Temp::GameObjectSearch).append(" GameObject not Found\n");
	}

	Globals::Components.clear();
	Globals::Gui::DisplayComponents = false;
}

void FindAllGameObjects()
{
	Globals::Gui::LogContent.append("Searching all active GameObjects in the defined ModuleName...\n");

	IL2CPP::Class::FetchClasses(&Globals::m_vClasses, Globals::Temp::ModuleNameSearch.c_str(), nullptr);

	Unity::CGameObject* tempGameObject;

	uintptr_t rangeStartBackup = Globals::rangeStart;

	for (Globals::rangeStart; Globals::rangeEnd > Globals::rangeStart; ++Globals::rangeStart) {

		tempGameObject = Unity::GameObject::Find(Globals::m_vClasses.at(Globals::rangeStart)->m_pName);

		if (tempGameObject != nullptr)
		{
			Globals::GameObjects.push_back(tempGameObject);
		}
	}

	Globals::rangeStart = rangeStartBackup;

	Globals::Components.clear();
	Globals::Gui::DisplayComponents = false;
}

void FindComponents()
{
	Unity::CComponent* tempComponent;

	for (uintptr_t u{}; Globals::m_vClasses.size() > u; ++u)
	{
		tempComponent = Globals::GameObject->GetComponent(Globals::m_vClasses.at(u)->m_pName);

		if (tempComponent != nullptr)
		{
			Globals::ComponentsName.push_back(Globals::m_vClasses.at(u)->m_pName);

			Globals::Components.push_back(tempComponent);
		}
	}
}

void FindChildren()
{
	if (Globals::GameObject)
	{
		Globals::childCount = Globals::GameObject->GetTransform()->GetChildCount();

		for (uintptr_t u{}; Globals::childCount > u; ++u)
		{
			Globals::Childs.push_back(Globals::GameObject->GetTransform()->GetChild(u));
		}
	}
}

void FindFields()
{
	if (Globals::Gui::ModuleNamespaceTypeSearch_Current == 1) // Namespace defined
	{
		Globals::Namespace = Globals::Temp::NameSpaceSearch; // Namespace text backup

		Unity::il2cppClass* classe = IL2CPP::Class::Find(Globals::Temp::NameSpaceSearch.append(".").append(Globals::Gui::CurrentComponentString).c_str());
		IL2CPP::Class::FetchFields(classe, &Globals::m_vFields, nullptr);

		// Restore and Cleanup
		Globals::Temp::NameSpaceSearch = Globals::Namespace;
		Globals::Namespace.clear();
	}

	else // Default namespace
	{
		Unity::il2cppClass* classe = IL2CPP::Class::Find(Globals::Gui::CurrentComponentString.c_str());
		IL2CPP::Class::FetchFields(classe, &Globals::m_vFields, nullptr);
	}

	Globals::Gui::LogContent.append("Searching fields in ").append(Globals::Gui::CurrentComponentString).append(" component...\n\n");

	for (uintptr_t u{}; Globals::m_vFields.size() > u; ++u)
	{
		Globals::Gui::LogContent.append(Globals::m_vFields.at(u)->m_pName).append("\n");
	}

	if (Globals::m_vFields.size() == 0)
	{
		Globals::Gui::LogContent.append("[-] Couldn't find any ").append(Globals::Gui::CurrentComponentString).append(" field\n\n");
		return;
	}

	for (uintptr_t u{}; Globals::m_vFields.size() > u; ++u)
	{
		Globals::fieldType.push_back(Globals::m_vFields.at(u)->m_pType->m_uType);
	}
}

void FindProperties()
{
	if (Globals::Gui::ModuleNamespaceTypeSearch_Current == 1) // Namespace defined
	{
		Globals::Namespace = Globals::Temp::NameSpaceSearch; // Namespace text backup

		Unity::il2cppClass* classe = IL2CPP::Class::Find(Globals::Temp::NameSpaceSearch.append(".").append(Globals::Gui::CurrentComponentString).c_str());
		IL2CPP::Class::FetchProperties(classe, &Globals::m_vProperties, nullptr);

		// Restore and Cleanup
		Globals::Temp::NameSpaceSearch = Globals::Namespace;
		Globals::Namespace.clear();
	}

	else // Default namespace
	{
		Unity::il2cppClass* classe = IL2CPP::Class::Find(Globals::Gui::CurrentComponentString.c_str());
		IL2CPP::Class::FetchProperties(classe, &Globals::m_vProperties, nullptr);
	}

	Globals::Gui::LogContent.append("Searching properties in ").append(Globals::Gui::CurrentComponentString).append(" component...\n\n");

	for (uintptr_t u{}; Globals::m_vProperties.size() > u; ++u)
	{
		Globals::Gui::LogContent.append(Globals::m_vProperties.at(u)->m_pName).append("\n");
	}

	if (Globals::m_vProperties.size() == 0)
	{
		Globals::Gui::LogContent.append("[-] Couldn't find any ").append(Globals::Gui::CurrentComponentString).append(" property\n\n");
		return;
	}
}

void FindChildrenComponents()
{
	Globals::Namespace = Globals::Temp::NameSpaceSearch;

	for (uintptr_t u{}; Globals::m_vClasses.size() > u; ++u)
	{
		Globals::ChildrenComponentsName.push_back(Globals::m_vClasses.at(u)->m_pName);

		Globals::ChildrenComponents.push_back(Globals::GameObject->GetComponentInChildren(Globals::Temp::NameSpaceSearch.append(".").append(Globals::m_vClasses.at(u)->m_pName).c_str()));
		Globals::Temp::NameSpaceSearch = Globals::Namespace;
	}
}

void FindAllChildrenComponents()
{
	std::vector<Unity::il2cppClass*> classesBackup = Globals::m_vClasses;
	std::string NamespaceBackup;
	Unity::CComponent* tempComponent;

	for (uintptr_t u{}; Globals::ClassesNamespaces.size() > u; ++u)
	{	
		std::string tempNamespaceStr = Globals::ClassesNamespaces.at(u);

		IL2CPP::Class::FetchClasses(&Globals::m_vClasses, Globals::Temp::ModuleNameSearch.c_str(), tempNamespaceStr.c_str()); // To search classes (components) in their namespace only

		for (uintptr_t i{}; Globals::m_vClasses.size() > i; ++i)
		{
			NamespaceBackup = tempNamespaceStr;

			tempComponent = Globals::GameObject->GetComponentInChildren(tempNamespaceStr.append(".").append(Globals::m_vClasses.at(i)->m_pName).c_str());

			if (tempComponent != nullptr)
			{
				Globals::ChildrenComponents.push_back(tempComponent);
				Globals::ChildrenComponentsName.push_back(tempComponent->m_Object.m_pClass->m_pName);
			}

			tempNamespaceStr.clear();
			tempNamespaceStr = NamespaceBackup;
		}
	}

	Globals::m_vClasses = classesBackup; 
}

void FindNamespaces()
{
	std::string tempNamespace;

	for (uintptr_t u{}; Globals::m_vClasses.size() > u; ++u)
	{
		tempNamespace = Globals::m_vClasses.at(u)->m_pNamespace;

		if (tempNamespace == "\0" /*empty namespace*/)
		{
			continue;
		}

		if (std::find(Globals::ClassesNamespaces.begin(), Globals::ClassesNamespaces.end(), tempNamespace) != Globals::ClassesNamespaces.end()) // Skip if already present
		{
			continue;
		}

		Globals::ClassesNamespaces.push_back(tempNamespace);
	}
}