/*
 放置自定义的一些打印函数，以便查找输出结果
*/
#pragma once
#ifndef _UTILITY_H_
#define _UTILITY_H_

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
/*
* message:osip_message_t消息体
*/
void printBranch(void* message);

/*
*username:用户名
*ip:用户ip或域名
*port:端口，如果用户采用域名，该项省略
*format:格式化字符串
*/
void createSipFormat(char* username,char* ip/*domain*/,char* port,char *format,rsize_t len);
/*
*创建SDP;
*sdp:创建的sdp字符串
*/
void createSdp(char sdp[],char* localip,char* play,char* uri,char* t1,char* t2,char* port,char* b,char* y,char* f);
void createSubject(char sub[],char* sendid,char* sendsqu,char* recvid,char* recvsqu,rsize_t len);
void createGCallid(char* username,char* gCallid,int len);
unsigned long long convertTouInt64(char* number);

int isThreeParty(void* header);
int isInfoOK(void* header);
int isFileToEndOK(void* header);
void createInfo(int isRequest,char info[]);
int getPlayType(void* header);

/*
*得到全局调用的Callid;
*/
int getGCallidFromHeader(void* header,char* gCallid,rsize_t len);

void getSdpFromBody(void* message,char* sdp);

/*
  构建各种命令的消息体
*/
void createBodyOfCommandForNoAnwser(char* body);
void createBodyOfCommandForRequest(char* body);
void createBodyOfCommandForResponse(char* body);
void createBodyOfAlarm(char* body);
void createBodyOfAlarmForResposne(char* body);
void createBodyOfQuery(char* body);
void createBodyOfQueryForResposne(char* body);
void createBodyOfStatus(char* body);
void createBodyOfRetrieve(char* body);
void createBodyOfRetrieveForResposne(char* body);
void createBodyOfSubscribeForEvent(char* body);
void createBodyOfSubscribeForEvent200OK(char* body);
void createBodyOfSubscribeForEventNotify(char* body);
void createBodyOfSubscribeForEventNotify200OK(char* body);
void createBodyOfSubscribeForDirectory(char* body);
void createBodyOfSubscribeForDirectory200OK(char* body);
void createBodyOfSubscribeForDirectoryNotify(char* body);
void createBodyOfSubscribeForDirectoryNotify200OK(char* body);

#endif