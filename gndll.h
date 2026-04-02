#ifndef _DLL_H_
#define _DLL_H_
#include <windows.h>
#include <cmath>
#include <cstddef>
#include <cstring>
#if BUILDING_DLL
#define DLLIMPORT __declspec(dllexport)
#else
#define DLLIMPORT __declspec(dllimport)
#endif
#ifdef __cplusplus
extern "C"{
#endif
int DLLIMPORT logarithm(int base, int result);
void DLLIMPORT INIT_COUNTER();
void DLLIMPORT ADD_COUNTER();
int DLLIMPORT GET_COUNTER();
void DLLIMPORT fastprint(const char* str, size_t len);
int DLLIMPORT sum(int start, int end);
int DLLIMPORT prod(int start, int end);
int DLLIMPORT cp1251_2_utf8(const char* input, char* output, int out_size);
int DLLIMPORT signum(double val);
double DLLIMPORT clamp_gn(double val, double min, double max);
double DLLIMPORT lerp_gn(double a, double b, double t);
double DLLIMPORT get_pi();
const char* DLLIMPORT get_pc_name();
const char* DLLIMPORT get_user_name();
const char* DLLIMPORT get_nt_ver();
const char* DLLIMPORT get_sysarch();
void DLLIMPORT set_console_color(int col);
void DLLIMPORT rtimer();
void DLLIMPORT itimer();
const char* DLLIMPORT log_message(const char* msg, const char* type);
#ifdef __cplusplus
}
#endif
#endif
