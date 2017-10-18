#include "StdAfx.h"
#include "PhaseValue698.h"


CPhaseValue698::CPhaseValue698(INT8U *vSrcBuf,INT16U vSrcBPlen ,INT16U vSrcLen , Data * pSrcStuData , INT16U vSrcBPStuDatalen ,INT16U vSrcStuDatalen)
{
	m_ramStuData = pSrcStuData;
	m_ramStuDatalen = vSrcStuDatalen;
	m_bpStuDatalen = vSrcBPStuDatalen;
	m_rambuf = vSrcBuf;
	s_rambuflen = vSrcLen;
	m_bpbuflen = vSrcBPlen;
}


CPhaseValue698::~CPhaseValue698(void)
{
}
INT8U CPhaseValue698::SetMalloc(INT8U ** pGetRAMbuf , INT16U nGetRAMlen)
{
	if((m_bpbuflen+nGetRAMlen)<=s_rambuflen)
	{
		*pGetRAMbuf = &m_rambuf[m_bpbuflen];
		m_bpbuflen += nGetRAMlen;
		return true;
	}
	else
	{
		*pGetRAMbuf = NULL;
	}

	return 0;
}

INT8U CPhaseValue698::SetMallocStuData(Data ** pGetRAMStuData , INT16U nGetRAMStuDatalen)
{
	if((m_bpStuDatalen + nGetRAMStuDatalen)<=m_ramStuDatalen)
	{
		*pGetRAMStuData = &m_ramStuData[m_bpStuDatalen];
		m_bpStuDatalen += nGetRAMStuDatalen;
		return true;
	}
	else
	{
		*pGetRAMStuData = NULL;
	}

	return 0;
}
INT8U CPhaseValue698::GetClassIDMeterdata(OAD SrcOAD , Data & DstData , INT8U &nDataChoose)
{
	DstData.OctetStringbuf = (INT8U *)malloc(sizeof(INT8U));
	switch(SrcOAD.OID)
	{
	case 0x4001:
		nDataChoose = 0x09;
		DstData.OctetStringbuf[0] = 0x06;
		DstData.OctetStringbuf[1] = 0x20;
		DstData.OctetStringbuf[2] = 0x16;
		DstData.OctetStringbuf[3] = 0x01;
		DstData.OctetStringbuf[4] = 0x29;
		DstData.OctetStringbuf[5] = 0x00;
		DstData.OctetStringbuf[6] = 0x01;
		break;
	case 0x2000:
		nDataChoose = 0x01;
		DstData.pArryA.nTimes = 0x03;
		//SetMalloc(&DstData.pArryA.nARRYChoose ,3);
		//SetMallocStuData(&DstData.pArryA.pArry ,DstData.pArryA.nTimes );
		DstData.pArryA.nARRYChoose[0] = 0x12;
		DstData.pArryA.pArry[0].ulong = 0x2210;
		DstData.pArryA.nARRYChoose[1] = 0x12;
		DstData.pArryA.pArry[1].ulong = 0x2200;
		DstData.pArryA.nARRYChoose[2] = 0x12;
		DstData.pArryA.pArry[2].ulong = 0x2190;
		break;
	case 0x2001:
		nDataChoose = 0x01;
		DstData.pArryA.nTimes = 0x03;
		DstData.pArryA.nARRYChoose[0] = 0x05;
		DstData.pArryA.pArry[0].udoublelong = 0x80000121;
		DstData.pArryA.nARRYChoose[1] = 0x05;
		DstData.pArryA.pArry[1].udoublelong = 0x00002000;
		DstData.pArryA.nARRYChoose[2] = 0x05;
		DstData.pArryA.pArry[2].udoublelong = 0x80003000;
		break;
	}
	return 0;
}