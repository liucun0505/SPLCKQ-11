#pragma once
#include "DLT698_45.h"
#define  DATANUMB_LINE		1	//数据行数
#define  DATANUMB_ROW		5	//数据列数
#define  DATANUMB_FREE		5	//冻结数据的数据个数
#define  DATANUMB_RATE		21	//费率个数
#define  DATANUMB_LIST		5	//读取N个对象属性
#define  PASSWORD_LEN		10	//密码长度
#define  MIWEN_LEN			10	//密文长度



typedef struct 
{
	INT8U nNumb;
}DAR;
typedef struct 
{
	INT8U * DI;
	INT8U * SubjoinData;
}S_ID;
typedef struct 
{
	S_ID pSID;
	INT8U * MacData;
}SID_MAC;
typedef union
{
	INT32U doublelong;
	INT32U udoublelong;
	INT16U long16;
	INT16U ulong;
	INT8U integer;//15
	INT8U unsign;//17
	INT8U * Datetime_S;
	INT8U * OctetStringbuf;//9
	SID_MAC pSID_MAC;
}STRUCTURE;
typedef struct
{
	INT8U nTimes;
	INT8U nStructChoose[DATANUMB_RATE + 1];
	STRUCTURE pStructrea[DATANUMB_RATE + 1];
}STRUCTUREA;

typedef union
{
	INT8U * DatetimeBCD;
	INT32U doublelong;
	INT16U long16;
	INT32U udoublelong;
	INT8U unsign;
	INT16U ulong;
	INT8U integer;//15
	STRUCTUREA pStructureA;
}ARRY;

typedef struct
{
	INT8U nTimes;
	INT8U nARRYChoose[DATANUMB_RATE + 1];
	ARRY pArry[DATANUMB_RATE + 1];
}ARRYA;

typedef struct
{
	INT8U buflen;
	INT8U * bufAddr;
}TSA;
typedef struct  sProcess_DataNodeType
{
	struct sProcess_DataNodeType *s_nextlink;
	INT32U      s_workStartTime; 
	INT32U      s_MaxDlyTime; 
	INT8U       s_CuReCnt;
	INT8U       s_MaxReCnt;
} ;
typedef union Data
{
	struct Arry
	{
		INT8U nTimes;
		INT8U * nARRYChoose;
		Data * pArry;
	}pArryA;

	struct Structurea
	{
		INT8U nTimes;
		INT8U * nStructChoose;
		Data * pStructrea;
	}pStructureA;
	bool boolean;//3
	INT8U * BitStringbuf;//4
	INT32U doublelong;//5
	INT32U udoublelong;//6
	INT8U * OctetStringbuf;//9
	INT8U * VisibleStringbuf;//10
	INT8U integer;//15
	INT16U long16;//16
	INT8U unsign;//17
	INT16U ulong;//18
	//INT64U long64;//20
	//INT64U ulong64;//21
	INT8U uenum;//22
	INT8U * Datetime;//25
	INT8U * Date;//26
	INT8U * Time;//27
	INT8U * Datetime_S;//28
	TSA pTSA;//85
	SID_MAC pSID_MAC;//94
} ;
//
//typedef union
//{
//	ARRYA pArryA; //1
//	STRUCTUREA pStructureA;//2
//	bool boolean;//3
//	INT8U * BitStringbuf;//4
//	INT32U doublelong;//5
//	INT32U udoublelong;//6
//	INT8U * OctetStringbuf;//9
//	INT8U * VisibleStringbuf;//10
//	INT8U integer;//15
//	INT16U long16;//16
//	INT8U unsign;//17
//	INT16U ulong;//18
//	//INT64U long64;//20
//	//INT64U ulong64;//21
//	INT8U uenum;//22
//	INT8U * Datetime;//25
//	INT8U * Date;//26
//	INT8U * Time;//27
//	INT8U * Datetime_S;//28
//	TSA pTSA;//85
//}Data;

typedef struct 
{
	INT16U OID;
	INT8U PID;
	INT8U DENT;
}OAD;

typedef struct 
{
	INT16U OID;
	INT8U AID;
	INT8U DENT;
}OMD;


typedef struct 
{
}RN;

typedef struct 
{
}RN_MAC;

typedef union
{
	INT8U nChooseNumb;
	SID_MAC pSID_MAC;
	RN pRN;
	RN_MAC pRN_MAC;
	S_ID pSID;
}ESAM_MSG;

typedef struct 
{
	INT8U * pRasswordSecurityBuf;//1

	INT8U * pSymmetrySecurityM1Buf;//2
	INT8U * pSymmetrySecurityCQ1Buf;

	INT8U * pSignatureSecurityM2Buf;//3
	INT8U * pSignatureSecurityCQ2Buf;

}ConnectMechanismInfo;

typedef struct 
{
	INT8U nPIID;
	INT16U nTVnumb;
	INT8U nProtocolConformance[8];
	INT8U nFunctionConformance[16];
	INT16U nClientSendMax;
	INT16U nClientRecvMax;
	INT8U nClientFramMax;
	INT16U nClientAPDUMax;
	INT32U nMaxTime;
	INT8U nChooseInfo;
	ConnectMechanismInfo sConnectMechanismInfo;
}stuConnectRequest;

typedef struct 
{
	OAD pOAD;
	INT8U nDataChoose;
	Data OADData;
}Selector1;
typedef struct 
{
	INT32U OAD;
	INT8U nDataBeginChoose;
	Data OADDataBegin;
	INT8U nDataEndChoose;
	Data OADDataEnd;
	INT8U nDataJGChoose;
	Data OADDataJG;
}Selector2;



typedef struct
{
	INT8U nTSATimes;
	TSA  pTSA;
}MS;
typedef struct 
{
	INT8U datatimeBCD[7];
	MS pMS;
}Selector5;

typedef struct 
{
	INT8U u8LastTimes;
}Selector9;

typedef union 
{
	Selector1 st1;
	Selector2 st2;
	Selector5 st5;
	Selector9 st9;
}RSDA;

typedef struct 
{
	INT8U nChoose;
	RSDA pRSDA;
}RSD;

typedef struct
{
	OAD sOAD;
	INT8U u8Numb;
	OAD * pOAD;
}ROAD;

typedef union
{
	OAD sOAD;
	ROAD sROAD;
}CSD;

typedef struct 
{
	INT8U u8Choose;
	CSD sCSD;
}RCSDA;
typedef struct 
{
	INT8U u8Numb;
	RCSDA * sRCSDA;
}RCSD;

typedef struct 
{
	INT8U nDataNumb;
	INT8U * pDataChoose;
	Data * pData;
}A_RecordRow;




//typedef struct
//{
//	INT16U OID;
//	INT8U PID;
//	INT8U DENT;
//}OMD;
//typedef struct 
//{
//	OAD pOAD;
//	INT8U nTimes;
//	OAD arryOAD[DATANUMB_FREE];
//}ROAD;
//typedef struct 
//{
//	OAD pOAD;
//	INT8U nDataChoose;
//	Data OADData;
//}Selector1;
//typedef struct 
//{
//	INT32U OAD;
//	INT8U nDataBeginChoose;
//	Data OADDataBegin;
//	INT8U nDataEndChoose;
//	Data OADDataEnd;
//	INT8U nDataJGChoose;
//	Data OADDataJG;
//}Selector2;
//
//
//
//typedef struct
//{
//	INT8U nTSATimes;
//	TSA  pTSA;
//}MS;
//typedef struct 
//{
//	INT8U datatimeBCD[7];
//	MS pMS;
//}Selector5;

//typedef union 
//{
//	Selector1 st1;
//	//Selector2 st2;
//	//Selector5 st5;
//}RSD;

//typedef struct 
//{
//	OAD pOAD;
//	ROAD pROAD;
//}CSD;
//typedef struct 
//{
//	INT8U nTimes;
//	INT8U nCSDChoose[DATANUMB_ROW];
//	CSD pCSD[DATANUMB_ROW];
//}RCSD;


//typedef struct 
//{
//	INT8U nTimes;
//	INT8U nDataChoose[DATANUMB_ROW];
//	Data pData[DATANUMB_ROW];
//}A_RecordRow;
//
//typedef struct 
//{
//	OAD pOAD;
//	RCSD pRCSD;
//	INT8U nTimes;
//	A_RecordRow recordrow[DATANUMB_LINE]; //N条记录
//}A_RecordData;
//
//typedef struct
//{
//	DAR pDAR;
//	INT8U nDataChoose;
//	Data pData;
//}Get_Result;
//typedef struct 
//{
//	OAD pOAD;
//	INT8U nGetResultChoose;
//	Get_Result pGet_Result;
//}A_ResultNormal;
//
//typedef union 
//{
//	DAR pDAR;
//	A_RecordData recorddata;
//}A_ResultRecord;
//typedef struct 
//{
//	OAD pOAD;
//	INT8U nRSDChoose;
//	RSD pRSD;
//	RCSD pRCSD;
//}GetRecord;
//typedef struct 
//{
//	INT8U PIID;
//	GetRecord getRecd;
//}GetRequestRecord;
//
//typedef struct 
//{
//	INT8U PIID;
//	INT8U nTimes;
//	GetRecord getRecd[DATANUMB_LIST];
//}GetRequestRecordList;
//
//typedef struct
//{
//	INT8U PIID;
//	OAD pOAD;
//}GetRequestNormal;
//
//typedef struct
//{
//	INT8U PIID;
//	INT8U nTimes;
//	OAD pOAD[DATANUMB_LIST];
//}GetRequestNormalList;
//
//typedef struct
//{
//	INT8U nCipher;
//	INT8U Cipher[MIWEN_LEN];
//	INT8U nSignature;
//	INT8U SIGNATURE[MIWEN_LEN];
//}SymmetrySecurity;
//typedef struct
//{
//	INT8U nCipher;
//	INT8U Cipher[MIWEN_LEN];
//	INT8U nSignature;
//	INT8U SIGNATURE[MIWEN_LEN];
//}SignatureSecurity;
//typedef union
//{
//	INT8U nPassword;
//	INT8U PasswordSecurity[PASSWORD_LEN];
//	SymmetrySecurity pSymmetry;
//	SignatureSecurity pSignature;
//}ConnectMechanismInfo;
//typedef struct 
//{
//	INT8U PIID;
//	INT16U ComBCD4;
//	INT8U Portocol[8];
//	INT8U Function[16];
//	INT16U SendMaxlen;
//	INT16U RecvMaxlen;
//	INT8U  DlgMaxlen;
//	INT16U APDUMaxlen;
//	INT32U TimeOut;
//	INT8U nConnectMechanismInfoChoose;
//	ConnectMechanismInfo ConnectM;
//}CONNECT_Request;
//typedef struct 
//{
//	INT8U PIID;
//}RELEASE_Request;
//
//typedef union 
//{
//	GetRequestNormal normal;
//	GetRequestNormalList normalList;
//	GetRequestRecord grequestrecord;
//}GET_Request;
//
//typedef struct
//{
//	OAD pOAD;
//	INT8U nDataChoose;
//	Data pData;
//}MSETRequestOAD;
//typedef struct
//{
//	INT8U PIID;
//	MSETRequestOAD pMSETRequestOAD;
//}SetRequestNormal;
//typedef struct
//{
//	INT8U PIID;
//	INT8U nTimes;
//	MSETRequestOAD pMSETRequestOAD[DATANUMB_LIST];
//}SetRequestNormalList;
//
//typedef struct
//{
//	OAD pSetOAD;
//	INT8U nDataChoose;
//	Data pData;
//	OAD pGetOAD;
//	INT8U DelayTime;
//}MSETThenGetRequest;
//typedef struct
//{
//	INT8U PIID;
//	INT8U nTimes;
//	MSETThenGetRequest pMSETThenGetRequest[DATANUMB_LIST];
//}SetThenGetRequestNormalList;
//typedef union 
//{
//	SetRequestNormal pSetRequestNormal;
//	SetRequestNormalList pSetRequestNormalList;
//	SetThenGetRequestNormalList pSetThenGetRequestNormalList;
//}SET_Requset;
//typedef struct 
//{
//	INT8U nSET_RequsetChoose;
//	SET_Requset setrequest;
//}SET_RequsetA;
//
//typedef struct
//{
//	OMD pOMD;
//	INT8U nDataChoose;
//	Data pData;
//}MActionRequest;
//typedef struct
//{
//	INT8U PIID;
//	MActionRequest pMActionRequest;
//}ActionRequest;
//typedef struct
//{
//	INT8U PIID;
//	INT8U nTimes;
//	MActionRequest pMActionRequest[DATANUMB_LIST];
//}ActionRequestList;
//typedef struct
//{
//	OMD pOMD;
//	INT8U nDataChoose;
//	Data pData;
//	OAD pOAD;
//	INT8U nDelayTime;
//}ActionRequestActThenGet;
//typedef struct
//{
//	INT8U PIID;
//	INT8U nTimes;
//	ActionRequestActThenGet pActionRequestActThenGet[DATANUMB_LIST];
//}ActionThenGetRequestNormalList;
//typedef union 
//{
//	ActionRequest pActionRequest;
//	ActionRequestList pActionRequestList;
//	//ActionThenGetRequestNormalList pActionThenGetRequestNormalList;
//}ACTION_Request;
//typedef struct 
//{
//	INT8U nACTIONRequestChoose;
//	ACTION_Request pACTIONRequest;
//}ACTION_RequestA;
//typedef struct
//{
//	int nGET_RequestChoose;
//	GET_Request getrequest;
//}GET_RequestA;
//typedef union 
//{
//	CONNECT_Request connectrequest;
//	RELEASE_Request releaserequest;
//	GET_RequestA getrequestA;
//	SET_RequsetA setrequestA;
//	ACTION_RequestA actionrequestA;
//}Client_Applayer;
//
//
//typedef struct 
//{
//	INT8U enumerated;
//	INT16U time;
//}TI;
//typedef struct 
//{
//	INT8U datatimebcd[7];
//	TI time;
//}TimeTag;
//typedef struct 
//{
//	int nClient_ApplayerChoose;
//	Client_Applayer applayer;
//
//	bool btimeTag;
//	TimeTag tTag;
//}Client_APDU;
//
//typedef struct 
//{
//	INT8U VendorCode[4];
//	INT8U SoftVersion[4];
//	INT8U SoftDate[6];
//	INT8U HardVersion[4];
//	INT8U HardDate[6];
//	INT8U ExtendedInfor[8];
//}FactoryVersion;
//typedef struct 
//{
//	INT8U nRN;
//	INT8U RN[MIWEN_LEN];
//	INT8U nSignature;
//	INT8U SIGNATURE[MIWEN_LEN];
//}SecurityData;
//typedef struct 
//{
//	INT8U ConnectResult;
//	SecurityData pSecurityData;
//}ConnectResponseInfo;
//typedef struct 
//{
//	INT8U PIID_ACD;
//	FactoryVersion pFactoryVersion;
//	INT16U ComBCD4;
//	INT8U Portocol[8];
//	INT8U Function[16];
//	INT16U SendMaxlen;
//	INT16U RecvMaxlen;
//	INT8U  DlgMaxlen;
//	INT32U TimeOut;
//	ConnectResponseInfo pConnectResponseInfo;
//}CONNECT_Response;
//typedef struct 
//{
//	INT8U PIID_ACD;
//	INT8U Result;
//}RELEASE_Response;
//typedef struct 
//{
//	INT8U PIID_ACD;
//	INT8U CONNECTTIME[7];
//	INT8U NOWTIME[7];
//}RELEASE_Notification;
//
//typedef struct 
//{
//	INT8U PIID_ACD;
//	int nA_ResultRecordChoose;
//	A_ResultRecord resultRecord;
//}GetResponseRecord;
//typedef struct 
//{
//	INT8U PIID_ACD;
//	A_ResultNormal pAResultNormal;
//}GetResponseNormal;
//typedef struct 
//{
//	INT8U PIID_ACD;
//	INT8U nTimes;
//	A_ResultNormal pAResultNormal[DATANUMB_LIST];
//}GetResponseNormalList;
//typedef union 
//{
//	GetResponseNormal pGetResponseNormal; //164
//	GetResponseNormalList pGetResponseNormalList;//804
//	GetResponseRecord gresponserecord;//920
//}GET_Response;
//typedef struct
//{
//	OAD pOAD;
//	DAR pDAR;
//}MSetResponseOAD;
//typedef struct
//{
//	INT8U PIID_ACD;
//	MSetResponseOAD pMSetResponseOAD;
//}SetResponseNormal;
//
//
//typedef struct
//{
//	INT8U PIID_ACD;
//	INT8U nTimes;
//	MSetResponseOAD pMSetResponseOAD[DATANUMB_LIST];
//}SetResponseNormalList;
//typedef struct
//{
//	OAD pSetOAD;
//	DAR pDAR;
//	OAD pGetOAD;
//	Get_Result pGetResult;
//}MSetThenGet;
//typedef struct
//{
//	INT8U PIID_ACD;
//	INT8U nTimes;
//	MSetThenGet pMSetThenGet[DATANUMB_LIST];
//}SetThenGetResponseNormalList;
//typedef union 
//{
//	SetResponseNormal pSetResponseNormal;
//	//SetResponseNormalList pSetResponseNormalList;
//	//SetThenGetResponseNormalList pSetThenGetResponseNormalList;
//}SET_Response;
//typedef struct 
//{
//	INT8U nSET_ResponseChoose;
//	SET_Response pSET_Response;
//}SET_ResponseA;
//
//
//typedef struct 
//{
//	OMD pOMD;
//	DAR pDAR;
//	bool bData;
//	INT8U nDataChoose;
//	Data pData;
//}MAction;
//typedef struct 
//{
//	OMD pOMD;
//	DAR pDAR;
//	bool bData;
//	INT8U nDataChoose;
//	Data pData;
//	OAD pOAD;
//	Get_Result pGetResult;
//}MActionSetThenGet;
//typedef struct
//{
//	INT8U PIID_ACD;
//	MAction pMAction;
//}ActionResponseNormal;
//typedef struct
//{
//	INT8U PIID_ACD;
//	INT8U nTimes;
//	MAction pMAction[DATANUMB_LIST];
//}ActionResponseNormalList;
//
//typedef struct
//{
//	INT8U PIID_ACD;
//	INT8U nTimes;
//	MActionSetThenGet pMActionSetThenGet[DATANUMB_LIST];
//}ActionThenGetResponseNormalList;
//typedef union 
//{
//	ActionResponseNormal pActionResponseNormal;
//	ActionResponseNormalList pActionResponseNormalList;
//	ActionThenGetResponseNormalList pActionThenGetResponseNormalList;
//
//}ACTION_Response;
//typedef struct 
//{
//	INT8U nACTION_ResponseChoose;
//	ACTION_Response pACTION_Response;
//}ACTION_ResponseA;
//typedef struct 
//{
//
//}PROXY_Response;
//
//typedef struct
//{
//	int GET_ResponseChoose;
//	GET_Response getresponse;
//}GET_ResponseA;
//typedef union//struct 
//{
//	CONNECT_Response connectresponse;
//	RELEASE_Response releaseresponse;
//	RELEASE_Notification releasenotification;
//	GET_ResponseA getresponseA;
//	SET_ResponseA setresponseA;
//	//ACTION_ResponseA actionresponseA;
//}Server_Applayer;
//
//typedef struct 
//{
//	int nNumb;
//	A_ResultNormal arryNormal[1];
//	A_ResultRecord arryRecord[1];
//}FollowReport;
//typedef struct 
//{
//	int nServer_ApplayerChoose;
//	Server_Applayer applayer;
//	bool breport;
//	//FollowReport report;
//	bool btimeTag;
//	TimeTag tTag;
//}Server_APDU;

#include "Tools.h"
class CAPDUdata
{
public:
	CAPDUdata(INT8U *vSrcBuf,INT16U vSrcLen , Data * pSrcStuData , INT16U vSrcStuDatalen);
	~CAPDUdata(void);

public:
	Data * m_ramStuData;
	INT16U m_bpStuDatalen;
	INT16U m_ramStuDatalen;
	INT8U * m_rambuf;
	INT16U m_bpbuflen;
	INT16U s_rambuflen;
public:
	CTools m_tools;
	
public:
	INT8U m_ServerAPDUBuf[1024];
	INT16U m_ServerAPDUlen;
public:
	INT8U SetMalloc(INT8U ** pGetRAMbuf , INT16U nGetRAMlen);
	INT8U SetMallocStuData(Data ** pGetRAMStuData , INT16U nGetRAMStuDatalen);
	INT8U CoadAPDU(PartQGDW698_45 cGdw698  , INT8U * pDstAPDUbuf , INT16U & pDstAPDUlen);
	INT8U CoadAPDU_Data(Data apduData , INT8U nChoose  ,INT8U * pDSTBuf, INT16U &pDstlen);
	INT8U DecoadAPDU_Data(INT8U * pSrcBuf, INT16U pSrclen ,INT8U &Srclen , Data &pDstData ,INT8U &nDstDataChoose);
	INT8U DecoadClient_APDU(INT8U * pSrcAPDUbuf , INT16U pSrcAPDUlen , INT8U * serverbuf, INT16U &serverlen);
	INT8U ConnectRequest(INT8U * pSrcAPDUbuf, INT16U pSrcAPDUlen ,INT8U * serverbuf, INT16U &serverlen);
	INT8U GetConnectRespones(stuConnectRequest SrcConnectRequest , INT8U * DstBuf , INT16U & DstLen);
	INT8U GetRequest(INT8U * pSrcAPDUbuf, INT16U pSrcAPDUlen , INT8U * serverbuf, INT16U &serverlen);
	INT8U GetRequestRecord(INT8U * pSrcAPDUbuf, INT16U pSrcAPDUlen , INT8U * serverbuf, INT16U &serverlen);
	void SetBufToRSD(INT8U * pSrcAPDUbuf, INT16U pSrcAPDUlen , RSD & pRSD, INT8U &nRSDlen);
	INT8U GetClassTest(OAD SrcOAD , RSD SrcRSD , RCSD SrcRCSD , INT8U * DstBuf , INT16U & DstLen);
	INT8U GetRequestNormsal(INT8U * pSrcAPDUbuf, INT16U pSrcAPDUlen , INT8U * serverbuf, INT16U &serverlen);
	INT8U GetRequestNormsalList(INT8U * pSrcAPDUbuf, INT16U pSrcAPDUlen , INT8U * serverbuf, INT16U &serverlen);

	INT8U DecoadSecurity_APDU(INT8U * pSrcAPDUbuf , INT16U pSrcAPDUlen , INT8U * responsebuf, INT16U &responselen);
	INT8U SetESAMMsg(ESAM_MSG pSrcEsam_Msg , INT8U DataType , INT8U & bRespMsg , INT8U * EsamMsgRespBuf , INT8U  & EsamMsgResplen);

	//INT8U GetRequestNormsalList(INT8U * pSrcAPDUbuf, INT16U pSrcAPDUlen , Client_APDU &clientapdu , Server_APDU &serverapdu);
	INT8U GetClassIDTrecdata(OAD SrcOAD , INT8U * pSrcDatetimeBCD ,INT16U SrcDatatimeBCDlen , INT8U * pSrcTSA , INT16U SrcTSAlen , OAD SrcRCSD_OAD , Data * DstData);
	//INT8U GetClassIDTrecdata(OAD SrcOAD , INT8U * pSrcDatetimeBCD ,INT16U SrcDatatimeBCDlen , INT8U * pSrcTSA , INT16U SrcTSAlen , ROAD SrcRCSD_ROAD , Data * DstData);
	INT8U GetClassID9Meterdata(OAD SrcOAD , INT8U * pSrcDatetimeBCD ,INT16U SrcDatatimeBCDlen ,OAD SrcRCSD_OAD , Data & DstData , INT8U &nDataChoose);//
	INT8U GetClassIDMeterdata(OAD SrcOAD , Data & DstData , INT8U &nDataChoose);
	//INT8U GetClassIDdata(OAD SrcOAD , RSD SrcRSD ,ROAD SrcRCSD_OAD , Data * DstData);

	INT8U SetRequest(INT8U * pSrcAPDUbuf, INT16U pSrcAPDUlen ,INT8U * serverbuf, INT16U &serverlen);
	INT8U SetRequestNormsal(INT8U * pSrcAPDUbuf, INT16U pSrcAPDUlen , INT8U &Srclen ,INT8U * serverbuf, INT16U &serverlen);
	INT8U SetRequestNormsalList(INT8U * pSrcAPDUbuf, INT16U pSrcAPDUlen , INT8U * serverbuf, INT16U &serverlen);
	INT8U SetClassIDMeterdata(OAD SrcOAD , Data DstData , INT8U nDataChoose , DAR & pDAR);

	INT8U ActionRequest(INT8U * pSrcAPDUbuf, INT16U pSrcAPDUlen ,INT8U * serverbuf, INT16U &serverlen);
	INT8U ActionRequestNormsal(INT8U * pSrcAPDUbuf, INT16U pSrcAPDUlen ,  INT8U &Srclen ,INT8U * serverbuf, INT16U &serverlen);
	INT8U ActionRequestNormsallist(INT8U * pSrcAPDUbuf, INT16U pSrcAPDUlen , INT8U * serverbuf, INT16U &serverlen);
	INT8U ActionClassIDMeterdata(OMD SrcOAD , Data SrcData , INT8U nDataChoose , DAR & pDAR , int & nDstDataChoose , Data &DstData);
	INT8U BCDtoInteger(INT8U integer, INT8U * pDstbuf , INT8U & Dstlen);
	INT8U BCDtoDoublelong(INT32U sdoublong, INT8U * pDstbuf , INT8U & Dstlen);
	INT8U BCDtouDoublelong(INT32U udoublong, INT8U * pDstbuf , INT8U & Dstlen);
	INT8U BCDtolong(INT16U slong, INT8U * pDstbuf , INT8U & Dstlen);
	INT8U BCDtoulong(INT16U ulong, INT8U * pDstbuf , INT8U & Dstlen);
	INT8U BCDtounsign(INT8U unsign, INT8U * pDstbuf , INT8U & Dstlen);
	INT8U BCDtoDatetime(INT8U * BCDbuf, INT8U * pDstbuf , INT8U & Dstlen);
	INT8U BCDtoDate(INT8U * BCDbuf, INT8U * pDstbuf , INT8U & Dstlen);
	INT8U BCDtoTime(INT8U * BCDbuf, INT8U * pDstbuf , INT8U & Dstlen);
	INT8U BCDtoDatatime_s(INT8U * BCDbuf, INT8U * pDstbuf , INT8U & Dstlen);
};

