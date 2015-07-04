#include "stdafx.h"

#include <windows.h>
#include <stdio.h>

#include "MemoryMap.h"
#include "Hash.h"

#include "ReadVirusLib.h"

#include <stdlib.h>


VIRUSLIB StruVirusLibA[2];



//////////////////////////////////////////////////////////////////////////
//����ֵ 1�ɹ�
//		 0ʧ��
bool MemoryMap(wchar_t WCFilePath[])
{
	HANDLE hFile ;//�ļ����
	HANDLE hMapFile; //�ļ��ڴ�ӳ������ľ��
	LPVOID lpMapAddress;//����ӳ���������ʼλ��

	//////////////////////////////////////////////////////////////////////////
	//��һ���ļ�

	hFile = CreateFile(WCFilePath,GENERIC_READ,0,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);//�����ҪдȨ�������"|GENERIC_WRITE"

	if (INVALID_HANDLE_VALUE==hFile) 
	{
		OutputDebugString(L"File Create Error");
		return FALSE;
	}
	//////////////////////////////////////////////////////////////////////////
	//�����ļ�ӳ��
	//GetFileSize��Ӧ�õ���Ŀ��ֻ����С��2GB;
	DWORD FileSize=0;
	FileSize=GetFileSize(hFile,NULL);

	hMapFile = CreateFileMapping(hFile,NULL,PAGE_READONLY,0,FileSize,NULL);//�����ҪдȨ�����ΪPAGE_READWRITE

	if (NULL==hMapFile)
	{
		OutputDebugString(L"File Map Create Error");
		//�ͷ�fFile���
		if (!CloseHandle(hFile))
		{
			OutputDebugString(L"Close File Handle error");
			return FALSE;
		}
		return FALSE;
	}
	//////////////////////////////////////////////////////////////////////////
	//���ļ�ӳ�䵽View
	lpMapAddress=MapViewOfFile(hMapFile,FILE_MAP_READ,0,0,0);//�����ҪдȨ�����ΪFILE_MAP_ALL_ACCESS
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

	//����
	//wscanf_s(L"%s",lpMapAddress);

	//����ָ���ڴ泤�ȵ����ݺ�·��
	//SendData(lpMapAddress,FileSize,WCFilePath);


	//////////////////////////////////////////////////////////////////////////
	//�������

	//HashĿ��
	wchar_t Hash_result[256]={0};
	GetHash(CALG_MD5,*Hash_result, lpMapAddress,FileSize);
	//�ж�Hash

	ReadVirusLib();


	for (DWORD i=0;i<_countof(StruVirusLibA);i++)
	{


		if(0==wcscmp(StruVirusLibA[i].MD5,Hash_result))
		{



			//ƴ����ʾ�ַ���
			wchar_t WCTempstrA[256]={0};
			wchar_t WCMessageTipsA[]=L"��⵽�������!";
			wcscpy_s(WCTempstrA,WCMessageTipsA);
			wcscat_s(WCTempstrA,WCFilePath);
			wcscat_s(WCTempstrA,L"     �Ƿ���ӵ�##����ɾ��##?");

			//�߼�:�Ƕ������.��ʾ,�����û�����,ȷ��:����ɾ��.ȡ��:·����ʾ�ڽ�����.

			int iAvgA=MessageBox(NULL,WCTempstrA,NULL,MB_OKCANCEL|MB_ICONWARNING);

			if (IDOK==iAvgA)
			{
				//ȷ��,�������ɾ��
				MoveFileEx
					(
					WCFilePath,NULL,MOVEFILE_DELAY_UNTIL_REBOOT
					);
				wprintf_s(L"������ĵ��Խ�ɾ���������:%s\r\n",WCFilePath);
			}
			else if(IDCANCEL==iAvgA)
			{
				//ȡ��,ֻ�����ʾ��Ϣ
				wprintf_s(L"�Ѻ��Ե���в:%s\r\n",WCFilePath);

			}

			//ƴ����ʾ�ַ���
			wchar_t WCTempstrB[256]={0};
			wchar_t WCMessageTipsB[]=L"�Ƿ�������ϼ����ö���������Ϊ?";
			wcscpy_s(WCTempstrB,WCMessageTipsB);
			

			//�߼�:�Ƕ������.��ʾ,�����û�����,ȷ��:����ɾ��.ȡ��:·����ʾ�ڽ�����.

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
	//��ӳ�������д�ص�Ӳ����
	//FlushViewOfFile(lpMapAddress,0);��Ҫ�ڶ�ȡ��ʱ�����дȨ��.



	//////////////////////////////////////////////////////////////////////////
	//�ر�mappint����
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