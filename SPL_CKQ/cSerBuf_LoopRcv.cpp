
/*---------------------------------------------------------------------------------
* Copyright (c)  2016 TENHE  TECHNOLOGY
* All rights reserved.
*
* 文件名称SerBuf_LoopRcv.cpp

* 摘    要： 循环缓冲接收区没有发送
*
* 当前版本：V1.0
* 作    者：杨虎岳
* 完成日期：2016年6月29日
*
* 取代版本：
* 原 作 者：
* 完成日期：
*------------------------------------------------------------------------------*/
#include "stdafx.h"
#include "cSerBuf_LoopRcv.h"

//循坏缓冲区,只有接收,没有发送
cSerBuf_LoopRcv :: cSerBuf_LoopRcv(INT8U *rcvbuf, INT16U rcvlen)
{
	m_BufRcvMaxData=rcvlen;
	BufRcv=rcvbuf;
	m_RcvOut=0;
	m_RcvIn=0;
}
//-------------------------------------------------------------------------------------------------------
// 函数名称: LoopReadRcvBufNByte(INT16U vSrcLen,INT8U *vDstBuf)
// 功能描述: 从接收缓冲区中，读数据。 缓冲区数据>=vSrcLen，返回vSrcLen个数据.
//           如果缓冲区数据<vSrcLen,返回缓冲区实际的数据个数。
 // 参数描述:
//      输　入: 
//           INT16U vSrcLen:vDstBuf数据区最大长度
//           INT8U *vDstBuf : 数据区指针
//      输　出: 
//   
// return :  从接收缓冲区中，读到的数据长度
// 全局变量: 无
//创 建  人: 杨虎岳
//日     期: 2006年6月16日
//-------------------------------------------------------------------------------------------------------
//修改人:
//日　期:
//------------------------------------------------------------------------------------------------------

INT16U  cSerBuf_LoopRcv::LoopReadRcvBufNByte(INT16U vSrcLen,INT8U *vDstBuf)
{
	INT16U len16=0;
	if(m_RcvIn>=m_RcvOut)
		len16=m_RcvIn-m_RcvOut;
	else
		len16=m_BufRcvMaxData+m_RcvIn-m_RcvOut;
	
	if (len16 > vSrcLen)
	{
		len16 = vSrcLen;
	}

	for(INT16U m=0; m<len16; m++)
	{
		vDstBuf[m] = BufRcv[ m_RcvOut]; 
		m_RcvOut++;                                       /* 调整出队指针 */
		if (m_RcvOut >=  m_BufRcvMaxData)
		{
			m_RcvOut =0;
		}
	}
	return len16;
}
//-------------------------------------------------------------------------------------------------------
// 函数名称: InPutRcvByte(INT8U Data)
// 功能描述: 往缓冲区写一个字节数据，一般是中断调用
// 参数描述:
//     输　入: 
//        INT8U Data：数据
//      
//     输　出: 
//   
// return :  DACK_SUCESS，DACK_ERR_FULL
// 全局变量: 无
//创 建  人: 杨虎岳
//日     期: 2006年6月16日
//-------------------------------------------------------------------------------------------------------
//修改人:
//日　期:
//------------------------------------------------------------------------------------------------------
INT8U  cSerBuf_LoopRcv :: InPutRcvByte(INT8U Data)
{
	INT8U  err=DACK_SUCESS;
	INT16U RcvNData;
	
	if(m_RcvIn>=m_RcvOut)
		RcvNData=m_RcvIn-m_RcvOut;
	else
		RcvNData=m_BufRcvMaxData+m_RcvIn-m_RcvOut;
	if (RcvNData < m_BufRcvMaxData)                             //队列是否满  
	{
		BufRcv[m_RcvIn++] = Data;									//数据入队
		if (m_RcvIn >= m_BufRcvMaxData)								//调整入队指
		{
			m_RcvIn =0;
		}
	}
	else
	{																//满          
		err = DACK_ERR_FULL;
	}
	return err;
}

//-------------------------------------------------------------------------------------------------------
// 函数名称: InPutRcvByteInPutRcvNByte(const INT8U *vSrcBuf,INT16U vSrcLen)
// 功能描述: 往缓冲区写多个字节数据，一般是中断调用
// 参数描述:
//   输　入: 
//        INT8U *vSrcBuf：数据源
//        INT16U vSrcLen：数据个数
//   输　出: 
//   
// return :  DACK_SUCESS，DACK_ERR_FULL
// 全局变量: 无
//创 建  人: 杨虎岳
//日     期: 2006年6月16日
//-------------------------------------------------------------------------------------------------------
//修改人:
//日　期:
//------------------------------------------------------------------------------------------------------
INT8U cSerBuf_LoopRcv :: InPutRcvNByte(const INT8U *vSrcBuf, INT16U vSrcLen)
{
	INT8U  err=DACK_SUCESS;;
	INT16U tmp16=0;
	INT16U RcvNData;
	
	if(m_RcvIn>=m_RcvOut)
		RcvNData=m_RcvIn-m_RcvOut;
	else
		RcvNData=m_BufRcvMaxData+m_RcvIn-m_RcvOut;

	if ( RcvNData < m_BufRcvMaxData)                             //队列是否满  
	{
		if((RcvNData+vSrcLen)<=m_BufRcvMaxData)
		{
			tmp16 = vSrcLen;
		}
		else
		{
							tmp16=m_BufRcvMaxData-RcvNData;
			err = DACK_ERR_FULL;
		}
		for(INT16U m=0;m<tmp16;m++)
		{
			BufRcv[m_RcvIn++] = vSrcBuf[m];						//数据入队
			if (m_RcvIn >= m_BufRcvMaxData)						//调整入队指
			{
				m_RcvIn =0;
			}
		}
	}
	else
	{																//满
		err = DACK_ERR_FULL;
	}
	return err;
}

//-------------------------------------------------------------------------------------------------------
// 函数名称: ClrRcvBuf(void)
// 功能描述: 清缓冲区
// 参数描述:
//     输　入: 无
//        
//      
//     输　出: 无
//   
// return :   无
// 全局变量: 无
//创 建  人: 杨虎岳
//日     期: 2006年6月16日
//-------------------------------------------------------------------------------------------------------
//修改人:
//日　期:
//------------------------------------------------------------------------------------------------------
void cSerBuf_LoopRcv::ClrRcvBuf(void)
{
	if(m_RcvIn!=m_RcvOut)
	{
		m_RcvOut=0;
		m_RcvIn=0;
	}
}

//-------------------------------------------------------------------------------------------------------
// 函数名称: QueueSizeRcvBuf(void)
// 功能描述: 查询缓冲区的最大长度
// 参数描述:
//     输　入: 无
//        
//      
//     输　出: 无
//   
// return :   最大长度
// 全局变量: 无
//创 建  人: 杨虎岳
//日     期: 2006年6月16日
//-------------------------------------------------------------------------------------------------------
//修改人:
//日　期:
//------------------------------------------------------------------------------------------------------
INT16U cSerBuf_LoopRcv :: QueueSizeRcvBuf()
{
	INT16U temp;                                                
	temp = m_BufRcvMaxData;
	return temp;
}
//-------------------------------------------------------------------------------------------------------
// 函数名称: QueRcvCnt(void)
// 功能描述: 查询接收到的数据长度。
// 参数描述:
//     输　入: 无
//        
//      
//     输　出: 无
//   
// return :   数据长度
// 全局变量: 无
//创 建  人: 杨虎岳
//日     期: 2006年6月16日
//-------------------------------------------------------------------------------------------------------
//修改人:
//日　期:
//------------------------------------------------------------------------------------------------------
INT16U cSerBuf_LoopRcv :: QueRcvCnt(void)
{
	INT16U RcvNData;

	if(m_RcvIn>=m_RcvOut)
		RcvNData=m_RcvIn-m_RcvOut;
	else
		RcvNData=m_BufRcvMaxData+m_RcvIn-m_RcvOut;
	
	return RcvNData;
}
//-------------------------------------------------------------------------------------------------------
// 函数名称: QueStartRcvBuf(void)
// 功能描述: 查询有数据的起始地址
// 参数描述:
//     输　入: 无
//        
//      
//     输　出: 无
//   
// return :   数据的起始地址
// 全局变量: 无
//创 建  人: 杨虎岳
//日     期: 2006年6月16日
//-------------------------------------------------------------------------------------------------------
//修改人:
//日　期:
//------------------------------------------------------------------------------------------------------
INT8U *cSerBuf_LoopRcv :: QueStartRcvBuf(void)
{
	return &BufRcv[m_RcvOut];
}

