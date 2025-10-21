




	
#ifndef _SINMEDIA_HEADER_ 
#define _SINMEDIA_HEADER_ 


#include "amstream.h"


	
class SINMOVIE
{ 
	
	int StartMovie();

	IMultiMediaStream *pMMStream;              
	IMediaStream *pPrimaryVidStream;     
	IDirectDrawMediaStream *pDDStream;     
	IDirectDrawSurface *pSurface;     
	IDirectDrawStreamSample *pSample;
	IDirectDrawSurface      *pMovieSurface;
	char FileName[MAX_PATH];
	RECT DRect,SRect;  
	int MovieState; 
	bool Open(IDirectDraw* pDD, char* name, IMultiMediaStream** ptMMStream);
	public :
	SINMOVIE();
	~SINMOVIE(); 
	void SetBlitPos(int t,int b,int l,int r); 
	void SetBlitPos(RECT dest); 
	int GetMovieState() { return MovieState; }
	void ShutDown();
	bool PrepareMovie(IDirectDraw* pDD, IDirectDrawSurface *pDDSurface, char* FName);
	bool RenderStreamToSurface();
	void RenderStreamToSurfaceAll();

};
extern SINMOVIE sinMovie;
#endif
