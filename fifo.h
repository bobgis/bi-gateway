//���й���
#pragma once
#ifndef _FIFO_H_
#define _FIFO_H_
#include "stdafx.h"
#include ".\SIPA-SDK\iMPSDKSipACore.h"
/*
*��ӵ㲥ʵ�嵽����׼���㲥
*lpSipAPlayInfo:�ṹ��sipAPlayInfo_tָ��
*/
void addSipAPlayInfoToFifo(sipAPlayInfo_t*  lpSipAPlayInfo);
/*
*���ֹͣ�㲥ʵ�嵽����׼��ֹͣ�㲥
*lpSipAStopPlayInfo:�ṹ��sipAStopPlayInfo_tָ��
*/
void addSipAStopPlayInfoToFifo(sipAStopPlayInfo_t* lpSipAStopPlayInfo);
/*
*�Ӷ���ȡ���㲥ʵ��ָ��
*����sipAStopPlayInfo_tָ��
*/
sipAPlayInfo_t* getSipAPlayInfoFromFifo();
/*
*�Ӷ���ȡ��ֹͣ�㲥ʵ��ָ��
*����sipAStopPlayInfo_tָ��
*/
sipAStopPlayInfo_t* getSipAStopPlayInfoFromFifo();
/*
*���ض����е㲥ʵ������
*/
int getSipAPlayInfoInFifoCounts();
/*
*���ض�����ֹͣ�㲥ʵ������
*/
int getsipAStopPlayInfoInFifoCounts();
/*
*��յ㲥����
*/
void clearSipAPlayInfoFifo();
/*
*���ֹͣ�㲥����
*/
void clearSipAStopPlayInfoFifo();
/*
*��ʼ��SIPA����
*/
void initSipAFifo();
/*
*ɾ��SIPA����
*/
void deleteSipAFifo();
#endif;