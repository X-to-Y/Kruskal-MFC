#pragma once


// CAllEdgesDlg 对话框

class CAllEdgesDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAllEdgesDlg)

public:
	CAllEdgesDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CAllEdgesDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	int edge_num;
	int start[45];
	int end[45];
	int weight[45];
};
