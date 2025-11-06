#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;

int main(array<String^>^ args) {

	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	SnakeGame::MainForm Form;
	Application::Run(% Form);

}

