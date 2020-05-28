//队列管理
#pragma once
#ifndef _FIFO_H_
#define _FIFO_H_
#include "stdafx.h"
#include ".\SIPA-SDK\iMPSDKSipACore.h"
/*
*添加点播实体到队列准备点播
*lpSipAPlayInfo:结构体sipAPlayInfo_t指针
*/
void addSipAPlayInfoToFifo(sipAPlayInfo_t*  lpSipAPlayInfo);
/*
*添加停止点播实体到队列准备停止点播
*lpSipAStopPlayInfo:结构体sipAStopPlayInfo_t指针
*/
void addSipAStopPlayInfoToFifo(sipAStopPlayInfo_t* lpSipAStopPlayInfo);
/*
*从队列取出点播实体指针
*返回sipAStopPlayInfo_t指针
*/
sipAPlayInfo_t* getSipAPlayInfoFromFifo();
/*
*从队列取出停止点播实体指针
*返回sipAStopPlayInfo_t指针
*/
sipAStopPlayInfo_t* getSipAStopPlayInfoFromFifo();
/*
*返回队列中点播实体数量
*/
int getSipAPlayInfoInFifoCounts();
/*
*返回队列中停止点播实体数量
*/
int getsipAStopPlayInfoInFifoCounts();
/*
*清空点播队列
*/
void clearSipAPlayInfoFifo();
/*
*清空停止点播队列
*/
void clearSipAStopPlayInfoFifo();
/*
*初始化SIPA队列
*/
void initSipAFifo();
/*
*删除SIPA队列
*/
void deleteSipAFifo();
#endif;