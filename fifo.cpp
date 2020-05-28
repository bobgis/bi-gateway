#include "stdafx.h"
#include "fifo.h"
#include <WinSock2.h>
#include <deque>
using namespace std;

//声明队列
deque<sipAPlayInfo_t*> sipAPlayInfoFifo;
deque<sipAStopPlayInfo_t*> sipAStopPlayInfoFifo;

//声明临界对象
static CRITICAL_SECTION sipAPlayInfoCs;
static CRITICAL_SECTION sipAStopPlayInfoCs;

static int sipAPlayInfoCounts=0;
static int sipAStopPlayCounts=0;

void initSipAFifo(){
	InitializeCriticalSection(&sipAPlayInfoCs);
	InitializeCriticalSection(&sipAStopPlayInfoCs);
}

void deleteSipAFifo(){
	DeleteCriticalSection(&sipAPlayInfoCs);
	DeleteCriticalSection(&sipAStopPlayInfoCs);
}
void addSipAPlayInfoToFifo(sipAPlayInfo_t*  lpSipAPlayInfo){
	EnterCriticalSection(&sipAPlayInfoCs);
	sipAPlayInfoFifo.push_back(lpSipAPlayInfo);
	sipAPlayInfoCounts++;
	LeaveCriticalSection(&sipAPlayInfoCs);
}
void addSipAStopPlayInfoToFifo(sipAStopPlayInfo_t* lpSipAStopPlayInfo){
	EnterCriticalSection(&sipAStopPlayInfoCs);
	sipAStopPlayInfoFifo.push_back(lpSipAStopPlayInfo);
	sipAStopPlayCounts++;
	LeaveCriticalSection(&sipAStopPlayInfoCs);
}

sipAPlayInfo_t* getSipAPlayInfoFromFifo(){
	sipAPlayInfo_t* lp;
	EnterCriticalSection(&sipAPlayInfoCs);
	if(sipAPlayInfoFifo.empty()){
		lp = NULL;
	}else{
		lp = sipAPlayInfoFifo.front();
		sipAPlayInfoFifo.pop_front();
		sipAPlayInfoCounts--;
	}
	LeaveCriticalSection(&sipAPlayInfoCs);
	return lp;
}

sipAStopPlayInfo_t* getSipAStopPlayInfoFromFifo(){
	sipAStopPlayInfo_t* lp;
	EnterCriticalSection(&sipAStopPlayInfoCs);
	if(sipAStopPlayInfoFifo.empty()){
		lp = NULL;
	}else{
		lp = sipAStopPlayInfoFifo.front();
		sipAStopPlayInfoFifo.pop_front();
		sipAStopPlayCounts--;
	}
	LeaveCriticalSection(&sipAStopPlayInfoCs);
	return lp;
}
void clearSipAPlayInfoFifo(){
	if(sipAPlayInfoCounts>0){
		EnterCriticalSection(&sipAPlayInfoCs);
		sipAPlayInfoFifo.clear();
		sipAPlayInfoCounts=0;
		LeaveCriticalSection(&sipAPlayInfoCs);
	}
}
void clearSipAStopPlayInfoFifo(){
	if(sipAStopPlayCounts>0){
		EnterCriticalSection(&sipAStopPlayInfoCs);
		sipAStopPlayInfoFifo.clear();
		sipAStopPlayCounts=0;
		LeaveCriticalSection(&sipAStopPlayInfoCs);
	}
}
int getSipAPlayInfoInFifoCounts(){
	return sipAPlayInfoCounts;
}
int getsipAStopPlayInfoInFifoCounts(){
	return sipAStopPlayCounts;
}

