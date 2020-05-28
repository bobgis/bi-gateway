/************************************************************
Copyright (C), 2016 ��������һ�о�����Ϣ������ҵ���з�һ��
FileName: iMPSDKSipACore.h
Author:	liuyumei    
version : 1.0
Date: 2016/9/13
Description:   �ӿں�������  
History:	   
***********************************************************/
#ifndef __SIPUA_IMPSDK_CLIENTUA_H__INCLUDED_
#define __SIPUA_IMPSDK_CLIENTUA_H__INCLUDED_

#ifdef _BUILD_DLL_
#define CLIENTUA_EXPORT32 __declspec(dllexport) 
#else
#define CLIENTUA_EXPORT32 __declspec(dllimport) 
#endif

//������ʼֵ����
#define ERRORCODE_BEGIN -1000
/*****************���󷵻�ֵ*****************************************/
enum iMPSdkSip_ERRORCODE
{
	iMPSdkSip_EXOSIP_INIT_SUCCESS = ERRORCODE_BEGIN,
	iMPSdkSip_EXOSIP_MALLOC_FAILED,      //exosip�ṹ������ڴ�ʧ��
	iMPSdkSip_EXOSIP_INIT_FAILED,        //ExosipЭ��ջ��ʼ��ʧ��
	iMPSdkSip_INTI_CLEAR_AUTHENTICATION_FAILED, //��ʼ��ʱ�������Ȩ��Ϣʧ��
	iMPSdkSip_INIT_BUILD_REGISTER_FAILED,
	iMPSdkSip_INTI_SEND_REGISTER_FAILED,        //����ע����Ϣʧ��
	iMPSdkSip_INIT_PLATFORM_TYPE_ERROR,     //sip������ƽ̨�������ô���
	iMPSdkSip_INIT_REGISTE_FAILED,         //ע��ʧ��

	iMPSdkSip_PLAY_MEDIA_TRANSPRO_ERROR,  //ʵʱ�㲥ʱ������ý��������Э�����
	iMPSdkSip_PLAY_TCP_SETUP_ERROR,  //ʵʱ�㲥ʱ����ý�����TCP��ʽ����ʱ������ˡ����ն����ô���
	iMPSdkSip_PLAY_BUILD_INVITE_FAILED,  //ʵʱ�㲥ʱ������invite��Ϣʧ��
	iMPSdkSip_PLAY_SET_INVITE_BODY_FAILED, //ʵʱ�㲥ʱ������invite��Ϣ��ʧ��
	iMPSdkSip_PLAY_SEND_INVITE_FAILED,   //ʵʱ�㲥ʱ������invite��Ϣʧ��

	iMPSdkSip_STOP_GET_CID_FAILED,       //ֹͣ�㲥ʱ������ý��˿ںŻ�ȡcidʧ��
	iMPSdkSip_STOP_SEND_BYE_FAILED,      //ֹͣ�㲥ʱ������bye��Ϣʧ��

	iMPSdkSip_CLOSECLIENT_BUILD_REGISTER_FAILED,
	iMPSdkSip_CLOSECLIENT_SEND_REGISTER_FAILED,  //�ر�sdk���ñ�׼��ʽע��ʱ������ע����Ϣʧ��
	iMPSdkSip_CLOSECLIENT_UNREGISTER_FAILED,     //�ر�sdk���ñ�׼��ʽע��ʱ��ʧ��
};

/***************SIP����������*********************/
enum iMPSdkSip_PLATFORM
{
	iMPSdkSip_YSPLATFORM = 0,  //һ��ƽ̨
	iMPSdkSip_OTHERPLATFORM = 1, //����ƽ̨
};

/***************ƽ̨״̬**************************/
enum iMPSdkSipA_PLATFORM_STATUS
{
	iMPSdkSipA_PLATFORM_ONLINE = 0,  //ƽ̨����
	iMPSdkSipA_PLATFORM_OFFLINE = 1,  //ƽ̨����
};

/***************SIP�����Э��*******************/
enum iMPSdkSipA_SIPNetType
{
	iMPSdkSipA_SIP_TCP = 0,  //�������tcp��ʽ����
	iMPSdkSipA_SIP_UDP = 1,  //�������udp��ʽ����
};

/***************ý���������Э�飬Ĭ��Ϊtcp*******************/
enum iMPSdkSipA_MEDIANETTYPE
{
	iMPSdkSipA_MEDIA_TCP = 0,  //ý��������tcp��ʽ����
	iMPSdkSipA_MEDIA_UDP = 1,  //ý��������udp��ʽ����
};

/***************��ý��������TCP����ʱ���������ͻ��˵�Э��*********/
enum iMPSdkSipA_TCP_SETUP
{
	iMPSdkSipA_TCP_ACTIVE = 0,  //TCP��������
	iMPSdkSipA_TCP_PASSIVE = 1,  //TCP�������շ�
};

/***************ý�������ͣ�Ĭ��ȡֵΪ0������ʹ����ǿ��*************/
enum iMPSdkSipA_SVC_SPACE   
{
	iMPSdkSipA_SVC_SPACE_0 = 0,  //��ʹ����ǿ��
	iMPSdkSipA_SVC_SPACE_1 = 1,  //ʹ��1����ǿ
	iMPSdkSipA_SVC_SPACE_2 = 2,  //ʹ��2����ǿ
	iMPSdkSipA_SVC_SPACE_3 = 3,  //ʹ��3����ǿ
};

typedef struct sipAPlayInfo
{
	char Ip[20];
	int Port;
	char deviceID[21];
	char ssrc[11];
	char sdpStartTime[11];
	char sdpEndTime[11];
	int mediaNetType; //ý��������Э��
	int tcpSetUp;  //������TCP��ʽ����ý����ʱ����ʶ�÷�Ϊ�������𷽻��Ǳ������շ�	 
	int iSvcSpace; //��Ƶ�ֱ��ʿ��Ʋ���
} sipAPlayInfo_t ;

typedef struct sipAStopPlayInfo
{
	char deviceID[21];   //ID�ſ���Ψһ��ʶһ���Ի�
} sipAStopPlayInfo_t;

typedef  sipAStopPlayInfo_t  sipAAckPlayInfo_t;

typedef struct sipAStatusInfo
{
	bool bPlatformStatus;   //һ��ƽ̨״̬��Ĭ������
} sipAStatusInfo_t;


/*************************************************
Function:		SIPAMsgCB_PLAY
Description:	SIPA������Invite��Ϣ�󣬽��յ�200OK�󣬻ص�֪ͨý�巢������Ϣ
Input:          pSendSdpInfo: �ṹ��ָ�룬����ý����Ϣ
                cbFuncMsgParam_play���ص���������ָ��
*************************************************/
typedef void (*SIPAMsgCB_PLAY)(struct sipAPlayInfo *pSendSdpInfo, void* cbFuncMsgParam_play);

/*************************************************
Function:		SIPAMsgCB_BYE
Description:	SIPA������Bye��Ϣ�󣬽��յ�200OK�󣬻ص�֪ͨ�ϵ�����Ƶ����Ϣ
Input:          pStopInfo: �ṹ��ָ�룬����Ψһ��ʶ�Ի�����Ϣ
                cbFuncMsgParam_bye���ص���������ָ��
*************************************************/
typedef void (*SIPAMsgCB_BYE)(struct sipAStopPlayInfo *pStopInfo, void* cbFuncMsgParam_bye);

/*************************************************
Function:		SIPAMsgCB_STATUS
Description:	��ƽ̨����ʱ���ص�֪ͨƽ̨״̬
Input:          pStatusInfo: �ṹ��ָ�룬����ƽ̨״̬��Ϣ
                cbFuncMsgParam_status���ص���������ָ��
*************************************************/
typedef void (*SIPAMsgCB_STATUS)(struct sipAStatusInfo *pStatusInfo, void* cbFuncMsgParam_status);

/*************************************************
Function:		iMPSdkSipA_initClient_V10
Description:	SipSdk��ʼ������������ȫ�ֱ���ӳ�䣬��½
Input:			platFormType��SIP����������
                sipNetType�������Э��
                serverId��ע�������ID��
				serverIp��ע�������IP
				serverPort��ע��������˿ں�
				UserId���û�ID��
				localIp���û�IP
				localPot�������˿ں�
Return:			SipSdk���
*************************************************/
CLIENTUA_EXPORT32 long iMPSdkSipA_initClient_V10(int platFormType, int sipNetType, char* serverId, char* serverIp, long serverPort, char* UserId, char* localIp, long localPort);

/*************************************************
Function:		iMPSdkSipA_setCallbackFunc_V10
Description:	���ûص�����
Input:			cbFuncMsg_play: �㲥�ص�����ָ��
				cbFuncMsgParam_play���㲥�ص���������ָ��
				cbFuncMsg_bye��ֹͣ�㲥�ص�����ָ��
				cbFuncMsgParam_bye��ֹͣ�㲥�ص���������ָ��
				cbFuncMsg_status��ƽ̨״̬�ص�����
				cbFuncMsgParam_status��ƽ̨״̬�ص���������ָ��
Return:			
*************************************************/
CLIENTUA_EXPORT32 int iMPSdkSipA_setCallbackFunc_V10(SIPAMsgCB_PLAY cbFuncMsg_play, void* cbFuncMsgParam_play, SIPAMsgCB_BYE cbFuncMsg_bye, void* cbFuncMsgParam_bye, SIPAMsgCB_STATUS cbFuncMsg_status, void* cbFuncMsgParam_status);

/*************************************************
Function:		iMPSdkSipA_playClient_V10
Description:	ʵʱ�㲥����
Input:			handle:SipSdk���
				sipAPlayInfo_t��sdp��Ϣ�ṹ��
Return:			
*************************************************/
CLIENTUA_EXPORT32 int iMPSdkSipA_playClient_V10(long handle, struct sipAPlayInfo *pReceiveSdpInfo);

/*************************************************
Function:		iMPSdkSipA_playStop_V10
Description:	ֹͣ�㲥����
Input:			handle:SipSdk���
				pStopInfo���ṹ��ָ�룬�����ỰΨһ��ʶ
		
Return:			
*************************************************/
CLIENTUA_EXPORT32 int  iMPSdkSipA_playStop_V10(long handle, struct sipAStopPlayInfo *pStopInfo);

/*************************************************
Function:		iMPSdkSipA_closeClient_V10
Description:	SipSdk�رպ���
Input:			handle:SipSdk���
Return:			
*************************************************/
CLIENTUA_EXPORT32 int iMPSdkSipA_closeClient_V10(long handle);

#endif