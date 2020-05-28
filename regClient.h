//本文件头用于用户注册
#pragma once
#ifndef _REGCLIENT_H_
#define _REGCLIENT_H_
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

/**
* 初始化注册信息
* exoip：全局变量
* from：注册者
* proxy:代理注册服务器
* contact: 注册者联系地址
* rid:注册成功的ID号
* 返回0表示成功;-1不成功
*/
int registerInit(void* exosip,int expire,char *from,char *proxy,char *contact,int *rid);
/**
*响应服务器端的401挑战
* exoip：全局变量
* message:放回的消息
* expire: 生效时间
* username:用户名
* userid:用户编号
* password:用户密码
* rid:注册号
*返回0表示成功;-1不成功
*/
int registerFor401(void* exosip,void* message,int expire,char *username,char *userid,char *password,int rid,char** heartStr);
/*
*注册心跳
*/
int registerHeart(void* exosip,char* message,int expire,int rid);

/*
*取消注册
*返回0表示成功;-1不成功
*/
int unregister(void* exosip,int rid);


#endif;
