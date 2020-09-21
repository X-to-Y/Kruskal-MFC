
// KruskalDlg.h: 头文件
//

#pragma once


// CKruskalDlg 对话框
class CKruskalDlg : public CDialogEx
{
	// 构造
public:
	CKruskalDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KRUSKAL_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedinputvexnum();//创建图部分
	CEdit m_vexnum;
	void DrawVertex();
	CListBox m_start;
	CListBox m_end;
	CPen m_pen[4];
	CEdit m_weight;
	afx_msg void OnBnClickedAddedge();
	int edge_num;
	int vexnum;
	void DrawEdge(bool flag, int start, int end, int weight);
	afx_msg void OnBnClickedRandommatrix();

	int cnt;//绘制演示部分
	int cnt_timer;
	bool startflag;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int min_tree[10][10];
	int flag[9];
	int partition(struct EdgeNode *edge, int low, int high);
	void quikSort(struct EdgeNode *edge, int low, int high);
	void Kruskal();
	int Find(int *parent, int f);
	void Show();
	afx_msg void OnBnClickedAutoshow();
	afx_msg void OnBnClickedSlowdown();
	afx_msg void OnBnClickedSpeedup();
	afx_msg void OnBnClickedManuelshow();
	afx_msg void OnBnClickedNextstep();
	afx_msg void OnBnClickedResult();
	afx_msg void OnBnClickedPause();
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedDefaultspeed();

	afx_msg void OnBnClickedTreematrix();//查看信息部分
	afx_msg void OnBnClickedGraphmatrix();
	afx_msg void OnBnClickedAlledges();
	afx_msg void OnBnClickedAbout();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	CBrush m_bgBrush;//后期美化部分
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnBnClickedExit();
	CFont m_FontTitle;
	CStatic m_staTitle;
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
};
