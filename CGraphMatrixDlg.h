#pragma once


// CGraphMatrixDlg 对话框

class CGraphMatrixDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGraphMatrixDlg)

public:
	CGraphMatrixDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGraphMatrixDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	int matrix[10][10];
	int vexnum;
};
