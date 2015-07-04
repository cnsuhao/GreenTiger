#include <Windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <stdio.h>

int WriteVirusLib();
int ReadVirusLib();



struct VIRUSLIB 
{
	wchar_t MD5[64];//32位长度是否会出问题?
	wchar_t VirusName[256];
	DWORD	VirusStyle;
	DWORD	Treatment;//关于如何独特地处理此病毒的方法顺序
	wchar_t	AddLibTime[256];
};

VIRUSLIB StruA[2]={
	L"d8f6566c5f9caa795204a40b3aaaafa2",
	L"ZeroAccessRootkit",NULL,NULL,
	L"2015-7-4 08:22:12",

	L"cb7c8b90a89767e5ab1f7cc6f644a30c",
	L"Bi mat 病毒",NULL,NULL,
	L"2015-7-4 08:27:56"
};

VIRUSLIB StruB[2]={0};

int main()
{
	//wchar_t WCVirusName[MAX_PATH]=L"cb7c8b90a89767e5ab1f7cc6f644a30c";
	////wchar_t WCSearchName[]=L"http://www.baidu.com/s?wd=";
	//wchar_t WCSearchMD5[]=L"http://fireeye.ijinshan.com/analyse.html?md5=";
	//wchar_t WCTemp[MAX_PATH]={0};
	//wcscat_s(WCTemp,WCSearchMD5);
	//wcscat_s(WCTemp,WCVirusName);
	//ShellExecute(NULL,_T("open"),WCTemp,NULL,NULL,SW_SHOW);


	int a=_countof(StruA);


	WriteVirusLib();
	ReadVirusLib();





	return 0;


}

int WriteVirusLib()
{
	FILE *fpWrite;
	_wfopen_s(&fpWrite,L"A.virlib",L"wb");

	if (fpWrite==nullptr)
	{
		return -1;
	}
	fwrite(&StruA,sizeof(StruA),1,fpWrite);

	fclose(fpWrite);



}


int ReadVirusLib()
{
	FILE *fpRead;
	_wfopen_s(&fpRead,L"A.virlib",L"rb");

	if (fpRead==nullptr)
	{
		return -1;
	}

	fread(&StruB,sizeof(StruB),1,fpRead);
	fclose(fpRead);
	
	return 0;

}


