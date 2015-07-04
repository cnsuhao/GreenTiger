#include "stdafx.h"

#include "Hash.h"


//
//参数:
//Hash_type使用的Hash类型,参见ALG_ID.MD5是CALG_MD5
//盛放Hash结果的宽字符串的引用.
//Hash目标内存起始地址
//Hash目标内存长度
bool GetHash(int Hash_type,wchar_t &Hash_result, static PVOID StartMemoryStr,DWORD Legth)

{

	HCRYPTPROV hCryptProv;

	HCRYPTHASH hCryptHash;



	if (!CryptAcquireContext(&hCryptProv, NULL, MS_DEF_PROV, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))

	{
		int e = GetLastError();
		WCHAR WCStringA[18];

		swprintf(WCStringA,16,L"%d",e);
		WCHAR WCStringB[64]=L"创建CSP容器出错！错误代码为:";
		wcscat_s(WCStringB,WCStringA);


		OutputDebugString(WCStringB);


		return false;

	}    



	if (!CryptCreateHash(hCryptProv, Hash_type, 0, 0, &hCryptHash))

	{

		int e = GetLastError();
		WCHAR WCStringA[18];

		swprintf(WCStringA,16,L"%d",e);
		WCHAR WCStringB[64]=L"创建Hash句柄出错！错误代码为:";
		wcscat_s(WCStringB,WCStringA);


		OutputDebugString(WCStringB);


		return false;

	}



	if (!CryptHashData(hCryptHash, (BYTE*)StartMemoryStr, Legth, 0))

	{
		int e = GetLastError();
		WCHAR WCStringA[18];

		swprintf(WCStringA,16,L"%d",e);
		WCHAR WCStringB[64]=L"计算Hash值出错！错误代码为:";
		wcscat_s(WCStringB,WCStringA);


		OutputDebugString(WCStringB);


		return false;

	}



	char hash_data[512];

	DWORD hash_len = 512;

	if (!CryptGetHashParam(hCryptHash, HP_HASHVAL, (BYTE*)hash_data, &hash_len, 0))

	{

		int e = GetLastError();
		WCHAR WCStringA[18];

		swprintf(WCStringA,16,L"%d",e);
		WCHAR WCStringB[64]=L"获取Hash值出错！错误代码为:";
		wcscat_s(WCStringB,WCStringA);


		OutputDebugString(WCStringB);


		return false;

	}

	char hash_hex[512];

	for (unsigned int i=0; i<=hash_len-1; i++)

	{

		int hash_bit = hash_data[i];

		int first = (hash_bit & 0xf0) >> 4;

		int second = hash_bit & 0x0f;

		char tmp[2];

		_itoa_s(first, tmp,2, 16);

		hash_hex[i*2] = tmp[0];

		_itoa_s(second, tmp,2, 16);

		hash_hex[i*2+1] = tmp[0];

	}

	hash_hex[hash_len*2] = '\0';



	


	//hash_result.Format("%s", hash_hex);
	
		C2W(&Hash_result,256,hash_hex);
	

	CryptDestroyHash(hCryptHash);

	CryptReleaseContext(hCryptProv, NULL);



	return true;

}

void C2W(wchar_t *pwstr,size_t len,const char *str)

{

	if(str)

	{

		size_t nu = strlen(str);

		size_t n =(size_t)MultiByteToWideChar(CP_ACP,0,(const char *)str,(int)nu,NULL,0);

		if(n>=len)n=len-1;

		int 测试=MultiByteToWideChar(CP_ACP,0,(const char *)str,(int)nu,pwstr,(int)n);

		pwstr[n]=0;

	}

}