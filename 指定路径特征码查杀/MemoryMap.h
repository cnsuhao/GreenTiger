#pragma once
#include <Windows.h>




bool MemoryMap(wchar_t WCFilePath[]);

//һ�������ƽ����Ľӿں���ԭ��
//bool SendData( LPVOID StartMemoryStr,DWORD Legth,wchar_t FilePath[]);


struct VIRUSLIB 
{
	wchar_t MD5[64];//32λ�����Ƿ�������?
	wchar_t VirusName[256];
	DWORD	VirusStyle;
	DWORD	Treatment;//������ζ��صش���˲����ķ���˳��
	wchar_t	AddLibTime[256];
};





