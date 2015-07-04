#pragma once
#include <Windows.h>




bool MemoryMap(wchar_t WCFilePath[]);

//一个用于云交互的接口函数原形
//bool SendData( LPVOID StartMemoryStr,DWORD Legth,wchar_t FilePath[]);


struct VIRUSLIB 
{
	wchar_t MD5[64];//32位长度是否会出问题?
	wchar_t VirusName[256];
	DWORD	VirusStyle;
	DWORD	Treatment;//关于如何独特地处理此病毒的方法顺序
	wchar_t	AddLibTime[256];
};





