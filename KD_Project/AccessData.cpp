#include "StdAfx.h"
#include "AccessData.h"


CAccessData::CAccessData(void)
{
}


CAccessData::~CAccessData(void)
{
}
//创建数据库
bool CAccessData::CreatDataBase(CString strIntelligentName)
{	
	CString strMdbConn = _T("Provider=Microsoft.ACE.OLEDB.12.0;Data Source=") +strIntelligentName+_T(".accdb");
	//CString strMdbConn = _T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=") +strIntelligentName+_T(".mdb");
	try
	{
		ADOX::_CatalogPtr pCatalog = NULL;
		pCatalog.CreateInstance(__uuidof(ADOX::Catalog));
		_bstr_t cnnstring(strMdbConn);
		pCatalog->Create(cnnstring);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
		return false;
	}
	return true;
}
bool CAccessData::DelectDataBase(CString strIntelligentName)
{		

	return true;
}
///创建表
bool CAccessData::CreatTable(CString strIntelligentName, CString strTableName , CString * strlist , int nNumb)
{
	strIntelligentName = _T("Provider=Microsoft.ACE.OLEDB.12.0;Data Source=") + strIntelligentName;
	//strIntelligentName = _T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=")+strIntelligentName;
	_ConnectionPtr ConZhineng;
	HRESULT hr;
	hr=ConZhineng.CreateInstance(_T("ADODB.Connection"));
	if (SUCCEEDED(hr))
	{
		hr = ConZhineng->Open((_bstr_t)strIntelligentName,_T(""),_T(""),adModeUnknown);
	}
	_RecordsetPtr m_pRecordset;
	m_pRecordset.CreateInstance(_T("ADODB.Recordset"));

	CString strSql,strType;
	strSql = _T("create table ") + strTableName + _T(" (");
	for(int n = 0; n < nNumb; n++)
	{
		if (n == nNumb - 1)
		{
			strSql += strlist[n] + _T(")");
		} 
		else
		{
			strSql += strlist[n] + _T(",");
		}
	}
	try
	{
		m_pRecordset->Open((_variant_t)strSql,_variant_t((IDispatch*)ConZhineng,true), adOpenStatic,adLockOptimistic,adCmdText);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
		return false;
	}
	return true;
}

bool CAccessData::DelectTable(CString strIntelligentName, CString strTableName)
{
	strIntelligentName = _T("Provider=Microsoft.ACE.OLEDB.12.0;Data Source=") + strIntelligentName;
	//strIntelligentName = _T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=")+strIntelligentName;
	_ConnectionPtr ConZhineng;
	HRESULT hr;
	hr=ConZhineng.CreateInstance("ADODB.Connection");
	if (SUCCEEDED(hr))
	{
		hr = ConZhineng->Open((_bstr_t)strIntelligentName,_T(""),_T(""),adModeUnknown);
	}
	_RecordsetPtr m_pRecordset;
	m_pRecordset.CreateInstance(_T("ADODB.Recordset"));

	CString strSql,strType;
	strSql = _T("Drop table ") + strTableName;
	try
	{
		m_pRecordset->Open((_variant_t)strSql,_variant_t((IDispatch*)ConZhineng,true), adOpenStatic,adLockOptimistic,adCmdText);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
		return false;
	}
	return true;
}
//插入一行
bool CAccessData::AddDataToTable(CString strIntelligentName, CString strTableName,CString listType[],CString listData[],int Numb)
{
	strIntelligentName = _T("Provider=Microsoft.ACE.OLEDB.12.0;Data Source=") + strIntelligentName;
	//strIntelligentName = _T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=")+strIntelligentName;
	_ConnectionPtr ConZhineng;
	CoInitialize(NULL);
	HRESULT hr;
	hr=ConZhineng.CreateInstance(_T("ADODB.Connection"));
	if (SUCCEEDED(hr))
	{
		hr = ConZhineng->Open((_bstr_t)strIntelligentName,_T(""),_T(""),adModeUnknown);
	}
	_RecordsetPtr m_pRecordset;
	m_pRecordset.CreateInstance(_T("ADODB.Recordset"));

	CString strType;
	CString strSql = _T("insert into ") + strTableName + _T("(");
	for (int n = 0; n < Numb; n++)
	{
		if (n == Numb - 1)
		{
			strSql += listType[n] + _T(") values ('");
		}
		else
		{
			strSql += listType[n] + _T(",");
		}
	}

	for (int n = 0; n < Numb; n++)
	{
		if (n == Numb - 1)
		{
			strSql += listData[n] + _T("')");
		}
		else
		{
			strSql += listData[n] + _T("','");
		}
	}
	try
	{
		m_pRecordset->Open((_variant_t)strSql,_variant_t((IDispatch*)ConZhineng,true), adOpenStatic,adLockOptimistic,adCmdText);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
		return false;
	}
	return true;
}
void CAccessData::GetStrList(CString strData,CString strFind , CString listData[])
{
	int m = 0;
	for(int n = 0;n<wcslen(strData);n++)
	{
		if (strData.Mid(n,1) == strFind)
		{
			listData[m] = strData.Left(n);
			strData = strData.Mid(n+1);
			n=-1;
			m+=1;
			continue;
		}
	}
}
bool CAccessData::SelectDataFromTable(CString strIntelligentName, CString strTableName,CString strSelectData,CString strWhere,CString strListData[],int &nRow)
{
	strIntelligentName = _T("Provider=Microsoft.ACE.OLEDB.12.0;Data Source=") + strIntelligentName;
	//strIntelligentName = _T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=") + strIntelligentName;
	int nShibaiTimes = 0;
	_variant_t vData,vLen;
	CString strData;
	CString strSql;
	_ConnectionPtr pConnectData;
	_variant_t RecordsAffected;
	_RecordsetPtr m_pRecordset;
	CoInitialize(NULL);
JIXU:
	nShibaiTimes+=1;
	try
	{
		pConnectData.CreateInstance(_uuidof(Connection));
		pConnectData->Open((_bstr_t)strIntelligentName,_T(""),_T(""),adModeUnknown);
		m_pRecordset.CreateInstance(_T("ADODB.Recordset"));
		if (strWhere == _T(""))
		{
			strSql = _T("select ") + strSelectData + _T(" from ")+strTableName;
		} 
		else
		{
			strSql = _T("select ") + strSelectData + _T(" from ")+strTableName +_T(" where ")+strWhere;
		}
		
		m_pRecordset = pConnectData->Execute((_bstr_t)strSql,&RecordsAffected,adCmdText);
		nRow=0;
		CString strSelect;
		while(!m_pRecordset->adoEOF)
		{
			strListData[nRow] = _T("");
			if (strSelectData == _T("*"))
			{
				//vData = m_pRecordset->GetCollect((_variant_t)strSelectData);
			} 
			else
			{
				strSelect = strSelectData+_T(",");
				for(int n = 0 ; n<strSelect.GetLength();n++)
				{
					if (strSelect.Mid(n,1) == _T(","))
					{
						vData = m_pRecordset->GetCollect((_variant_t)strSelect.Left(n));
						if(vData.vt != VT_NULL)
						{
							strData = (LPCSTR)_bstr_t(vData);
							strListData[nRow] += strData+_T("$");
						}
						else
						{
							strListData[nRow] += _T("$");
							/*Sleep(100);
							pConnectData->Close();
							if (nShibaiTimes == 10)
							{
								return false;
							}
							goto JIXU;*/
						}
						strSelect = strSelect.Mid(n+1);
						n=0;
					}
				}
			}
			m_pRecordset->MoveNext();///移到下一条记录
			nRow+=1;
		}

		pConnectData->Close();
		return true;
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
		Sleep(10);
		pConnectData->Close();
		if (nShibaiTimes == 10)
		{
			return false;
		}
		goto JIXU;
	}
	
}
//删除一行或所有数据
bool CAccessData::DelectDataFromTable(CString strIntelligentName, CString strTableName,CString strWhere)//查询数据
{
	strIntelligentName = _T("Provider=Microsoft.ACE.OLEDB.12.0;Data Source=") + strIntelligentName;
	//strIntelligentName = _T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=")+strIntelligentName;
	_ConnectionPtr ConZhineng;
	CoInitialize(NULL);
	HRESULT hr;
	hr=ConZhineng.CreateInstance(_T("ADODB.Connection"));
	if (SUCCEEDED(hr))
	{
		hr = ConZhineng->Open((_bstr_t)strIntelligentName,_T(""),_T(""),adModeUnknown);
	}
	_RecordsetPtr m_pRecordset;
	m_pRecordset.CreateInstance(_T("ADODB.Recordset"));

	CString strSql = _T("");
	if (strWhere == "")
	{
		strSql = _T("delete from ")+strTableName+_T(" where 1=1");
	}
	else
	{
		strSql = _T("delete from ")+strTableName+_T(" where ")+strWhere;
	}
	
	try
	{
		m_pRecordset->Open((_variant_t)strSql,_variant_t((IDispatch*)ConZhineng,true), adOpenStatic,adLockOptimistic,adCmdText); 
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
		return false;
	}
	return true;
}

//复制表内容到另一表
bool CAccessData::SetCopyTable(CString strIntelligentName, CString strTableName,CString strlastTable)
{
	strIntelligentName = _T("Provider=Microsoft.ACE.OLEDB.12.0;Data Source=") + strIntelligentName;
	//strIntelligentName = _T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=")+strIntelligentName;
	_ConnectionPtr ConZhineng;
	CoInitialize(NULL);
	HRESULT hr;
	hr=ConZhineng.CreateInstance(_T("ADODB.Connection"));
	if (SUCCEEDED(hr))
	{
		hr = ConZhineng->Open((_bstr_t)strIntelligentName,_T(""),_T(""),adModeUnknown);
	}
	_RecordsetPtr m_pRecordset;
	m_pRecordset.CreateInstance(_T("ADODB.Recordset"));

	CString strSql = _T("insert into ")+ strlastTable +_T(" select * from ") + strTableName;

	try
	{
		m_pRecordset->Open((_variant_t)strSql,_variant_t((IDispatch*)ConZhineng,true), adOpenStatic,adLockOptimistic,adCmdText); 
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
		return false;
	}
	return true;
}
//更新一行数据
bool CAccessData::UpdataFromTable(CString strIntelligentName, CString strTableName,CString strSet,CString strWhere)
{
	strIntelligentName = _T("Provider=Microsoft.ACE.OLEDB.12.0;Data Source=") + strIntelligentName;
	//strIntelligentName = _T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=")+strIntelligentName;
	_ConnectionPtr ConZhineng;
	HRESULT hr;
	hr=ConZhineng.CreateInstance(_T("ADODB.Connection"));
	if (SUCCEEDED(hr))
	{
		hr = ConZhineng->Open((_bstr_t)strIntelligentName,_T(""),_T(""),adModeUnknown);
	}
	_RecordsetPtr m_pRecordset;
	m_pRecordset.CreateInstance(_T("ADODB.Recordset"));

	CString strSql = _T("UPDATE  ")+strTableName+_T(" set ")+strSet+_T(" where ")+strWhere;
	try
	{
		m_pRecordset->Open((_variant_t)strSql,_variant_t((IDispatch*)ConZhineng,true), adOpenStatic,adLockOptimistic,adCmdText); 
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
		return false;
	}
	return true;
}