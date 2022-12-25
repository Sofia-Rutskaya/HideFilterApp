#include "MyForm.h"
#include <Windows.h>

using namespace HideFilterApp;


[STAThreadAttribute]
void main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	HideFilterApp::MyForm form;
	Application::Run(% form);
}