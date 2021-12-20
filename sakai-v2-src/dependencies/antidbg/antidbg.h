#pragma once
#include <cinttypes>
#include <Windows.h>
#include <Winternl.h>
#include <stdio.h>
#include <Tlhelp32.h>

// Error Codes
enum DBG_CATCH
{
	DBG_NONE = 0x0000,

	// Memory Codes (0x1000 range)
	DBG_BEINGEBUGGEDPEB = 0x1000,
	DBG_CHECKREMOTEDEBUGGERPRESENT = 0x1001,
	DBG_ISDEBUGGERPRESENT = 0x1002,
	DBG_NTGLOBALFLAGPEB = 0x1003,
	DBG_NTQUERYINFORMATIONPROCESS = 0x1004,
	DBG_FINDWINDOW = 0x1005,
	DBG_OUTPUTDEBUGSTRING = 0x1006,
	DBG_NTSETINFORMATIONTHREAD = 0x1007,
	DBG_DEBUGACTIVEPROCESS = 0x1008,
	DBG_PROCESSFILENAME = 0x1009,

	// CPU Codes (0x2000 range)
	DBG_HARDWAREDEBUGREGISTERS = 0x2000,
	DBG_MOVSS = 0x2001,

	// Timing Codes (0x3000 range)
	DBG_RDTSC = 0x3000,
	DBG_QUERYPERFORMANCECOUNTER = 0x3001,
	DBG_GETTICKCOUNT = 0x3002,

	// Exception Codes (0x4000 range)
	DBG_CLOSEHANDLEEXCEPTION = 0x4000,
	DBG_SINGLESTEPEXCEPTION = 0x4001,
	DBG_INT3CC = 0x4002,
	DBG_PREFIXHOP = 0x4003,
};

// Debugging messages
void DBG_MSG(WORD dbg_code, char* message);

// Dynamically resolved functions
typedef NTSTATUS(__stdcall* _NtQueryInformationProcess)(_In_ HANDLE, _In_  unsigned int, _Out_ PVOID, _In_ ULONG, _Out_ PULONG);
typedef NTSTATUS(__stdcall* _NtSetInformationThread)(_In_ HANDLE, _In_ THREAD_INFORMATION_CLASS, _In_ PVOID, _In_ ULONG);

typedef struct timeKeeper {
	uint64_t timeUpperA;
	uint64_t timeLowerA;
	uint64_t timeUpperB;
	uint64_t timeLowerB;
} TimeKeeper;

#ifdef _WIN64
extern "C"
{
	int adbg_BeingDebuggedPEBx64(void);
	int adbg_NtGlobalFlagPEBx64(void);
	void adbg_GetTickCountx64(void);
	void adbg_QueryPerformanceCounterx64(void);
	void adbg_RDTSCx64(TimeKeeper*);
	void adbg_Int2Dx64(void);
	void adbg_Int3x64(void);
	void adbg_SingleStepExceptionx64(void);
};
#endif

// Memory
bool adbg_BeingDebuggedPEB(void);
bool adbg_CheckRemoteDebuggerPresent(void);
bool adbg_CheckWindowClassName(void);
bool adbg_CheckWindowName(void);
bool adbg_ProcessFileName(void);
bool adbg_IsDebuggerPresent(void);
bool adbg_NtGlobalFlagPEB(void);
bool adbg_NtQueryInformationProcess(void);
bool adbg_NtSetInformationThread(void);
bool adbg_DebugActiveProcess(const char*);

// CPU
bool adbg_HardwareDebugRegisters(void);
bool adbg_MovSS(void);

// Timing
bool adbg_RDTSC(void);
bool adbg_QueryPerformanceCounter(void);
bool adbg_GetTickCount(void);

// Other
void adbg_CrashOllyDbg(void);

// Exception
bool adbg_CloseHandleException(void);
bool adbg_SingleStepException(void);
bool adbg_Int3(void);
bool adbg_Int2D(void);
bool adbg_PrefixHop(void);