#pragma once

#include <Windows.h>
#include <wchar.h>
//#include <WinNls.h>

bool GetHash(int Hash_type,wchar_t &Hash_result, static PVOID StartMemoryStr,DWORD Legth);

void C2W(wchar_t *pwstr,size_t len,const char *str);

