#pragma once


// CMinMatrixDlg 对话框

class CMinMatrixDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMinMatrixDlg)

public:
	CMinMatrixDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMinMatrixDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	int matrix[10][10];
	int vexnum;
};
