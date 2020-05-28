#include "stdafx.h"
#include "stdio.h"
#include <iostream>  
#include <string>  
#include <fstream>
#include "sipa.h"
#include ".\SIPA-SDK\iMPSDKSipACore.h"
#include "fifo.h"
#include "time.h"
#include "common.h"
#include "pnetsdk.h"
using namespace std;

FILE *logFp;

void getParam(string s[], char* p)
{

	string value;
	ifstream cfgFile;
    cfgFile.open(p,ios::in);//打开文件      
    if( !cfgFile.is_open())  
    {  
        cout<<"can not open cfg file!"<<endl;   
    }
	
    char tmp[1000];
	int i=0;
    while(!cfgFile.eof())//循环读取每一行  
    {  
        cfgFile.getline(tmp,1000);//每行读取前1000个字符  
        string line(tmp);  
        size_t pos = line.find('=');//找到每行的“=”号位置，之前是key之后是value    
        string tmpKey = line.substr(0,pos);//取=号之前
        value = line.substr(pos+1);//取=号之后
		s[i]=value;
		i++;
		//Sleep(1000);	
	}
	cfgFile.close();
	return ;

}


//播放线程
DWORD WINAPI sipaplayThread(LPVOID pParam){
	DWORD dw;
	sipAPlayInfo_t *pReceiveSdpInfo;
	LPSipaPlayThreadParam lpParam = (LPSipaPlayThreadParam)pParam;
	while(lpParam->isRunning){
		dw=::WaitForSingleObject(lpParam->hEvent,100);
		switch(dw){
		case WAIT_OBJECT_0://有信号状态处理
			pReceiveSdpInfo = getSipAPlayInfoFromFifo();
			if(pReceiveSdpInfo!=NULL){
				SipA_play(lpParam->handle,pReceiveSdpInfo);
				free(pReceiveSdpInfo);
			}else{
				::ResetEvent(lpParam->hEvent);
			}
			break;
		case WAIT_TIMEOUT://超时状态处理
			pReceiveSdpInfo = getSipAPlayInfoFromFifo();
			if(pReceiveSdpInfo!=NULL){
				SipA_play(lpParam->handle,pReceiveSdpInfo);
				free(pReceiveSdpInfo);
			}
			break;
		default:
			break;
		}
	}
	return 0;
}

//停播线程
DWORD WINAPI sipaStopThread(LPVOID pParam){
	DWORD dw;
	sipAStopPlayInfo_t  *pStopInfo;
	LPSipaStopThreadParam lpParam = (LPSipaStopThreadParam)pParam;
	while(lpParam->isRunning){
		dw=::WaitForSingleObject(lpParam->hEvent,100);
		switch(dw){
		case WAIT_OBJECT_0:
			pStopInfo = getSipAStopPlayInfoFromFifo();
			if(pStopInfo!=NULL){
				SipA_playStop(lpParam->handle,pStopInfo);
				free(pStopInfo);
			}else{
				::ResetEvent(lpParam->hEvent);
			}
			break;
		case WAIT_TIMEOUT://超时状态处理
			pStopInfo = getSipAStopPlayInfoFromFifo();
			if(pStopInfo!=NULL){
				SipA_playStop(lpParam->handle,pStopInfo);
				free(pStopInfo);
			}
			break;
		default:
			break;
		}
	}
	return 0;
}

void  sipaplaybc(struct sipAPlayInfo *pSendSdpInfo, void* cbFuncMsgParam_play)
{
	LPSipaPlayCallbackParam pParam = (LPSipaPlayCallbackParam)cbFuncMsgParam_play;
	printf("deviceID:%s\n",pSendSdpInfo->deviceID);
	pNetSdk_RealplayResultInfo_V10 pResultInfo = (pNetSdk_RealplayResultInfo_V10)pParam->pVoid;
	if(pResultInfo(pParam->handle, pSendSdpInfo->deviceID,pSendSdpInfo->iSvcSpace,NETSDK_MEDIATRANS_TCP,NETSDK_MEDIAENCODE_PS,pSendSdpInfo->tcpSetUp,pSendSdpInfo->Ip, pSendSdpInfo->Port,pSendSdpInfo->ssrc,pSendSdpInfo->userID,pParam->exDatas)<0){
		//日志文件
		LogEvent(_T("请求结果返回失败\n"),EVENTLOG_ERROR_TYPE);
	}else{
		LogEvent(_T("请求结果返回成功\n"),EVENTLOG_SUCCESS);
	}// 视高监看请求的回复
}

void  sipabytebc(struct sipAStopPlayInfo *pStopInfo, void* cbFuncMsgParam_bye)
{
	printf("deviceID:%s\n",pStopInfo->deviceID);
}

void  sipastatusbc(struct sipAStatusInfo *pStatusInfo, void* cbFuncMsgParam_status)
{
	printf("status:%d\n",pStatusInfo->bPlatformStatus);
}


void SipA_play(long handle, sipAPlayInfo_t *pReceiveSdpInfo){
	int retPlay = iMPSdkSipA_playClient_V10(handle,pReceiveSdpInfo);
	if(retPlay<0){
		printf("点播失败，错误代码为：%d\n",retPlay);
		LogEvent(_T("点播失败\n"),EVENTLOG_ERROR_TYPE);
	}else{
		LogEvent(_T("点播成功\n"),EVENTLOG_SUCCESS);
	}
	return ;
}

void SipA_playStop(long handle,sipAStopPlayInfo_t *pStopInfo){
	int stopPlay = iMPSdkSipA_playStop_V10(handle,pStopInfo);
	if(stopPlay<0){
		printf("停止点播失败，错误代码为：%d\n",stopPlay);
		LogEvent(_T("停止点播失败\n"),EVENTLOG_ERROR_TYPE);
	}else{
		LogEvent(_T("停止点播成功\n"),EVENTLOG_SUCCESS);
	}
	return ;
}


BOOL LogInit(){
	 WCHAR filename[256];
	 WCHAR tmp[256];
	 WCHAR relFile[256];
	 ::GetModuleFileName(NULL,tmp,256);
	 size_t len = _tcsclen(tmp);
	 _tcsnccpy_s(filename,tmp,len-4);

	  time_t currentt = time(NULL);
	  struct tm TM;
	  localtime_s(&TM,&currentt);
	  swprintf_s(relFile,_T("%d-%d-%d.txt"),TM.tm_year+1900,TM.tm_mon+1,TM.tm_mday);
	 _tcsnccat_s(filename,relFile,256);
	 _tfopen_s(&logFp,filename,_T("a+,ccs=UTF-8"));
	 if(logFp!=NULL){
		 LogEvent(_T("日志文件初始化成功\n"),EVENTLOG_SUCCESS);
		 return TRUE;
	 }
	 return FALSE;
 }
void LogClose(){
	LogEvent(_T("关闭日志文件\n"),EVENTLOG_SUCCESS);
	fclose(logFp);
	logFp = NULL;
}
void LogEvent(LPCTSTR pFormat,WORD type)
{
	WCHAR ctimeString[30];
	time_t currentTime = time(NULL);
	_tcsncpy_s(ctimeString,_tctime(&currentTime),30);
	_ftprintf_s(logFp,_T("%s"),ctimeString);
	if(type==EVENTLOG_SUCCESS||type==EVENTLOG_INFORMATION_TYPE){
		_ftprintf_s(logFp,_T("%s."),_T("信息  "));
	}else if(type==EVENTLOG_ERROR_TYPE){
		_ftprintf_s(logFp,_T("%s."),_T("错误  "));
	}else if(type==EVENTLOG_WARNING_TYPE){
		_ftprintf_s(logFp,_T("%s."),_T("警告  "));
	}else{
		_ftprintf_s(logFp,_T("%s."),_T("未知  "));
	}
	_ftprintf_s(logFp,_T("%s\n"),pFormat);
	fflush(logFp);
}


