#pragma once
#include <ntifs.h>
#include <ntddk.h>

#include "../../../../../../Program Files (x86)/Windows Kits/10/Include/10.0.22621.0/shared/minwindef.h"



NTSTATUS DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath);

NTSTATUS DriverFilterUnload(_In_ PDRIVER_OBJECT DriverObject);

NTSTATUS Control(PDEVICE_OBJECT DeviceObject, PIRP Irp);

NTSTATUS OnCreate(PDEVICE_OBJECT DeviceObject, PIRP Irp);
NTSTATUS OnClose(PDEVICE_OBJECT DeviceObject, PIRP Irp);

