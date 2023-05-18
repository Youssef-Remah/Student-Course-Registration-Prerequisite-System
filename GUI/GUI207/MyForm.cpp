#include "MyForm.h"
#include"CourseBinaryTree.h"


using namespace System;
using namespace System::Windows::Forms;
[STAThreadAttribute]
//cli:: and System:: to be able to use std without conflict
void main(cli::array<System::String^>^ args) {

	//initiating our course tree , tree is built with constructor as well
	
	
	//dont touch
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	GUI207::MyForm form;
	Application::Run(% form);
	
	
	 
}
