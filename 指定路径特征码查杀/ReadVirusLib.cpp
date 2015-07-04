#include "stdafx.h"

#include "MemoryMap.h"
#include "ReadVirusLib.h"

extern VIRUSLIB StruVirusLibA[2];

//注意:病毒库大小改变后需要改变StruVirusLibA的声明大小.
//暂时没有使用动态大小.导致了这个问题.
//

int ReadVirusLib()
{
	FILE *fpRead;
	_wfopen_s(&fpRead,L"VirLib\\A.virlib",L"rb");

	if (fpRead==nullptr)
	{
		return -1;
	}

	fread(&StruVirusLibA,sizeof(StruVirusLibA),1,fpRead);
	fclose(fpRead);

	return 0;

}

