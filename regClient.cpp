/*
reg.h�ļ���ʵ�ַ���
*/

#include "stdafx.h"
#include <WinSock2.h>
#include "osip2\osip.h"
#include "eXosip2\eX_setup.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "regClient.h"
#include "utility.h"

int registerInit(void* exosip,int expire,char *from,char *proxy,char *contact,int *rid){
	osip_message_t *reg=NULL;
	int i=0;
	eXosip_t *context_eXosip = (eXosip_t*)exosip;
	eXosip_lock(context_eXosip);
	*rid=eXosip_register_build_initial_register(context_eXosip,from,proxy,contact,expire,&reg);
	if(*rid<0){
		printf("ע���ʼ��ʧ�ܣ�\n");
		i=*rid;
	}else{	
		osip_message_set_supported (reg, "100rel");
		osip_message_set_supported (reg, "path");
		i= eXosip_register_send_register(context_eXosip,*rid,reg);
		if(i!=0){
			printf("���ͳ�ʼ��ע����Ϣ����ʧ��\n");
		}
	}
	eXosip_unlock(context_eXosip);
	printBranch((osip_message_t*)reg);
	return i;
}

int registerFor401(void* exosip,void* message,int expire,char *username,char *userid,char *password,int rid,char** heartStr){
	osip_www_authenticate_t *aHeader;
	osip_message_t *reg;
	int i= 0;
	osip_message_t *sip = (osip_message_t*)message;
	eXosip_t *context_eXosip = (eXosip_t*)exosip;
	i = osip_message_get_www_authenticate(sip,0,&aHeader);
	if(i!=0){
		printf("�޷������Ȩͷ!\n");
		return i;
	}
	eXosip_clear_authentication_info(context_eXosip);
	//�ڴ˴���������ϻ�ȡ��������������
	eXosip_lock(context_eXosip);
	i = eXosip_add_authentication_info(context_eXosip,username,userid,password,NULL,aHeader->realm);
	if(i!=0){
		printf("�޷������Ȩ��Ϣ!\n");
		eXosip_unlock(context_eXosip);
		return i;
	}
	i = eXosip_register_build_register(context_eXosip,rid,expire,&reg);

	if(i!=0){
		printf("�޷�����ע����Ϣ!\n");
		eXosip_unlock(context_eXosip);
		return i;
	}
	osip_authorization_t *auth;
	osip_message_get_authorization(reg,0,&auth);
	osip_authorization_to_str(auth,heartStr);

	i = eXosip_register_send_register(context_eXosip,rid,reg);
	if(i!=0){
		printf("���ʹ���ע����Ϣ����ʧ��!\n");
		eXosip_unlock(context_eXosip);
		return i;
	}
	eXosip_unlock(context_eXosip);

	printBranch(reg);
	return i;
}
int registerHeart(void* exosip,char* message,int expire,int rid){
	osip_message_t *reg;
	int i= 0;
	eXosip_t *context_eXosip = (eXosip_t*)exosip;
	i = eXosip_register_build_register(context_eXosip,rid,expire,&reg);
	osip_authorization_t *auth;
	osip_message_get_authorization(reg,0,&auth);
	if(auth==NULL){
		osip_message_set_header(reg,"authorization",message);
	}
	i = eXosip_register_send_register(context_eXosip,rid,reg);
	if(i!=0){
		printf("���ʹ���ע����Ϣ����ʧ��!\n");
	}
	eXosip_unlock(context_eXosip);
	return i;
}
int unregister(void* exosip,int rid){
	osip_message_t *reg;
	int i=0;
	eXosip_t* context_eXosip = (eXosip_t*)exosip;
	eXosip_lock(context_eXosip);
	i = eXosip_register_build_register(context_eXosip,rid,0,&reg);
	if(i<0){
			printf("ע��ע��ʧ��!\n");
	}
	else{
			i = eXosip_register_send_register(context_eXosip,rid,reg);
			if(i!=0){
                printf("����ע��ע����Ϣ����ʧ��!\n");
			}else{
				i = eXosip_register_remove (context_eXosip, rid);
			    if(i==0){
				    printf("ע��ע��ɹ�!\n");
			    }else{
				    printf("�û��ѱ��󶨣��޷�ȡ��ע��!\n");
			    }
			}	
	}
   eXosip_unlock(context_eXosip);
   return i;
}