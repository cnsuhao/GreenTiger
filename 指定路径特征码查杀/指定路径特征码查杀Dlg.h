
// ָ��·���������ɱDlg.h : ͷ�ļ�
//

#pragma once


// Cָ��·���������ɱDlg �Ի���
class Cָ��·���������ɱDlg : public CDialogEx
{
// ����
public:
	Cָ��·���������ɱDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonselect();
	CString m_Path;
	afx_msg void OnBnClickedOk();
};
