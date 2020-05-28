#ifndef _COMMON_H_
#define _COMMON_H_

enum NETSDK_MESSAGETYPE_E
{
	NETSDK_MSGTYPE_PLATFORM_UNAVAILABLE = 0, // 视高平台不可用(如离线)
	NETSDK_MSGTYPE_REALPLAY_START = 1,       // 视高平台向一所平台请求启动实时视频点播
	NETSDK_MSGTYPE_REALPLAY_STOP = 2,        // 视高平台向一所平台请求停止实时视频点播
	NETSDK_MSGTYPE_REALPLAY_START_RESP = 3,  // 一所平台向视高平台启动实时视频点播回复
	NETSDK_MSGTYPE_PLATFORM_AVAILABLE = 4,   // 视高平台可用
};

/*视高平台可用*/
typedef struct _STRU_NETSDK_PLATFORM_AVAILABLE_INFO
{
	long hSdkHandle;

} STRU_NETSDK_PLATFORM_AVAILABLE_INFO, *PSTRU_NETSDK_PLATFORM_AVAILABLE_INFO;

enum NETSDK_MEDIATRANSPRO_E
{
	NETSDK_MEDIATRANS_TCP = 0,   // 媒体流采用tcp方式传输 
};

enum NETSDK_MEDIAENCODEPRO_E
{
	NETSDK_MEDIAENCODE_PS = 96,  // GB/T 28181 PS编码格式
}; 

/*视高停止监看请求*/
typedef struct _STRU_NETSDK_RPSTOP_INFO
{
	char strDeviceID[21]; // 20位设备ID

} STRU_NETSDK_RPSTOP_INFO, *PSTRU_NETSDK_RPSTOP_INFO;

/*视高开启监看请求*/
typedef struct _STRU_NETSDK_RPSTRAT_INFO
{
	char                    strDeviceID[21];                   // 20位设备ID
	int                     iStreamType;                       // 主副码流(0:基本流(副码流),1:一级增强流(主码流))，目前默认仅支持0
	NETSDK_MEDIATRANSPRO_E  eMediaTransPro;                    // 媒体流传输协议
	NETSDK_MEDIAENCODEPRO_E eMediaEncodePro;                   // 媒体流编码协议
	BOOL                    bTcpSetUp;                         // 媒体流采用TCP方式传输时，该参数标识视高平台主动发起TCP连接还是被动接收TCP连接：TRUE时视高平台媒体服务器主动发起TCP连接，FALSE时视高平台媒体服务器被动接收TCP连接。目前根据前期协商的“发流端被动接收TCP连接(即监听)”的原则：这里应固定支持TRUE即可。
	char                    szMediaRecvIP[16];                 // 媒体流接收IP地址
	long                    nMediaRecvPort;                    // 媒体流接收端口号
	char                    strUserID[21];                     // 视高中心SIP服务器ID(视高可填空，由双向网关填充)
} STRU_NETSDK_RPSTRAT_INFO, *PSTRU_NETSDK_RPSTRAT_INFO;

/*一所监看回复*/
typedef struct _STRU_NETSDK_RPSTRAT_RESP_INFO
{
	char          strDeviceID[21];                    // 20位设备ID
	int           iStreamType;                        // 主副码流(0:基本流(副码流),1:一级增强流(主码流))，目前默认仅支持0
	int	          iResult;                            // 结果
	enum NETSDK_MEDIATRANSPRO_E  eMediaTransPro;      // 媒体流传输协议
	enum NETSDK_MEDIAENCODEPRO_E eMediaEncodePro;     // 媒体流编码协议
	BOOL          bTcpSetUp;
	char          strMediaListenIP[16];              // 媒体服务器ip
	long          nMediaListenPort;                  // 媒体服务器端口
	char          strSSRC[11];                       // 该SSRC由视高平台生成并告诉一所
	char          strServerID[21];                   // 媒体流发送者ID(此处为视高平台SIP服务器ID) (视高可填空，由双向网关填充)
	char          szExtendData[1024];                // 该参数用于返回一所平台媒体服务器主动发起TCP连接时需要携带的验证信息(暂不使用，验证信息使用GB/T 28181标准方式，参考《附件F-一所互联网平台中心媒体服务接入控制接口说明》文档，由双方媒体服务器按照GB/T 28181标准方式独立生成及解析)

} STRU_NETSDK_RPSTRAT_RESP_INFO, *PSTRU_NETSDK_RPSTRAT_RESP_INFO;

typedef int (*PNETSDKMSGCB)( enum NETSDK_MESSAGETYPE_E eMsgType,
							void*  pMsgInfo, 
							void*  pResultInfo,
							void*  pMsgFuncCallbackParam );


#endif