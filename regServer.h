#pragma once 
#ifndef _REGSERVER_H_
#define _REGSERVER_H_

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

/**
* 发送401挑战信息
* exoip：全局变量
* message:接受的消息
* 返回0表示成功;-1不成功
*/
int regSend401(void* exosip,void *message);
/**
*发送Nxx信息
* exoip：全局变量
* message:接受消息
* status:状态码
*返回0表示成功;-1不成功
*/
int regSenNxx(void* exosip,void* message,int status);


#endif