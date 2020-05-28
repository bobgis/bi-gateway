/*
 �����Զ����һЩ��ӡ�������Ա����������
*/
#pragma once
#ifndef _UTILITY_H_
#define _UTILITY_H_

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
/*
* message:osip_message_t��Ϣ��
*/
void printBranch(void* message);

/*
*username:�û���
*ip:�û�ip������
*port:�˿ڣ�����û���������������ʡ��
*format:��ʽ���ַ���
*/
void createSipFormat(char* username,char* ip/*domain*/,char* port,char *format,rsize_t len);
/*
*����SDP;
*sdp:������sdp�ַ���
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
*�õ�ȫ�ֵ��õ�Callid;
*/
int getGCallidFromHeader(void* header,char* gCallid,rsize_t len);

void getSdpFromBody(void* message,char* sdp);

/*
  ���������������Ϣ��
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