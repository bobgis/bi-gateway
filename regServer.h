#pragma once 
#ifndef _REGSERVER_H_
#define _REGSERVER_H_

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

/**
* ����401��ս��Ϣ
* exoip��ȫ�ֱ���
* message:���ܵ���Ϣ
* ����0��ʾ�ɹ�;-1���ɹ�
*/
int regSend401(void* exosip,void *message);
/**
*����Nxx��Ϣ
* exoip��ȫ�ֱ���
* message:������Ϣ
* status:״̬��
*����0��ʾ�ɹ�;-1���ɹ�
*/
int regSenNxx(void* exosip,void* message,int status);


#endif