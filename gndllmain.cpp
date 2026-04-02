#include "gndll.h"
#include <windows.h>
#include <cmath>
#include <cstddef>
#include <cstring>
#include <stdio.h>
extern "C"{
static int counter = 0;
static LARGE_INTEGER start_time;
static LARGE_INTEGER freq;
static bool init_timer = false;
__declspec(dllexport) int WINAPI logarithm(int base, int result){
	if (base <= 1 || result <= 0) {
		return 0;
	}
	return (int)(std::log(result)/std::log(base));
}
__declspec(dllexport) void WINAPI INIT_COUNTER(){
	counter = 0;
}
__declspec(dllexport) void WINAPI ADD_COUNTER(){
	counter = counter + 1;
}
__declspec(dllexport) int WINAPI GET_COUNTER(){
	return counter;
}


__declspec(dllexport) void WINAPI fastprint(const char* str, size_t len){
	if (len == 0) len = std::strlen(str);
	HANDLE  hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;
	DWORD written;
	WriteFile(hStdOut, str, static_cast<DWORD>(len), &written, nullptr);
}

__declspec(dllexport) int WINAPI sum(int start, int end){
	int m;
	for (int i = start; i<(end+1); i++){
		m += i;
	}
	return m;
}

__declspec(dllexport) int WINAPI prod(int start, int end){
	int m = 1;
	for (int i = start; i<(end+1); i++){
		m *= i;
	}
	return m;
}

__declspec(dllexport) int WINAPI cp1251_2_utf8(const char* input, char* output, int out_size){
	int ws = MultiByteToWideChar(1251,0,input,-1,NULL,0);
	if (!ws) return 0;
	wchar_t* wide = new wchar_t[ws];
	int utf8_s = WideCharToMultiByte(CP_UTF8,0,wide,-1,NULL,0,NULL,NULL);
	if (utf8_s > out_size){
		delete[] wide;
		return -1;
	}
	WideCharToMultiByte(CP_UTF8, 0, wide, -1, output, out_size,NULL,NULL);
	delete[] wide;
	return utf8_s;
}
__declspec(dllexport) int WINAPI signum(double val){
	return (0 < val) - (val < 0);
}
__declspec(dllexport) double WINAPI clamp_gn(double val, double min, double max){
	if (val < min) return min;
	if (val > max) return max;
	return val;
}
__declspec(dllexport) double WINAPI lerp_gn(double a, double b, double t){
	return a + t * (b - a);
}
__declspec(dllexport) double WINAPI get_pi(){
	return 3.14159265358979323846;
}
__declspec(dllexport) const char* WINAPI get_pc_name(){
	static char buffer[MAX_COMPUTERNAME_LENGTH+1];
	DWORD size = sizeof(buffer);
	if(GetComputerNameA(buffer, &size)){
		return buffer;
	}
	return "";
}
__declspec(dllexport) const char* WINAPI get_user_name(){
	static char buffer[256];
	DWORD size = sizeof(buffer);
	if(GetUserNameA(buffer,&size)){
		return buffer;
	}
	return "";
}
__declspec(dllexport) const char* WINAPI get_nt_ver(){
	static char buffer[16];
	OSVERSIONINFO osvi;
	ZeroMemory(&osvi,sizeof(OSVERSIONINFO));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	
	if(GetVersionEx(&osvi)){
		sprintf(buffer, "%d.%d", osvi.dwMajorVersion, osvi.dwMinorVersion);
		return buffer;
	}
	return "Unknown NT";
}
__declspec(dllexport) const char* WINAPI get_sysarch(){
	SYSTEM_INFO si;
	GetNativeSystemInfo(&si);
	
	if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64){
		return "64-bit (x64)";
	} else if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL){
		return "32-bit (x86)";
	}
	return "Unknown arch";
}
__declspec(dllexport) void WINAPI set_console_color(int col){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, col);
}
__declspec(dllexport) void WINAPI itimer(){
	if (!init_timer){
		QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&start_time);
		init_timer = true;
	}
}
__declspec(dllexport) void WINAPI rtimer(){
	QueryPerformanceCounter(&start_time);
}
__declspec(dllexport) const char* WINAPI log_message(const char* msg, const char* type){
	itimer();
	LARGE_INTEGER now;
	QueryPerformanceCounter(&now);
	double elapsed = (double)(now.QuadPart - start_time.QuadPart) / (double)freq.QuadPart;
	thread_local char buffer[4096];
	snprintf(buffer, sizeof(buffer), "[%.4f] [%s] %s\n", elapsed, type, msg);
	return buffer;
}
}
BOOL WINAPI DllMain(HINSTANCE hinstDLL,DWORD fdwReason,LPVOID lpvReserved)
{
	switch(fdwReason)
	{
		case DLL_PROCESS_ATTACH:
		{
			break;
		}
		case DLL_PROCESS_DETACH:
		{
			break;
		}
		case DLL_THREAD_ATTACH:
		{
			break;
		}
		case DLL_THREAD_DETACH:
		{
			break;
		}
	}
	
	/* Return TRUE on success, FALSE on failure */
	return TRUE;
}
