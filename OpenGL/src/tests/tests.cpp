#include "tests.h"

#include "imgui\imgui.h"

namespace tests {

	TestMenu::TestMenu(Test*& currentTest)
		: m_currentTest(currentTest)
	{

	}

	void TestMenu::OnGUI()
	{
		for (auto& test : m_tests)
		{
			if (ImGui::Button(test.first.c_str()))
				m_currentTest = test.second();
		}
	}

}
