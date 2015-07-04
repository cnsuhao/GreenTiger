#include "stdafx.h"

#include "FindFile.h"
#include "MemoryMap.h"


extern int iFileNumber;


//Ŀǰû�а취�ҵ�ÿһ���ļ�.��*������չ������Ч��.



//����ֻ�ǲ��Ժ���
//һ�����Ǳ����ļ�������Ŀ�� ͬ���д���Ʋ���һЩ����
//���ǵĲ��Ժ���
void Test(wchar_t *pFileName,WIN32_FIND_DATA *fd)

{
	//MessageBox(0,fd->cFileName,0,0);



	wchar_t WCFilePath[MAX_PATH]={0};

	wcscat_s(WCFilePath,pFileName);
	wcscat_s(WCFilePath,L"\\");
	wcscat_s(WCFilePath,fd->cFileName);//ƴ��Ŀ���ļ�·��

	//ӳ���ڴ�
	MemoryMap(WCFilePath);

	//wprintf_s(L"%s\r\n",WCFilePath);


	iFileNumber++;
}




//�Զ���һ�����ַ������Һ���wstrstr,Ч�����
//http://www.cnblogs.com/ziwuge/archive/2011/12/09/2281455.html

wchar_t * __cdecl wstrstr (
	const wchar_t * str1,
	const wchar_t * str2
	)
{
	wchar_t *cp = (wchar_t *) str1;
	wchar_t *s1, *s2;
	if ( !*str2 )
		return((wchar_t *)str1);
	while (*cp)
	{
		s1 = cp;
		s2 = (wchar_t *) str2;
		while ( *s1 && *s2 && !(*s1-*s2) )
			s1++, s2++;
		if (!*s2)
			return(cp);
		cp++;
	}
	return(NULL);
}




BOOL FindFile(wchar_t *pFileName, wchar_t * FindFileType)
{
	WIN32_FIND_DATA fd;
	HANDLE hFind;
	wchar_t Type[10]={0};
	wsprintf(Type,L".%s",FindFileType);
	//HANDLE hFindType;//���Ҷ�Ӧ�ļ�����
	wchar_t FileName[260]={0};

	wsprintf(FileName,L"%s\\*.*",pFileName);
	ZeroMemory(&fd,sizeof(fd));

	if(0 == wcslen(FileName))
	{
		MessageBox(0,L"�ļ�������Ϊ��",0,0);
		return FALSE;
	}
	else
	{
		hFind = FindFirstFile(FileName,&fd);
		if(INVALID_HANDLE_VALUE==hFind)
		{
			return FALSE;
		}
		else
		{
			do
			{
				//�����ļ���������û�� .�ļ���׺  ע��Ҫ�ӵ� ��Ϊ�����ļ��������������
				//һ���ǲ������õġ������������ⷽ������ӡ�
				//U �����߾��������з����� ������һ����������ͨ����ɾ��autorun.inf���ļ���
				if(wstrstr(fd.cFileName,Type))
				{
					Test(pFileName,&fd);
				}
				else
				{
					//�����ĵ����ļ�ʱ��������в���
					if(fd.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
					{
						//���� . ��ʾ��ǰĿ¼ ��..��һ��Ŀ¼ �����dos �п��Կ���
						if(wcscmp(fd.cFileName,L".")!=0&&wcscmp(fd.cFileName,L"..")!=0)
						{
							wchar_t Temp[256]={0};
							wsprintf(Temp,L"%s\\%s",pFileName,fd.cFileName);
							FindFile(Temp,FindFileType);

						}

					}
				}

				//����������һ���ļ�
			} while (FindNextFile(hFind,&fd));
		}
	}
	return TRUE;
}