#include "stdafx.h"

#include "MemoryMap.h"
#include "ReadVirusLib.h"

extern VIRUSLIB StruVirusLibA[2];

//ע��:�������С�ı����Ҫ�ı�StruVirusLibA��������С.
//��ʱû��ʹ�ö�̬��С.�������������.
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

