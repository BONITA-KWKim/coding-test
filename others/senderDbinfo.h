#ifndef _SENDER_DB_INFO_H_
#define _SENDER_DB_INFO_H_

#include "smsPacketStruct.h"
#include "logonDbInfo.h"
#include "atalk_data_info.h"
#include "senderInfo.h"

enum {
	GETCTNID,
	GETMMSID,
	SETSENDQUE,
	SETSENDTBL,
	SETSENDCTNTBL,
	SETSENDQUE_FILTER,
	SETRPTTBL,
	SETSENDQUE_V2,
	SETSENDQUE_V3,
	GETMMSSEQ,
	SETSENDRPT,
	REQRPT, // add to request a report by agent
	SEND_MESSAGE
};

class CSenderDbInfo {
public:
	TypeMsgDataSnd smsData;
	CLogonDbInfo logonDbInfo;
	char szReserve[128];
	CSenderInfo senderInfo;
	int result;
};

class CSenderDbInfoAck {
public:
	int msgid;
	char szResult[10];
	long long mmsid;
	int ctnid;
	int seq;
};

/* Classify working by connection pool */
class Header {
public:
	int type;
	int leng;
};

/* Class for one transaction(oracle procedure) */
class CSendMessage {
public:
	Header header;
	/* common */
	char cid[LENGTH_CID];
	char ptn_sn[LENGTH_PTN_SN];
	int priority;
	/* table */
	char callback[LENGTH_CALL_BACK];
	char msg_title[LENGTH_MESSAGE_TITLE];
	char resv_data[LENGTH_RESV_DATA];
	int msg_type;
	int ctn_id;
	int ctn_type;
	int rgn_rate;
	int interval;
	int text_cnt;
	int img_cnt;
	int aug_cnt;
	int mp_cnt;
	char real_ptn_id[10+1];
	/* queue */
	char q_name[LENGTH_Q_NAME];
	char sender_key[LENGTH_SENDER_KEY];
	char dest_addr[LENGTH_DEST_ADDR];
	char app_user_id[20+1];
	char template_code[LENGTH_TEMPLATE_CODE];
	char btn_name[LENGTH_BUTTON_NAME];
	char btn_url[LENGTH_BUTTON_URL];
	char btn_value[LENGTH_BUTTON_DATA];
	char msg_body[LENGTH_MESSAGE_BODY];
	char res_method[LENGTH_RES_METHOD];
	char timeout[LENGTH_TIMEOUT];
	int pid;
	char char_set[LENGTH_CHARSET];
	char title[50+1];
	char reserved[4000+1];
	/* output */
	long long mms_id;
	/* not used */
	char szPartnerKey[40 + 1];
};

/********** old version(31.Oct.2019) **********/
//????? ??? 20170622
class CSenderDbMMSSEQ {
public:
	Header header;
	int seq;
};

class CSenderDbMMSTBL {
public:
	Header header;
	char szDstAddr[16 + 1];
	char szCallBack[16 + 1];
	char szMsgTitle[200 + 1];
	char szPtnSn[32 + 1];
	char szResvData[200 + 1];
	char szCid[10 + 1];
	int nMsgType;
	int nPriority;
	int nCtnId;
	int nCtnType;
	int nRgnRate;
	int nInterval;
	int nTextCnt;
	int nImgCnt;
	int nAugCnt;
	int nMpCnt;
	long long nMMSId;
  char template_code[50+1]; 
  char real_ptn_id[10+1];
};

class CSenderDbMMSMSG {
public:
	Header header;
	char szQName[32 + 1];
	int nPriority;
	int nCtnId;
	char szCallBack[16 + 1];
	char szDstAddr[16 + 1];
	char szMsgTitle[100 + 1];
	int nCntType;
	char szTxtPath[256 + 1];
	int nRgnRate;
	int nInterval;
	long long nMMSId;
};

class CSenderDbMMSID {
public:
	Header header;
	char szCid[10 + 1];
	long long mmsid;
	int ctnid;
};

class CSenderDbMMSCTNTBL {
public:
	Header header;
	int nCtnId;
	char szCtnName[50 + 1];
	char szCtnMime[50 + 1];
	int nCtnSeq;
	char szCtnSvc[5 + 1];
};

//??????? ????T ???? ?????? ??? 20150910
class CSenderDbMMSRPTTBL {
public:
	Header header;
	long long nMMSId;
	char szDstAddr[16 + 1];
	char szCallBack[16 + 1];
	int res_code;
	char res_text[200];
};

//????? ??? 20151103
class CSenderDbMMSMSG_TALK {
public:
	Header header;
	char szQName[32 + 1];
	int nPriority;
	char szSenderKey[40 + 1];
	char szAppUserId[20 + 1];
	char szDstAddr[16 + 1];
	char szTmplCd[30 + 1];
	char szBtName[50 + 1];
	char szBtUrl[1000 + 1];
	char szButton[4000 + 1];
	char szMsgBody[2000 + 1];
	char szPartnerKey[40 + 1];
	char szResMethod[8 + 1];
	char szTimeout[5 + 1];
	long long nMMSId;
	char szCID[10 + 1];
	char szPtnSn[32 + 1];
	int nmPID;
	char szCharset[15 + 1];
	char szTitle[50 + 1];
	char szReserved[4000];
};

//SEND ERROR ?? ????T ???? ?????? ??? 20160818
class CSenderDbMMSRPTQUE {
public:
	Header header;
	char szCid[10 + 1];
	char szPtnSn[32 + 1];
	char szDstAddr[16 + 1];
	int res_code;
	long long nMMSId;
	char res_text[200];
	int nTelcoId;
	int nType;
};

#define SIZE_PTNSN (32+1)
#define MAXIMUN_LENGTH_OF_CID 40
#define MAXIMUN_COUNT_OF_CID 30
class CSenderDBRerequestReport {
public:
	Header header; // need for senderAtalkPool.cpp
	int cidCount;
	char ptnsn[SIZE_PTNSN];
	//char** cid;
	char cid[MAXIMUN_COUNT_OF_CID][MAXIMUN_LENGTH_OF_CID];
};

class NVRSendMessage{
public:
	Header header; // need for senderAtalkPool.cpp
	/* common */
	char cid[LENGTH_CID];
	char ptn_sn[LENGTH_PTN_SN];
	int priority;

	/* table */
	char callback[LENGTH_CALL_BACK];
	char msg_title[LENGTH_MESSAGE_TITLE];
	char resv_data[LENGTH_RESV_DATA];
	int msg_type;
	int ctn_id;
	int ctn_type;
	int rgn_rate;
	int interval;
	int text_cnt;
	int img_cnt;
	int aug_cnt;
	int mp_cnt;
	char real_ptn_id[10+1];

	/* queue */
	int q_no;
	char receiver[16];
	char partner_key[100];
	char user_name[100];
	char user_access_token[100];
	char template_code[50];
	char template_params[4000+1];
	char message[4000];
	char attachments[4000+1];
	char reserved[4000+1];

	/* output */
	long long mms_id;

	NVRSendMessage(){
		memset(this, 0x00, sizeof(NVRSendMessage));
	}
};

#endif
