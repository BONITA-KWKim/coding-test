#ifndef _SENDER_MMS_PROCESS_H_
#define _SENDER_MMS_PROCESS_H_

//**************************************************
// Include
//**************************************************
#include "stdafx.h"
#include <string>
//#include "smsPacketStruct.h"
//#include "fifoInfo.h"
/* inc */
#include "logonDbInfo.h"
#include "adminInfo.h"
#include "senderInfo.h"
#include "senderDbInfo.h"
#include "processInfo.h"
/* lib */
#include "adminUtil.h"
#include "logonUtil.h"
#include "dbUtil.h"
//#include "mmsPacketBase.h"
#include "mmsPacketSend.h"
#include "mmsFileProcess.h"
#include "DatabaseORA_MMS.h"
#include "json.h"

#include "monitor.h"
/* kskyb lib */
#include "kssocket.h"
#include "ksconfig.h"
//#include "mmsPacketUtil.h"
#include "checkCallback.h"

#include "atalk_data_info.h"
using namespace std;

//**************************************************
// Define
//**************************************************
/*
#define TELCO_SKT "QUEUE_SKT"
#define TELCO_KTF "QUEUE_KTF"
#define TELCO_SSN "QUEUE_SKT"
#define TELCO_LGT "QUEUE_LGT" 
#define TELCO_SKB "QUEUE_SKB_BCK"
#define TELCO_KTC "QUEUE_KTC"
*/

/* LOG type; 0: monitor log, 1: custom log */
#define MON 0
#define LOG 1

//**************************************************
// Class definitions
//**************************************************
class CConfigSender {
public:
	char logonDBName[LENGTH_NAME_LOGON_DB];
	char monitorName[LENGTH_NAME_MONITOR];
	char domainPath[LENGTH_NAME_DOMAIN_PATH];
	char ContentPath[LENGTH_NAME_CONTENT_PATH];
	char dbuid[LENGTH_DB_UID];
	char dbdsn[LENGTH_DB_DSN];
	int socketLinkTimeOut;
	int dbRequestTimeOut;
	int dbMmsIdHeader;
};

class SenderProcess {
public:
	char szLimitTime[16];
	char szLimitCurTime[16];
	int nCurAccCnt;
	bool bDayWarnCheck;
	bool bMonWarnCheck;

	SenderProcess();
	~SenderProcess(){};

	void SenderMain(int sockfd, CLogonDbInfo& logonDbInfo);
private:
	int classifyS(CMonitor& monitor, CProcessInfo& processInfo,
			CLogonDbInfo& logonDbInfo, CKSSocket& db, CKSSocket& hRemoteSock);
	//* < brief �߼� ���� üũ
	int SenderLimit(CLogonDbInfo& logonDbInfo);
	int LimitCheck(CLogonDbInfo& logonDbInfo);
	// deprecated
	int get_data_fields_from_json(NVRSendMessage* data, Json::Value *raw);
	int get_data_fields_from_json_v1(NVRSendMessage* data, Json::Value *raw);
	void decrypt_string(char* desc, const char* source, int size);
	void create_receiver(char *desc, const char *receiver, const char *nation_code, int size);
};

//**************************************************
// Declare variables
//**************************************************
CConfigSender gConf; /* Configuration */
CSenderInfo gSenderInfo;
CCheckCallback checkCallback;
KSKYB::CDatabaseORA g_oracle;

struct _message_info message_info;
struct _shm_info* shm_info;

char PROCESS_NO[LENGTH_PROCESS_NO];
char PROCESS_NAME[LENGTH_PROCESS_NAME];
char _DATALOG[LENGTH_CUSTOM_LOG_FILE_NAME];
char _MONILOG[LENGTH_MONITOR_LOG_FILE_NAME];

char szSenderID[LENGTH_CID];
char senderDbDomainName[LENGTH_SENDER_DB_DOMAIN_NAME];

int activeProcess = TRUE;
bool bSActive = true;
int sum = 0;

time_t SThisT, SLastTLink;
time_t monLastT;

//**************************************************
// Define functions
//**************************************************
/* socket communication */
int recvLink(CKSSocket& hRemoteSock, char* buff);
int sendPong(CKSSocket& hRemoteSock);
int sendAck(CKSSocket& hRemoteSock, CMMSPacketSend& mmsPacketSend, int nCode,
		int ctnid, string strDesc);
/* utility */
/*
 * name: logPrintS
 * desc: Write file log
 * params
 * - type: monitor log(0; MON), custom log(1; LOG)
 * - format: something to write
 * results:
 * - none
 */
void logPrintS(int type, const char *format, ...);
int configParse(char* file);
void viewPackSender(char *a, int n);
void writeLogMMSData(CMMSPacketSend& mmsPacketSend, long long mmsid, int ctnid);
//int loadDialCodeAll();
/* dont know */
char* getTelcoQName(char* dstaddr, char* telco = NULL);
int getTelcoId(int imgCnt, char* szTelco, int nColorYN);
int getTelcoId(int imgCnt, char* szTelco, char *szQType);

/* DB */
int write_send_table_and_enqueue(NVRSendMessage *nvr_send_message, int priority);

#endif

/* End fo the File */
