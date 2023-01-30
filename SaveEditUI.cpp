/*
	Julian O. Rose
	TRC-SaveEditUI.cpp
	1-29-2023
*/

#include "SaveEditUI.h"
#include <iostream>
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

using namespace System;
using namespace System::Windows::Forms;

[STAThread]

int main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	TRCSaveEdit::SaveEditUI saveEdit;
	Application::Run(% saveEdit);

	return 0;
}