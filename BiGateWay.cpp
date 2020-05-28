// BiGateWay.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <WinSock2.h>
#include ".\SIPA-SDK\iMPSDKSipACore.h"
#include "fifo.h"
#include "sipa.h"
#include <string>
#include "pnetsdk.h"

#include <stdlib.h>
#include <malloc.h>
using namespace std;

char command;
string net[4];


int _tmain(int argc, _TCHAR* argv[])
{
	if(!LogInit())return 0;
	
	LPSipaPlayAndStopThreadParam lpSipaPlayAndStopStop = (LPSipaPlayAndStopThreadParam)malloc(sizeof(SipaPlayAndStopThreadParam));
	//��ʼ���Ӹ�ƽ̨
	HINSTANCE hInst;   
	pNetSdk_Open_V10  pInit;
	pNetSdk_SetMsgCallbackFunc_V10 pSetBack;
	pNetSdk_RealplayStart_V10 pPalyStart;
	pNetSdk_RealplayResultInfo_V10 pResultInfo=NULL;
	pNetSdk_RealplayStop_V10 pPlayStop;
	pNetSdk_Close_V10 pClose=NULL;
	int NetConnCts=0;
    long hSdkHandle=-1;

	hInst = LoadLibrary(L"NETSDK_EXPORT32.dll");
	if (hInst == NULL) 
	{
		LogEvent(_T("Dll����ʧ��\n"),EVENTLOG_ERROR_TYPE);
		return -1;
	}
	else if( hInst != NULL)
	{
		LogEvent(_T("Dll���سɹ�\n"),EVENTLOG_SUCCESS);
		initSipAFifo();

		pInit = (pNetSdk_Open_V10)GetProcAddress( hInst,"NetSdk_Open_V10" );
		pSetBack = (pNetSdk_SetMsgCallbackFunc_V10)GetProcAddress( hInst,"NetSdk_SetMsgCallbackFunc_V10" );
		pPalyStart = (pNetSdk_RealplayStart_V10)GetProcAddress( hInst,"NetSdk_RealplayStart_V10" );
		pResultInfo = (pNetSdk_RealplayResultInfo_V10)GetProcAddress(hInst, "NetSdk_RealplayResultInfo_V10");
		pPlayStop = (pNetSdk_RealplayStop_V10)GetProcAddress( hInst,"NetSdk_RealplayStop_V10" );
		pClose = (pNetSdk_Close_V10)GetProcAddress( hInst,"NetSdk_Close_V10" );
		
		
	}

	
	bool isRunning = true;
	string str[8];
	
	DWORD threadId;
	HANDLE hThread[2];
	LPSipaPlayThreadParam pThreadParam = NULL;
	LPSipaStopThreadParam pSThreadParam = NULL;
	LPSipaPlayCallbackParam pPlayCallbackParam = (LPSipaPlayCallbackParam)malloc(sizeof(SipaPlayCallbackParam));
	strcpy_s(pPlayCallbackParam->exDatas,"aaaaaa");
	pPlayCallbackParam->handle = hSdkHandle;
	pPlayCallbackParam->pVoid = pResultInfo;
	int i = iMPSdkSipA_setCallbackFunc_V10(sipaplaybc,pPlayCallbackParam,sipabytebc,NULL,sipastatusbc,NULL);
	getParam(str,"./Config.cfg");
	long l = iMPSdkSipA_initClient_V10(atoi(str[0].c_str()),atoi(str[1].c_str()),const_cast<char*>(str[2].c_str()),
		const_cast<char*>(str[3].c_str()),atol(str[4].c_str()),const_cast<char*>(str[5].c_str()),const_cast<char*>(str[6].c_str()),atol(str[7].c_str()));
	LogEvent(_T("SIPͨ����ʼ��\n"),EVENTLOG_SUCCESS);
	if(l>=0){
		pThreadParam = new SipaPlayThreadParam();
		pThreadParam->handle = l;
		pThreadParam->isRunning = true;
		pThreadParam->hEvent = ::CreateEvent(NULL,TRUE,FALSE,NULL);
		hThread[0] = ::CreateThread(NULL,0,sipaplayThread,pThreadParam,0,&threadId);

	    pSThreadParam = new SipaStopThreadParam();
		pSThreadParam->handle = l;
		pSThreadParam->isRunning = true;
		pSThreadParam->hEvent = ::CreateEvent(NULL,TRUE,FALSE,NULL);
		hThread[1] = ::CreateThread(NULL,0,sipaStopThread,pSThreadParam,0,&threadId);

		setNetPlayEvent(pThreadParam->hEvent);
		setNetStopEvent(pSThreadParam->hEvent);



		lpSipaPlayAndStopStop->pPlayParam = pThreadParam;
		lpSipaPlayAndStopStop->pStopParam = pSThreadParam;
		

	}else{
		isRunning = false;
	}
	//



		//�����Ӹ�ƽ̨
		getParam(net,"./netConfig.cfg");
		if (0 != pInit(const_cast<char*>(net[0].c_str()), atol(net[1].c_str()), const_cast<char*>(net[2].c_str()), atol(net[3].c_str())))
		{
			LogEvent(_T("�Ӹ߳�ʼ��ʧ��\n"),EVENTLOG_ERROR_TYPE);
			return 0;
		}else{
			LogEvent(_T("�Ӹ߳�ʼ���ɹ�\n"),EVENTLOG_SUCCESS);
		}
		//������Ϣ�ص�����
		if (0 != pSetBack(hSdkHandle, NetSdkMsgCb,lpSipaPlayAndStopStop))
		{
			return 0;
		}

		
	// ע�� ���ﲻ�ж� hSdkHandle
		
		while (NetConnCts<15) // ģ��ȴ����ӳɹ� ʵ��ʹ�ÿ��������¼�֪ͨ�ȷ�ʽ
		{
			hSdkHandle=getNetSdkHandle();
			if(hSdkHandle != -1)
			//if (hSdkHandle != -1)
			{
				LogEvent(_T("�Ӹ����ӳɹ�\n"),EVENTLOG_SUCCESS);
				break;
			}
			NetConnCts++;
			Sleep(2000);//����2��
		}
		if(NetConnCts>=15){
			LogEvent(_T("�Ӹ�����ʧ��\n"),EVENTLOG_ERROR_TYPE);
			return -1;//�޷������Ӹ�ƽ̨
		}
		
		//setNetSdkHandle(hSdkHandle);



	while(isRunning){
		printf("����������:\n");
		scanf_s("%c",&command);
		getchar();
		switch(command){
		case 'x':
			isRunning = false;
			pThreadParam->isRunning = false;
			pSThreadParam->isRunning = false;
			break;
		default:
			break;
		}
	}
	WaitForMultipleObjects(2,hThread,TRUE,INFINITE);
	if(pThreadParam!=NULL){
		delete pThreadParam;
	}
	if(pSThreadParam!=NULL){
		delete pSThreadParam;
	}
	if(pPlayCallbackParam!=NULL){
		delete pPlayCallbackParam;
	}

	deleteSipAFifo();
	if(l>=0)i = iMPSdkSipA_closeClient_V10(l);
	// �ͷ�
	pClose(hSdkHandle);
	FreeLibrary(hInst);
	hInst = NULL;
	LogClose();

	//system("pause");
	return 0;
}

