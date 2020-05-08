#include "sender_nvr_db.h"
#include "Encrypt.h"
#include "ksbase64.h"
#include <sys/time.h>
//#include <time.h>
static CMMSPacketSend mmsPacketSend;
static int S_PROCESS_NO;

static int proc_id;
int nmPID;

int sendAck(CKSSocket& hRemoteSock,
			string key,
            string code,
            string desc)
{
	int ret=0;

	string strPacket;
	strPacket = "";
	strPacket.reserve(0);

	/* old
	strPacket  = "BEGIN ACK\r\nKEY:" + key + "\r\nCODE:" ;
	strPacket += szCode;
	strPacket += "\r\nDESC:" + strDesc + "\r\nEND\r\n";
	*/
	/* new */
	strPacket  = "BEGIN ACK\r\nKEY:" + key + "\r\nCODE:" + code +
               "\r\nDESC:" + desc + "\r\nEND\r\n";

	ret = hRemoteSock.send((char*)strPacket.c_str(), strPacket.length());
	
	logPrintS(LOG, "[INF] send ack key[%s]code[%s]strDesc[%s]",
    	key.c_str(), code.c_str(), desc.c_str());

	return ret;
}

int sendPong(CKSSocket& hRemoteSock)
{
	string strPacket;
	//string strKey;
	//CMMSPacketBase packetBase;
	int ret;
	
	//packetBase.findValue((char*)hRemoteSock.getMsg(),"KEY",strKey);

	//strPacket = "BEGIN PONG\r\nKEY:" + strKey + "\r\nEND\r\n";
	strPacket = "BEGIN PONG\r\nKEY:1234\r\nEND\r\n";

	ret = hRemoteSock.send((char*)strPacket.c_str(), strPacket.length());
	if (ret != strPacket.length()) {
		logPrintS(MON, "[ERR] socket ack send failed sendSize/packetSize[%d/%d]",
			ret,strPacket.length());
		return ret;
	}
  
	fflush(stdout);
	return 0;
}

int recvLink(CKSSocket& hRemoteSock, char* buff)
{
	int ret;

	TypeMsgDataAck *pLinkAck = (TypeMsgDataAck *)buff;
	memset(pLinkAck->header.msgType, 0x00, sizeof(pLinkAck->header.msgType));
	strcpy(pLinkAck->header.msgType,"8");

	ret = hRemoteSock.send(buff,sizeof(TypeMsgDataAck));
	if (ret != sizeof(TypeMsgDataAck)) {
		logPrintS(MON,"[%s()][ERR] socket link ack send failed - errno[%s] sendSize/packetSize[%d/%d]",
				__func__, strerror(errno), ret, sizeof(TypeMsgDataAck));
		return -1;
	}
	time(&SLastTLink);

	return 0;
}

void logPrintS(int type, const char *format, ...)
{
	va_list args;
	char logMsg[SOCKET_BUFF];
	char tmpMsg[SOCKET_BUFF];

	va_start(args, format);
	vsprintf(tmpMsg, format, args);
	va_end(args);

	sprintf(logMsg, "[S][%s] %s", szSenderID,tmpMsg);
	if (type==1) {
		_logPrint(_DATALOG,logMsg);
	} else {
		_monPrint(_MONILOG,logMsg);
	}
}

int configParse(char* file)
{
	Q_Entry *pEntry;
	int  i;
	int  nRetFlag = TRUE;
	char *pszTmp;
	CKSConfig conf;

	if ((pEntry = conf.qfDecoder(file)) == NULL) {
		printf("WARNING: Configuration file(%s) not found.\n", file);
		return -1;
	}

	/* Get configure file */
	conf.strncpy2(gConf.logonDBName, conf.FetchEntry("domain.logondb"), 64);
	conf.strncpy2(gConf.monitorName, conf.FetchEntry("domain.monitor"), 64);
	conf.strncpy2(gConf.domainPath,  conf.FetchEntry("domain.self"), 64);
	conf.strncpy2(gConf.ContentPath, conf.FetchEntry("path.mmscontent"), 64);
	conf.strncpy2(gConf.dbuid,       conf.FetchEntry("db.uid"), 64);
	conf.strncpy2(gConf.dbdsn,       conf.FetchEntry("db.dsn"), 64);

	gConf.socketLinkTimeOut = conf.FetchEntryInt("socket.linktimeout");
	gConf.dbRequestTimeOut =  conf.FetchEntryInt("db.requesttimeout");
	gConf.dbMmsIdHeader =     conf.FetchEntryInt("db.mmsidhead");

	/* Error treatment */
	if(gConf.logonDBName == NULL) strcpy(gConf.logonDBName, "");
	if(gConf.monitorName == NULL) strcpy(gConf.monitorName, "");
	if(gConf.domainPath == NULL)  strcpy(gConf.domainPath, "");
	if(gConf.ContentPath == NULL) strcpy(gConf.ContentPath, "");
	if(gConf.dbuid == NULL)       strcpy(gConf.dbuid, "");
	if(gConf.dbdsn == NULL)       strcpy(gConf.dbuid, "");

	if(gConf.socketLinkTimeOut <= 1) gConf.socketLinkTimeOut = 2;
	if(gConf.dbRequestTimeOut <= 0)  gConf.dbRequestTimeOut = 1;
	if(gConf.dbMmsIdHeader <= 0)     gConf.dbMmsIdHeader = 0;
	
	return 0;
}

void viewPackSender(char *a, int n)
{
	int i;
	char logMsg[VIEWPACK_MAX_SIZE];
	char strtmp[VIEWPACK_MAX_SIZE];
	
	memset(logMsg,0x00, sizeof logMsg);
	memset(strtmp,0x00, sizeof strtmp);
	
	for (i = 0; i < n; i++) {
		if (a[i] == 0x00) {
			strtmp[i] = '.';
		} else {
			memcpy(strtmp + i, a + i,1);
		}
	}
	
	sprintf(logMsg, "info:[%s]", strtmp);
	_monPrint(_MONILOG, logMsg);
	
	return ;
}

int getTelcoId(int imgCnt, char* szTelco, int nColorYN)
{
	char* p;
	int telcoArray[4];
	int i = 0;
	
	memset(telcoArray,0x00,sizeof(telcoArray));

	p = strtok(szTelco,"|");
	
	if( p == NULL )
	{
		return 1;
	}

	telcoArray[i++] = atoi(p);

	while(p = strtok(NULL,"|") )
	{
		telcoArray[i++]= atoi(p);
		if( i >= 4 )
		{
			break;
		}
	}

	//szTelco �ٽ� ����.���� ����.2012.12.10.
	sprintf(szTelco, "%d|%d|%d|%d", telcoArray[0], telcoArray[1], telcoArray[2], telcoArray[3]);
	return telcoArray[3];
}

int getTelcoId(int imgCnt, char* szTelco, char *szQType)
{
	char* p;
	int telcoArray[6];
	int i = 0;
		
	memset(telcoArray,0x00,sizeof(telcoArray));

	p = strtok(szTelco,"|");
	
	if( p == NULL )
	{
		return 1;
	}
	telcoArray[i++] = atoi(p);

	while(p = strtok(NULL,"|") )
	{
		telcoArray[i++]= atoi(p);
		if( i >= 6 )
		{
			break;
		}
	}
	
	sprintf(szTelco, "%d|%d|%d|%d|%d|%d", 
			telcoArray[0], telcoArray[1], telcoArray[2], telcoArray[3], telcoArray[4], telcoArray[5]);

	if(strncmp(szQType, "type_real", 9) == 0) {
		return telcoArray[3];
	} else if(strncmp(szQType, "type_bt", 7) == 0) {
		return telcoArray[5];
	} else {
		return telcoArray[3];
	}
}

void writeLogMMSData(CMMSPacketSend& mmsPacketSend,long long mmsid, int ctnid)
{
	logPrintS(1, "[%s()][INF] send message mmsid[%lld]ctnid[%d]key[%s]extend[%s]"\
			"subject[%s]dst[]call[%s]",
			__func__, mmsid, ctnid, mmsPacketSend.getKeyValue(),
			mmsPacketSend.getExtendValue(), mmsPacketSend.getSubjectValue(),
			mmsPacketSend.getSenderValue());
}


int write_send_table_and_enqueue(NVRSendMessage *nvr_send_message, int priority) {
	int rst = -1;
	
	rst = g_oracle.send_nvr_message(nvr_send_message);
	if(0 > rst) {
		// error
	}
	
	return rst;
}

/// main parameters
/// 1 : sockfd
/// 2 : pipe
/// 3 : version
/// 4 : conf file
int main(int argc,char* argv[]) {
	int   sockfd;
	int   fd;
	int   ret;
	char  buff[SOCKET_BUFF];
	char* p;
	CLogonDbInfo logonDbInfo;
	
	sockfd = atoi(argv[1]);
	fd = atoi(argv[2]);
	memset(&logonDbInfo, 0x00, sizeof(logonDbInfo));
	read(fd, (char*)&logonDbInfo, sizeof(logonDbInfo));
	close(fd);
	
	memset(_DATALOG, 0x00, sizeof(_DATALOG));//CCL(_DATALOG);
	memset(_MONILOG, 0x00, sizeof(_MONILOG));//CCL(_MONILOG);
	
	sprintf(_DATALOG, "%s/", logonDbInfo.szLogPath);
	sprintf(_MONILOG, "%s/", logonDbInfo.szLogPath);
	
	memset(szSenderID, 0x00, sizeof(szSenderID));//CCL(szSenderID);
	strcpy(szSenderID, logonDbInfo.szCID);
	
	nmPID = logonDbInfo.nmPID;
	
	S_PROCESS_NO = getpid();

	p = strtok(logonDbInfo.szLogFilePath, "|");
	if (p) {
		strcat(_MONILOG, p);
	} else {
	  logPrintS(MON, "[ERR] logondbinfo logfilepath failed - get monitor [%s]",
	            logonDbInfo.szLogFilePath);
	  return -1;
	}
	
	p = strtok(NULL, "|");
	if (p) {
		strcat(_DATALOG, p);
	} else {
	  logPrintS(MON, "[ERR] logondbinfo logfilepath failed - get data [%s]",
	            logonDbInfo.szLogFilePath);
	  return -1;
	}
	
	logPrintS(MON, "[INF] filepath - logfile[%s] monitorfile[%s] PID[%d]",
	          _DATALOG, _MONILOG, S_PROCESS_NO);
	logPrintS(MON, "[INF] argv[4][%s]", argv[4]);
		
	ret = configParse(argv[4]);
	if (ret != 0) {
		logPrintS(MON, "[ERR] configParse Failed");
		exit(1);
	}
	
	logPrintS(MON, "[INF] config file - logonDBName [%s]", gConf.logonDBName);

	// NLS_LANG
	//setenv("NLS_LANG", "KOREAN_KOREA.UTF-8", 0);
	setenv("NLS_LANG", "KOREAN_KOREA.UTF8", 1);

	if (g_oracle.connectToOracle(gConf.dbuid, gConf.dbdsn) < 0) {
    logPrintS(MON, "[ERR] connectToOracle Failed");
    return -1;
	}
	
	logPrintS(MON, "[INF] ORACLE CONNECT");
	
	// 20170621 MMSID SEQ USE
	proc_id = g_oracle.selectSEQ();
	if(proc_id == -1)
		proc_id = 9999;
		
	SenderProcess *mSenderProcess = new SenderProcess();

	// sendre Main Process Start 
	mSenderProcess->SenderMain(sockfd, logonDbInfo);
	
	/* End process */
	if (g_oracle.closeFromOracle() < 0) {
		logPrintS(MON, "[ERR] closeFromOracle Failed");
	    return -1;
	}
	logPrintS(MON, "[INF] ORACLE DISCONNECT");
	
	return 0;
}

SenderProcess::SenderProcess() {
	bDayWarnCheck=false;
	bMonWarnCheck=false;
}

void SenderProcess::SenderMain(int sockfd, CLogonDbInfo& logonDbInfo) {
	int ret;
	CLogonUtil util;
	CAdminUtil admin;
	CKSSocket db;
	CProcessInfo processInfo;
	CMonitor monitor;

	memset(&processInfo, 0x00, sizeof(processInfo));
	memset(&gSenderInfo, 0x00, sizeof(gSenderInfo));
	  
	strcpy(processInfo.processName, logonDbInfo.szSenderName);
	get_timestring("%04d%02d%02d%02d%02d%02d", time(NULL), processInfo.startTime);
	
	sprintf(processInfo.szPid,"%d",getpid());
	strcpy(processInfo.logonDBName,gConf.logonDBName);
	
	util.findValueParse(logonDbInfo.szReserve, "mms_tel",    gSenderInfo.szSmsTelcoInfo);
	util.findValueParse(logonDbInfo.szReserve, "mms_yn",     gSenderInfo.szSmsFlag);
	util.findValueParse(logonDbInfo.szReserve, "res_method", gSenderInfo.szResMethod);
	util.findValueParse(logonDbInfo.szReserve, "timeout",    gSenderInfo.szTimeout);
	util.findValueParse(logonDbInfo.szReserve, "q_type",     gSenderInfo.szQType);
	util.findValueParse(logonDbInfo.szReserve, "block_yn",   gSenderInfo.szBlockYN);
	
	util.findValueParse(logonDbInfo.szReserve, "sender_key",  gSenderInfo.szSenderKey);
	
	strcpy(gSenderInfo.szUrlTelcoInfo, "0");
	strcpy(gSenderInfo.szUrlFlag, "0");
	
	logPrintS(MON, "[INF] send process sender main start " \
	    "sockfd[%d] CID[%s] processInfo.startTime[%s] pid[%s] "\
	    "logonDbInfo.Reserve[%s] senderInfo[%s] smsFlag[%s] "\
	    "SenderKey[%s]BlockYN[%s]",
	    sockfd, logonDbInfo.szCID, processInfo.startTime, processInfo.szPid, 
	    logonDbInfo.szReserve, gSenderInfo.szSmsTelcoInfo, gSenderInfo.szSmsFlag,
	    gSenderInfo.szSenderKey, gSenderInfo.szBlockYN);
	
	util.displayLogonDbInfo(logonDbInfo,_MONILOG);

	int recvLen;
   
	CKSSocket hRemoteSock;
	hRemoteSock.attach(sockfd);
   
	ret = admin.createDomainID(logonDbInfo.szCID,logonDbInfo.classify,gConf.domainPath);
	if (ret != 0) {
		logPrintS(MON, "[ERR] socket_domain create failed - "
			"CID[%s]classify[%c]domain_path[%s]",
	        logonDbInfo.szCID, logonDbInfo.classify, gConf.domainPath);
		goto SenderEND;
	}
	
	monitor.Init("logon7", "sender", processInfo.processName, logonDbInfo.szCID, logonDbInfo.nmPID, logonDbInfo.szIP);
	time(&SLastTLink);
	
	nCurAccCnt = 0;

	memset(szLimitTime, 0x00, sizeof(szLimitTime));
	get_timestring("%04d%02d%02d%02d%02d%02d", time(NULL), szLimitTime);	// ���� ��¥ ���ϱ�
	memset(szLimitCurTime, 0x00, sizeof(szLimitCurTime));
    
	while (bSActive) {
		ret = hRemoteSock.recvAllMsg(0);
		if (ret < 0) {
			logPrintS(MON, "[%s()][ERR] socket read msg failed - [%s][%s]",
					__func__, hRemoteSock.getErrMsg(), strerror(errno));
			goto SenderEND;
		}
		      
		if (ret == 0) {
			//wait_a_moment(logonDbInfo.nmCNT);
			ret = admin.checkPacket(processInfo, logonDbInfo, sum);// check admin packet
			if (ret < 0) {
				logPrintS(MON, "[%s()][ERR] socket_domain packet check failed - CID[%s]ErrMsg[%s]",
						__func__, logonDbInfo.szCID, admin.getErrMsg());
				goto SenderEND;
			}
	
			switch (ret) {
				case 3: // end
					bSActive = false;
					continue;
				case 5: // info
					memset(gSenderInfo.szSmsTelcoInfo, 0x00, sizeof(gSenderInfo.szSmsTelcoInfo)); 
					memset(gSenderInfo.szSmsFlag,      0x00, sizeof(gSenderInfo.szSmsFlag)); 
					memset(gSenderInfo.szResMethod,    0x00, sizeof(gSenderInfo.szResMethod));
					memset(gSenderInfo.szTimeout,      0x00, sizeof(gSenderInfo.szTimeout));
					memset(gSenderInfo.szQType,        0x00, sizeof(gSenderInfo.szQType));
					memset(gSenderInfo.szBlockYN,      0x00, sizeof(gSenderInfo.szBlockYN));

					util.findValueParse(logonDbInfo.szReserve, "mms_tel",    gSenderInfo.szSmsTelcoInfo); 
					util.findValueParse(logonDbInfo.szReserve, "mms_yn"	,    gSenderInfo.szSmsFlag);
					util.findValueParse(logonDbInfo.szReserve, "res_method", gSenderInfo.szResMethod);
					util.findValueParse(logonDbInfo.szReserve, "timeout",    gSenderInfo.szTimeout);
					util.findValueParse(logonDbInfo.szReserve, "q_type",     gSenderInfo.szQType);
					util.findValueParse(logonDbInfo.szReserve, "block_yn",   gSenderInfo.szBlockYN);

					nCurAccCnt = 0;

					logPrintS(LOG, "[%s()][INF] gSenderInfo.szResMethod[%s]", __func__, gSenderInfo.szResMethod); // ????
					logPrintS(LOG, "[%s()][INF] info modify ok", __func__);
					break;
				default:
					break;
			}
	
			time(&SThisT);	
			ret = (int)difftime(SThisT,monLastT);
			if (ret > 30) {
				monitor.setDataSum(sum);
				monitor.setCurDate();
				monitor.send(gConf.monitorName);
				time(&monLastT);
				sum=0;
			}
			continue; // no data
		}
		
		ret = classifyS(monitor, processInfo, logonDbInfo, db, hRemoteSock);
		if (ret < 0) {
			logPrintS(MON, "[%s()][ERR] classifyS Error ret [%d]",__func__, ret);
			goto SenderEND;
		}
	} // while
	
			
SenderEND:
	logPrintS(LOG,"[%s()][INF] socket END sockfd[%d]CID[%s]",
		__func__, hRemoteSock.getSockfd(), logonDbInfo.szCID);
	hRemoteSock.close();
	
	return;
}

int SenderProcess::classifyS(CMonitor& monitor,
	                         CProcessInfo& processInfo,
	                         CLogonDbInfo& logonDbInfo,
	                         CKSSocket& db,
	                         CKSSocket& hRemoteSock) {
	int ret = -1;

	CSenderDbMMSID senderDbMMSID;
	
	string raw_message = "";
	raw_message = hRemoteSock.getMsg();

	if(0 == strncmp(raw_message.c_str(), "BEGIN PING\r\n", 12)){
		// ping
		ret = sendPong(hRemoteSock);
		monitor.setLinkTime();
	} else if(0 == strncmp(raw_message.c_str(), "BEGIN SEND\r\n", 12)) {
		char *start_pos = (char *)strstr(raw_message.c_str(), "\r\n");
		start_pos += 2;

		// get JSON formatted message
		Json::Reader reader;
		Json::Value message;
		const bool parsing_flag = reader.parse(start_pos, message);
	
		if(!parsing_flag) {
			// fail to parse
			ret = -1;
			logPrintS(MON, "[ERR] parsing error");

			char key[100];
			memset(key, 0x00, sizeof(100));
			
			/* find key; serial, ptn_sn */
			string str_key = "KEY:";
			const char *key_st = strstr(raw_message.c_str(), str_key.c_str());
			const char *key_sp = strstr(key_st, "\r\n");
			
			int str_key_size = strlen(str_key.c_str());
			memcpy(key, key_st+str_key_size, key_sp - (key_st + str_key_size));
#ifdef DEBUG
			logPrintS(LOG, "[DEB] VC(get key): %s", key);
#endif
			sendAck(hRemoteSock, key, "201", "Invalid JSON format");
		} else {
			logPrintS(LOG, "[INF] request to send message");
			// send message
			NVRSendMessage *nvr_send_message = new NVRSendMessage();
			/* parsing JSON from agent */
			ret = get_data_fields_from_json_v1(nvr_send_message, &message);
			if(0 > ret) {
				// error
				logPrintS(MON, "[ERR] parsing JSON failed");
				sendAck(hRemoteSock, nvr_send_message->ptn_sn, "211", "JSON parsing error");
				
				return -1;
			}

			logPrintS(LOG, "[INF] JSON parsing succ; ptn_sn: %s", nvr_send_message->ptn_sn);

			/* DB operation */
			ret = g_oracle.send_nvr_message(nvr_send_message);
			if(0 > ret) {
				// DB error
				logPrintS(MON, "[ERR] DB insert failed; code: %d", ret);
				sendAck(hRemoteSock, nvr_send_message->ptn_sn, "301", "DB insert failed");

				return -1;
			}

			logPrintS(LOG, "[INF] DB operation succ; ptn_sn: %s, mms_id: %lld", nvr_send_message->ptn_sn, nvr_send_message->mms_id);
			
			sendAck(hRemoteSock, nvr_send_message->ptn_sn, "100", "succ");

			logPrintS(LOG, "[INF] success to send request; ptn_sn: %s, mms_id: %lld", nvr_send_message->ptn_sn, nvr_send_message->mms_id);
		}
	} else {
		// invalid type
		ret = -1;
		logPrintS(MON, "[ERR] invalid message type;\r\nraw msg: %.800s", raw_message.c_str());
	}

	return ret;
}								

int SenderProcess::get_data_fields_from_json_v1(NVRSendMessage *data, 
                                                Json::Value *raw){
#ifdef DEBUG
	logPrintS(LOG, "[DEB] call %s()", __func__);
#endif
	int rst = -1;
	
	Json::Value const *msg = raw;
		
	map<string, string> json_fields;

	for(Json::ValueConstIterator it = msg->begin(); it != msg->end(); ++it) {
		// treat attachments
		if((*msg)[it.name()].isArray() || (*msg)[it.name()].isObject()) {
#ifdef DEBUG
		logPrintS(LOG, "[DEB] get array field: %.800s", it.name().c_str());
#endif
			if(strstr(it.name().c_str(), "attachments")) {
			  	Json::FastWriter writer;
			  	const string buf_attachment = writer.write((*msg)["attachments"]);
			  	
				strncpy(data->attachments,     buf_attachment.c_str(),  sizeof(data->attachments));
			}
			continue;
		}
		
		json_fields[it.name()] = msg->get(it.name(), "").asString();

#ifdef DEBUG
		logPrintS(LOG, "[DEB] VC; <%s: %s>", it.name().c_str(), json_fields[it.name()].c_str());
#endif
	} // for(Json iterator)

	/* convert base64 to string */
	if(0 == strncmp(json_fields["encoding"].c_str(), " aes_base64", 10) || 
		0 == strncmp(json_fields["encoding"].c_str(), "aes_base64", 10)) {
		// decrypt receive number
		char tmp_receiver[16];
		memset(tmp_receiver, 0x00, sizeof(tmp_receiver));
		decrypt_string(tmp_receiver, json_fields["receiver"].c_str(), sizeof(tmp_receiver));
		// save receiver on buffer
		create_receiver(data->receiver, (const char*)tmp_receiver, json_fields["nation_code"].c_str(), sizeof(data->receiver));
		// decrypt message body
		decrypt_string(data->message, json_fields["message"].c_str(), sizeof(data->message));
		// decrypt template params
		decrypt_string(data->template_params, json_fields["template_params"].c_str(), sizeof(data->template_params));
		// decrypt user name
		decrypt_string(data->user_name, json_fields["user_name"].c_str(), sizeof(data->user_name));
	} else {
		// receiver
		create_receiver(data->receiver, json_fields["receiver"].c_str(), json_fields["nation_code"].c_str(), sizeof(data->receiver));
		// message body (queue)
		strncpy(data->message, json_fields["message"].c_str(), sizeof(data->message)-1);
		// template params
		strncpy(data->template_params, json_fields["template_params"].c_str(), sizeof(data->template_params)-1);
		// user name
		strncpy(data->user_name, json_fields["user_name"].c_str(), sizeof(data->user_name));
	}

#ifdef DEBUG
	logPrintS(LOG, "[DEB] VC, save in buffer;\nreceiver: %s\nmsg: %s\nparams: %s\nattachment: %s", data->receiver, data->message, data->template_params, data->attachments);
#endif

	// copy data
	strncpy(data->ptn_sn, json_fields["key"].c_str(), sizeof(data->ptn_sn));
	if(0 == strlen(json_fields["call_back"].c_str())) {
		strcpy(data->callback, "010");
	} else {
		strncpy(data->callback, json_fields["call_back"].c_str(), sizeof(data->callback));
	}
	strncpy(data->partner_key,       json_fields["partner_key"].c_str(),       sizeof(data->partner_key));
	strncpy(data->template_code,     json_fields["template_code"].c_str(),     sizeof(data->template_code));
	strncpy(data->user_access_token, json_fields["user_access_token"].c_str(), sizeof(data->user_access_token));

	strncpy(data->cid, szSenderID, sizeof(data->cid));
	data->q_no = getTelcoId(0, gSenderInfo.szSmsTelcoInfo, gSenderInfo.szQType);

	rst = 0;
	return rst;
}

int SenderProcess::get_data_fields_from_json(NVRSendMessage *data, 
                                             Json::Value *raw){
	int rst = -1;
	
	Json::Value const *msg = raw;

#ifdef DEBUG
	logPrintS(LOG, "[DEB] start JSON parsing");
#endif

	const string buf_key         = msg->get("key", "").asString();
	const string buf_encoding    = msg->get("encoding", "").asString();
	const string buf_receiver    = msg->get("receiver", "").asString();
	const string buf_user_name   = msg->get("user_name", "").asString();
	const string buf_user_access_token = msg->get("user_access_token", "").asString();
	const string buf_p_key       = msg->get("partner_key", "").asString();
	const string buf_tmlp_cd     = msg->get("template_code", "").asString();
	const string buf_tmlp_params = msg->get("template_params", "").asString();
	const string buf_msg         = msg->get("message", "").asString();
	const string buf_extend      = msg->get("extend", "").asString();
	const string buf_n_cd        = msg->get("nation_code", "").asString();

  	Json::FastWriter writer;
  	const string buf_attachment = writer.write((*msg)["attachments"]);

	const string buf_callback = msg->get("call_back", "").asString();
	
#ifdef DEBUG
	logPrintS(LOG, "[DEB] get data from JSON fields");
#endif

	/* convert base64 to string */
	if(0 == strncmp(buf_encoding.c_str(), " aes_base64", 10) || 
		0 == strncmp(buf_encoding.c_str(), "aes_base64", 10)) {
#ifdef DEBUG
		logPrintS(LOG, "[DEB] Decryption");
#endif
		// decrypt receive number
		char tmp_receiver[16];
		memset(tmp_receiver, 0x00, sizeof(tmp_receiver));
		decrypt_string(tmp_receiver, buf_receiver.c_str(), sizeof(tmp_receiver));

		if(0 < strlen(tmp_receiver)) {
			if(0 < strlen(buf_n_cd.c_str())) {
				snprintf(data->receiver, sizeof(data->receiver), "%s%s", buf_n_cd.c_str(), string(tmp_receiver).substr(1).c_str());
			} else {
				snprintf(data->receiver, sizeof(data->receiver), "82%s", string(tmp_receiver).substr(1).c_str());
			}
		} else {
			strcpy(data->receiver, "821000000000");
		}
		// decrypt message body
		decrypt_string(data->message, buf_msg.c_str(), sizeof(data->message));
		// decrypt template params
		decrypt_string(data->template_params, buf_tmlp_params.c_str(), sizeof(data->template_params));
		
	} else {
		if(0 < strlen(buf_receiver.c_str())) {
			if(0 < strlen(buf_n_cd.c_str())) {
				snprintf(data->receiver, sizeof(data->receiver), "%s%s", buf_n_cd.c_str(), buf_receiver.substr(1).c_str());
			} else {
				snprintf(data->receiver, sizeof(data->receiver), "82%s", buf_receiver.substr(1).c_str());
			}
		} else {
			strcpy(data->receiver, "821000000000");
		}

		// message body (queue)
		strncpy(data->message, buf_msg.c_str(), sizeof(data->message)-1);
		
		// template params
		strncpy(data->template_params, buf_tmlp_params.c_str(), sizeof(data->template_params)-1);
	}

#ifdef DEBUG
	logPrintS(LOG, "[DEB] preprocessing");
#endif
	// validation check

	// copy data
	strncpy(data->ptn_sn,          buf_key.c_str(),         sizeof(data->ptn_sn));
	if(0 == strlen(data->callback)) {
		strcpy(data->callback, "010");
	} else {
		strncpy(data->callback,        buf_callback.c_str(),    sizeof(data->callback));
	}
	strncpy(data->partner_key,     buf_p_key.c_str(),       sizeof(data->partner_key));
	strncpy(data->template_code,   buf_tmlp_cd.c_str(),     sizeof(data->template_code));
	//strncpy(data->extend,          buf_extend.c_str(),      sizeof(data->extend));
	strncpy(data->attachments,     buf_attachment.c_str(),  sizeof(data->attachments));

	strncpy(data->cid, szSenderID, sizeof(data->cid));
	data->q_no = getTelcoId(0, gSenderInfo.szSmsTelcoInfo, gSenderInfo.szQType);

#ifdef DEBUG
	logPrintS(LOG, "[DEB] End of parsing JSON");
#endif

	rst = 0;
	
	return rst;
}

void SenderProcess::decrypt_string(char* desc, const char* source, int size) {
	if(0 == strlen(source)) {
		strcpy(desc, "");
		return;
	}

	Encrypt en;
	en.set_key();
	int n;
	unsigned char *decoded = (unsigned char*)__base64_decode((unsigned char *)source,
			strlen(source), &n);
	//en.decrypt(decoded, decoded, strlen((char*)decoded));
	en.decrypt(decoded, decoded, n);

	strncpy(desc, (const char*)decoded, size);

#ifdef DEBUG
	logPrintS(LOG, "[DEB] VC(decrypt); desc size: %d, desc: %.850s", size, desc);
#endif

	free(decoded);
}

void SenderProcess::create_receiver(char *desc, const char *receiver, const char *nation_code, int size) {
	if(0 < strlen(receiver)) {
		if(0 < strlen(nation_code)) {
			snprintf(desc, size, "%s%s", receiver, receiver+1);
		} else {
			snprintf(desc, size, "82%s", receiver+1);
		}
	} else {
		strncpy(desc, "821000000000", size);
	}
}

int SenderProcess::SenderLimit(CLogonDbInfo& logonDbInfo)
{
	int ret;
	char szTemp[256];
	
	//* < brief �߼� ���� üũ
	if (atoi(logonDbInfo.szLimitType) != 0)
	{
		memset(szTemp	,0x00	,sizeof(szTemp));
	
		get_timestring("%04d%02d%02d%02d%02d%02d", time(NULL), szLimitCurTime);	// ���� ��¥ ���ϱ�
		
		if (strcmp(szLimitTime,"") == 0)
		{
			strcpy(szLimitTime,szLimitCurTime);	// ����� �� ���ϱ�
		}

		ret = LimitCheck(logonDbInfo);
		//ī��Ʈ ��꿡 ���� ���� ���� �� �˸� ��� ����
		// logPrintS(1,"ret(%d)",ret);
		switch (ret)
		{
			case 9 : // �� ���濡 ���� ���� ī��Ʈ �ʱ�ȭ �� ���ν��� ����
			case 10 : // �� ���濡 ���� ���� ī��Ʈ �ʱ�ȭ �� ���ν��� ����
				if (ret == 9)
					logPrintS(1,"[INF]day change total count reset and run");
				if (ret == 10)
					logPrintS(1,"[INF]month change total count reset and run");
	
				//�߼� ���� ���� �ʱ�ȭ
				bDayWarnCheck = false;
				bMonWarnCheck = false;
				
				if (ret == 9)
					logonDbInfo.nMonAccCnt += logonDbInfo.nCurAccCnt;	//�� ���� �� �� ī��Ʈ�� ����
				if (ret == 10)
					logonDbInfo.nMonAccCnt = 0;	//�� ����� �� ī��Ʈ�� �ʱ�ȭ
					
				logonDbInfo.nDayAccCnt = 0;	//��,�� ����� �� ī��Ʈ�� �׻� �ʱ�ȭ
				nCurAccCnt = 0;	//��,�� ����� ���� ���� ī��Ʈ�� �׻� �ʱ�ȭ
				memset(szLimitTime,(char)NULL,sizeof(char)*16);
				break;
			default :
				break;
		}
				
		switch (ret)
		{
			case 0 : // ���� ����
				break;
			case 1 : // �� ���� ����
				logPrintS(1,"[INF] daily limit [%d]"	,logonDbInfo.nDayLimitCnt);
				return -1;
			case 2 : // �� ���� ����
				logPrintS(1,"[INF] monthly limit [%d]"	,logonDbInfo.nMonLimitCnt);
				return -1;
			case 3 : // �� ���� ����	+ �˶�
				sprintf(szTemp,"[ERR] daily limit - CID[%s] cnt[%d] Process close.", logonDbInfo.szCID, logonDbInfo.nDayLimitCnt);
				logPrintS(0,"[%s]"	,szTemp);
				
				if ( Alert2Admin("msgbody=%s&type=%d", szTemp, 0) < 0 )
				{
					monitoring("[ERR] alert2admin daily service limit send failed",0,0);
				}
					
				return -1;
			case 4 : // �� ���� ����	+ �˶�
				sprintf(szTemp,"[ERR] monthly limit - CID[%s] cnt[%d] Process close.", logonDbInfo.szCID, logonDbInfo.nMonLimitCnt);
				logPrintS(0,"[%s]",szTemp);
				
				if ( Alert2Admin("msgbody=%s&type=%d", szTemp, 0) < 0 )
				{
					monitoring("[ERR] alert2admin monthly service limit send failed",0,0);
				}
					
				return -1;
			case 5 : // �� �˶�
				sprintf(szTemp,"[INF] daily limit orver - CID[%s] cnt[%d] alert msg send.", logonDbInfo.szCID, logonDbInfo.nDayLimitCnt);
				logPrintS(1,"[%s]",szTemp);
				
				if ( Alert2Admin("msgbody=%s&type=%d", szTemp, 0) < 0 )
				{
					monitoring("[ERR] alert2admin daily service limit send failed",0,0);
				}
					
				break;
			case 6 : // �� �˶�
				sprintf(szTemp,"[INF] monthly limit over - CID[%s] cnt[%d] alert msg send.", logonDbInfo.szCID, logonDbInfo.nMonLimitCnt);
				logPrintS(1,"%s",szTemp);
				
				if ( Alert2Admin("msgbody=%s&type=%d", szTemp, 0) < 0 )
				{
					monitoring("[ERR] alert2admin monthly service limit send failed",0,0);
				}
					
				break;
			case 7 : // �� �Ӱ�ġ �˶�
				if (!bDayWarnCheck)
				{
					bDayWarnCheck = true;
					sprintf(szTemp,"[INF] daily limit warnning alert - CID[%s] cnt[%d]", logonDbInfo.szCID, logonDbInfo.nDayWarnCnt);
					logPrintS(1,"[%s]",szTemp);
					
					if ( Alert2Admin("msgbody=%s&type=%d", szTemp, 0) < 0 )
					{
						monitoring("[ERR] alert2admin daily limit msg send failed",0,0);
					}
						
				}
				break;
			case 8 : // �� �Ӱ�ġ �˶�
				if (!bMonWarnCheck)
				{
					bMonWarnCheck = true;
					sprintf(szTemp,"[INF] monthly limit warnning alert - CID[%s] cnt[%d]", logonDbInfo.szCID, logonDbInfo.nMonWarnCnt);
					logPrintS(1,"[%s]",szTemp);
					
					if ( Alert2Admin("msgbody=%s&type=%d", szTemp, 0) < 0 )
					{
						monitoring("[ERR] alert2admin monthly limit msg send failed",0,0);
					}
						
				}
				break;
			default :
				break;
		}
	}
	
	return 0;
}


//* < brief �߼� ���� üũ
int SenderProcess::LimitCheck(CLogonDbInfo& logonDbInfo)
{
/* return value
	1 : �� ���� ����
	2 : �� ���� ����
	3 : �� ���� ����	+ �˶�
	4 : �� ���� ����	+ �˶�
	5 : �� �˶�
	6 : �� �˶�
	7 : �� �Ӱ�ġ �˶�
	8 : �� �Ӱ�ġ �˶�
	9 : �� ���濡 ���� ���� ī��Ʈ �ʱ�ȭ
	10 : �� ���濡 ���� ���� ī��Ʈ �ʱ�ȭ
	0 : ���� ����
*/
	bool bDay=false;
	bool bMon=false;
	int  nDayAccCnt 		= logonDbInfo.nDayAccCnt;
	int  nMonAccCnt 		= logonDbInfo.nMonAccCnt;
	int  nDayWarnCnt 		= logonDbInfo.nDayWarnCnt;
	int  nMonWarnCnt 		= logonDbInfo.nMonWarnCnt;
	int  nDayLimitCnt 		= logonDbInfo.nDayLimitCnt;
	int  nMonLimitCnt 		= logonDbInfo.nMonLimitCnt;
	int  nLimitType 		= atoi(logonDbInfo.szLimitType);
	int  nLimitFlag 		= atoi(logonDbInfo.szLimitFlag);

	//logPrintS(1,"szLimitCurTime(%s)szLimitTime(%s)",szLimitCurTime,szLimitTime);
	if (strncmp(szLimitTime	,szLimitCurTime	,8) != 0)
		bDay = true;	//�� ����
		
	if (strncmp(szLimitTime,szLimitCurTime,6) != 0) 
		bMon = true;	//�� ����

	if (bDay)
	{
		if (bMon)
		{
			return 10;	// �� ������ �̷�� ���� ���
		}
		else
		{
			return 9;	// �� ������ �̷�� ���� ���
		}
	}
 //logPrintS(1,"nLimitType(%d),nDayWarnCnt(%d),nCurAccCnt(%d),nDayAccCnt(%d)",nLimitType, nDayWarnCnt, nCurAccCnt,nDayAccCnt);
	//���� ���� üũ
	switch (nLimitType)
	{
		case 0:	//�߼� ���� ���� ����
			return 0;
		case 1:	//��,�� �߼� ����
		case 2:	//�� �߼� ����
		case 3:	// �� �߼� ����
			if (nLimitType == 1 || nLimitType == 2)
			{
				//�� �Ӱ�ġ üũ (�Ӱ�ġ�� ���� �Ǽ� ����)
				if (((nDayAccCnt + nCurAccCnt) > nDayWarnCnt) && ((nDayAccCnt + nCurAccCnt) < nDayLimitCnt))
				{
					logPrintS(1,"[INF] daily limit - limit over [%d/%d]", nDayWarnCnt, (nDayAccCnt + nCurAccCnt)-nDayWarnCnt);
					return 7;
				}
				//�� ���� ���� üũ
				if ((nDayAccCnt + nCurAccCnt) > nDayLimitCnt)
				{
					logPrintS(1,"[INF] daily limit - config value [%d]", nDayLimitCnt);
				
					switch (nLimitFlag)
					{
						case 1 :
							return 1;
						case 2 :
							return 3;
						case 3 :
							return 5;
						default :
							return 0;
					}
				}
			}
//logPrintS(1,"nMonWarnCnt(%d),nMonAccCnt(%d),nMonLimitCnt(%d)",nMonWarnCnt, nMonAccCnt+nCurAccCnt+nDayAccCnt, nMonLimitCnt);

			if (nLimitType == 1 || nLimitType == 3)
			{
				//�� �Ӱ�ġ üũ (�Ӱ�ġ�� ���� �Ǽ� ����)
				//20180829 �� �Ӱ�ġ üũ ���� nDayAccCnt �߰�
				//if (((nMonAccCnt + nCurAccCnt) > nMonWarnCnt) && ((nMonAccCnt + nCurAccCnt) < nMonLimitCnt))
				if (((nMonAccCnt + nCurAccCnt + nDayAccCnt) > nMonWarnCnt) && ((nMonAccCnt + nCurAccCnt + nDayAccCnt) < nMonLimitCnt))
				{
					logPrintS(1,"[INF] monthly limit - limit over [%d/%d]", nMonWarnCnt, (nMonAccCnt + nCurAccCnt + nDayAccCnt)-nMonWarnCnt);
					return 8;
				}
				//�� ���� ���� üũ
				//	if ((nMonAccCnt + nCurAccCnt) > nMonLimitCnt)
				if ((nMonAccCnt + nCurAccCnt + nDayAccCnt) > nMonLimitCnt)
				{
					logPrintS(1,"[INF] monthly limit - config value [%d]", nMonLimitCnt);
					switch (nLimitFlag)
					{
						case 1 :
							return 2;
						case 2 :
							return 4;
						case 3 :
							return 6;
						default :
							return 0;
					}
				}
			}
		default:
			return 0;
		break;
	}
	return 0;
}


/* End of the File */
