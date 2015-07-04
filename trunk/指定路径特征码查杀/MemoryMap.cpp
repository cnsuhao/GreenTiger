#include "stdafx.h"

#include <windows.h>
#include <stdio.h>

#include "MemoryMap.h"
#include "Hash.h"

#include "ReadVirusLib.h"

#include <stdlib.h>


VIRUSLIB StruVirusLibA[2];



//////////////////////////////////////////////////////////////////////////
//返回值 1成功
//		 0失败
bool MemoryMap(wchar_t WCFilePath[])
{
	HANDLE hFile ;//文件句柄
	HANDLE hMapFile; //文件内存映射区域的句柄
	LPVOID lpMapAddress;//内在映射区域的起始位置

	//////////////////////////////////////////////////////////////////////////
	//建一个文件

	hFile = CreateFile(WCFilePath,GENERIC_READ,0,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);//如果需要写权限请添加"|GENERIC_WRITE"

	if (INVALID_HANDLE_VALUE==hFile) 
	{
		OutputDebugString(L"File Create Error");
		return FALSE;
	}
	//////////////////////////////////////////////////////////////////////////
	//创建文件映射
	//GetFileSize的应用导致目标只能是小于2GB;
	DWORD FileSize=0;
	FileSize=GetFileSize(hFile,NULL);

	hMapFile = CreateFileMapping(hFile,NULL,PAGE_READONLY,0,FileSize,NULL);//如果需要写权限请改为PAGE_READWRITE

	if (NULL==hMapFile)
	{
		OutputDebugString(L"File Map Create Error");
		//释放fFile句柄
		if (!CloseHandle(hFile))
		{
			OutputDebugString(L"Close File Handle error");
			return FALSE;
		}
		return FALSE;
	}
	//////////////////////////////////////////////////////////////////////////
	//将文件映射到View
	lpMapAddress=MapViewOfFile(hMapFile,FILE_MAP_READ,0,0,0);//如果需要写权限请改为FILE_MAP_ALL_ACCESS
	if (NULL==lpMapAddress)
	{
		OutputDebugString(L"File Mappint Error");
		if(!CloseHandle(hMapFile))
		{
			OutputDebugString(L"Close File Mapping Handle error");
			return FALSE;
		}
		if (!CloseHandle(hFile))
		{
			OutputDebugString(L"Close File Handle error");
			return FALSE;
		}
		return FALSE;
	}
	//DO some thing...

	//干事
	//wscanf_s(L"%s",lpMapAddress);

	//发送指定内存长度的内容和路径
	//SendData(lpMapAddress,FileSize,WCFilePath);


	//////////////////////////////////////////////////////////////////////////
	//特征检测

	//Hash目标
	wchar_t Hash_result[256]={0};
	GetHash(CALG_MD5,*Hash_result, lpMapAddress,FileSize);
	//判断Hash

	ReadVirusLib();


	for (DWORD i=0;i<_countof(StruVirusLibA);i++)
	{


		if(0==wcscmp(StruVirusLibA[i].MD5,Hash_result))
		{



			//拼接提示字符串
			wchar_t WCTempstrA[256]={0};
			wchar_t WCMessageTipsA[]=L"检测到恶意程序!";
			wcscpy_s(WCTempstrA,WCMessageTipsA);
			wcscat_s(WCTempstrA,WCFilePath);
			wcscat_s(WCTempstrA,L"     是否添加到##重启删除##?");

			//逻辑:是恶意程序.提示,根据用户操作,确定:重启删除.取消:路径显示在界面上.

			int iAvgA=MessageBox(NULL,WCTempstrA,NULL,MB_OKCANCEL|MB_ICONWARNING);

			if (IDOK==iAvgA)
			{
				//确定,添加重启删除
				MoveFileEx
					(
					WCFilePath,NULL,MOVEFILE_DELAY_UNTIL_REBOOT
					);
				wprintf_s(L"重启你的电脑将删除恶意程序:%s\r\n",WCFilePath);
			}
			else if(IDCANCEL==iAvgA)
			{
				//取消,只输出提示信息
				wprintf_s(L"已忽略的威胁:%s\r\n",WCFilePath);

			}

			//拼接提示字符串
			wchar_t WCTempstrB[256]={0};
			wchar_t WCMessageTipsB[]=L"是否想从云上检索该恶意程序的行为?";
			wcscpy_s(WCTempstrB,WCMessageTipsB);
			

			//逻辑:是恶意程序.提示,根据用户操作,确定:重启删除.取消:路径显示在界面上.

			int iAvgB=MessageBox(NULL,WCTempstrB,NULL,MB_OKCANCEL|MB_USERICON);

			if (IDOK==iAvgB)
			{
				wchar_t WCSearchMD5[]=L"http://fireeye.ijinshan.com/analyse.html?md5=";
				wchar_t WCTemp[MAX_PATH]={0};
				wcscat_s(WCTemp,WCSearchMD5);
				wcscat_s(WCTemp,StruVirusLibA[i].MD5);
				ShellExecute(NULL,_T("open"),WCTemp,NULL,NULL,SW_SHOW);
			}
			
		}

	}






	//
	//////////////////////////////////////////////////////////////////////////
	//将映射的数据写回到硬盘上
	//FlushViewOfFile(lpMapAddress,0);需要在读取的时候加入写权限.



	//////////////////////////////////////////////////////////////////////////
	//关闭mappint对象
	if(!CloseHandle(hMapFile))
	{
		OutputDebugString(L"Close File Mapping Handle error");
		return FALSE;
	}
	if (!CloseHandle(hFile))
	{
		OutputDebugString(L"Close File Handle error");
		return FALSE;
	}

	return 1;

}