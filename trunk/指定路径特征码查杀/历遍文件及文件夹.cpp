#include "stdafx.h"

#include "FindFile.h"
#include "MemoryMap.h"


extern int iFileNumber;


//目前没有办法找到每一个文件.用*代替扩展名是无效的.



//这里只是测试函数
//一般我们遍历文件都是有目的 同这个写类似病毒一些东西
//我们的测试函数
void Test(wchar_t *pFileName,WIN32_FIND_DATA *fd)

{
	//MessageBox(0,fd->cFileName,0,0);



	wchar_t WCFilePath[MAX_PATH]={0};

	wcscat_s(WCFilePath,pFileName);
	wcscat_s(WCFilePath,L"\\");
	wcscat_s(WCFilePath,fd->cFileName);//拼接目标文件路径

	//映射内存
	MemoryMap(WCFilePath);

	//wprintf_s(L"%s\r\n",WCFilePath);


	iFileNumber++;
}




//自定义一个宽字符串查找函数wstrstr,效率最低
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
	//HANDLE hFindType;//查找对应文件类型
	wchar_t FileName[260]={0};

	wsprintf(FileName,L"%s\\*.*",pFileName);
	ZeroMemory(&fd,sizeof(fd));

	if(0 == wcslen(FileName))
	{
		MessageBox(0,L"文件名不能为空",0,0);
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
				//查找文件名字中有没与 .文件后缀  注意要加点 因为点在文件名字是特殊符号
				//一般是不可以用的。但可以用特殊方法来添加。
				//U 盘免疫就是用这中方法来 来建立一个不能用普通方法删除autorun.inf的文件夹
				if(wstrstr(fd.cFileName,Type))
				{
					Test(pFileName,&fd);
				}
				else
				{
					//当该文档是文件时候进行下列操作
					if(fd.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
					{
						//除掉 . 表示当前目录 和..上一个目录 这个在dos 中可以看到
						if(wcscmp(fd.cFileName,L".")!=0&&wcscmp(fd.cFileName,L"..")!=0)
						{
							wchar_t Temp[256]={0};
							wsprintf(Temp,L"%s\\%s",pFileName,fd.cFileName);
							FindFile(Temp,FindFileType);

						}

					}
				}

				//继续查找下一个文件
			} while (FindNextFile(hFind,&fd));
		}
	}
	return TRUE;
}