

























#ifndef __XTRAPCCMODULE_H
#define __XTRAPCCMODULE_H

#if		defined(XTRAPCC_EXPORTS)
#define XTRAPCC_API __declspec(dllexport)
#elif	defined(XTRAPCC_IMPORTS)
#define XTRAPCC_API __declspec(dllimport)
#else
#define XTRAPCC_API
#endif

#define			XC_CMF_SIZE				4128
#define			XC_KEYVALUE_SIZE		12
#define			XC_ADDR_SIZE			264
#define			XC_CLIENTBUF_SIZE		544

typedef unsigned char XC_CMF		[XC_CMF_SIZE		];
typedef unsigned char XC_KEYVALUE	[XC_KEYVALUE_SIZE	];
typedef unsigned char XC_ADDR		[XC_ADDR_SIZE		];
typedef unsigned char XC_CLIENTBUF	[XC_CLIENTBUF_SIZE	];



#ifdef __cplusplus
extern "C" {
#endif


	XTRAPCC_API void SeedKeyGen(char * );				

	XTRAPCC_API int XCrackCheck(char *,					
								char *,					
								char *);				


	XTRAPCC_API void SeedKeyGenEx(	XC_CMF*,			
									unsigned char,		
									XC_KEYVALUE*,		
									XC_ADDR*);			

	XTRAPCC_API int XCrackCheckEx(	XC_CMF*,			
									unsigned char,		
									XC_KEYVALUE*,		
									XC_CLIENTBUF*);		
#ifdef __cplusplus
}
#endif

#endif
