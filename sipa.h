
#pragma once
#ifndef _SIPA_H_
#define _SIPA_H_
#include "stdafx.h"
#include <WinSock2.h>
#include ".\SIPA-SDK\iMPSDKSipACore.h"
#include "common.h"
#include <string> 
using namespace std;


typedef struct SipaPlayCallbackParam
{
	long handle;
	PVOID pVoid;
	char exDatas[1024];

}*LPSipaPlayCallbackParam;


typedef struct SipaPlayThreadParam
{
	boolean isRunning;
	HANDLE  hEvent;
	long handle;
}*LPSipaPlayThreadParam;
typedef struct SipaStopThreadParam
{
	boolean isRunning;
	HANDLE  hEvent;
	long handle;
}*LPSipaStopThreadParam;

typedef struct SipaPlayAndStopThreadParam
{
	LPSipaPlayThreadParam pPlayParam;
	LPSipaStopThreadParam pStopParam;
}*LPSipaPlayAndStopThreadParam;



//�����߳�
DWORD WINAPI sipaplayThread(LPVOID pParam);
//ͣ���߳�
DWORD WINAPI sipaStopThread(LPVOID pParam);

DWORD WINAPI testThread(LPVOID pParam);


//�ص�����

void  sipaplaybc(struct sipAPlayInfo *pSendSdpInfo, void* cbFuncMsgParam_play);

void  sipabytebc(struct sipAStopPlayInfo *pStopInfo, void* cbFuncMsgParam_bye);

void  sipastatusbc(struct sipAStatusInfo *pStatusInfo, void* cbFuncMsgParam_status);

void getParam(string[] , char* p);

//�㲥�¼�

void SipA_play(long handle,sipAPlayInfo_t *pReceiveSdpInfo);

void SipA_playStop(long handle,sipAStopPlayInfo_t *pStopInfo);

//д��־
BOOL LogInit();

void LogClose();

void LogEvent(LPCTSTR pFormat,WORD type);



#endif;