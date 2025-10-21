







#ifndef __DXWAV_H_
#define __DXWAV_H_



#include <dsound.h>
#include <stdio.h>


#define NUM_SOUNDS      1700


#pragma pack(1)




struct WaveHeader0	
{
    BYTE        RIFF[4];          
    DWORD       dwSize;           
    BYTE        WAVE[4];          
    BYTE        fmt_[4];          
    DWORD       dw16;             
    WORD        wOne_0;           
    WORD        wChnls;           
    DWORD       dwSRate;          
    DWORD       BytesPerSec;      
    WORD        wBlkAlign;        
    WORD        BitsPerSample;    
    BYTE        DATA[18];          
    DWORD       dwDSize;          
};


struct WaveHeader1
{
    BYTE        RIFF[4];          
    DWORD       dwSize;           
    BYTE        WAVE[4];          
    BYTE        fmt_[4];          
    DWORD       dw16;             
    WORD        wOne_0;           
    WORD        wChnls;           
    DWORD       dwSRate;          
    DWORD       BytesPerSec;      
    WORD        wBlkAlign;        
    WORD        BitsPerSample;    
    BYTE        DATA[4];          
    DWORD       dwDSize;          
};


struct WaveHeader2	
{
    BYTE        RIFF[4];          
    DWORD       dwSize;           
    BYTE        WAVE[4];          
    BYTE        fmt_[4];          
    DWORD       dw16;             
    WORD        wOne_0;           
    WORD        wChnls;           
    DWORD       dwSRate;          
    DWORD       BytesPerSec;      
    WORD        wBlkAlign;        
    WORD        BitsPerSample;    
    BYTE        DATA[16];          
    DWORD       dwDSize;          
};



#pragma pack()





BOOL CreateSoundBuffer(DWORD dwBuf, DWORD dwBufSize, DWORD dwFreq, DWORD dwBitsPerSample, DWORD dwBlkAlign, BOOL bStereo, BOOL bStaticBuf);
BOOL ReadData(LPDIRECTSOUNDBUFFER lpDSB, FILE* pFile, DWORD dwSize, DWORD dwPos);
BOOL CreateBufferFromWaveFile(char* FileName, DWORD dwBuf);



BOOL InitDX_Wav(HWND g_hwnd); 
void TermDX_Wav();            
BOOL StopAllWav();            












BOOL PlayWav(DWORD dwSound, DWORD dwFlags=0, DWORD dwVol=400, DWORD dwfreq=2205);

BOOL PlayWav2(DWORD dwSound, DWORD dwFlags=0, DWORD dwVol=400, DWORD dwfreq=2205);


			

BOOL PlayWav3(DWORD dwSound, DWORD dwFlags=0, DWORD dwVol=400, DWORD dwfreq=2205, DWORD dwPan=400);



BOOL PlayWav_VolChange(DWORD dwSound, DWORD dwVol=400);

BOOL PlayWav_FrequencyChange(DWORD dwSound, DWORD dwfreq=2205);

BOOL PlayWav_PanChange(DWORD dwSound, DWORD dwPan=400);
















BOOL InitDX_Wav2(HWND g_hwnd);  
void TermDX_Wav2();
BOOL CreateBufferFromWaveFile2(char* FileName, int sbufN);
BOOL CreateBufferFromWavBUF(unsigned char* wavBUf, unsigned int dwBuf);
BOOL sBufferClear(int sbufN);

void allWAVE_playORstop(int flag);	

BYTE getmouTH();		


BOOL StopWav(int i);





int  BackMusic_Load( int stageNumber );     
void BackMusicPlay();           
void BackMusicClr();            
void BackMusic_Stop();


#endif














#define WAV_READY()     PlayWav(1)		
#define WAV_CLOCK()     PlayWav(2)		
#define WAV_SEND()      PlayWav(3)		

#define WAV_CLEAVE()    PlayWav(4)		
#define WAV_DRAP()      PlayWav(5)		
#define WAV_BANSA()     PlayWav(6)		



#define WAV_VICTOR1()	PlayWav(7)	
#define WAV_VICTOR2()	PlayWav(8)	

#define WAV_LOSS1()	PlayWav(9)	
#define WAV_LOSS2()	PlayWav(10)	
#define WAV_LOSS3()	PlayWav(11)	
#define WAV_LOSS4()	PlayWav(12)	


#define WAV_ENBALL1()	PlayWav(13)		
#define WAV_ENBALL2()	PlayWav(14)		

#define WAV_BALLDOWN1() PlayWav(15)		
#define WAV_BALLDOWN2() PlayWav(16)		

#define WAV_LINEDOWN()	PlayWav(17)		
#define WAV_JOJUN()		PlayWav(18)		


#define WAV_WIN_M()		PlayWav(19)		
#define WAV_LOSE_M()		PlayWav(20)		









BOOL Init_BGM(HWND hwnd);		
void Uninit_BGM(void);			
BOOL OpenBGM(LPSTR lpszFileName);	
void PlayBGM(void);
void StopBGM(void);
void SetVolumeBGM( DWORD dwVol );		


BOOL IsPlayWav( DWORD dwSound );

void InitDirectSound();	










































