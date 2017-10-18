#include "StdAfx.h"
#include "APDUdata.h"
#include "LibExtern.h"
#include "PhaseValue698.h"


CAPDUdata::CAPDUdata(INT8U *vSrcBuf,INT16U vSrcLen , Data * pSrcStuData , INT16U vSrcStuDatalen)
{
	m_ramStuData = pSrcStuData;
	m_ramStuDatalen = vSrcStuDatalen;
	m_bpStuDatalen = 0;
	m_rambuf = vSrcBuf;
	s_rambuflen = vSrcLen;
	m_bpbuflen = 0;
}


CAPDUdata::~CAPDUdata(void)
{
}

u_long BCD_Change_Hex(u_long BCDValue)//,u_char num_)
{

    u_long X = 0, Y = 1;
    for(u_char i = 0; i < 8; i++)
    {
        X += (BCDValue & 0xf) * Y;
        BCDValue >>= 4;
        Y *= 10;
    }
    return(X);
}
INT8U CAPDUdata::BCDtoInteger(INT8U integer, INT8U * pDstbuf , INT8U & Dstlen)
{
	if (integer >> 7)
	{
		integer &= 0x7f;
		integer = (INT8U)BCD_Change_Hex(integer);
		integer = ~integer + 1;
	}
	else
	{
		integer = (INT8U)BCD_Change_Hex(integer);
	}
	pDstbuf[0] = integer;
	Dstlen = 1;
	return true;
}
INT8U CAPDUdata::BCDtolong(INT16U slong, INT8U * pDstbuf , INT8U & Dstlen)
{
	if (slong >> 15)
	{
		slong &= 0x7fff;
		slong = (INT16U)BCD_Change_Hex(slong);
		slong = ~slong + 1;
	}
	else
	{
		slong = (INT16U)BCD_Change_Hex(slong);
	}
	pDstbuf[0] = (INT8U)(slong >> 8);
	pDstbuf[1] = (INT8U)slong;
	Dstlen = 2;
	return true;
}
INT8U CAPDUdata::BCDtoDoublelong(INT32U sdoublong, INT8U * pDstbuf , INT8U & Dstlen)
{
	if (sdoublong >> 31)
	{
		sdoublong &= 0x7fffffff;
		sdoublong = BCD_Change_Hex(sdoublong);
		sdoublong = ~sdoublong + 1;
	}
	else
	{
		sdoublong = BCD_Change_Hex(sdoublong);
	}
	pDstbuf[0] = (INT8U)(sdoublong >> 24);
	pDstbuf[1] = (INT8U)(sdoublong >> 16);
	pDstbuf[2] = (INT8U)(sdoublong >> 8);
	pDstbuf[3] = (INT8U)sdoublong;
	Dstlen = 4;
	return true;
}
INT8U CAPDUdata::BCDtouDoublelong(INT32U udoublong, INT8U * pDstbuf , INT8U & Dstlen)
{
	udoublong = BCD_Change_Hex(udoublong);
	pDstbuf[0] = (INT8U)(udoublong>>24);
	pDstbuf[1] = (INT8U)(udoublong>>16);
	pDstbuf[2] = (INT8U)(udoublong>>8);
	pDstbuf[3] = (INT8U)(udoublong>>0);
	Dstlen = 4;
	return true;
}
INT8U CAPDUdata::BCDtoulong(INT16U ulong, INT8U * pDstbuf , INT8U & Dstlen)
{
	ulong = (INT16U)BCD_Change_Hex(ulong);
	pDstbuf[0] = (INT8U)(ulong >> 8);
	pDstbuf[1] = (INT8U)ulong;
	Dstlen = 2;
	return true;
}
INT8U CAPDUdata::BCDtounsign(INT8U unsign, INT8U * pDstbuf , INT8U & Dstlen)
{
	unsign = (INT8U)BCD_Change_Hex(unsign);
	pDstbuf[0] = unsign;
	Dstlen = 1;
	return true;
}
INT8U CAPDUdata::BCDtoDatetime(INT8U * BCDbuf, INT8U * pDstbuf , INT8U & Dstlen)
{
	INT8U temp8 = 0;
	INT16U temp16 = 0;
	temp16 = BCDbuf[0] << 8 | BCDbuf[1];
	temp16 = (INT16U)BCD_Change_Hex(temp16);
	pDstbuf[0] = (INT8U)(temp16 >> 8);
	pDstbuf[1] = (INT8U)temp16;
	pDstbuf[2] = (INT8U)BCD_Change_Hex(BCDbuf[2]);
	pDstbuf[3] = (INT8U)BCD_Change_Hex(BCDbuf[3]);
	pDstbuf[4] = (INT8U)BCD_Change_Hex(BCDbuf[4]);
	pDstbuf[5] = (INT8U)BCD_Change_Hex(BCDbuf[5]);
	pDstbuf[6] = (INT8U)BCD_Change_Hex(BCDbuf[6]);
	pDstbuf[7] = (INT8U)BCD_Change_Hex(BCDbuf[7]);
	temp16 = BCDbuf[8] << 8 | BCDbuf[9];
	temp16 = (INT16U)BCD_Change_Hex(temp16);
	pDstbuf[8] = (INT8U)(temp16 >> 8);
	pDstbuf[9] = (INT8U)temp16;
	Dstlen = 10;
	return true;
}
INT8U CAPDUdata::BCDtoDate(INT8U * BCDbuf, INT8U * pDstbuf , INT8U & Dstlen)
{
	INT8U temp8 = 0;
	INT16U temp16 = 0;
	temp16 = BCDbuf[0] << 8 | BCDbuf[1];
	temp16 = (INT16U)BCD_Change_Hex(temp16);
	pDstbuf[0] = (INT8U)(temp16 >> 8);
	pDstbuf[1] = (INT8U)temp16;
	pDstbuf[2] = (INT8U)BCD_Change_Hex(BCDbuf[2]);
	pDstbuf[3] = (INT8U)BCD_Change_Hex(BCDbuf[3]);
	pDstbuf[4] = (INT8U)BCD_Change_Hex(BCDbuf[4]);
	Dstlen = 5;
	return true;
}
INT8U CAPDUdata::BCDtoTime(INT8U * BCDbuf, INT8U * pDstbuf , INT8U & Dstlen)
{
	pDstbuf[0] = (INT8U)BCD_Change_Hex(BCDbuf[0]);
	pDstbuf[1] = (INT8U)BCD_Change_Hex(BCDbuf[1]);
	pDstbuf[2] = (INT8U)BCD_Change_Hex(BCDbuf[2]);
	Dstlen = 3;
	return true;
}
INT8U CAPDUdata::BCDtoDatatime_s(INT8U * BCDbuf, INT8U * pDstbuf , INT8U & Dstlen)
{
	INT8U temp8 = 0;
	INT16U temp16 = 0;
	temp16 = BCDbuf[0] << 8 | BCDbuf[1];
	temp16 = (INT16U)BCD_Change_Hex(temp16);
	pDstbuf[0] = (INT8U)(temp16 >> 8);
	pDstbuf[1] = (INT8U)temp16;
	pDstbuf[2] = (INT8U)BCD_Change_Hex(BCDbuf[2]);
	pDstbuf[3] = (INT8U)BCD_Change_Hex(BCDbuf[3]);
	pDstbuf[4] = (INT8U)BCD_Change_Hex(BCDbuf[4]);
	pDstbuf[5] = (INT8U)BCD_Change_Hex(BCDbuf[5]);
	pDstbuf[6] = (INT8U)BCD_Change_Hex(BCDbuf[6]);
	Dstlen = 7;
	return true;
}
//Data结构体转Buf数组
INT8U CAPDUdata::CoadAPDU_Data(Data pData ,INT8U nDataChoose , INT8U * pDSTBuf, INT16U &pDstlen)
{
	INT16U utemp16 = 0;
	INT32U utemp32 = 0;
	INT8U n = 0 , m = 0 , i = 0;
	INT8U utemp1 = 0 , utemp2 = 0, utemp3 = 0 , ulen = 0;
	pDstlen = 0;
	utemp1 = nDataChoose;
	pDSTBuf[pDstlen++] = utemp1;
	switch(utemp1)
	{
	case 0x00:
		break;
	case 0x01://array
		utemp1 = pData.pArryA.nTimes;
		pDSTBuf[pDstlen++] = utemp1;
		for(n = 0; n< utemp1 ; n++)
		{
			utemp2 = pData.pArryA.nARRYChoose[n];
			pDSTBuf[pDstlen++] = utemp2;
			switch(utemp2)
			{
			case 0x02:
				utemp2 = pData.pArryA.pArry[n].pStructureA.nTimes;
				pDSTBuf[pDstlen++] = utemp2;
				for (m = 0 ; m < utemp2 ; m++)
				{
					utemp3 = pData.pArryA.pArry[n].pStructureA.nStructChoose[m];
					pDSTBuf[pDstlen++] = utemp3;
					switch(utemp3)
					{
					case 0x05://doublelong
						BCDtoDoublelong(pData.pArryA.pArry[n].pStructureA.pStructrea[m].doublelong , &pDSTBuf[pDstlen],ulen);
						break;
					case 0x06://udoublelong
						BCDtouDoublelong(pData.pArryA.pArry[n].pStructureA.pStructrea[m].udoublelong,&pDSTBuf[pDstlen],ulen);
						break;
					case 0x0f://integer
						BCDtounsign(pData.pArryA.pArry[n].pStructureA.pStructrea[m].integer,&pDSTBuf[pDstlen],ulen);
						break;
					case 0x10://long16
						BCDtolong(pData.pArryA.pArry[n].pStructureA.pStructrea[m].long16,&pDSTBuf[pDstlen],ulen);
						break;
					case 0x11://unsign
						BCDtoulong(pData.pArryA.pArry[n].pStructureA.pStructrea[m].unsign,&pDSTBuf[pDstlen],ulen);
						break;
					case 0x12://ulong
						BCDtoulong(pData.pArryA.pArry[n].pStructureA.pStructrea[m].ulong,&pDSTBuf[pDstlen],ulen);
						break;
					case 0x1c:
						BCDtoDate(pData.Datetime_S , &pDSTBuf[pDstlen],ulen);
						break;
					}
					pDstlen += ulen;
					ulen=0;
				}
				break;
			case 0x05://doublelong
				BCDtoDoublelong(pData.pArryA.pArry[n].doublelong , &pDSTBuf[pDstlen],ulen);
				break;
			case 0x06://udoublelong
				BCDtouDoublelong(pData.pArryA.pArry[n].udoublelong,&pDSTBuf[pDstlen],ulen);
				break;
			case 0x0f://integer
				BCDtounsign(pData.pArryA.pArry[n].integer,&pDSTBuf[pDstlen],ulen);
				break;
			case 0x10://long16
				BCDtolong(pData.pArryA.pArry[n].long16,&pDSTBuf[pDstlen],ulen);
				break;
			case 0x11://unsign
				BCDtoulong(pData.pArryA.pArry[n].unsign,&pDSTBuf[pDstlen],ulen);
				break;
			case 0x12://ulong
				BCDtoulong(pData.pArryA.pArry[n].ulong,&pDSTBuf[pDstlen],ulen);
				break;
			}
			pDstlen += ulen;
			ulen=0;
		}
		break;
	case 0x02://STRUCTURE
		break;
	case 0x03://boolean
		break;
	case 0x04://BitStringbuf
		break;
	case 0x05://doublelong
		BCDtoDoublelong(pData.doublelong , &pDSTBuf[pDstlen],ulen);
		break;
	case 0x06://udoublelong
		BCDtouDoublelong(pData.udoublelong,&pDSTBuf[pDstlen],ulen);
		break;
	case 0x09://OctetStringbuf
		ulen = pData.OctetStringbuf[0] + 1;
		for (n = 0; n < ulen; n++)
		{
			pDSTBuf[pDstlen + n] = pData.OctetStringbuf[n];
		}
		break;
	case 0x0A://VisibleStringbuf
		break;
	case 0x0C://
		break;
	case 0x0f://integer
		BCDtounsign(pData.integer,&pDSTBuf[pDstlen],ulen);
		break;
	case 0x10://long16
		BCDtolong(pData.long16,&pDSTBuf[pDstlen],ulen);
		break;
	case 0x11://unsign
		BCDtoulong(pData.unsign,&pDSTBuf[pDstlen],ulen);
		break;
	case 0x12://ulong
		BCDtoulong(pData.ulong,&pDSTBuf[pDstlen],ulen);
		break;
	case 0x14://long64
		break;
	case 0x15://ulong64
		break;
	case 0x16://uenum
		break;
	case 0x19://Datetime
		BCDtoDatetime(pData.Datetime , &pDSTBuf[pDstlen],ulen);
		break;
	case 0x1A://Date
		BCDtoDate(pData.Date , &pDSTBuf[pDstlen],ulen);
		break;
	case 0x1B://Time
		BCDtoDate(pData.Time , &pDSTBuf[pDstlen],ulen);
		break;
	case 0x1c://STRUCTUREA
		BCDtoDate(pData.Datetime_S , &pDSTBuf[pDstlen],ulen);
		break;
	case 0x55://TSA
		pDSTBuf[pDstlen++] = pData.pTSA.buflen;
		for (n = 0 ;n < pData.pTSA.buflen ; n++)
		{
			pDSTBuf[pDstlen++] = pData.pTSA.bufAddr[n];
		}
		ulen = 0;
		break;
	}
	pDstlen += ulen;
	return true;
}
//Buf数组转Data结构体
INT8U CAPDUdata::DecoadAPDU_Data(INT8U * pSrcAPDUbuf, INT16U pSrclen , INT8U &Srclen , Data &pData ,INT8U &nDstDataChoose)
{
	INT8U i = 0 , n = 0 , m = 0;
	INT32U uDoublong = 0;
	nDstDataChoose = pSrcAPDUbuf[i++];
	switch(nDstDataChoose)
	{
	case 0x01:
		pData.pArryA.nTimes = pSrcAPDUbuf[i++];
		for ( n = 0 ; n < pData.pArryA.nTimes ; n++)
		{
			pData.pArryA.nARRYChoose[n] = pSrcAPDUbuf[i++];
			switch(pData.pArryA.nARRYChoose[n])
			{
			case 0x02:
				pData.pArryA.pArry[n].pStructureA.nTimes = pSrcAPDUbuf[i++];
				for ( m = 0 ; m < pData.pArryA.pArry[n].pStructureA.nTimes ; m++)
				{
					pData.pArryA.pArry[n].pStructureA.nStructChoose[m] = pSrcAPDUbuf[i++];
					switch (pData.pArryA.pArry[n].pStructureA.nStructChoose[m])
					{
					case 0x03://bool
						break;
					case 0x05://doublelong
						break;
					case 0x06://udoublelong
						break;
					case 0x0f://integer
						break;
					case 0x10://long16
						break;
					case 0x11://unsign
						break;
					case 0x12://ulong
						break;
					case 0x1c:
						break;
					}
				}
				break;
			case 0x05://doublelong
				break;
			case 0x06://udoublelong
				break;
			case 0x0f://integer
				break;
			case 0x10://long16
				break;
			case 0x11://unsign
				break;
			case 0x12://ulong
				break;
			}
		}
		break;
	case 0x02:
		pData.pStructureA.nTimes = pSrcAPDUbuf[i++];
		for ( n = 0 ; n < pData.pStructureA.nTimes ; n++)
		{
			pData.pStructureA.nStructChoose[n] = pSrcAPDUbuf[i++];
			switch (pData.pStructureA.nStructChoose[n])
			{
			case 0x05:
				uDoublong = (INT32U)((pSrcAPDUbuf[i] << 24) | (pSrcAPDUbuf[i + 1] << 16) |(pSrcAPDUbuf[i + 2] << 8) |(pSrcAPDUbuf[i + 3]));
				i += 4;
				pData.pStructureA.pStructrea[n].doublelong = uDoublong;
				break;
			case 0x06:
				uDoublong = (INT32U)((pSrcAPDUbuf[i] << 24) | (pSrcAPDUbuf[i + 1] << 16) |(pSrcAPDUbuf[i + 2] << 8) |(pSrcAPDUbuf[i + 3]));
				i += 4;
				pData.pStructureA.pStructrea[n].udoublelong = uDoublong;
				break;
			case 0x09://OctetStringbuf	
				SetMalloc (&pData.pStructureA.pStructrea[n].OctetStringbuf , pSrcAPDUbuf[i]+1);
				pData.pStructureA.pStructrea[n].OctetStringbuf[0] = pSrcAPDUbuf[i++];
				for( m = 0;m < pData.pStructureA.pStructrea[n].OctetStringbuf[0];m++ )
				{
					pData.pStructureA.pStructrea[n].OctetStringbuf[1 + m] = pSrcAPDUbuf[i++];
				}
				break;
			case 0x10:
				uDoublong = (pSrcAPDUbuf[i] << 8) |(pSrcAPDUbuf[i + 1]);
				i += 2;
				pData.pStructureA.pStructrea[n].long16 = (INT16U) uDoublong;
				break;
			case 0x11:
				pData.pStructureA.pStructrea[n].unsign = pSrcAPDUbuf[i++];
				break;
			case 0x12:
				uDoublong = (pSrcAPDUbuf[i] << 8) |(pSrcAPDUbuf[i + 1]);
				i += 2;
				pData.pStructureA.pStructrea[n].ulong = (INT16U) uDoublong;
				break;
			case 0x5E://SID_MAC
				SetMalloc (&pData.pStructureA.pStructrea[n].pSID_MAC.pSID.DI , 4);
				pData.pStructureA.pStructrea[n].pSID_MAC.pSID.DI[0] = pSrcAPDUbuf[i++];
				pData.pStructureA.pStructrea[n].pSID_MAC.pSID.DI[1] = pSrcAPDUbuf[i++];
				pData.pStructureA.pStructrea[n].pSID_MAC.pSID.DI[2] = pSrcAPDUbuf[i++];
				pData.pStructureA.pStructrea[n].pSID_MAC.pSID.DI[3] = pSrcAPDUbuf[i++];

				SetMalloc (&pData.pStructureA.pStructrea[n].pSID_MAC.pSID.SubjoinData , pSrcAPDUbuf[i] + 1);
				pData.pStructureA.pStructrea[n].pSID_MAC.pSID.SubjoinData[0] = pSrcAPDUbuf[i++];
				for(m = 0 ; m < pData.pStructureA.pStructrea[n].pSID_MAC.pSID.SubjoinData[0] ; m++)
				{
					pData.pStructureA.pStructrea[n].pSID_MAC.pSID.SubjoinData[1 + m] = pSrcAPDUbuf[i++];
				}

				SetMalloc (&pData.pStructureA.pStructrea[n].pSID_MAC.MacData , pSrcAPDUbuf[i] + 1);
				pData.pStructureA.pStructrea[n].pSID_MAC.MacData[0] = pSrcAPDUbuf[i++];
				for(m = 0 ; m < pData.pStructureA.pStructrea[n].pSID_MAC.MacData[0] ; m++)
				{
					pData.pStructureA.pStructrea[n].pSID_MAC.MacData[1 + m] = pSrcAPDUbuf[i++];
				}
				break;
			}
		}
		break;
	case 0x03://boolean
		pData.boolean = pSrcAPDUbuf[i++];
		break;
	case 0x04://BitStringbuf
		break;
	case 0x05://doublelong
		break;
	case 0x06://udoublelong
		uDoublong = (INT32U)((pSrcAPDUbuf[i] << 24) | (pSrcAPDUbuf[i + 1] << 16) |(pSrcAPDUbuf[i + 2] << 8) |(pSrcAPDUbuf[i + 3]));
		i += 4;
		pData.udoublelong = uDoublong;
		break;
	case 0x09://OctetStringbuf	

		pData.OctetStringbuf=(INT8U *)malloc(sizeof(INT8U));
		for( n = 0;n < pSrcAPDUbuf[i]+1;n++ )
			*(pData.OctetStringbuf+n)= pSrcAPDUbuf[i+n];
		i +=1+pSrcAPDUbuf[i];
		break;
	case 0x0A://VisibleStringbuf
		pData.OctetStringbuf=(INT8U *)malloc(sizeof(INT8U));
		for( n = 0;n < pSrcAPDUbuf[i]+1;n++ )
			*(pData.OctetStringbuf+n)= pSrcAPDUbuf[i+n];
		i +=1+pSrcAPDUbuf[i];
		break;
	case 0x0C://
		break;
	case 0x0f://integer
		break;
	case 0x10://long16
		break;
	case 0x11://unsign
		break;
	case 0x12://ulong
		uDoublong = (pSrcAPDUbuf[i] << 8) |(pSrcAPDUbuf[i + 1]);
		i += 2;
		pData.ulong = (INT16U)uDoublong;
		break;
	case 0x14://long64
		break;
	case 0x15://ulong64
		break;
	case 0x16://uenum
		i += 1;
		pData.uenum=pSrcAPDUbuf[i];
		break;
	case 0x19://Datetime
		break;
	case 0x1A://Date
		break;
	case 0x1B://Time
		break;
	case 0x1c://STRUCTUREA
		for( n = 0 ; n < 7 ; n++)
		{
			pData.Datetime_S[n] = pSrcAPDUbuf[i++];
		}
		break;
	case 0x55://TSA
		break;
	}

	return true;
}
INT8U CAPDUdata::SetMalloc(INT8U ** pGetRAMbuf , INT16U nGetRAMlen)
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

INT8U CAPDUdata::SetMallocStuData(Data ** pGetRAMStuData , INT16U nGetRAMStuDatalen)
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

INT8U CAPDUdata::CoadAPDU(PartQGDW698_45 cGdw698 ,INT8U * pDstAPDUbuf , INT16U & pDstAPDUlen)
{
	INT8U ack = false;
	m_ServerAPDUlen = 0;
	pDstAPDUlen = 0;
	Data pData;	

	switch(cGdw698.pSrcAPDU[0])
	{
	case 0x01:
		break;
	case 0x02:
	case 0x03:
	case 0x05:
	case 0x06:
	case 0x07:
	case 0x09:
		ack = DecoadClient_APDU(cGdw698.pSrcAPDU , cGdw698.pSrcAPDUlen , pDstAPDUbuf, pDstAPDUlen);
		break;
	case 0x10:	// Security
		ack = DecoadSecurity_APDU( cGdw698.pSrcAPDU , cGdw698.pSrcAPDUlen , pDstAPDUbuf, pDstAPDUlen);
		break;
	default:
		break;
	}
	return ack;
}
INT8U CAPDUdata::DecoadSecurity_APDU(INT8U * pSrcAPDUbuf , INT16U pSrcAPDUlen , INT8U * responsebuf, INT16U &responselen)
{
	INT8U ack = false , i = 0 , n = 0;
	INT16U temp16 = 0;
	ESAM_MSG pESAM_MSG;
	INT8U EsamMsgRespBuf[20];
	INT8U EsamMsgResplen = 0;
	INT8U bRespMsg = 0;
	INT8U temp = 0;
	INT8U DataType = 0;
	INT8U clientAPDUbuf[255];
	INT8U clientAPDUlen = 0;
	i++;
	DataType = pSrcAPDUbuf[i++];//明文或密文

	responsebuf[0] = 0x90;
	responsebuf[1] = DataType;
	responselen += 2;

	clientAPDUlen = pSrcAPDUbuf[i++];
	for(n = 0 ; n < clientAPDUlen ; n++)
	{
		clientAPDUbuf[n] = pSrcAPDUbuf[i++];
	}
	pESAM_MSG.nChooseNumb = pSrcAPDUbuf[i++];
	switch(pESAM_MSG.nChooseNumb)
	{
	case 0://数据验证码
		//pESAM_MSG.pSID_MAC.pSID.DI = (pSrcAPDUbuf[i]<<24) | (pSrcAPDUbuf[i+1]<<16) |(pSrcAPDUbuf[i+2]<<8) |pSrcAPDUbuf[i+3];
		i += 4;
		pESAM_MSG.pSID_MAC.pSID.SubjoinData = &pSrcAPDUbuf[i];
		i += pSrcAPDUbuf[i] + 1;
		pESAM_MSG.pSID_MAC.MacData = &pSrcAPDUbuf[i];
		i += pSrcAPDUbuf[i] + 1;
		break;
	case 1://随机数
		break;
	case 2://随机数+数据MAC
		break;
	case 3://安全标识
		break;
	}


	ack = SetESAMMsg(pESAM_MSG , DataType , bRespMsg , EsamMsgRespBuf , EsamMsgResplen);//数据验证信息 及 明文密文类型


	if (ack)
	{
		DecoadClient_APDU(clientAPDUbuf , clientAPDUlen , &responsebuf[responselen + 1] , temp16);
		responsebuf[responselen] = temp16;
		responselen += temp16 + 1;
	}
	responsebuf[responselen++] = bRespMsg;
	if (bRespMsg)
	{
		for(n = 0; n < EsamMsgResplen ; n++)
		{
			responsebuf[responselen++] = EsamMsgRespBuf[n];
		}
	}
	return ack;
}
INT8U CAPDUdata::SetESAMMsg(ESAM_MSG pSrcEsam_Msg , INT8U DataType , INT8U & bRespMsg , INT8U * EsamMsgRespBuf , INT8U  & EsamMsgResplen)
{
	INT8U macbuf[7];
	bRespMsg = 0x01;
	EsamMsgRespBuf[0] = 0x00;
	EsamMsgRespBuf[1] = 0x04;
	EsamMsgRespBuf[2] = 0x12;
	EsamMsgRespBuf[3] = 0x34;
	EsamMsgRespBuf[4] = 0x56;
	EsamMsgRespBuf[5] = 0x78;
	EsamMsgResplen = 6;
	return 1;
}


INT8U CAPDUdata::DecoadClient_APDU(INT8U * pSrcAPDUbuf , INT16U pSrcAPDUlen ,INT8U * serverbuf, INT16U &serverlen )
{
	INT8U ack = false;
	INT16U temp16 = 0;
	switch (pSrcAPDUbuf[0])
	{
	case 0x02:
		serverbuf[0] = 0x82;
		serverlen += 1;
		ConnectRequest(&pSrcAPDUbuf[1] , pSrcAPDUlen - 1 , &serverbuf[serverlen] , temp16);
		break;
	case 0x03:
		serverbuf[0] = 0x83;
		serverlen += 1;
		//ConnectRequest(INT8U * pSrcAPDUbuf, INT16U pSrcAPDUlen ,INT8U * serverbuf, INT16U &serverlen)
			break;
	case 0x05:
		serverbuf[0] = 0x85;
		serverlen += 1;
		ack = GetRequest(&pSrcAPDUbuf[1] , pSrcAPDUlen - 1 , &serverbuf[serverlen] , temp16);
		break;
	case 0x06:
		serverbuf[0] = 0x86;
		serverlen += 1;
		ack = SetRequest(&pSrcAPDUbuf[1] , pSrcAPDUlen - 1 , &serverbuf[serverlen] , temp16);
		break;
	case 0x07:
		serverbuf[0] = 0x87;
		serverlen += 1;
		ack = ActionRequest(&pSrcAPDUbuf[1] , pSrcAPDUlen - 1 , &serverbuf[serverlen] , temp16);
		break;
	default:
		break;
	}
	serverlen += temp16;
	serverbuf[serverlen++] = 0x00;
	serverbuf[serverlen++] = 0x00;
	return ack;
}
//ConnectRequest相关
INT8U CAPDUdata::ConnectRequest(INT8U * pSrcAPDUbuf, INT16U pSrcAPDUlen ,INT8U * serverbuf, INT16U &serverlen)
{
	stuConnectRequest sConnectRequest;
	INT8U ack = false , n = 0 , i = 0;
	INT16U temp16 = 0;

	sConnectRequest.nPIID = pSrcAPDUbuf[i];

	sConnectRequest.nTVnumb = pSrcAPDUbuf[i +1]<<8 | pSrcAPDUbuf[i]; 
	i += 2;

	for(n = 0 ; n < 8 ; n++)
	{
		sConnectRequest.nProtocolConformance[n] =  pSrcAPDUbuf[i++];
	}

	for(n = 0 ; n < 16 ; n++)
	{
		sConnectRequest.nFunctionConformance[n] =  pSrcAPDUbuf[i++];
	}

	sConnectRequest.nClientSendMax = pSrcAPDUbuf[i +1]<<8 | pSrcAPDUbuf[i]; 
	i += 2;

	sConnectRequest.nClientRecvMax = pSrcAPDUbuf[i +1]<<8 | pSrcAPDUbuf[i]; 
	i += 2;

	sConnectRequest.nClientFramMax = pSrcAPDUbuf[i++]; 

	sConnectRequest.nClientAPDUMax = pSrcAPDUbuf[i +1]<<8 | pSrcAPDUbuf[i]; 
	i += 2;

	sConnectRequest.nMaxTime = pSrcAPDUbuf[i +3]<<24 | pSrcAPDUbuf[i + 2]<<16 | pSrcAPDUbuf[i +1]<<8 | pSrcAPDUbuf[i]; 
	i += 4;

	//INT8U testbuf[5];
	//sConnectRequest.sConnectMechanismInfo.pRasswordSecurityBuf = testbuf;
	SetMalloc(&sConnectRequest.sConnectMechanismInfo.pRasswordSecurityBuf , 5);
	sConnectRequest.sConnectMechanismInfo.pRasswordSecurityBuf[0] = 0x01;

	sConnectRequest.nChooseInfo = pSrcAPDUbuf[i++];
	switch(sConnectRequest.nChooseInfo)
	{
	case 1:
		temp16 = pSrcAPDUbuf[i +1]<<8 | pSrcAPDUbuf[i]; 
		i += 2;
		sConnectRequest.sConnectMechanismInfo.pRasswordSecurityBuf = new INT8U[temp16 + 2];
		sConnectRequest.sConnectMechanismInfo.pRasswordSecurityBuf[0] = temp16;
		sConnectRequest.sConnectMechanismInfo.pRasswordSecurityBuf[1] = temp16 >> 8;
		for(n = 0 ; n < temp16 ; n++)
		{
			sConnectRequest.sConnectMechanismInfo.pRasswordSecurityBuf[n + 2] =  pSrcAPDUbuf[i++];
		}
		break;
	case 2:
		temp16 = pSrcAPDUbuf[i +1]<<8 | pSrcAPDUbuf[i]; 
		i += 2;
		sConnectRequest.sConnectMechanismInfo.pSymmetrySecurityM1Buf = new INT8U[temp16 + 2];
		sConnectRequest.sConnectMechanismInfo.pSymmetrySecurityM1Buf[0] = temp16;
		sConnectRequest.sConnectMechanismInfo.pSymmetrySecurityM1Buf[1] = temp16 >> 8;
		for(n = 0 ; n < temp16 ; n++)
		{
			sConnectRequest.sConnectMechanismInfo.pSymmetrySecurityM1Buf[n + 2] =  pSrcAPDUbuf[i++];
		}

		temp16 = pSrcAPDUbuf[i +1]<<8 | pSrcAPDUbuf[i]; 
		i += 2;
		sConnectRequest.sConnectMechanismInfo.pSymmetrySecurityCQ1Buf = new INT8U[temp16 + 2];
		sConnectRequest.sConnectMechanismInfo.pSymmetrySecurityCQ1Buf[0] = temp16;
		sConnectRequest.sConnectMechanismInfo.pSymmetrySecurityCQ1Buf[1] = temp16 >> 8;
		for(n = 0 ; n < temp16 ; n++)
		{
			sConnectRequest.sConnectMechanismInfo.pSymmetrySecurityCQ1Buf[n + 2] =  pSrcAPDUbuf[i++];
		}
		break;
	case 3:
		temp16 = pSrcAPDUbuf[i +1]<<8 | pSrcAPDUbuf[i]; 
		i += 2;
		sConnectRequest.sConnectMechanismInfo.pSignatureSecurityM2Buf = new INT8U[temp16 + 2];
		sConnectRequest.sConnectMechanismInfo.pSignatureSecurityM2Buf[0] = temp16;
		sConnectRequest.sConnectMechanismInfo.pSignatureSecurityM2Buf[1] = temp16 >> 8;
		for(n = 0 ; n < temp16 ; n++)
		{
			sConnectRequest.sConnectMechanismInfo.pSignatureSecurityM2Buf[n + 2] =  pSrcAPDUbuf[i++];
		}

		temp16 = pSrcAPDUbuf[i +1]<<8 | pSrcAPDUbuf[i]; 
		i += 2;
		sConnectRequest.sConnectMechanismInfo.pSignatureSecurityCQ2Buf = new INT8U[temp16 + 2];
		sConnectRequest.sConnectMechanismInfo.pSignatureSecurityCQ2Buf[0] = temp16;
		sConnectRequest.sConnectMechanismInfo.pSignatureSecurityCQ2Buf[1] = temp16 >> 8;
		for(n = 0 ; n < temp16 ; n++)
		{
			sConnectRequest.sConnectMechanismInfo.pSignatureSecurityCQ2Buf[n + 2] =  pSrcAPDUbuf[i++];
		}
		break;
	}

	GetConnectRespones(sConnectRequest , serverbuf , serverlen);

	AfxMessageBox(m_tools._buf16tostr16(sConnectRequest.sConnectMechanismInfo.pRasswordSecurityBuf , 6));
	switch(sConnectRequest.nChooseInfo)
	{
	case 1:
		delete [] sConnectRequest.sConnectMechanismInfo.pRasswordSecurityBuf;
		break;
	case 2:
		delete [] sConnectRequest.sConnectMechanismInfo.pSymmetrySecurityM1Buf;
		delete [] sConnectRequest.sConnectMechanismInfo.pSymmetrySecurityCQ1Buf;
		break;
	case 3:
		delete [] sConnectRequest.sConnectMechanismInfo.pSignatureSecurityM2Buf;
		delete [] sConnectRequest.sConnectMechanismInfo.pSignatureSecurityCQ2Buf;
		break;
	}
	return 0;
}
INT8U CAPDUdata::GetConnectRespones(stuConnectRequest SrcConnectRequest , INT8U * DstBuf , INT16U & DstLen)
{
	SrcConnectRequest.sConnectMechanismInfo.pRasswordSecurityBuf = (INT8U *)malloc((1024)*sizeof(INT8U));
	SrcConnectRequest.sConnectMechanismInfo.pRasswordSecurityBuf[0] = 0x01;
	SrcConnectRequest.sConnectMechanismInfo.pRasswordSecurityBuf[1] = 0x02;
	SrcConnectRequest.sConnectMechanismInfo.pRasswordSecurityBuf[2] = 0x03;
	SrcConnectRequest.sConnectMechanismInfo.pRasswordSecurityBuf[3] = 0x04;
	SrcConnectRequest.sConnectMechanismInfo.pRasswordSecurityBuf[4] = 0x05;
	SrcConnectRequest.sConnectMechanismInfo.pRasswordSecurityBuf[5] = 0x06;
	free(SrcConnectRequest.sConnectMechanismInfo.pRasswordSecurityBuf);
	SrcConnectRequest.sConnectMechanismInfo.pRasswordSecurityBuf = (INT8U *)malloc((1024)*sizeof(INT8U));
	free(SrcConnectRequest.sConnectMechanismInfo.pRasswordSecurityBuf);
	return 0;
}
//GetRequest相关
INT8U CAPDUdata::GetRequest(INT8U * pSrcAPDUbuf, INT16U pSrcAPDUlen ,INT8U * serverbuf, INT16U &serverlen)
{
	INT8U ack = false , n = 0;
	INT16U temp16 = 0;
	serverbuf[0] = pSrcAPDUbuf[0];	//GET-Request∷=CHOICE
	serverbuf[1] = pSrcAPDUbuf[1];	//PIID
	serverlen += 2;
	switch(pSrcAPDUbuf[0])
	{
	case 0x01://GetRequestNormsal
		ack = GetRequestNormsal(&pSrcAPDUbuf[2] , pSrcAPDUlen - 2 , &serverbuf[serverlen] , temp16);
		break;
	case 0x02://GetRequestNormsalList
		ack = GetRequestNormsalList(&pSrcAPDUbuf[2] , pSrcAPDUlen - 2 , &serverbuf[serverlen] , temp16);
		break;
	case 0x03://GetRequestRecord
		ack = GetRequestRecord(&pSrcAPDUbuf[2] , pSrcAPDUlen - 2 , &serverbuf[serverlen] , temp16);
		break;
	case 0x04://GetRequestRecordList
		break;
	case 0x05://GetRequestNext
		break;
	}
	serverlen += temp16;
	return ack;
}
INT8U CAPDUdata::GetRequestNormsal(INT8U * pSrcAPDUbuf, INT16U pSrcAPDUlen , INT8U * serverbuf, INT16U &serverlen)
{
	INT8U ask = 0;
	Data pData;
	long nLong = sizeof(pData);
	OAD pOAD;
	INT8U nChoose = 0;
	INT16U temp16 = 0;
	INT8U i = 0 , j = 0;
	serverbuf[temp16++] = pSrcAPDUbuf[i];
	serverbuf[temp16++] = pSrcAPDUbuf[i + 1]; //OID
	serverbuf[temp16++] = pSrcAPDUbuf[i + 2]; //PID
	serverbuf[temp16++] = pSrcAPDUbuf[i + 3]; //DENT
	pOAD.OID = (pSrcAPDUbuf[i] << 8) | pSrcAPDUbuf[i + 1];
	pOAD.PID = pSrcAPDUbuf[i + 2];
	pOAD.DENT = pSrcAPDUbuf[i + 3];
	i += 4;
	CPhaseValue698 sPhase(m_rambuf , m_bpbuflen , s_rambuflen , m_ramStuData , m_bpStuDatalen , m_ramStuDatalen);
	ask = sPhase.GetClassIDMeterdata(pOAD , pData , nChoose);
	if (0 == ask)
	{
		serverbuf[temp16++] = 0x01;//Data
		serverlen += temp16;
		temp16 = 0;
		CoadAPDU_Data(pData , nChoose , &serverbuf[serverlen] , temp16);
		serverlen += temp16;
	}
	else
	{
		serverbuf[temp16++] = 0x00;//DAR
		serverbuf[temp16++] = ask;
		serverlen += temp16;
	}
	return 0;
}
INT8U CAPDUdata::GetRequestNormsalList(INT8U * pSrcAPDUbuf, INT16U pSrcAPDUlen , INT8U * serverbuf, INT16U &serverlen)
{
	INT8U ack = false , n = 0;
	INT16U temp16 = 0;
	serverbuf[0] = pSrcAPDUbuf[0]; //list个数
	serverlen += 1;
	for (n = 0 ; n < pSrcAPDUbuf[0] ; n++)
	{
		ack = GetRequestNormsal(&pSrcAPDUbuf[1 + 4 * n] , pSrcAPDUlen - 1 - 4 * n , &serverbuf[serverlen] , temp16);
		serverlen += temp16;
		temp16 = 0;
	}
	return 0;
}
INT8U CAPDUdata::GetRequestRecord(INT8U * pSrcAPDUbuf, INT16U pSrcAPDUlen , INT8U * serverbuf, INT16U &serverlen)
{
	OAD sOADFree;
	RSD sRSD;
	RCSD sRCSD;
	A_RecordRow sARecordRow;
	Data sDataRecv;
	
	INT8U n = 0 ,m = 0 ,j = 0;
	INT8U i = 0;
	INT8U RsdChoose = 0 , firtemp = 0 , Sectemp = 0 ,Thrtemp = 0 , srclen = 0;
	INT8U nDataChoose = 0;
	INT16U temp16 = 0;
	INT32U OAD32;
	INT8U RSDbuf[10];
	INT8U RSDbuflen = 0;

	serverbuf[temp16++] = pSrcAPDUbuf[i];
	serverbuf[temp16++] = pSrcAPDUbuf[i + 1];//OID
	serverbuf[temp16++] = pSrcAPDUbuf[i + 2];//PID
	serverbuf[temp16++] = pSrcAPDUbuf[i + 3];//DENT

	sOADFree.OID = (pSrcAPDUbuf[i] << 8) | pSrcAPDUbuf[i + 1];
	sOADFree.PID = pSrcAPDUbuf[i + 2];
	sOADFree.DENT = pSrcAPDUbuf[i + 3];
	i += 4;

	SetBufToRSD(&pSrcAPDUbuf[i] , pSrcAPDUlen - i , sRSD , srclen);
	i += srclen;

	
	sRCSD.sRCSDA = (RCSDA *)malloc(sizeof(RCSDA));
	sRCSD.u8Numb = pSrcAPDUbuf[i++];
	serverbuf[temp16++] = sRCSD.u8Numb; //RCSD 个数
	for (n = 0 ; n < sRCSD.u8Numb ; n++)
	{
		sRCSD.sRCSDA[n].u8Choose = pSrcAPDUbuf[i++];
		serverbuf[temp16++] = sRCSD.sRCSDA[n].u8Choose;
		switch(Sectemp)
		{
		case 0x00:
			serverbuf[temp16++] = pSrcAPDUbuf[i];
			serverbuf[temp16++] = pSrcAPDUbuf[i + 1];
			serverbuf[temp16++] = pSrcAPDUbuf[i + 2];
			serverbuf[temp16++] = pSrcAPDUbuf[i + 3];
			sRCSD.sRCSDA[n].sCSD.sOAD.OID = (pSrcAPDUbuf[i] << 8) | pSrcAPDUbuf[i + 1];
			sRCSD.sRCSDA[n].sCSD.sOAD.PID = pSrcAPDUbuf[i + 2];
			sRCSD.sRCSDA[n].sCSD.sOAD.DENT = pSrcAPDUbuf[i + 3];
			i += 4;
			break;
		}
	}
	serverbuf[temp16++] = 0x01; //记录数据
	serverlen += temp16;
	temp16 = 0;

	switch(sOADFree.OID >> 12)
	{
	case 0x03://事件
		break;
	case 0x05://冻结
		GetClassTest(sOADFree , sRSD , sRCSD , &serverbuf[serverlen] , temp16);
		break;
	}
	serverlen += temp16;
	return 0;
}
void CAPDUdata::SetBufToRSD(INT8U * pSrcAPDUbuf, INT16U pSrcAPDUlen , RSD & pRSD, INT8U &nRSDlen)
{
	INT8U i = 0 , srclen = 0;
	pRSD.nChoose = pSrcAPDUbuf[i++];
	switch(pRSD.nChoose)
	{
	case 0x01: //Selector1
		pRSD.pRSDA.st1.pOAD.OID = (pSrcAPDUbuf[i] << 8) | pSrcAPDUbuf[i + 1];
		pRSD.pRSDA.st1.pOAD.PID = pSrcAPDUbuf[i + 2];
		pRSD.pRSDA.st1.pOAD.DENT = pSrcAPDUbuf[i + 3];
		i += 4;
		DecoadAPDU_Data(&pSrcAPDUbuf[i] , pSrcAPDUlen - i , srclen , pRSD.pRSDA.st1.OADData , pRSD.pRSDA.st1.nDataChoose);
		i += srclen;
		break;
	case 0x09: //Selector9
		 pRSD.pRSDA.st9.u8LastTimes = pSrcAPDUbuf[i++];
		break;
	}
	nRSDlen = i;
}

INT8U CAPDUdata::GetClassTest(OAD SrcOAD , RSD SrcRSD , RCSD SrcRCSD , INT8U * DstBuf , INT16U & DstLen)
{
	INT8U n = 0 , i = 0;
	switch(SrcRSD.nChoose)
	{
	case 1://根据冻结时间找数据
		
		switch(SrcRSD.pRSDA.st1.pOAD.OID)
		{
		case 0x2021:
			//TimeBuf
			break;
		}

		//Databuf

		DstBuf[i++] = 1; //一条记录
		for (n = 0 ; n < SrcRCSD.u8Numb ; n++)
		{
			switch (SrcRCSD.sRCSDA[n].u8Choose)
			{
			case 0:
				switch(SrcRCSD.sRCSDA[n].sCSD.sOAD.OID)
				{
				case 0x2021:
					DstBuf[i++] = 0x1C;
					DstBuf[i++] = 0x20;
					DstBuf[i++] = 0x16;
					DstBuf[i++] = 0x01;
					DstBuf[i++] = 0x20;
					DstBuf[i++] = 0x00;
					DstBuf[i++] = 0x00;
					DstBuf[i++] = 0x00;
					break;
				case 0x0010:
					DstBuf[i++] = 0x01;
					DstBuf[i++] = 0x05;

					DstBuf[i++] = 0x06;
					DstBuf[i++] = 0x00;
					DstBuf[i++] = 0x00;
					DstBuf[i++] = 0x00;
					DstBuf[i++] = 0x00;
					
					DstBuf[i++] = 0x06;
					DstBuf[i++] = 0x00;
					DstBuf[i++] = 0x00;
					DstBuf[i++] = 0x00;
					DstBuf[i++] = 0x00;

					DstBuf[i++] = 0x06;
					DstBuf[i++] = 0x00;
					DstBuf[i++] = 0x00;
					DstBuf[i++] = 0x00;
					DstBuf[i++] = 0x00;

					DstBuf[i++] = 0x06;
					DstBuf[i++] = 0x00;
					DstBuf[i++] = 0x00;
					DstBuf[i++] = 0x00;
					DstBuf[i++] = 0x00;

					DstBuf[i++] = 0x06;
					DstBuf[i++] = 0x00;
					DstBuf[i++] = 0x00;
					DstBuf[i++] = 0x00;
					DstBuf[i++] = 0x00;
					break;
				case 0x0020:
					break;
				}
				break;
			case 1:
				break;
			}
		}

		break;
	case 9://根据上N次找数据
		break;
	}
	DstLen = i;
	return 1;
}

INT8U CAPDUdata::GetClassID9Meterdata(OAD SrcOAD , INT8U * pSrcDatetimeBCD , INT16U SrcDatatimeBCDlen , OAD SrcRCSD_OAD , Data &DstData , INT8U &nDataChoose)
{
	switch(SrcRCSD_OAD.OID)
	{
	case 0x2021:
		nDataChoose = 0x1C;
		(DstData).Datetime_S[0] = 0x20;
		(DstData).Datetime_S[1] = 0x16;
		(DstData).Datetime_S[2] = 0x01;
		(DstData).Datetime_S[3] = 0x20;
		(DstData).Datetime_S[4] = 0x00;
		(DstData).Datetime_S[5] = 0x00;
		(DstData).Datetime_S[6] = 0x00;
		break;
	case 0x0010:
		nDataChoose = 0x01;
		DstData.pArryA.nTimes = 0x05;
		DstData.pArryA.nARRYChoose[0] = 0x06;
		DstData.pArryA.pArry[0].udoublelong = 0x00000000;
		DstData.pArryA.nARRYChoose[1] = 0x06;
		DstData.pArryA.pArry[1].udoublelong = 0x00000000;
		DstData.pArryA.nARRYChoose[2] = 0x06;
		DstData.pArryA.pArry[2].udoublelong = 0x00000000;
		DstData.pArryA.nARRYChoose[3] = 0x06;
		DstData.pArryA.pArry[3].udoublelong = 0x00000000;
		DstData.pArryA.nARRYChoose[4] = 0x06;
		DstData.pArryA.pArry[4].udoublelong = 0x00000000;
		break;
	}
	return 1;
}
INT8U CAPDUdata::GetClassIDMeterdata(OAD SrcOAD , Data & DstData , INT8U &nDataChoose)
{
	INT8U bufAddr[7];
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
//SetRequest相关
INT8U CAPDUdata::SetRequest(INT8U * pSrcAPDUbuf, INT16U pSrcAPDUlen , INT8U * serverbuf, INT16U &serverlen)
{
	INT8U ack = false;
	INT8U srclen = 0;
	INT16U temp16 = 0;
	serverbuf[0] = pSrcAPDUbuf[0];
	serverlen += 1;
	switch(pSrcAPDUbuf[0])
	{
	case 0x01://SetResponseNormal
		ack = SetRequestNormsal(&pSrcAPDUbuf[1] , pSrcAPDUlen - 1 ,srclen , &serverbuf[serverlen] , temp16);
		break;
	case 0x02://SetResponseNormalList
		ack = SetRequestNormsalList(&pSrcAPDUbuf[1] , pSrcAPDUlen - 1 , &serverbuf[serverlen] , temp16);
		break;
	case 0x03://SetThenGetResponseNormalList
		break;
	}
	serverlen += temp16;
	return ack;
}
INT8U CAPDUdata::SetRequestNormsal(INT8U * pSrcAPDUbuf, INT16U pSrcAPDUlen ,INT8U &Srclen ,INT8U * serverbuf, INT16U &serverlen)
{
	DAR pDar;
	INT8U i = 0;
	INT8U nChoose;
	INT16U temp16 = 0;
	OAD pOAD;
	Data pData;
	serverbuf[temp16++] = pSrcAPDUbuf[i++];
	serverbuf[temp16++] = pSrcAPDUbuf[i];
	serverbuf[temp16++] = pSrcAPDUbuf[i + 1];
	serverbuf[temp16++] = pSrcAPDUbuf[i + 2];
	serverbuf[temp16++] = pSrcAPDUbuf[i + 3];
	pOAD.OID = (pSrcAPDUbuf[i] << 8) | pSrcAPDUbuf[i + 1];
	pOAD.PID = pSrcAPDUbuf[i + 2];
	pOAD.DENT = pSrcAPDUbuf[i + 3];
	i += 4;
	DecoadAPDU_Data(&pSrcAPDUbuf[i] , pSrcAPDUlen - i , Srclen , pData , nChoose);
	Srclen += 4;
	SetClassIDMeterdata(pOAD,pData,nChoose,pDar);
	serverbuf[temp16++] = pDar.nNumb;
	serverlen += temp16;
	return 0;
}
INT8U CAPDUdata::SetRequestNormsalList(INT8U * pSrcAPDUbuf, INT16U pSrcAPDUlen ,INT8U * serverbuf, INT16U &serverlen)
{
	INT8U ack = false , n = 0;
	INT8U srtlen = 0 , beginlen = 0;
	INT16U temp16 = 0;
	serverbuf[0] = pSrcAPDUbuf[0]; //list个数
	serverlen += 1;
	for (n = 0 ; n < pSrcAPDUbuf[0] ; n++)
	{
		srtlen = 0;
		ack = SetRequestNormsal(&pSrcAPDUbuf[1 + beginlen] , pSrcAPDUlen - 1 - beginlen ,srtlen , &serverbuf[serverlen] , temp16);
		beginlen += srtlen;
		serverlen += temp16;
		temp16 = 0;
	}
	return 0;
}
INT8U CAPDUdata::SetClassIDMeterdata(OAD SrcOAD , Data DstData , INT8U nDataChoose , DAR & pDAR)
{
	INT8U n = 0;
	switch(SrcOAD.OID)
	{
	case 0x4000:
		switch(SrcOAD.PID)
		{
		case 0x05:
			switch(nDataChoose)
			{
			case 0x02:
				for(n = 0 ; n < DstData.pStructureA.nTimes ; n++)
				{
					switch(DstData.pStructureA.nStructChoose[n])
					{
					case 5:

						break;
					case 6:

						break;
					case 16:

						break;
					case 17:

						break;
					case 18:

						break;
					}
				}

				break;
			case 0x1C:
				//AfxMessageBox(m_tools._buf16tostr16(DstData.DatetimeBCD,7,1,0));
				pDAR.nNumb = 0;
				break;
			}
			break;
		case 02:
			pDAR.nNumb = 0;
			break;
		}
		break;
	}
	return 0;
}
//ActionRequest相关
INT8U CAPDUdata::ActionRequest(INT8U * pSrcAPDUbuf, INT16U pSrcAPDUlen ,INT8U * serverbuf, INT16U &serverlen)
{
	INT8U ack = false , n = 0;
	INT8U srclen = 0;
	INT16U temp16 = 0;
	serverbuf[0] = pSrcAPDUbuf[0];	//GET-Request∷=CHOICE
	serverbuf[1] = pSrcAPDUbuf[1];	//PIID
	serverlen += 2;
	switch(pSrcAPDUbuf[0])
	{
	case 0x01://ActionRequestNormsal
		ack = ActionRequestNormsal(&pSrcAPDUbuf[2] , pSrcAPDUlen - 2 ,srclen , &serverbuf[serverlen] , temp16);
		break;
	case 0x02://ActionRequestNormsallist
		ack = ActionRequestNormsallist(&pSrcAPDUbuf[2] , pSrcAPDUlen - 2 , &serverbuf[serverlen] , temp16);
		break;
	}
	serverlen += temp16;
	return ack;
}
INT8U CAPDUdata::ActionRequestNormsal(INT8U * pSrcAPDUbuf, INT16U pSrcAPDUlen , INT8U &Srclen , INT8U * serverbuf, INT16U &serverlen)
{
	DAR pDar;
	INT8U i = 0;
	INT8U nChoose = 0 ;
	int nDstChoose = 0;
	INT16U temp16 = 0;
	OMD pOMD;
	Data pData;
	Data pDstData;
	serverbuf[temp16++] = pSrcAPDUbuf[i];
	serverbuf[temp16++] = pSrcAPDUbuf[i + 1];
	serverbuf[temp16++] = pSrcAPDUbuf[i + 2];
	serverbuf[temp16++] = pSrcAPDUbuf[i + 3];
	pOMD.OID = (pSrcAPDUbuf[i] << 8) | pSrcAPDUbuf[i + 1];
	pOMD.AID = pSrcAPDUbuf[i + 2];
	pOMD.DENT = pSrcAPDUbuf[i + 3];
	i += 4;
	DecoadAPDU_Data(&pSrcAPDUbuf[i] , pSrcAPDUlen - i ,Srclen , pData , nChoose);

	CString str1 = m_tools._buf16tostr16(pData.pStructureA.pStructrea[0].OctetStringbuf ,pData.pStructureA.pStructrea[0].OctetStringbuf[0] + 1);
	CString str2 = m_tools._buf16tostr16(pData.pStructureA.pStructrea[1].pSID_MAC.pSID.DI ,4);
	CString str3 = m_tools._buf16tostr16(pData.pStructureA.pStructrea[1].pSID_MAC.pSID.SubjoinData ,pData.pStructureA.pStructrea[1].pSID_MAC.pSID.SubjoinData[0] + 1);
	CString str4 = m_tools._buf16tostr16(pData.pStructureA.pStructrea[1].pSID_MAC.MacData ,pData.pStructureA.pStructrea[1].pSID_MAC.MacData[0] + 1);
	AfxMessageBox(str1 + _T("\r\n") + str2 + _T("\r\n") + str3 +_T("\r\n") + str4);
	Srclen += 4;
	ActionClassIDMeterdata(pOMD , pData , nChoose , pDar , nDstChoose , pDstData);
	serverbuf[temp16++] = pDar.nNumb;
	if (nDstChoose == -1)
	{
		serverbuf[temp16++] = 0x00;
	}
	else
	{
		serverbuf[temp16++] = 0x01;
		serverlen += temp16;
		temp16 = 0;
		CoadAPDU_Data(pDstData , nDstChoose , &serverbuf[serverlen] , temp16);
	}
	serverlen += temp16;
	return 0;
}
INT8U CAPDUdata::ActionRequestNormsallist(INT8U * pSrcAPDUbuf, INT16U pSrcAPDUlen , INT8U * serverbuf, INT16U &serverlen)
{
	INT8U ack = false , n = 0;
	INT8U srtlen = 0 , beginlen = 0;
	INT16U temp16 = 0;
	serverbuf[0] = pSrcAPDUbuf[0]; //list个数
	serverlen += 1;
	for (n = 0 ; n < pSrcAPDUbuf[0] ; n++)
	{
		srtlen = 0;
		ack = ActionRequestNormsal(&pSrcAPDUbuf[1 + beginlen] , pSrcAPDUlen - 1 - beginlen ,srtlen , &serverbuf[serverlen] , temp16);
		beginlen += srtlen;
		serverlen += temp16;
		temp16 = 0;
	}
	return 0;
}
INT8U CAPDUdata::ActionClassIDMeterdata(OMD SrcOAD , Data SrcData , INT8U nDataChoose , DAR & pDAR , int & nDstDataChoose , Data &DstData)
{
	INT8U n = 0;
	switch(SrcOAD.OID)
	{
	case 0x0010:
		pDAR.nNumb = 0;
		nDstDataChoose = 0x0F;
		DstData.integer = 1;
		break;
	}
	return 0;
}

//INT8U CAPDUdata::CoadServer_APDU(Server_APDU Srcserverapdu , INT8U * pDSTBuf, INT16U &pDstlen)
//{
//	INT16U utemp16 = 0;
//	INT32U utemp32 = 0;
//	INT8U n = 0 , m = 0 , i = 0;
//	INT8U utemp1 = 0 , utemp2 = 0, utemp3 = 0 , ulen = 0;
//	pDstlen = 0;
//	pDSTBuf[pDstlen++] = (INT8U)Srcserverapdu.nServer_ApplayerChoose;
//	switch(Srcserverapdu.nServer_ApplayerChoose)
//	{
//	case 130:
//		break;
//	case 131:
//		break;
//	case 132:
//		break;
//	case 133:
//		pDSTBuf[pDstlen++] = Srcserverapdu.applayer.getresponseA.GET_ResponseChoose;
//		switch(Srcserverapdu.applayer.getresponseA.GET_ResponseChoose)
//		{
//		case 1://GetResponseNormal
//			pDSTBuf[pDstlen++] = Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormal.PIID_ACD;
//			utemp16 = Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormal.pAResultNormal.pOAD.OID;
//			pDSTBuf[pDstlen++] = (INT8U)(utemp16>>8);
//			pDSTBuf[pDstlen++] = (INT8U) utemp16;
//			pDSTBuf[pDstlen++] = Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormal.pAResultNormal.pOAD.PID;
//			pDSTBuf[pDstlen++] = Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormal.pAResultNormal.pOAD.DENT;
//
//			utemp1 = Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormal.pAResultNormal.nGetResultChoose;
//			pDSTBuf[pDstlen++] = utemp1;
//			switch(utemp1)
//			{
//			case 0://错误信息  [0]   DAR，
//				break;
//			case 1://数据      [1]   Data
//				utemp1 = Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormal.pAResultNormal.pGet_Result.nDataChoose;
//				pDSTBuf[pDstlen++] = utemp1;
//				switch(utemp1)
//				{
//				case 0x00:
//					break;
//				case 0x01://array	[1] 
//					utemp1 = Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormal.pAResultNormal.pGet_Result.pData.pArryA.nTimes;
//					pDSTBuf[pDstlen++] = utemp1;
//					for(n = 0; n< utemp1 ; n++)
//					{
//						utemp2 = Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormal.pAResultNormal.pGet_Result.pData.pArryA.nARRYChoose[n];
//						pDSTBuf[pDstlen++] = utemp2;
//						switch(utemp2)
//						{
//						case 0x02:
//							utemp2 = Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormal.pAResultNormal.pGet_Result.pData.pArryA.pArry[n].pStructureA.nTimes;
//							pDSTBuf[pDstlen++] = utemp2;
//							for (m = 0 ; m < utemp2 ; m++)
//							{
//								utemp3 = Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormal.pAResultNormal.pGet_Result.pData.pArryA.pArry[n].pStructureA.nStructChoose[m];
//								pDSTBuf[pDstlen++] = utemp3;
//								switch(utemp3)
//								{
//								case 0x05:
//									DoublongTobuf(Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormal.pAResultNormal.pGet_Result.pData.pArryA.pArry[n].pStructureA.pStructrea[m].doublelong , &pDSTBuf[pDstlen],ulen);
//									pDstlen += ulen;
//									break;
//								case 0x06:
//									uDoublongTobuf(Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormal.pAResultNormal.pGet_Result.pData.pArryA.pArry[n].pStructureA.pStructrea[m].udoublelong,&pDSTBuf[pDstlen],ulen);
//									pDstlen += ulen;
//									break;
//								case 0x10:
//									longTobuf(Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormal.pAResultNormal.pGet_Result.pData.pArryA.pArry[n].pStructureA.pStructrea[m].long16,&pDSTBuf[pDstlen],ulen);
//									pDstlen += ulen;
//									break;
//								case 0x11:
//									pDSTBuf[pDstlen++] = Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormal.pAResultNormal.pGet_Result.pData.pArryA.pArry[n].pStructureA.pStructrea[m].unsign;
//									break;
//								case 0x12:
//									ulongTobuf(Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormal.pAResultNormal.pGet_Result.pData.pArryA.pArry[n].pStructureA.pStructrea[m].ulong,&pDSTBuf[pDstlen],ulen);
//									pDstlen += ulen;
//									break;
//								case 0x1c:
//									pDSTBuf[pDstlen++] = Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormal.pAResultNormal.pGet_Result.pData.pArryA.pArry[n].pStructureA.pStructrea[m].DateTimeBCD_S[0];
//									pDSTBuf[pDstlen++] = Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormal.pAResultNormal.pGet_Result.pData.pArryA.pArry[n].pStructureA.pStructrea[m].DateTimeBCD_S[1];
//									pDSTBuf[pDstlen++] = Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormal.pAResultNormal.pGet_Result.pData.pArryA.pArry[n].pStructureA.pStructrea[m].DateTimeBCD_S[2];
//									pDSTBuf[pDstlen++] = Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormal.pAResultNormal.pGet_Result.pData.pArryA.pArry[n].pStructureA.pStructrea[m].DateTimeBCD_S[3];
//									pDSTBuf[pDstlen++] = Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormal.pAResultNormal.pGet_Result.pData.pArryA.pArry[n].pStructureA.pStructrea[m].DateTimeBCD_S[4];
//									pDSTBuf[pDstlen++] = Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormal.pAResultNormal.pGet_Result.pData.pArryA.pArry[n].pStructureA.pStructrea[m].DateTimeBCD_S[5];
//									pDSTBuf[pDstlen++] = Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormal.pAResultNormal.pGet_Result.pData.pArryA.pArry[n].pStructureA.pStructrea[m].DateTimeBCD_S[6];
//									break;
//								}
//							}
//							break;
//						case 0x05:
//							DoublongTobuf(Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormal.pAResultNormal.pGet_Result.pData.pArryA.pArry[n].doublelong ,  &pDSTBuf[pDstlen] , ulen);
//							pDstlen += ulen;
//							break;
//						case 0x06:
//							uDoublongTobuf(Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormal.pAResultNormal.pGet_Result.pData.pArryA.pArry[n].udoublelong,&pDSTBuf[pDstlen],ulen);
//							pDstlen += ulen;
//							break;
//						case 0x10:
//							longTobuf(Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormal.pAResultNormal.pGet_Result.pData.pArryA.pArry[n].long16,&pDSTBuf[pDstlen],ulen);
//							pDstlen += ulen;
//							break;
//						case 0x11:
//							pDSTBuf[pDstlen++] = Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormal.pAResultNormal.pGet_Result.pData.pArryA.pArry[n].unsign;
//							break;
//						case 0x12:
//							ulongTobuf(Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormal.pAResultNormal.pGet_Result.pData.pArryA.pArry[n].long16,&pDSTBuf[pDstlen],ulen);
//							pDstlen += ulen;
//							break;
//						}
//					}
//					break;
//				case 0x05:
//					DoublongTobuf(Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormal.pAResultNormal.pGet_Result.pData.doublelong ,  &pDSTBuf[pDstlen] , ulen);
//					pDstlen += ulen;
//					break;
//				case 0x06:
//					uDoublongTobuf(Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormal.pAResultNormal.pGet_Result.pData.udoublelong,&pDSTBuf[pDstlen],ulen);
//					pDstlen += ulen;
//					break;
//				case 0x10:
//					longTobuf(Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormal.pAResultNormal.pGet_Result.pData.long16,&pDSTBuf[pDstlen],ulen);
//					pDstlen += ulen;
//					break;
//				case 0x11:
//					pDSTBuf[pDstlen++] = Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormal.pAResultNormal.pGet_Result.pData.unsign;
//					break;
//				case 0x12:
//					ulongTobuf(Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormal.pAResultNormal.pGet_Result.pData.long16,&pDSTBuf[pDstlen],ulen);
//					pDstlen += ulen;
//					break;
//				case 0x55:
//					pDSTBuf[pDstlen++] = Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormal.pAResultNormal.pGet_Result.pData.pTSA.buflen;
//					for (n = 0 ;n < Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormal.pAResultNormal.pGet_Result.pData.pTSA.buflen ; n++)
//					{
//						pDSTBuf[pDstlen++] = Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormal.pAResultNormal.pGet_Result.pData.pTSA.bufAddr[n];
//					}
//					break;
//				
//				}
//				break;
//			}
//			break;
//		case 2://GetResponseNormalList
//			/*pDSTBuf[pDstlen++] = Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormalList.PIID_ACD;
//			pDSTBuf[pDstlen++] = Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormalList.nTimes;
//			for(n = 0 ; n < Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormalList.nTimes ; n++)
//			{
//			utemp16 = Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormalList.pAResultNormal[n].pOAD.OID;
//			pDSTBuf[pDstlen++] = (INT8U)(utemp16>>8);
//			pDSTBuf[pDstlen++] = (INT8U) utemp16;
//			pDSTBuf[pDstlen++] = Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormalList.pAResultNormal[n].pOAD.PID;
//			pDSTBuf[pDstlen++] = Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormalList.pAResultNormal[n].pOAD.DENT;
//			pDSTBuf[pDstlen++] = Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormalList.pAResultNormal[n].nGetResultChoose;
//			switch(Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormalList.pAResultNormal[n].nGetResultChoose)
//			{
//			case 0:
//			break;
//			case 1:
//			pDSTBuf[pDstlen++] = Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormalList.pAResultNormal[n].pGet_Result.nDataChoose;
//			switch(Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormalList.pAResultNormal[n].pGet_Result.nDataChoose)
//			{
//			case 0x01:
//			pDSTBuf[pDstlen++] = Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormalList.pAResultNormal[n].pGet_Result.pData.pArryA.nTimes;
//			for (m = 0;m < Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormalList.pAResultNormal[n].pGet_Result.pData.pArryA.nTimes ;m++)
//			{
//			pDSTBuf[pDstlen++] = Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormalList.pAResultNormal[n].pGet_Result.pData.pArryA.nARRYChoose[m];
//			switch(Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormalList.pAResultNormal[n].pGet_Result.pData.pArryA.nARRYChoose[m])
//			{
//			case 0x05:
//			utemp32 = Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormalList.pAResultNormal[n].pGet_Result.pData.pArryA.pArry[m].udoublelong;
//			pDSTBuf[pDstlen++] = (INT8U)(utemp32 >> 24);
//			pDSTBuf[pDstlen++] = (INT8U)(utemp32 >> 16);
//			pDSTBuf[pDstlen++] = (INT8U)(utemp32 >> 8);
//			pDSTBuf[pDstlen++] = (INT8U)(utemp32 >> 0);
//			break;
//			case 0x12:
//			utemp16 = Srcserverapdu.applayer.getresponseA.getresponse.pGetResponseNormalList.pAResultNormal[n].pGet_Result.pData.pArryA.pArry[m].ulong;
//			pDSTBuf[pDstlen++] = (INT8U)(utemp16>>8);
//			pDSTBuf[pDstlen++] = (INT8U) utemp16;
//			break;
//			}
//			}
//			break;
//			}
//			break;
//			}
//			}*/
//			break;
//		case 3://GetResponseRecord
//			pDSTBuf[pDstlen++] = Srcserverapdu.applayer.getresponseA.getresponse.gresponserecord.PIID_ACD;
//			pDSTBuf[pDstlen++] = Srcserverapdu.applayer.getresponseA.getresponse.gresponserecord.nA_ResultRecordChoose;
//			switch(Srcserverapdu.applayer.getresponseA.getresponse.gresponserecord.nA_ResultRecordChoose)
//			{
//			case 0:
//				break;
//			case 1:
//				utemp16 = Srcserverapdu.applayer.getresponseA.getresponse.gresponserecord.resultRecord.recorddata.pOAD.OID;
//				pDSTBuf[pDstlen++] = (INT8U)(utemp16>>8);
//				pDSTBuf[pDstlen++] = (INT8U) utemp16;
//				pDSTBuf[pDstlen++] = Srcserverapdu.applayer.getresponseA.getresponse.gresponserecord.resultRecord.recorddata.pOAD.PID;
//				pDSTBuf[pDstlen++] = Srcserverapdu.applayer.getresponseA.getresponse.gresponserecord.resultRecord.recorddata.pOAD.DENT;
//				pDSTBuf[pDstlen++] = Srcserverapdu.applayer.getresponseA.getresponse.gresponserecord.resultRecord.recorddata.pRCSD.nTimes;
//				for (n = 0 ; n < Srcserverapdu.applayer.getresponseA.getresponse.gresponserecord.resultRecord.recorddata.pRCSD.nTimes ; n++)
//				{
//					pDSTBuf[pDstlen++] = Srcserverapdu.applayer.getresponseA.getresponse.gresponserecord.resultRecord.recorddata.pRCSD.nCSDChoose[n];
//					switch(Srcserverapdu.applayer.getresponseA.getresponse.gresponserecord.resultRecord.recorddata.pRCSD.nCSDChoose[n])
//					{
//					case 0:
//						utemp16 = Srcserverapdu.applayer.getresponseA.getresponse.gresponserecord.resultRecord.recorddata.pRCSD.pCSD[n].pOAD.OID;
//						pDSTBuf[pDstlen++] = (INT8U)(utemp16>>8);
//						pDSTBuf[pDstlen++] = (INT8U) utemp16;
//						pDSTBuf[pDstlen++] = Srcserverapdu.applayer.getresponseA.getresponse.gresponserecord.resultRecord.recorddata.pRCSD.pCSD[n].pOAD.PID;
//						pDSTBuf[pDstlen++] = Srcserverapdu.applayer.getresponseA.getresponse.gresponserecord.resultRecord.recorddata.pRCSD.pCSD[n].pOAD.DENT;
//						break;
//					case 1:
//						break;
//					}
//
//				}
//				pDSTBuf[pDstlen++] = Srcserverapdu.applayer.getresponseA.getresponse.gresponserecord.resultRecord.recorddata.nTimes;
//				for (n = 0; n < Srcserverapdu.applayer.getresponseA.getresponse.gresponserecord.resultRecord.recorddata.nTimes ; n++)
//				{
//					//pDSTBuf[pDstlen++] = Srcserverapdu.applayer.getresponseA.getresponse.gresponserecord.resultRecord.recorddata.recordrow[n].nTimes;
//					for (m = 0; m < Srcserverapdu.applayer.getresponseA.getresponse.gresponserecord.resultRecord.recorddata.recordrow[n].nTimes ; m++)
//					{
//						pDSTBuf[pDstlen++] = Srcserverapdu.applayer.getresponseA.getresponse.gresponserecord.resultRecord.recorddata.recordrow[n].nDataChoose[m];
//						switch (Srcserverapdu.applayer.getresponseA.getresponse.gresponserecord.resultRecord.recorddata.recordrow[n].nDataChoose[m])
//						{
//						case 0x01:
//							pDSTBuf[pDstlen++] = Srcserverapdu.applayer.getresponseA.getresponse.gresponserecord.resultRecord.recorddata.recordrow[n].pData[m].pArryA.nTimes;
//							for (i = 0 ; i < Srcserverapdu.applayer.getresponseA.getresponse.gresponserecord.resultRecord.recorddata.recordrow[n].pData[m].pArryA.nTimes ; i++)
//							{
//								pDSTBuf[pDstlen++] = Srcserverapdu.applayer.getresponseA.getresponse.gresponserecord.resultRecord.recorddata.recordrow[n].pData[m].pArryA.nARRYChoose[i];
//								switch (Srcserverapdu.applayer.getresponseA.getresponse.gresponserecord.resultRecord.recorddata.recordrow[n].pData[m].pArryA.nARRYChoose[i])
//								{
//								case 0x06:
//									utemp32 = Srcserverapdu.applayer.getresponseA.getresponse.gresponserecord.resultRecord.recorddata.recordrow[n].pData[m].pArryA.pArry[i].udoublelong;
//									pDSTBuf[pDstlen++] = (INT8U)(utemp32 >> 24);
//									pDSTBuf[pDstlen++] = (INT8U)(utemp32 >> 16);
//									pDSTBuf[pDstlen++] = (INT8U)(utemp32 >> 8);
//									pDSTBuf[pDstlen++] = (INT8U)(utemp32 >> 0);
//									break;
//								}
//							}
//							break;
//						case 0x1C:
//							for (i = 0 ; i < 7 ; i++)
//							{
//								pDSTBuf[pDstlen++] = Srcserverapdu.applayer.getresponseA.getresponse.gresponserecord.resultRecord.recorddata.recordrow[n].pData[m].DatetimeBCD[i];
//							}
//							break;
//						}
//					}
//				}
//				break;
//			}
//			break;
//		case 4:
//			break;
//		case 5:
//			break;
//		}
//		break;
//	case 134:
//		pDSTBuf[pDstlen++] = Srcserverapdu.applayer.setresponseA.nSET_ResponseChoose;
//		switch (Srcserverapdu.applayer.setresponseA.nSET_ResponseChoose)
//		{
//		case 1://SetResponseNormal
//			pDSTBuf[pDstlen++] = Srcserverapdu.applayer.setresponseA.pSET_Response.pSetResponseNormal.PIID_ACD;
//			utemp16 = Srcserverapdu.applayer.setresponseA.pSET_Response.pSetResponseNormal.pMSetResponseOAD.pOAD.OID;
//			pDSTBuf[pDstlen++] = (INT8U)(utemp16>>8);
//			pDSTBuf[pDstlen++] = (INT8U) utemp16;
//			pDSTBuf[pDstlen++] = Srcserverapdu.applayer.setresponseA.pSET_Response.pSetResponseNormal.pMSetResponseOAD.pOAD.PID;
//			pDSTBuf[pDstlen++] = Srcserverapdu.applayer.setresponseA.pSET_Response.pSetResponseNormal.pMSetResponseOAD.pOAD.DENT;
//			pDSTBuf[pDstlen++] = Srcserverapdu.applayer.setresponseA.pSET_Response.pSetResponseNormal.pMSetResponseOAD.pDAR.nNumb;
//			break;
//		case 2://SetResponseNormalList
//			break;
//		case 3://SetThenGetResponseNormalList
//			break;
//		}
//		break;
//	case 135:
//		break;
//	case 136:
//		break;
//	case 137:
//		break;
//	}
//	if (!Srcserverapdu.breport)
//	{
//		pDSTBuf[pDstlen++] = 0x00;
//	}
//	if (!Srcserverapdu.btimeTag)
//	{
//		pDSTBuf[pDstlen++] = 0x00;
//	}
//	return 0;
//}

//INT8U CAPDUdata::DecoadClient_APDU(INT8U * pSrcAPDUbuf , INT16U pSrcAPDUlen , Client_APDU &clientapdu , Server_APDU &serverapdu )
//{
//	INT8U ack = false;
//	clientapdu.nClient_ApplayerChoose = pSrcAPDUbuf[0];
//	switch (pSrcAPDUbuf[0])
//	{
//	case 0x02:
//
//		break;
//	case 0x05:
//		serverapdu.nServer_ApplayerChoose = 0x85;
//		m_ServerAPDUBuf[m_ServerAPDUlen++] = 0x85;
//		ack = GetRequest(&pSrcAPDUbuf[1] , pSrcAPDUlen - 1 , clientapdu , serverapdu);
//		break;
//	case 0x06:
//		serverapdu.nServer_ApplayerChoose = 0x86;
//		m_ServerAPDUBuf[m_ServerAPDUlen++] = 0x86;
//		ack = SetRequest(&pSrcAPDUbuf[1] , pSrcAPDUlen - 1 , clientapdu , serverapdu);
//		break;
//	case 0x07:
//		break;
//	}
//	return ack;
//}
//INT8U CAPDUdata::GetRequest(INT8U * pSrcAPDUbuf, INT16U pSrcAPDUlen , Client_APDU &clientapdu , Server_APDU &serverapdu)
//{
//	INT8U ack = false;
//	clientapdu.applayer.getrequestA.nGET_RequestChoose = pSrcAPDUbuf[0];
//	serverapdu.applayer.getresponseA.GET_ResponseChoose = pSrcAPDUbuf[0];
//	m_ServerAPDUBuf[m_ServerAPDUlen++] = pSrcAPDUbuf[0];
//	switch(pSrcAPDUbuf[0])
//	{
//	case 0x01://GetRequestNormsal
//		ack = GetRequestNormsal(&pSrcAPDUbuf[1] , pSrcAPDUlen - 1 , clientapdu , serverapdu);
//		break;
//	case 0x02://GetRequestNormsalList
//		ack = GetRequestNormsalList(&pSrcAPDUbuf[1] , pSrcAPDUlen - 1 , clientapdu , serverapdu);
//		break;
//	case 0x03://GetRequestRecord
//		ack = GetRequestRecord(&pSrcAPDUbuf[1] , pSrcAPDUlen - 1 , clientapdu , serverapdu);
//		break;
//	case 0x04://GetRequestRecordList
//		break;
//	case 0x05://GetRequestNext
//		break;
//	}
//	return ack;
//}
//INT8U CAPDUdata::GetRequestNormsal(INT8U * pSrcAPDUbuf, INT16U pSrcAPDUlen , Client_APDU &clientapdu , Server_APDU &serverapdu)
//{
//	Data pData;
//	INT8U nChoose = 0;
//	INT16U temp16 = 0;
//	INT8U i = 0;
//	
//	clientapdu.applayer.getrequestA.getrequest.normal.PIID = pSrcAPDUbuf[i];
//	serverapdu.applayer.getresponseA.getresponse.pGetResponseNormal.PIID_ACD = pSrcAPDUbuf[i++];
//	clientapdu.applayer.getrequestA.getrequest.normal.pOAD.OID = (pSrcAPDUbuf[i] << 8) | pSrcAPDUbuf[i + 1];
//	clientapdu.applayer.getrequestA.getrequest.normal.pOAD.PID = pSrcAPDUbuf[i + 2];
//	clientapdu.applayer.getrequestA.getrequest.normal.pOAD.DENT = pSrcAPDUbuf[i + 3];
//	i += 4;
//	GetClassIDMeterdata(clientapdu.applayer.getrequestA.getrequest.normal.pOAD,pData,nChoose);
//	serverapdu.applayer.getresponseA.getresponse.pGetResponseNormal.pAResultNormal.pOAD = clientapdu.applayer.getrequestA.getrequest.normal.pOAD;
//	serverapdu.applayer.getresponseA.getresponse.pGetResponseNormal.pAResultNormal.nGetResultChoose = 1;
//	serverapdu.applayer.getresponseA.getresponse.pGetResponseNormal.pAResultNormal.pGet_Result.nDataChoose = nChoose;
//	serverapdu.applayer.getresponseA.getresponse.pGetResponseNormal.pAResultNormal.pGet_Result.pData = pData;
//	return 0;
//}

//INT8U CAPDUdata::GetRequestRecord(INT8U * pSrcAPDUbuf, INT16U pSrcAPDUlen , Client_APDU &clientapdu , Server_APDU &serverapdu)
//{
//	INT8U n = 0 ,m = 0 ,j = 0;
//	INT8U i = 0;
//	INT8U firtemp = 0 , Sectemp = 0 ,Thrtemp = 0;
//	Data sDataRecv;
//	INT8U nDataChoose = 0;
//	clientapdu.applayer.getrequestA.getrequest.grequestrecord.PIID = pSrcAPDUbuf[i];
//	serverapdu.applayer.getresponseA.getresponse.gresponserecord.PIID_ACD = pSrcAPDUbuf[i++];
//
//
//	clientapdu.applayer.getrequestA.getrequest.grequestrecord.getRecd.pOAD.OID = (pSrcAPDUbuf[i] << 8) | pSrcAPDUbuf[i + 1];
//	clientapdu.applayer.getrequestA.getrequest.grequestrecord.getRecd.pOAD.PID = pSrcAPDUbuf[i + 2];
//	clientapdu.applayer.getrequestA.getrequest.grequestrecord.getRecd.pOAD.DENT = pSrcAPDUbuf[i + 3];
//	i += 4;
//
//	firtemp = pSrcAPDUbuf[i++];
//	clientapdu.applayer.getrequestA.getrequest.grequestrecord.getRecd.nRSDChoose = firtemp;
//	switch (firtemp)
//	{
//	case 1:
//		clientapdu.applayer.getrequestA.getrequest.grequestrecord.getRecd.pRSD.st1.pOAD.OID = (pSrcAPDUbuf[i] << 8) | pSrcAPDUbuf[i + 1];
//		clientapdu.applayer.getrequestA.getrequest.grequestrecord.getRecd.pRSD.st1.pOAD.PID = pSrcAPDUbuf[i + 2];
//		clientapdu.applayer.getrequestA.getrequest.grequestrecord.getRecd.pRSD.st1.pOAD.DENT = pSrcAPDUbuf[i + 3];
//		i += 4;
//
//		firtemp = pSrcAPDUbuf[i++];
//		clientapdu.applayer.getrequestA.getrequest.grequestrecord.getRecd.pRSD.st1.nDataChoose = firtemp;
//		switch (firtemp)
//		{
//		case 0x1C:
//			for (n = 0; n < 7 ;n++)
//			{
//				clientapdu.applayer.getrequestA.getrequest.grequestrecord.getRecd.pRSD.st1.OADData.DatetimeBCD[n] = pSrcAPDUbuf[i++];
//			}
//			break;
//		}
//		serverapdu.applayer.getresponseA.getresponse.gresponserecord.resultRecord.recorddata.nTimes = 1;
//
//		firtemp = pSrcAPDUbuf[i++];
//		clientapdu.applayer.getrequestA.getrequest.grequestrecord.getRecd.pRCSD.nTimes = firtemp;
//		for (n = 0 ; n < firtemp ; n++)
//		{
//			Sectemp = pSrcAPDUbuf[i++];
//			clientapdu.applayer.getrequestA.getrequest.grequestrecord.getRecd.pRCSD.nCSDChoose[n] = Sectemp;
//			switch (Sectemp)
//			{
//			case 0:
//				clientapdu.applayer.getrequestA.getrequest.grequestrecord.getRecd.pRCSD.pCSD[n].pOAD.OID = (pSrcAPDUbuf[i] << 8) | pSrcAPDUbuf[i + 1];
//				clientapdu.applayer.getrequestA.getrequest.grequestrecord.getRecd.pRCSD.pCSD[n].pOAD.PID = pSrcAPDUbuf[i + 2];
//				clientapdu.applayer.getrequestA.getrequest.grequestrecord.getRecd.pRCSD.pCSD[n].pOAD.DENT = pSrcAPDUbuf[i + 3];
//				i += 4;
//				break;
//			case 1:
//				//(*clientapdu).applayer.getrequest.grequestrecord.getRecd.pOAD
//				//(*clientapdu).applayer.getrequest.grequestrecord.getRecd.pRSD
//				//(*clientapdu).applayer.getrequest.grequestrecord.getRecd.pRCSD.pCSD[n].pROAD
//				break;
//			}
//		}
//
//		for (n = 0 ; n < firtemp ; n++)
//		{
//			GetClassID9Meterdata(clientapdu.applayer.getrequestA.getrequest.grequestrecord.getRecd.pOAD,
//				clientapdu.applayer.getrequestA.getrequest.grequestrecord.getRecd.pRSD.st1.OADData.DatetimeBCD, 7,
//				clientapdu.applayer.getrequestA.getrequest.grequestrecord.getRecd.pRCSD.pCSD[n].pOAD,
//				sDataRecv , nDataChoose);
//			serverapdu.applayer.getresponseA.getresponse.gresponserecord.resultRecord.recorddata.recordrow[0].nDataChoose[m] = nDataChoose;
//			serverapdu.applayer.getresponseA.getresponse.gresponserecord.resultRecord.recorddata.recordrow[0].pData[m] = sDataRecv;
//			m += 1;
//		}
//		serverapdu.applayer.getresponseA.getresponse.gresponserecord.resultRecord.recorddata.recordrow[0].nTimes = m;
//		break;
//	case 2:
//		break;
//	case 5:
//		/*for(n = 0 ;n < 7 ;n++)
//		{
//		clientapdu.applayer.getrequest.grequestrecord.getRecd.pRSD.st5.datatimeBCD[n] = pSrcAPDUbuf[i++];
//		}
//		firtemp = pSrcAPDUbuf[i++];
//		clientapdu.applayer.getrequest.grequestrecord.getRecd.pRSD.st5.pMS.nNumb = firtemp;
//		switch(firtemp)
//		{
//		case 0x03:
//		Sectemp = pSrcAPDUbuf[i++];
//		clientapdu.applayer.getrequest.grequestrecord.getRecd.pRSD.st5.pMS.nTSA = Sectemp;
//		for(n = 0 ;n < Sectemp ;n++)
//		{
//		Thrtemp = pSrcAPDUbuf[i++];
//		clientapdu.applayer.getrequest.grequestrecord.getRecd.pRSD.st5.pMS.pTSA[n].nNumb = Thrtemp;
//		serverapdu.applayer.getresponse.gresponserecord.resultRecord.recorddata.nTimes = Thrtemp;
//		for(m = 0 ;m < Thrtemp ; m++)
//		{
//		clientapdu.applayer.getrequest.grequestrecord.getRecd.pRSD.st5.pMS.pTSA[n].bufAddr[m] = pSrcAPDUbuf[i++];
//		}
//
//		firtemp = pSrcAPDUbuf[i++];
//		clientapdu.applayer.getrequest.grequestrecord.getRecd.pRCSD.nTimes = firtemp;
//		for (m = 0 ; m < firtemp ; m++)
//		{
//		Sectemp = pSrcAPDUbuf[i++];
//		clientapdu.applayer.getrequest.grequestrecord.getRecd.pRCSD.pCSD[m].nNumb = Sectemp;
//		switch (Sectemp)
//		{
//		case 0:
//		clientapdu.applayer.getrequest.grequestrecord.getRecd.pRCSD.pCSD[m].pOAD.OID = (pSrcAPDUbuf[i] << 8) | pSrcAPDUbuf[i + 1];
//		clientapdu.applayer.getrequest.grequestrecord.getRecd.pRCSD.pCSD[m].pOAD.PID = pSrcAPDUbuf[i + 2];
//		clientapdu.applayer.getrequest.grequestrecord.getRecd.pRCSD.pCSD[m].pOAD.DENT = pSrcAPDUbuf[i + 3];
//		i += 4;
//
//		GetClassIDTrecdata(clientapdu.applayer.getrequest.grequestrecord.getRecd.pOAD , 
//		clientapdu.applayer.getrequest.grequestrecord.getRecd.pRSD.st5.datatimeBCD , 7 , 
//		clientapdu.applayer.getrequest.grequestrecord.getRecd.pRSD.st5.pMS.pTSA[n].bufAddr , 
//		serverapdu.applayer.getresponse.gresponserecord.resultRecord.recorddata.nTimes , 
//		clientapdu.applayer.getrequest.grequestrecord.getRecd.pRCSD.pCSD[m].pOAD , 
//		&sDataRecv);
//		break;
//		case 1:
//		clientapdu.applayer.getrequest.grequestrecord.getRecd.pRCSD.pCSD[m].pROAD.pOAD.PID = (pSrcAPDUbuf[i] << 8) | pSrcAPDUbuf[i + 1];
//		clientapdu.applayer.getrequest.grequestrecord.getRecd.pRCSD.pCSD[m].pROAD.pOAD.PID = pSrcAPDUbuf[i + 2];
//		clientapdu.applayer.getrequest.grequestrecord.getRecd.pRCSD.pCSD[m].pROAD.pOAD.DENT = pSrcAPDUbuf[i + 3];
//		i += 4;
//		clientapdu.applayer.getrequest.grequestrecord.getRecd.pRCSD.pCSD[m].pROAD.nTimes = pSrcAPDUbuf[i++];
//		for (j = 0;j < clientapdu.applayer.getrequest.grequestrecord.getRecd.pRCSD.pCSD[m].pROAD.nTimes; j++)
//		{
//		clientapdu.applayer.getrequest.grequestrecord.getRecd.pRCSD.pCSD[m].pROAD.arryOAD[j].OID = (pSrcAPDUbuf[i] << 8) | pSrcAPDUbuf[i + 1];
//		clientapdu.applayer.getrequest.grequestrecord.getRecd.pRCSD.pCSD[m].pROAD.arryOAD[j].PID = pSrcAPDUbuf[i + 2];
//		clientapdu.applayer.getrequest.grequestrecord.getRecd.pRCSD.pCSD[m].pROAD.arryOAD[j].DENT = pSrcAPDUbuf[i + 3];
//		i += 4;
//		}
//		GetClassIDTrecdata(clientapdu.applayer.getrequest.grequestrecord.getRecd.pOAD , 
//		clientapdu.applayer.getrequest.grequestrecord.getRecd.pRSD.st5.datatimeBCD , 7 , 
//		clientapdu.applayer.getrequest.grequestrecord.getRecd.pRSD.st5.pMS.pTSA[n].bufAddr , 
//		serverapdu.applayer.getresponse.gresponserecord.resultRecord.recorddata.nTimes , 
//		clientapdu.applayer.getrequest.grequestrecord.getRecd.pRCSD.pCSD[m].pROAD , 
//		&sDataRecv);
//		break;
//		}
//
//
//		}
//		}
//			
//			break;
//		}*/
//		break;
//	}
//	
//	serverapdu.applayer.getresponseA.getresponse.gresponserecord.nA_ResultRecordChoose = 1;
//	serverapdu.applayer.getresponseA.getresponse.gresponserecord.resultRecord.recorddata.pOAD = clientapdu.applayer.getrequestA.getrequest.grequestrecord.getRecd.pOAD;
//	serverapdu.applayer.getresponseA.getresponse.gresponserecord.resultRecord.recorddata.pRCSD = clientapdu.applayer.getrequestA.getrequest.grequestrecord.getRecd.pRCSD;
//	return 0;
//}


