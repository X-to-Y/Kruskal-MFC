#pragma once


// CDialog2 对话框

class CDialog2 : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog2)

public:
	CDialog2(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDialog2();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
