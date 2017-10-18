#pragma once
#include "APDUdata.h"
class CPhaseValue698
{
public:
	Data * m_ramStuData;
	INT16U m_bpStuDatalen;
	INT16U m_ramStuDatalen;
	INT8U * m_rambuf;
	INT16U m_bpbuflen;
	INT16U s_rambuflen;
	INT8U SetMalloc(INT8U ** pGetRAMbuf , INT16U nGetRAMlen);
	INT8U SetMallocStuData(Data ** pGetRAMStuData , INT16U nGetRAMStuDatalen);
	CPhaseValue698(INT8U *vSrcBuf,INT16U vSrcBPlen ,INT16U vSrcLen , Data * pSrcStuData , INT16U vSrcBPStuDatalen ,INT16U vSrcStuDatalen);
	~CPhaseValue698(void);
	INT8U GetClassIDMeterdata(OAD SrcOAD , Data & DstData , INT8U &nDataChoose);
};

