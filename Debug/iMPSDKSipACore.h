/************************************************************
Copyright (C), 2016 公安部第一研究所信息技术事业部研发一部
FileName: iMPSDKSipACore.h
Author:	liuyumei    
version : 1.0
Date: 2016/9/13
Description:   接口函数声明  
History:	   
***********************************************************/
#ifndef __SIPUA_IMPSDK_CLIENTUA_H__INCLUDED_
#define __SIPUA_IMPSDK_CLIENTUA_H__INCLUDED_

#ifdef _BUILD_DLL_
#define CLIENTUA_EXPORT32 __declspec(dllexport) 
#else
#define CLIENTUA_EXPORT32 __declspec(dllimport) 
#endif

//错误起始值定义
#define ERRORCODE_BEGIN -1000
/*****************错误返回值*****************************************/
enum iMPSdkSip_ERRORCODE
{
	iMPSdkSip_EXOSIP_INIT_SUCCESS = ERRORCODE_BEGIN,
	iMPSdkSip_EXOSIP_MALLOC_FAILED,      //exosip结构体分配内存失败
	iMPSdkSip_EXOSIP_INIT_FAILED,        //Exosip协议栈初始化失败
	iMPSdkSip_INTI_CLEAR_AUTHENTICATION_FAILED, //初始化时，清除鉴权消息失败
	iMPSdkSip_INIT_BUILD_REGISTER_FAILED,
	iMPSdkSip_INTI_SEND_REGISTER_FAILED,        //发送注册消息失败
	iMPSdkSip_INIT_PLATFORM_TYPE_ERROR,     //sip服务器平台类型设置错误
	iMPSdkSip_INIT_REGISTE_FAILED,         //注册失败

	iMPSdkSip_PLAY_MEDIA_TRANSPRO_ERROR,  //实时点播时，设置媒体流传输协议错误
	iMPSdkSip_PLAY_TCP_SETUP_ERROR,  //实时点播时，当媒体采用TCP方式传输时，发起端、接收端设置错误
	iMPSdkSip_PLAY_BUILD_INVITE_FAILED,  //实时点播时，构建invite消息失败
	iMPSdkSip_PLAY_SET_INVITE_BODY_FAILED, //实时点播时，设置invite消息体失败
	iMPSdkSip_PLAY_SEND_INVITE_FAILED,   //实时点播时，发送invite消息失败

	iMPSdkSip_STOP_GET_CID_FAILED,       //停止点播时，根据媒体端口号获取cid失败
	iMPSdkSip_STOP_SEND_BYE_FAILED,      //停止点播时，发送bye消息失败

	iMPSdkSip_CLOSECLIENT_BUILD_REGISTER_FAILED,
	iMPSdkSip_CLOSECLIENT_SEND_REGISTER_FAILED,  //关闭sdk采用标准方式注销时，发送注销消息失败
	iMPSdkSip_CLOSECLIENT_UNREGISTER_FAILED,     //关闭sdk采用标准方式注销时，失败
};

/***************SIP服务器类型*********************/
enum iMPSdkSip_PLATFORM
{
	iMPSdkSip_YSPLATFORM = 0,  //一所平台
	iMPSdkSip_OTHERPLATFORM = 1, //其他平台
};

/***************平台状态**************************/
enum iMPSdkSipA_PLATFORM_STATUS
{
	iMPSdkSipA_PLATFORM_ONLINE = 0,  //平台在线
	iMPSdkSipA_PLATFORM_OFFLINE = 1,  //平台下线
};

/***************SIP信令传输协议*******************/
enum iMPSdkSipA_SIPNetType
{
	iMPSdkSipA_SIP_TCP = 0,  //信令采用tcp方式传输
	iMPSdkSipA_SIP_UDP = 1,  //信令采用udp方式传输
};

/***************媒体流信令传输协议，默认为tcp*******************/
enum iMPSdkSipA_MEDIANETTYPE
{
	iMPSdkSipA_MEDIA_TCP = 0,  //媒体流采用tcp方式传输
	iMPSdkSipA_MEDIA_UDP = 1,  //媒体流采用udp方式传输
};

/***************当媒体流采用TCP传输时，服务端与客户端的协商*********/
enum iMPSdkSipA_TCP_SETUP
{
	iMPSdkSipA_TCP_ACTIVE = 0,  //TCP主动发起方
	iMPSdkSipA_TCP_PASSIVE = 1,  //TCP被动接收方
};

/***************媒体流类型，默认取值为0，即不使用增强层*************/
enum iMPSdkSipA_SVC_SPACE   
{
	iMPSdkSipA_SVC_SPACE_0 = 0,  //不使用增强层
	iMPSdkSipA_SVC_SPACE_1 = 1,  //使用1级增强
	iMPSdkSipA_SVC_SPACE_2 = 2,  //使用2级增强
	iMPSdkSipA_SVC_SPACE_3 = 3,  //使用3级增强
};

typedef struct sipAPlayInfo
{
	char Ip[20];
	int Port;
	char deviceID[21];
	char ssrc[11];
	char sdpStartTime[11];
	char sdpEndTime[11];
	int mediaNetType; //媒体流传输协议
	int tcpSetUp;  //当采用TCP方式接收媒体流时，标识该方为主动发起方还是被动接收方	 
	int iSvcSpace; //视频分辨率控制参数
} sipAPlayInfo_t ;

typedef struct sipAStopPlayInfo
{
	char deviceID[21];   //ID号可以唯一标识一个对话
} sipAStopPlayInfo_t;

typedef  sipAStopPlayInfo_t  sipAAckPlayInfo_t;

typedef struct sipAStatusInfo
{
	bool bPlatformStatus;   //一所平台状态，默认在线
} sipAStatusInfo_t;


/*************************************************
Function:		SIPAMsgCB_PLAY
Description:	SIPA发送完Invite消息后，接收到200OK后，回调通知媒体发送者信息
Input:          pSendSdpInfo: 结构体指针，包含媒体信息
                cbFuncMsgParam_play：回调函数参数指针
*************************************************/
typedef void (*SIPAMsgCB_PLAY)(struct sipAPlayInfo *pSendSdpInfo, void* cbFuncMsgParam_play);

/*************************************************
Function:		SIPAMsgCB_BYE
Description:	SIPA发送完Bye消息后，接收到200OK后，回调通知断掉的视频流信息
Input:          pStopInfo: 结构体指针，包含唯一标识对话的信息
                cbFuncMsgParam_bye：回调函数参数指针
*************************************************/
typedef void (*SIPAMsgCB_BYE)(struct sipAStopPlayInfo *pStopInfo, void* cbFuncMsgParam_bye);

/*************************************************
Function:		SIPAMsgCB_STATUS
Description:	当平台掉线时，回调通知平台状态
Input:          pStatusInfo: 结构体指针，包含平台状态信息
                cbFuncMsgParam_status：回调函数参数指针
*************************************************/
typedef void (*SIPAMsgCB_STATUS)(struct sipAStatusInfo *pStatusInfo, void* cbFuncMsgParam_status);

/*************************************************
Function:		iMPSdkSipA_initClient_V10
Description:	SipSdk初始化函数，建立全局变量映射，登陆
Input:			platFormType：SIP服务器类型
                sipNetType：信令传输协议
                serverId：注册服务器ID号
				serverIp：注册服务器IP
				serverPort：注册服务器端口号
				UserId：用户ID号
				localIp：用户IP
				localPot：本机端口号
Return:			SipSdk句柄
*************************************************/
CLIENTUA_EXPORT32 long iMPSdkSipA_initClient_V10(int platFormType, int sipNetType, char* serverId, char* serverIp, long serverPort, char* UserId, char* localIp, long localPort);

/*************************************************
Function:		iMPSdkSipA_setCallbackFunc_V10
Description:	设置回调函数
Input:			cbFuncMsg_play: 点播回调函数指针
				cbFuncMsgParam_play：点播回调函数参数指针
				cbFuncMsg_bye：停止点播回调函数指针
				cbFuncMsgParam_bye：停止点播回调函数参数指针
				cbFuncMsg_status：平台状态回调函数
				cbFuncMsgParam_status：平台状态回调函数参数指针
Return:			
*************************************************/
CLIENTUA_EXPORT32 int iMPSdkSipA_setCallbackFunc_V10(SIPAMsgCB_PLAY cbFuncMsg_play, void* cbFuncMsgParam_play, SIPAMsgCB_BYE cbFuncMsg_bye, void* cbFuncMsgParam_bye, SIPAMsgCB_STATUS cbFuncMsg_status, void* cbFuncMsgParam_status);

/*************************************************
Function:		iMPSdkSipA_playClient_V10
Description:	实时点播函数
Input:			handle:SipSdk句柄
				sipAPlayInfo_t：sdp信息结构体
Return:			
*************************************************/
CLIENTUA_EXPORT32 int iMPSdkSipA_playClient_V10(long handle, struct sipAPlayInfo *pReceiveSdpInfo);

/*************************************************
Function:		iMPSdkSipA_playStop_V10
Description:	停止点播函数
Input:			handle:SipSdk句柄
				pStopInfo：结构体指针，包含会话唯一标识
		
Return:			
*************************************************/
CLIENTUA_EXPORT32 int  iMPSdkSipA_playStop_V10(long handle, struct sipAStopPlayInfo *pStopInfo);

/*************************************************
Function:		iMPSdkSipA_closeClient_V10
Description:	SipSdk关闭函数
Input:			handle:SipSdk句柄
Return:			
*************************************************/
CLIENTUA_EXPORT32 int iMPSdkSipA_closeClient_V10(long handle);

#endif