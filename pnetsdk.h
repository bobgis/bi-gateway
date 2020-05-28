#pragma once
#ifndef _PNETSDK_H_
#define _PNETSDK_H_
#include "stdafx.h"
#include "common.h"
#include <WinSock2.h>
#include ".\SIPA-SDK\iMPSDKSipACore.h"



typedef long (*pNetSdk_Open_V10)(char* strServerIP, long nServerPort, char* strLocalIP, long nLocalPort);
typedef long (*pNetSdk_SetMsgCallbackFunc_V10)(long hSdkHandle,PNETSDKMSGCB pMsgFuncCallback, void* pMsgFuncCallbackParam);
typedef long(*pNetSdk_RealplayStart_V10)(long hSdkHandle, 
										 char* strDeviceID, 
										 int iChannelID,
										 int iStreamType,
										  enum NETSDK_MEDIATRANSPRO_E eMediaTransPro, 
										  enum NETSDK_MEDIAENCODEPRO_E eMediaEncodePro,
										  BOOL bTcpSetUp,
										  char* strMediaRecvIP, 
										  long nMediaRecvPort, 
										  char* strUserID,
										  char* strSSRC);
typedef int(*pNetSdk_RealplayResultInfo_V10)(long hSdkHandle,
											char* strDeviceID,
											int nStreamType,
										enum NETSDK_MEDIATRANSPRO_E eMediaTransPro,
										enum NETSDK_MEDIAENCODEPRO_E eMediaEncodePro,
											BOOL bTcpSetUp,
											char* strMediaRecvIP,
											long nMediaRecvPort,
											char* strSSRC,
											char* strServerID,
											char* strExtendData);
typedef int (*pNetSdk_RealplayStop_V10)(long hSdkHandle, long hRPHandle);
typedef int (*pNetSdk_Close_V10)(long hSdkHandle);




// »Øµôº¯Êý
int NetSdkMsgCb( enum NETSDK_MESSAGETYPE_E eMsgType,
				void*  pMsgInfo, 
				void*  pResultInfo,
				void*  pMsgFuncCallbackParam);
long getNetSdkHandle();
void setNetSdkHandle(long h);
HANDLE getNetPlayEvent();
void setNetPlayEvent(HANDLE handle);
HANDLE getNetStopEvent();
void setNetStopEvent(HANDLE handle);

#endif;