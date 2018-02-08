#pragma once
class CAccessData
{
public:
	CAccessData(void);
	~CAccessData(void);


public:
	CStringList m_strlistTableShuxing;
	_RecordsetPtr m_pRecordset;
	CString m_strAccessName;
	void GetStrList(CString strData,CString strFind , CString listData[]);
	bool CreatDataBase(CString strIntelligentName); //创建数据库
	bool DelectDataBase(CString strIntelligentName); //删除数据库
	bool CreatTable(CString strIntelligentName, CString strTableName , CString * strlist , int nNumb); //创建表
	bool DelectTable(CString strIntelligentName, CString strTableName);//删除表
	bool AddDataToTable(CString strIntelligentName, CString strTableName ,CString listType[],CString listData[],int Numb);//插入数据
	bool SelectDataFromTable(CString strIntelligentName, CString strTableName,CString strSelectData,CString strWhere,CString strListData[],int &nRow);//查询数据
	bool DelectDataFromTable(CString strIntelligentName, CString strTableName,CString strWhere);
	bool UpdataFromTable(CString strIntelligentName, CString strTableName,CString strSet,CString strWhere);//更新数据
	bool SetCopyTable(CString strIntelligentName, CString strTableName,CString strlastTable);//复制表内容到另一表
};

