#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class ADOConn
{
public:
	//���һ��ָ��Connection�����ָ��:
		_ConnectionPtr m_pConnection;
		//���һ��ָ��Recordset�����ָ��:
		_RecordsetPtr m_pRecordset;
public:
	ADOConn(void);
	~ADOConn(void);

	// ��ʼ�����������ݿ�
	void  OnInitADOConn();
	// ִ�в�ѯ
	_RecordsetPtr& GetRecordSet(_bstr_t bstrSQL);
	// ִ��SQL��䣬Insert Update _variant_t
	BOOL ExecuteSQL(_bstr_t bstrSQL);
	void ExitConnect();
};
