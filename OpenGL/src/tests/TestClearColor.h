#pragma once

#include "tests.h"

namespace tests {

	class TestClearColor :
		public Test
	{
	public:
		TestClearColor();
		~TestClearColor();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnGUI() override;
	private:
		float m_clearColor[4];
	};

}