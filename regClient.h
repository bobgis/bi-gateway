//���ļ�ͷ�����û�ע��
#pragma once
#ifndef _REGCLIENT_H_
#define _REGCLIENT_H_
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

/**
* ��ʼ��ע����Ϣ
* exoip��ȫ�ֱ���
* from��ע����
* proxy:����ע�������
* contact: ע������ϵ��ַ
* rid:ע��ɹ���ID��
* ����0��ʾ�ɹ�;-1���ɹ�
*/
int registerInit(void* exosip,int expire,char *from,char *proxy,char *contact,int *rid);
/**
*��Ӧ�������˵�401��ս
* exoip��ȫ�ֱ���
* message:�Żص���Ϣ
* expire: ��Чʱ��
* username:�û���
* userid:�û����
* password:�û�����
* rid:ע���
*����0��ʾ�ɹ�;-1���ɹ�
*/
int registerFor401(void* exosip,void* message,int expire,char *username,char *userid,char *password,int rid,char** heartStr);
/*
*ע������
*/
int registerHeart(void* exosip,char* message,int expire,int rid);

/*
*ȡ��ע��
*����0��ʾ�ɹ�;-1���ɹ�
*/
int unregister(void* exosip,int rid);


#endif;
