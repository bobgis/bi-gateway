#ifndef _COMMON_H_
#define _COMMON_H_

enum NETSDK_MESSAGETYPE_E
{
	NETSDK_MSGTYPE_PLATFORM_UNAVAILABLE = 0, // �Ӹ�ƽ̨������(������)
	NETSDK_MSGTYPE_REALPLAY_START = 1,       // �Ӹ�ƽ̨��һ��ƽ̨��������ʵʱ��Ƶ�㲥
	NETSDK_MSGTYPE_REALPLAY_STOP = 2,        // �Ӹ�ƽ̨��һ��ƽ̨����ֹͣʵʱ��Ƶ�㲥
	NETSDK_MSGTYPE_REALPLAY_START_RESP = 3,  // һ��ƽ̨���Ӹ�ƽ̨����ʵʱ��Ƶ�㲥�ظ�
	NETSDK_MSGTYPE_PLATFORM_AVAILABLE = 4,   // �Ӹ�ƽ̨����
};

/*�Ӹ�ƽ̨����*/
typedef struct _STRU_NETSDK_PLATFORM_AVAILABLE_INFO
{
	long hSdkHandle;

} STRU_NETSDK_PLATFORM_AVAILABLE_INFO, *PSTRU_NETSDK_PLATFORM_AVAILABLE_INFO;

enum NETSDK_MEDIATRANSPRO_E
{
	NETSDK_MEDIATRANS_TCP = 0,   // ý��������tcp��ʽ���� 
};

enum NETSDK_MEDIAENCODEPRO_E
{
	NETSDK_MEDIAENCODE_PS = 96,  // GB/T 28181 PS�����ʽ
}; 

/*�Ӹ�ֹͣ�࿴����*/
typedef struct _STRU_NETSDK_RPSTOP_INFO
{
	char strDeviceID[21]; // 20λ�豸ID

} STRU_NETSDK_RPSTOP_INFO, *PSTRU_NETSDK_RPSTOP_INFO;

/*�Ӹ߿����࿴����*/
typedef struct _STRU_NETSDK_RPSTRAT_INFO
{
	char                    strDeviceID[21];                   // 20λ�豸ID
	int                     iStreamType;                       // ��������(0:������(������),1:һ����ǿ��(������))��ĿǰĬ�Ͻ�֧��0
	NETSDK_MEDIATRANSPRO_E  eMediaTransPro;                    // ý��������Э��
	NETSDK_MEDIAENCODEPRO_E eMediaEncodePro;                   // ý��������Э��
	BOOL                    bTcpSetUp;                         // ý��������TCP��ʽ����ʱ���ò�����ʶ�Ӹ�ƽ̨��������TCP���ӻ��Ǳ�������TCP���ӣ�TRUEʱ�Ӹ�ƽ̨ý���������������TCP���ӣ�FALSEʱ�Ӹ�ƽ̨ý���������������TCP���ӡ�Ŀǰ����ǰ��Э�̵ġ������˱�������TCP����(������)����ԭ������Ӧ�̶�֧��TRUE���ɡ�
	char                    szMediaRecvIP[16];                 // ý��������IP��ַ
	long                    nMediaRecvPort;                    // ý�������ն˿ں�
	char                    strUserID[21];                     // �Ӹ�����SIP������ID(�Ӹ߿���գ���˫���������)
} STRU_NETSDK_RPSTRAT_INFO, *PSTRU_NETSDK_RPSTRAT_INFO;

/*һ���࿴�ظ�*/
typedef struct _STRU_NETSDK_RPSTRAT_RESP_INFO
{
	char          strDeviceID[21];                    // 20λ�豸ID
	int           iStreamType;                        // ��������(0:������(������),1:һ����ǿ��(������))��ĿǰĬ�Ͻ�֧��0
	int	          iResult;                            // ���
	enum NETSDK_MEDIATRANSPRO_E  eMediaTransPro;      // ý��������Э��
	enum NETSDK_MEDIAENCODEPRO_E eMediaEncodePro;     // ý��������Э��
	BOOL          bTcpSetUp;
	char          strMediaListenIP[16];              // ý�������ip
	long          nMediaListenPort;                  // ý��������˿�
	char          strSSRC[11];                       // ��SSRC���Ӹ�ƽ̨���ɲ�����һ��
	char          strServerID[21];                   // ý����������ID(�˴�Ϊ�Ӹ�ƽ̨SIP������ID) (�Ӹ߿���գ���˫���������)
	char          szExtendData[1024];                // �ò������ڷ���һ��ƽ̨ý���������������TCP����ʱ��ҪЯ������֤��Ϣ(�ݲ�ʹ�ã���֤��Ϣʹ��GB/T 28181��׼��ʽ���ο�������F-һ��������ƽ̨����ý����������ƽӿ�˵�����ĵ�����˫��ý�����������GB/T 28181��׼��ʽ�������ɼ�����)

} STRU_NETSDK_RPSTRAT_RESP_INFO, *PSTRU_NETSDK_RPSTRAT_RESP_INFO;

typedef int (*PNETSDKMSGCB)( enum NETSDK_MESSAGETYPE_E eMsgType,
							void*  pMsgInfo, 
							void*  pResultInfo,
							void*  pMsgFuncCallbackParam );


#endif