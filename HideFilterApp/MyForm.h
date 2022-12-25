#pragma once
#pragma comment (lib, "Setupapi.lib")
#pragma comment(lib,"Advapi32.lib")
#include <Windows.h>
#include <vcclr.h>
#include <string>
#include <setupapi.h>
#include <clocale>
#include <msclr/marshal.h>
#include <msclr/marshal_cppstd.h>
using namespace System;
using namespace msclr::interop;

#define FILE_DEVICE_IOCTL 0x00008301
#define FSCTL_HIDE CTL_CODE(FILE_DEVICE_UNKNOWN, 0x811, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_UNHIDE CTL_CODE(FILE_DEVICE_UNKNOWN, 0x812, METHOD_BUFFERED, FILE_ANY_ACCESS)


namespace HideFilterApp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	protected:
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Button^ Add_File_Btn;


	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ driverToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ startDriverToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ stopDriverToolStripMenuItem;
	private: System::Windows::Forms::Button^ Open_File_Dir_Btn;

	private: System::Windows::Forms::Button^ Remove_All_Btn;

	private: System::Windows::Forms::Button^ Remove_Btn;

	private: System::Windows::Forms::ListBox^ listBox1;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->Open_File_Dir_Btn = (gcnew System::Windows::Forms::Button());
			this->Remove_All_Btn = (gcnew System::Windows::Forms::Button());
			this->Remove_Btn = (gcnew System::Windows::Forms::Button());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->Add_File_Btn = (gcnew System::Windows::Forms::Button());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->driverToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->startDriverToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->stopDriverToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->panel1->SuspendLayout();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(130, 33);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(268, 21);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Фільтрування файлової системи";
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->Open_File_Dir_Btn);
			this->panel1->Controls->Add(this->Remove_All_Btn);
			this->panel1->Controls->Add(this->Remove_Btn);
			this->panel1->Controls->Add(this->listBox1);
			this->panel1->Controls->Add(this->Add_File_Btn);
			this->panel1->Location = System::Drawing::Point(12, 57);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(588, 399);
			this->panel1->TabIndex = 1;
			// 
			// Open_File_Dir_Btn
			// 
			this->Open_File_Dir_Btn->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Open_File_Dir_Btn->Location = System::Drawing::Point(27, 319);
			this->Open_File_Dir_Btn->Name = L"Open_File_Dir_Btn";
			this->Open_File_Dir_Btn->Size = System::Drawing::Size(270, 42);
			this->Open_File_Dir_Btn->TabIndex = 5;
			this->Open_File_Dir_Btn->Text = L"Відкрити розташування файлу";
			this->Open_File_Dir_Btn->UseVisualStyleBackColor = true;
			this->Open_File_Dir_Btn->Click += gcnew System::EventHandler(this, &MyForm::Open_File_Dir_Btn_Click);
			// 
			// Remove_All_Btn
			// 
			this->Remove_All_Btn->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Remove_All_Btn->Location = System::Drawing::Point(27, 215);
			this->Remove_All_Btn->Name = L"Remove_All_Btn";
			this->Remove_All_Btn->Size = System::Drawing::Size(270, 42);
			this->Remove_All_Btn->TabIndex = 4;
			this->Remove_All_Btn->Text = L"Видалити всі файли";
			this->Remove_All_Btn->UseVisualStyleBackColor = true;
			this->Remove_All_Btn->Click += gcnew System::EventHandler(this, &MyForm::Remove_All_Btn_Click);
			// 
			// Remove_Btn
			// 
			this->Remove_Btn->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Remove_Btn->Location = System::Drawing::Point(27, 118);
			this->Remove_Btn->Name = L"Remove_Btn";
			this->Remove_Btn->Size = System::Drawing::Size(270, 42);
			this->Remove_Btn->TabIndex = 3;
			this->Remove_Btn->Text = L"Видалили файл";
			this->Remove_Btn->UseVisualStyleBackColor = true;
			this->Remove_Btn->Click += gcnew System::EventHandler(this, &MyForm::Remove_Btn_Click);
			// 
			// listBox1
			// 
			this->listBox1->Dock = System::Windows::Forms::DockStyle::Right;
			this->listBox1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->listBox1->FormattingEnabled = true;
			this->listBox1->ItemHeight = 21;
			this->listBox1->Location = System::Drawing::Point(324, 0);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(264, 399);
			this->listBox1->TabIndex = 2;
			// 
			// Add_File_Btn
			// 
			this->Add_File_Btn->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Add_File_Btn->Location = System::Drawing::Point(27, 27);
			this->Add_File_Btn->Name = L"Add_File_Btn";
			this->Add_File_Btn->Size = System::Drawing::Size(270, 42);
			this->Add_File_Btn->TabIndex = 1;
			this->Add_File_Btn->Text = L"Додати файл";
			this->Add_File_Btn->UseVisualStyleBackColor = true;
			this->Add_File_Btn->Click += gcnew System::EventHandler(this, &MyForm::Add_File_Btn_Click);
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->driverToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(612, 24);
			this->menuStrip1->TabIndex = 2;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// driverToolStripMenuItem
			// 
			this->driverToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->startDriverToolStripMenuItem,
					this->stopDriverToolStripMenuItem
			});
			this->driverToolStripMenuItem->Name = L"driverToolStripMenuItem";
			this->driverToolStripMenuItem->Size = System::Drawing::Size(50, 20);
			this->driverToolStripMenuItem->Text = L"Driver";
			// 
			// startDriverToolStripMenuItem
			// 
			this->startDriverToolStripMenuItem->Name = L"startDriverToolStripMenuItem";
			this->startDriverToolStripMenuItem->Size = System::Drawing::Size(131, 22);
			this->startDriverToolStripMenuItem->Text = L"Start driver";
			this->startDriverToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::startDriverToolStripMenuItem_Click);
			// 
			// stopDriverToolStripMenuItem
			// 
			this->stopDriverToolStripMenuItem->Name = L"stopDriverToolStripMenuItem";
			this->stopDriverToolStripMenuItem->Size = System::Drawing::Size(131, 22);
			this->stopDriverToolStripMenuItem->Text = L"Stop driver";
			this->stopDriverToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::stopDriverToolStripMenuItem_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(612, 468);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->panel1->ResumeLayout(false);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		SC_HANDLE schService;
		SC_HANDLE schSCManager;
		HANDLE hFile;
		LPCWSTR name = L"HideFileFilter";
	BOOL SendCtlCode(HANDLE hDevice, DWORD CtlCode, HANDLE InBuf, DWORD InBufSize, HANDLE OutBuf, DWORD OutBufSize) {

		ULONG returnLength = 0;
		if (hDevice != INVALID_HANDLE_VALUE && hDevice != NULL)
		{

			
			if (!DeviceIoControl(
				hDevice,
				CtlCode,
				InBuf,
				InBufSize,
				OutBuf,
				OutBufSize,
				&returnLength,
				0
			))
			{
				MessageBox::Show("DeviceIoControl is failed! Code: " + GetLastError().ToString() + ".\r\n");
				return FALSE;
			}
			
		}
		else
		{
			MessageBox::Show("Invalid handle value!\r\n");
			return FALSE;
		}

		return TRUE;
	}

private: System::Void Add_File_Btn_Click(System::Object^ sender, System::EventArgs^ e) {
	

	IO::Stream^ myStream;
	OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;

	STORAGE_DEVICE_DESCRIPTOR* buffer;
	openFileDialog1->InitialDirectory = "c:\\";
	openFileDialog1->Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
	openFileDialog1->FilterIndex = 2;
	openFileDialog1->RestoreDirectory = true;

	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		listBox1->Items->Add(openFileDialog1->FileName);

	//	pin_ptr<const wchar_t> wname = PtrToStringChars(openFileDialog1->FileName);
		//Message = wname;

		//std::string st = marshal_as<std::string, String^>(openFileDialog1->FileName);

		//strcpy(MessageIn, st.c_str());
		if ((myStream = openFileDialog1->OpenFile()) != nullptr)
		{
			// Insert code to read the stream here.
			myStream->Close();
		}
	}

	
	HANDLE hDev;
	ULONG returnLength = 0;

	HANDLE hFile;
	hDev = CreateFile(L"\\\\.\\FilterHideFileLink",
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_OVERLAPPED, // FILE_FLAG_OVERLAPPED   FILE_ATTRIBUTE_DEVICE
		NULL);


	//hFile = CreateFile(L"C:\\Users\\Admin\\Desktop\\testHide.txt",
	//	GENERIC_READ | GENERIC_WRITE | FILE_READ_ATTRIBUTES | FILE_WRITE_ATTRIBUTES,
	//	0,
	//	NULL,
	//	OPEN_EXISTING,
	//	FILE_ATTRIBUTE_NORMAL, // FILE_FLAG_OVERLAPPED   FILE_ATTRIBUTE_DEVICE
	//	NULL);

	//DWORD dwBytesWritten = 0;
	//if (WriteFile(hFile, "testHide.txt", 13, &dwBytesWritten, NULL)) {
	//	MessageBox::Show("File writen!\r\n");
	//}

		//hDev = CreateFile(L"C:\\Users\\Admin\\Desktop\\Filter\\testfile.txt",
		//GENERIC_READ | GENERIC_WRITE,
		//0,
		//NULL,
		//OPEN_EXISTING,
		//FILE_ATTRIBUTE_NORMAL, // FILE_FLAG_OVERLAPPED   FILE_ATTRIBUTE_DEVICE
		//NULL);

	if (hDev == 0 || hDev == INVALID_HANDLE_VALUE)
		MessageBox::Show("File cannot be open! Code: " + GetLastError().ToString() + ".\r\n");
	
	CreateDirectory(L"C:\\Hidden", NULL);

	MoveFile(L"C:\\Users\\Admin\\Desktop\\test22.txt", L"C:\\Hidden\\test22.txt");

	char MessageIn[8] = "id.txt";
	char MessageOut[8] = {0};

	SendCtlCode(hDev, FSCTL_HIDE, MessageIn, 8, MessageOut, 8);

	
//	SendCtlCode(hDev, FSCTL_HIDE, hFile, sizeof(hFile), hFile, sizeof(hFile));
	//SendCtlCode(hDev, DEVICE_SEND_BUFF, messageIn, 8, messageOut, 16);
	/*

	char MessageI[37] = "C:\\Users\\Admin\\Desktop\\testHide.txt";
	SendCtlCode(hDev, FSCTL_HIDE, MessageI, 37, MessageOut, 37);
	

	char MessageI1[42] = "\\??\\C:\\Users\\Admin\\Desktop\\testHide.txt\0";
	SendCtlCode(hDev, FSCTL_HIDE, MessageI1, 42, MessageOut, 42);

	*/
	if (!CloseHandle(hDev))
		MessageBox::Show("File is closed! Code: " + GetLastError().ToString() + ".\r\n");
		


}
private: System::Void Remove_Btn_Click(System::Object^ sender, System::EventArgs^ e) {
	if (listBox1->SelectedIndex >= 0) {
		listBox1->Items->Remove(listBox1->Items[listBox1->SelectedIndex]);
	
		HANDLE hDev;
		ULONG returnLength = 0;

		hDev = CreateFile(L"\\\\.\\FilterHideFileLink",
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL, // FILE_FLAG_OVERLAPPED   FILE_ATTRIBUTE_DEVICE
			NULL);

		if (hDev == 0 || hDev == INVALID_HANDLE_VALUE)
			MessageBox::Show("File cannot be open! Code: " + GetLastError().ToString() + ".\r\n");


		char messageIn[10] = "C:\\Users\\";
		char messageOut[16] = { 0 };


		SendCtlCode(hDev, FSCTL_UNHIDE, messageIn, 8, messageOut, 16);
		//SendCtlCode(hDev, DEVICE_SEND_BUFF, messageIn, 8, messageOut, 16);


		if (!CloseHandle(hDev))
			MessageBox::Show("File is closed! Code: " + GetLastError().ToString() + ".\r\n");

	}
}
private: System::Void Remove_All_Btn_Click(System::Object^ sender, System::EventArgs^ e) {
	int count = listBox1->Items->Count;
	for (int i = 0; i < count; i++) {
		listBox1->Items->Remove(listBox1->Items[0]);
	}
}
private: System::Void Open_File_Dir_Btn_Click(System::Object^ sender, System::EventArgs^ e) {
}

	   
private: System::Void startDriverToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	HINF hinf;
	BOOL ret;
	BOOL FileWasInUse = FALSE;
	//PCWSTR Path = L"C:\\Users\\Admin\\Desktop\\Filter\\FsFilter1.inf";
	PCWSTR Path = L"C:\\Users\\Admin\\Desktop\\Filter\\HideFilter.sys";


	schSCManager = OpenSCManager(
		NULL,                    // local computer
		NULL,                    // ServicesActive database 
		SC_MANAGER_ALL_ACCESS);  // full access rights 

	if (NULL == schSCManager)
	{
		MessageBox::Show("OpenSCManager failed. Code: " + GetLastError().ToString() + ".\r\n");
		
	}

	//hinf = SetupOpenInfFileA("C:\\Users\\Admin\\Desktop\\Filter\\FsFilter1.inf", NULL, INF_STYLE_WIN4, NULL);
	//if (NULL == hinf || hinf == INVALID_HANDLE_VALUE)
	//	{
	//		MessageBox::Show("SetupOpenInfFileA failed. Code: " + GetLastError().ToString() + ".\r\n");
	//	}
	//else MessageBox::Show("SetupOpenInfFileA success.\r\n");

	//RUNDLL32.EXE SETUPAPI.DLL,InstallHinfSection DefaultInstall 132 C:\\Users\\Admin\\Desktop\\Filter\\FsFilter1.inf
	
	
	
	schService = CreateService(
		schSCManager,
		name,
		name,
		SERVICE_ALL_ACCESS,
		SERVICE_FILE_SYSTEM_DRIVER,
		SERVICE_DEMAND_START,      // start type 
		SERVICE_ERROR_NORMAL,
		Path,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL);

	//if (schService == NULL)
	//{
	//	MessageBox::Show("CreateService failed. Code: " + GetLastError().ToString() + ".\r\n");
	//}
	//
	//
	
	//InstallHinfSection(NULL, NULL, TEXT("DefaultInstall 132 C:\\Users\\Admin\\Desktop\\Filter\\FsFilter1.inf"), 0);






	//if (!SetupInstallServicesFromInfSectionA(hinf, "DefaultInstall", SPSVCINST_TAGTOFRONT))
	//{
	//	MessageBox::Show("SetupInstallServicesFromInfSectionA failed. Code: " + GetLastError().ToString() + ".\r\n");
	//}
	//else MessageBox::Show("SetupInstallServicesFromInfSectionA success.\r\n");



	//if (!SetupInstallFileEx(hinf, NULL, L"FsFilter1.sys", L"C:\\Users\\Admin\\Desktop\\Filter\\", L"C:\\Users\\Admin\\Desktop\\Filter\\FsFilter1.sys", SP_COPY_NEWER_OR_SAME, NULL, NULL, &FileWasInUse))
	//{
	//	MessageBox::Show("SetupInstallFileA failed " + GetLastError().ToString() + ".\r\n");
	//}
	//else MessageBox::Show("SetupInstallFileA success.\r\n");


	//SC_HANDLE service = CreateService(schSCManager,
	//	L"FsFilter1",
	//	L"FsFilter1",
	//	SERVICE_ALL_ACCESS,
	//	SERVICE_FILE_SYSTEM_DRIVER,
	//	SERVICE_DEMAND_START,
	//	SERVICE_ERROR_NORMAL,
	//	NULL, // L"system32\\drivers\\FsFilter1.sys"
	//	NULL, NULL, NULL, NULL, NULL);


	/*if (NULL == service)
	{
		MessageBox::Show("CreateService failed. Code: " + GetLastError().ToString() + ".\r\n");

	}*/

	schService = OpenService(
		schSCManager,            // SCM database 
		name,             // name of service 
		SERVICE_ALL_ACCESS);  // need change config access 

	if (schService == NULL)
	{
		//LogBox->Text += "OpenService failed " + GetLastError().ToString() + ".\r\n";
		
		MessageBox::Show("OpenService failed. Code: " + GetLastError().ToString() + ".\r\n");
		return;
	}
	//else MessageBox::Show("Service opened successfully.\r\n");


	if (!StartService(
		schService,            // SCM database 
		0,              // name of service 
		NULL))  // need change config access 
	{
		MessageBox::Show("StartService failed. Code: " + GetLastError().ToString() + ".\r\n");
		//LogBox->Text += "StartService failed " + GetLastError().ToString() + ".\r\n";
		return;
	}

	//SetupCloseInfFile(hinf);


	//schSCManager = OpenSCManager(
	//	NULL,                    // local computer
	//	NULL,                    // ServicesActive database 
	//	SC_MANAGER_ALL_ACCESS);  // full access rights 

	//if (NULL == schSCManager)
	//{
	//	MessageBox::Show("OpenSCManager failed. Code: " + GetLastError().ToString() + ".\r\n");
	//	//LogBox->Text += "OpenSCManager failed " + GetLastError().ToString() + ".\r\n";
	//}
	////else LogBox->Text += "OpenSCManager was successful.\r\n";

	//schService = CreateServiceW(
	//	schSCManager,
	//	name,
	//	name,
	//	SERVICE_ALL_ACCESS,
	//	SERVICE_FILE_SYSTEM_DRIVER,
	//	SERVICE_DEMAND_START,      // start type 
	//	SERVICE_ERROR_NORMAL,
	//	Path,
	//	NULL,
	//	NULL,
	//	NULL,
	//	NULL,
	//	NULL);

	//if (schService == NULL)
	//{
	//	MessageBox::Show("CreateService failed. Code: " + GetLastError().ToString() + ".\r\n");
	//	//LogBox->Text += "CreateService failed " + GetLastError().ToString() + ".\r\n";
	//	return;
	//}
	////else LogBox->Text += "Service created successfully.\r\n";

	//schService = OpenService(
	//	schSCManager,            // SCM database 
	//	name,             // name of service 
	//	SC_MANAGER_ALL_ACCESS | SERVICE_ALL_ACCESS);  // need change config access 

	//if (schService == NULL)
	//{
	//	//LogBox->Text += "OpenService failed " + GetLastError().ToString() + ".\r\n";
	//	
	//	MessageBox::Show("OpenService failed. Code: " + GetLastError().ToString() + ".\r\n");
	//	return;
	//}
	////else MessageBox::Show("Service opened successfully.\r\n");

	//if (!StartService(
	//	schService,            // SCM database 
	//	NULL,              // name of service 
	//	NULL))  // need change config access 
	//{
	//	MessageBox::Show("StartService failed. Code: " + GetLastError().ToString() + ".\r\n");
	//	//LogBox->Text += "StartService failed " + GetLastError().ToString() + ".\r\n";
	//	return;
	//}
//	else LogBox->Text += "Service started successfully.\r\n";


	//hFile = CreateFile(L"\\\\.\\FsFilterHideLink", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	//if (hFile == 0)
	//	MessageBox::Show("File cannot be open! Code: " + GetLastError().ToString() + ".\r\n");
	//	LogBox->Text += "File cannot be open! " + GetLastError().ToString() + "\r\n";
	//else
//LogBox->Text += "File is open! \r\n";
}
private: System::Void stopDriverToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

	SERVICE_STATUS_PROCESS ssp;
	DWORD dwBytesNeeded;

	if (!QueryServiceStatusEx(
		schService,
		SC_STATUS_PROCESS_INFO,
		(LPBYTE)&ssp,
		sizeof(SERVICE_STATUS_PROCESS),
		&dwBytesNeeded))
	{
		MessageBox::Show("QueryServiceStatusEx failed. Code: " + GetLastError().ToString() + ".\r\n");
		//LogBox->Text += "QueryServiceStatusEx failed " + GetLastError().ToString() + ".\r\n";
	}

	if (ssp.dwCurrentState == SERVICE_STOPPED)
	{
		MessageBox::Show("Service is already stopped.\r\n");

		//LogBox->Text += "Service is already stopped.\r\n";
		return;
	}

	if (!ControlService(schService, SERVICE_CONTROL_STOP, (LPSERVICE_STATUS)&ssp))
	{
		MessageBox::Show("ControlService failed. Code: " + GetLastError().ToString() + ".\r\n");
		//LogBox->Text += "ControlService failed " + GetLastError().ToString() + ".\r\n";

		return;
	}

	//if (!DeleteService(schService))
	//{
	//	MessageBox::Show("DeleteService failed. Code: " + GetLastError().ToString() + ".\r\n");
	//}

	CloseServiceHandle(schService);
	CloseServiceHandle(schSCManager);

	//else LogBox->Text += "Service stopped successfully.\r\n";
}
};
}
