#include "Filter.h"

#define FILE_DEVICE_IOCTL 0x00008301
#define FSCTL_HIDE CTL_CODE(FILE_DEVICE_UNKNOWN, 0x811, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_UNHIDE CTL_CODE(FILE_DEVICE_UNKNOWN, 0x812, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define THE_BUFFER_LENGTH 80
UNICODE_STRING devName;
UNICODE_STRING symLink;
PDEVICE_OBJECT deviceObject = NULL;

typedef struct _DEVICE_EXTENSION
{
	unsigned char Image[THE_BUFFER_LENGTH];
}DEVICE_EXTENSION, * PDEVICE_EXTENSION;


NTSTATUS DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath) {
	UNREFERENCED_PARAMETER(RegistryPath);
	KdPrint(("Sample driver initialized successfully\n"));

	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = Control;
	DriverObject->MajorFunction[IRP_MJ_CREATE] = OnCreate;
	DriverObject->MajorFunction[IRP_MJ_CLOSE] = OnClose;
	DriverObject->DriverUnload = DriverFilterUnload;


	RtlInitUnicodeString(&devName, L"\\Device\\FilterHideFile");
	NTSTATUS status = IoCreateDevice(DriverObject, 16, &devName, 44444, 0, FALSE, &DriverObject->DeviceObject);
	RtlInitUnicodeString(&symLink, L"\\DosDevices\\FilterHideFileLink");
	status = IoCreateSymbolicLink(&symLink, &devName);

	if (!NT_SUCCESS(status)) {
		KdPrint(("Faild to create device object (0x%08X)\n", status));
		IoDeleteDevice(DriverObject->DeviceObject);
		return status;
	}

	KdPrint(("Entering DriverEntry\n"));
	return STATUS_SUCCESS;
}

NTSTATUS Control(PDEVICE_OBJECT DeviceObject, PIRP Irp) {

	//DbgPrint("Control\r\n");
	//UNREFERENCED_PARAMETER(DeviceObject);
	PFILE_BOTH_DIR_INFORMATION DirectoryInfo = {0}, Entry;


	PDEVICE_EXTENSION DeviceExtension = DeviceObject->DeviceExtension;
	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	NTSTATUS status = STATUS_SUCCESS;
	ULONG retLen = 0;
	PVOID InBuffer;
	PVOID OutBuffer = NULL;
	ULONG bufSize;
	FILE_BOTH_DIR_INFORMATION* pBuffer = {0};
	ULONG method;
	IO_STATUS_BLOCK		IoStatus = { 0x00 };
	HANDLE				hFile = NULL;
	OBJECT_ATTRIBUTES	oa;
	PFILE_OBJECT fileObj;
	ANSI_STRING szAnsiStr;
	UNICODE_STRING fileFullPath;
	UCHAR* uObjectName = {0};
	DbgPrint("FsFilter1  FsFilter1PreOperation --\n");
	DbgPrintEx(0, 0, ("win-driver: "__FUNCTION__""));
	//PFILE_DIRECTORY_INFORMATION	FileInfo, CurInfo;
	FILE_BASIC_INFORMATION	FileAttributes = { 0x00 };
	BOOLEAN bIsStarted = TRUE;
	switch (stack->Parameters.DeviceIoControl.IoControlCode)
	{

	case FSCTL_HIDE:
	{
		UNICODE_STRING unifilename;

		DbgPrint("FsFilter1  FsFilter1PreOperation --\n");

		DbgPrint("FsFilter1  HIDE !!!");

		//PUNICODE_STRING puszFileFullPath = {0};

		//RtlInitUnicodeString(&fileFullPath,  L"\\DosDevices\\C:\\Users\\Admin\\Desktop\\hide.txt");
	//	RtlInitUnicodeString(&fileFullPath, L"\\DosDevices\\C:\\Users\\Admin\\Desktop\\testHide.txt");


		//RtlInitUnicodeString(&fileFullPath, L"\\DosDevices\\C:\\Users\\Admin\\Desktop\\hide.txt");
		RtlInitUnicodeString(&fileFullPath, L"\\DosDevices\\C:\\Users\\Admin\\Desktop\\testHide.txt");


		DbgPrint("FsFilter1  FsFilter1PreOperation HIDE.TXT after RtlInitUnicodeString\n");

		//	status = ZwOpenFile(&hFile, SYNCHRONIZE, &oa, &IoStatus, FILE_SHARE_READ | FILE_SHARE_WRITE, FILE_OPEN);

		RtlInitUnicodeString(&unifilename, L"\\DosDevices\\C:\\Hidden\\");

		InitializeObjectAttributes(&oa, &unifilename,
			OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE,
			NULL, NULL);


		status = ZwCreateFile(&hFile,
			FILE_LIST_DIRECTORY,
			&oa,
			&IoStatus,
			NULL,
			0,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			FILE_OPEN,
			FILE_DIRECTORY_FILE,
			NULL,
			0);
		/*
		status = ZwCreateFile(&hFile,
			SYNCHRONIZE,
			&oa,
			&IoStatus,
			NULL,
			FILE_ATTRIBUTE_NORMAL,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			FILE_OPEN_IF,
			NULL, NULL, 0);*/



		if (!NT_SUCCESS(status)) {
			//	DbgPrint("Alert! 0x%0.8x, 0x%0.8x\r\n", status, IoStatus.Status);
			DbgPrint("ZwCreateFile failed \n");
			ZwClose(hFile);
			return status;
		}
		int Buffer[sizeof(FILE_FULL_DIR_INFORMATION) + 512];
		int i = 0;
		for (;;)
		{
			//
			// Get the contents of the directory, adding up the size as we go
			//
			status = ZwQueryDirectoryFile(hFile,
				NULL,
				NULL,
				0,
				&IoStatus,
				Buffer, 
				sizeof(Buffer),
				FileFullDirectoryInformation,
				-1,
				NULL,
				0);
			if (status == STATUS_PENDING)
			{
				//
				// Wait on the event
				//

				status = IoStatus.Status;
			}

			//
			// Check for success
			//
			if (!NT_SUCCESS(status))
			{
				//
				// Nothing left to enumerate. Close handles and free memory
				//
				DbgPrint("ZwQueryDirectoryFile failed \n");
				ZwClose(hFile);
			
				return STATUS_SUCCESS;
			}

			//
			// Loop every directory
			//
			Entry = DirectoryInfo;


			while (Entry)
			{
				//
				// List the file
				//
				DbgPrint("Entry: %s\n", uObjectName);
				if (++i > 20)
				{
					i = 0;
				
					while (TRUE)
					{
						if (uObjectName != NULL)
						{
							RtlCopyMemory(uObjectName, pBuffer->FileName, pBuffer->FileNameLength);
							DbgPrint("File name is: %S\n", uObjectName);
							
						}
						if (pBuffer->NextEntryOffset == 0)
							break;
						pBuffer += pBuffer->NextEntryOffset;
					}
					
				}

				//
				// Make sure we still have a file
				//
				if (!Entry->NextEntryOffset) break;

				//
				// Move to the next one
				//
				Entry = (PFILE_BOTH_DIR_INFORMATION)((ULONG_PTR)Entry +
					Entry->NextEntryOffset);
			}


			DbgPrint("FsFilter1  FsFilter1PreOperation HIDE.TXT after ZwCreateFile");

			//HANDLE hFileIn = {0};
			//memcpy(&hFileIn, InBuffer, sizeof(InBuffer));

			status = ZwQueryInformationFile(hFile, &IoStatus, &FileAttributes, sizeof(FileAttributes), FileBasicInformation);

			if (!NT_SUCCESS(status)) {
				DbgPrint("ZwQueryInformationFile failed \n");

				ZwClose(hFile);
				return status;
			}
			FileAttributes.FileAttributes = FILE_ATTRIBUTE_HIDDEN; // FILE_ATTRIBUTE_NORMAL
			status = ZwSetInformationFile(hFile, &IoStatus, &FileAttributes, sizeof(FileAttributes), FileBasicInformation);


			if (!NT_SUCCESS(status)) {
				DbgPrint("ZwSetInformationFile failed \n");
				ZwClose(hFile);
				return status;
			}

			ZwClose(hFile);
			return status;// FLT_PREOP_COMPLETE;	

		}
		break;
	case FSCTL_UNHIDE:
	{

		FILE_BASIC_INFORMATION	FileAttributes = { 0x00 };
		InBuffer = Irp->AssociatedIrp.SystemBuffer;
		//sizeBuf = stack->Parameters.DeviceIoControl.InputBufferLength;
		OutBuffer = Irp->AssociatedIrp.SystemBuffer;
		//	OutLength = stack->Parameters.DeviceIoControl.OutputBufferLength;

		KdPrint(("OutBuf 4 bytes: %s\n", OutBuffer));
		DbgPrint("FsFilter1  FsFilter1PreOperation --\n");

		WCHAR Name[200] = { 0 };

		DbgPrint("FsFilter1  HIDE !!!");

		//PUNICODE_STRING puszFileFullPath = {0};

		//RtlInitUnicodeString(&fileFullPath,  L"\\??\\C:\\Users\\Admin\\Desktop\\hide.txt");
		RtlInitUnicodeString(&fileFullPath, L"\\DosDevices\\C:\\Users\\Admin\\Desktop\\test22.txt");

		/*status = RtlUnicodeStringCopyString(
			puszFileFullPath,
			L"C:\\Users\\Admin\\Desktop\\hide.txt"
		);*/
		DbgPrint("FsFilter1  FsFilter1PreOperation HIDE.TXT after RtlInitUnicodeString\n");

		InitializeObjectAttributes(
			&oa,
			&fileFullPath,
			OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE,
			NULL,
			NULL
		);
		DbgPrint("FsFilter1  FsFilter1PreOperation HIDE.TXT after InitializeObjectAttributes\n");

		status = ZwCreateFile(&hFile, FILE_READ_ATTRIBUTES | FILE_WRITE_ATTRIBUTES,
			&oa, &IoStatus, NULL,
			FILE_ATTRIBUTE_NORMAL,
			0, FILE_OPEN, NULL, NULL, 0);

		KdPrint(("FsFilter1  FsFilter1PreOperation HIDE.TXT after ZwCreateFile %u", status));
		//DbgPrint("FsFilter1  FsFilter1PreOperation HIDE.TXT after ZwCreateFile");



		status = ZwQueryInformationFile(hFile, &IoStatus, &FileAttributes, sizeof(FileAttributes), FileBasicInformation);

		if (!NT_SUCCESS(status)) {
			DbgPrint("ZwQueryInformationFile failed \n");

			ZwClose(hFile);
			return status;
		}

		FileAttributes.FileAttributes = FILE_ATTRIBUTE_NORMAL;
		IoStatus.Information = retLen;
		status = ZwSetInformationFile(hFile, &IoStatus, &FileAttributes, sizeof(FileAttributes), FileBasicInformation);


		if (!NT_SUCCESS(status)) {
			DbgPrint("ZwSetInformationFile failed \n");
			ZwClose(hFile);
			return status;
		}

		ZwClose(hFile);
		return status;// FLT_PREOP_COMPLETE;	

	}
	break;
	default:
		switch (method = stack->Parameters.DeviceIoControl.IoControlCode & 0x03L) {
		case METHOD_BUFFERED:
			KdPrint(("IOCTL METHOD_BUFFERED\r\n"));

			InBuffer = Irp->AssociatedIrp.SystemBuffer;
			//	InLength = stack->Parameters.DeviceIoControl.InputBufferLength;
			OutBuffer = Irp->AssociatedIrp.SystemBuffer;
			//	OutLength = stack->Parameters.DeviceIoControl.OutputBufferLength;

			KdPrint(("OutBuf 4 bytes: %.4s\n", OutBuffer));
			KdPrint(("----------------------------\n"));
			break;
		case METHOD_IN_DIRECT:
			KdPrint(("IOCTL METHOD_IN_DIRECT\r\n"));
			OutBuffer = Irp->AssociatedIrp.SystemBuffer;
			//OutLength = stack->Parameters.DeviceIoControl.OutputBufferLength;
			InBuffer = MmGetSystemAddressForMdl(Irp->MdlAddress);
			//	InLength = stack->Parameters.DeviceIoControl.InputBufferLength;


			KdPrint(("OutBuf 4 bytes: %.4s\n", OutBuffer));
			KdPrint(("----------------------------\n"));
			break;
		case METHOD_OUT_DIRECT:
			KdPrint(("IOCTL METHOD_OUT_DIRECT\r\n"));
			InBuffer = Irp->AssociatedIrp.SystemBuffer;
			//	InLength = stack->Parameters.DeviceIoControl.InputBufferLength;
			OutBuffer = MmGetSystemAddressForMdl(Irp->MdlAddress);
			//	OutLength = stack->Parameters.DeviceIoControl.OutputBufferLength;

			KdPrint(("OutBuf 4 bytes: %.4s\n", OutBuffer));
			KdPrint(("----------------------------\n"));
			break;
		case METHOD_NEITHER:
			KdPrint(("IOCTL METHOD_NEITHER\r\n"));
			InBuffer = stack->Parameters.DeviceIoControl.Type3InputBuffer;
			//	InLength = stack->Parameters.DeviceIoControl.InputBufferLength;
			OutBuffer = Irp->UserBuffer;
			//	OutLength = stack->Parameters.DeviceIoControl.OutputBufferLength;

			KdPrint(("OutBuf 4 bytes: %s\n", OutBuffer));
			KdPrint(("----------------------------\n"));
			break;
		}
		break;
	}

	Irp->IoStatus.Status = status;
	Irp->IoStatus.Information = retLen;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return status;
	}
}

NTSTATUS DriverFilterUnload(_In_ PDRIVER_OBJECT DriverObject) {
	DbgPrint("Sample driver Unload called\n");
	IoDeleteSymbolicLink(&symLink);
	IoDeleteDevice(DriverObject->DeviceObject);
	return STATUS_SUCCESS;
};

NTSTATUS OnCreate(PDEVICE_OBJECT DeviceObject, PIRP Irp) {

	UNREFERENCED_PARAMETER(DeviceObject);
	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;
	IoCompleteRequest(Irp, 0);
	DbgPrint("OnCreate function successfully completed\n");
	return STATUS_SUCCESS;
};
NTSTATUS OnClose(PDEVICE_OBJECT DeviceObject, PIRP Irp) {
	UNREFERENCED_PARAMETER(DeviceObject);
	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;
	IoCompleteRequest(Irp, 0);
	DbgPrint("OnClose function successfully completed\n");
	return STATUS_SUCCESS;
};
