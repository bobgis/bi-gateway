#include "stdafx.h"
#include "sipa.h"
#include "pnetsdk.h"
#include "fifo.h"
// 回掉函数


long hNetSdkHandle = -1;
HANDLE pHandle,sHandle;

int NetSdkMsgCb( enum NETSDK_MESSAGETYPE_E eMsgType,
				void*  pMsgInfo, 
				void*  pResultInfo,
				void*  pMsgFuncCallbackParam)
{
	sipAPlayInfo_t* sipAPlayInfo;
	sipAStopPlayInfo_t* sipAStopPlayInfo;
	LPSipaPlayAndStopThreadParam pParam = (LPSipaPlayAndStopThreadParam)pMsgFuncCallbackParam;

	switch (eMsgType)
	{
	case NETSDK_MSGTYPE_PLATFORM_UNAVAILABLE:
	{
		hNetSdkHandle = -1;
		printf("平台不可用\r\n");
	}
		break;
	case NETSDK_MSGTYPE_REALPLAY_START:
	{
		PSTRU_NETSDK_RPSTRAT_INFO p = (PSTRU_NETSDK_RPSTRAT_INFO)pMsgInfo;
		printf("视高视频点播请求 devid: %s\r\n",p->strDeviceID);
		
		//视高点播一所平台
		sipAPlayInfo = (sipAPlayInfo_t*)malloc(sizeof(sipAPlayInfo_t));
		strcpy_s(sipAPlayInfo->sdpStartTime,"0");
		strcpy_s(sipAPlayInfo->sdpEndTime,"0");
		/*
		if (p->bTcpSetUp == FALSE)
		{
			strcpy_s(sipAPlayInfo->deviceID,p->strDeviceID);
			strcpy_s(sipAPlayInfo->Ip,p->szMediaRecvIP);
		}
		*/
		strcpy_s(sipAPlayInfo->deviceID,p->strDeviceID);
		strcpy_s(sipAPlayInfo->Ip,p->szMediaRecvIP);
		sipAPlayInfo->Port = p->nMediaRecvPort;
		sipAPlayInfo->mediaNetType = iMPSdkSipA_MEDIA_TCP;//只支持tcp
		sipAPlayInfo->tcpSetUp = p->bTcpSetUp;//固定为被动接受
		sipAPlayInfo->iSvcSpace = p->iStreamType;//分辨率控制参数
		strcpy_s(sipAPlayInfo->ssrc,"0100000001");
		if(p->strUserID == NULL)
		{
			strcpy_s(sipAPlayInfo->userID,"64010000000000000003");
		}else
		{
			strcpy_s(sipAPlayInfo->userID,p->strUserID);
		}

		//放入点播队列等待点播
		addSipAPlayInfoToFifo(sipAPlayInfo);
		
		::SetEvent(pHandle);

		
	}
		break;
	case NETSDK_MSGTYPE_REALPLAY_STOP:
	{
		PSTRU_NETSDK_RPSTOP_INFO p = (PSTRU_NETSDK_RPSTOP_INFO)pMsgInfo;
		printf("视高视频停止请求 devid: %s\r\n", p->strDeviceID);
		sipAStopPlayInfo = (sipAStopPlayInfo_t*)malloc(sizeof(sipAStopPlayInfo_t));
		strcpy_s(sipAStopPlayInfo->deviceID,p->strDeviceID);
		//放入停播队列等待停播
		addSipAStopPlayInfoToFifo(sipAStopPlayInfo);
		::SetEvent(sHandle);
	}
		break;
	case NETSDK_MSGTYPE_REALPLAY_START_RESP:
	{
		PSTRU_NETSDK_RPSTRAT_RESP_INFO p = (PSTRU_NETSDK_RPSTRAT_RESP_INFO)pMsgInfo;
		printf("一所请求视频点播回复 result: %d\r\n", p->iResult);
	}
		break;
	case NETSDK_MSGTYPE_PLATFORM_AVAILABLE:
	{
		PSTRU_NETSDK_PLATFORM_AVAILABLE_INFO p = (PSTRU_NETSDK_PLATFORM_AVAILABLE_INFO)pMsgInfo;
		hNetSdkHandle = p->hSdkHandle;
		if (hNetSdkHandle != -1)
			printf("连接平台成功\r\n");
	}
		break;
	default:
		break;
	}

	//printf("输出内容: %s\r\n", p->hSdkHandle);
	//printf("ip: %s\r\n", p->strMediaRecvIP);
	//printf("port: %d\r\n", p->nMediaRecvPort);
	//printf("bTcpSetUp: %d\r\n", p->bTcpSetUp);
	//printf("eMediaEncodePro: %d\r\n", p->eMediaEncodePro);
	//printf("eMediaTransPro: %d\r\n", p->eMediaTransPro);

	return 0;
}


long getNetSdkHandle(){
	return hNetSdkHandle;
}
void setNetSdkHandle(long h){
	hNetSdkHandle = h;
}
HANDLE getNetPlayEvent(){
	return pHandle;
}
void setNetPlayEvent(HANDLE handle){
	pHandle =  handle;
}
HANDLE getNetStopEvent(){
	return sHandle;
}
void setNetStopEvent(HANDLE handle){
	sHandle = handle;
}
