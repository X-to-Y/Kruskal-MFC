
// KruskalDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "GraphNode.h"
#include "EdgeNode.h"
#include "GraphPoint.h"
#include "time.h"
#include "Kruskal.h"
#include "KruskalDlg.h"
#include "afxdialogex.h"
#include "CMinMatrixDlg.h"
#include "CAllEdgesDlg.h"
#include "CGraphMatrixDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CKruskalDlg 对话框



CKruskalDlg::CKruskalDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_KRUSKAL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pen[0].CreatePen(PS_SOLID, 3, RGB(255, 182, 150));     //样式、宽度、颜色   顶点线条颜色
	m_pen[1].CreatePen(PS_SOLID, 6, RGB(186, 199, 167));     //       绘图背景边框颜色
	m_pen[2].CreatePen(PS_SOLID, 2, RGB(255, 255, 255));      //  图边线条颜色，字颜色
	m_pen[3].CreatePen(PS_SOLID, 4, RGB(248, 177, 149));       //  生成最小树的线条颜色
	//m_pen[4].CreatePen(PS_DASHDOTDOT, 1, RGB(255, 0, 0));//红色双点虚线，必须为一个像素宽

	edge_num = 0;
	vexnum = 0;
	cnt = 0;
	cnt_timer = 0;
	startflag = true;
}

void CKruskalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_vexnum, m_vexnum);
	DDX_Control(pDX, IDC_List_start, m_start);
	DDX_Control(pDX, IDC_List_end, m_end);
	DDX_Control(pDX, IDC_EDIT_Weight, m_weight);
	DDX_Control(pDX, IDC_STATIC_Title, m_staTitle);
}

BEGIN_MESSAGE_MAP(CKruskalDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_input_vexnum, &CKruskalDlg::OnBnClickedinputvexnum)
	ON_BN_CLICKED(IDC_AddEdge, &CKruskalDlg::OnBnClickedAddedge)
	ON_BN_CLICKED(IDC_RandomMatrix, &CKruskalDlg::OnBnClickedRandommatrix)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_AutoShow, &CKruskalDlg::OnBnClickedAutoshow)
	ON_BN_CLICKED(IDC_SlowDown, &CKruskalDlg::OnBnClickedSlowdown)
	ON_BN_CLICKED(IDC_SpeedUp, &CKruskalDlg::OnBnClickedSpeedup)
	ON_BN_CLICKED(IDC_ManuelShow, &CKruskalDlg::OnBnClickedManuelshow)
	ON_BN_CLICKED(IDC_NextStep, &CKruskalDlg::OnBnClickedNextstep)
	ON_BN_CLICKED(IDC_Result, &CKruskalDlg::OnBnClickedResult)
	ON_BN_CLICKED(IDC_TreeMatrix, &CKruskalDlg::OnBnClickedTreematrix)
	ON_BN_CLICKED(IDC_GraphMatrix, &CKruskalDlg::OnBnClickedGraphmatrix)
	ON_BN_CLICKED(IDC_AllEdges, &CKruskalDlg::OnBnClickedAlledges)
	ON_BN_CLICKED(IDC_Pause, &CKruskalDlg::OnBnClickedPause)
	ON_BN_CLICKED(IDC_Start, &CKruskalDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_DefaultSpeed, &CKruskalDlg::OnBnClickedDefaultspeed)
	ON_WM_CTLCOLOR()
	ON_WM_NCHITTEST()
	ON_BN_CLICKED(IDC_Exit, &CKruskalDlg::OnBnClickedExit)
	ON_WM_DRAWITEM()
	ON_BN_CLICKED(IDC_About, &CKruskalDlg::OnBnClickedAbout)
END_MESSAGE_MAP()


// CKruskalDlg 消息处理程序

BOOL CKruskalDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	CString sPath = _T("C:\\Users\\XY\\source\\repos\\Kruskal\\res\\BG1.jpg");//添加背景图片
	CImage img;
	img.Load(sPath);
	HBITMAP hbmp = img.Detach();
	CBitmap bmp;
	bmp.Attach(hbmp);
	m_bgBrush.CreatePatternBrush(&bmp);

	m_FontTitle.CreatePointFont(170, _T("微软雅黑"));//调整静态文本字体大小(标题）
	m_staTitle.SetFont(&m_FontTitle);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CKruskalDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CKruskalDlg::OnPaint()
{	//画出绘图区域背景
	CPaintDC dc(this); // 用于绘制的设备上下文
	CBrush brush(RGB(136, 158, 129));//画刷
	dc.SelectObject(&brush);//将画刷选入DC
	dc.SelectObject(&m_pen[1]);
	dc.Rectangle(370, 60, 1200, 640);
	
	CRgn rgnTmp;//调整对话框大小以及边框弧度
	RECT rc;
	GetClientRect(&rc);
	rgnTmp.CreateRoundRectRgn(rc.left + 3, rc.top + 3, rc.right - rc.left - 3, rc.bottom - rc.top - 3, 6, 6);
	SetWindowRgn(rgnTmp, TRUE);
	SetClassLong(this->m_hWnd, GCL_STYLE, GetClassLong(this->m_hWnd, GCL_STYLE) | CS_DROPSHADOW); //增加对话框阴影
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CKruskalDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CKruskalDlg::OnBnClickedinputvexnum() //确定按钮
{
	// TODO: 在此添加控件通知处理程序代码

	//初始化相关数据
	edge_num = 0;
	vexnum = 0;
	cnt = 0;
	cnt_timer = 0;
	startflag = true;
	KillTimer(1);//防止bug

	CString s;
	m_vexnum.GetWindowText(s);
	Graph.vexnum = vexnum = _ttoi(s);

	for (int i = 0; i < Graph.vexnum - 1; i++) {
		min_edges[i].start = -1;
		min_edges[i].end = -1;
		min_edges[i].weight = -1;
	}
	for (int i = 0; i < 10; i++) {//初始化邻接矩阵
		Graph.ch_vex[i] = char('A' + i);
	}
	for (int i = 0; i < 10; i++) {//初始化邻接矩阵
		for (int j = 0; j < 10; j++) {
			if (i == j) {
				Graph.Adjmatrix[i][j] = Graph.Adjmatrix[j][i] = 0;
			}
			else {
				Graph.Adjmatrix[i][j] = Graph.Adjmatrix[j][i] = -1;
			}
		}
	}
	if (vexnum >= 2 && vexnum <= 10) {//初始化Listbox里的内容及画出顶点
		DrawVertex();
		m_start.ResetContent();
		m_end.ResetContent();
		for (int i = 0; i < vexnum; i++) {
			CString temp = (CString)Graph.ch_vex[i];
			m_start.AddString(temp);
			m_end.AddString(temp);
		}
	}
	else if (vexnum == 0) {
		MessageBox(_T("你还没有任何输入！"));
	}
	else {
		MessageBox(_T("请输入2 - 10个节点数！"));
	}
}


void CKruskalDlg::DrawVertex()//实现画出图的顶点
{
	// TODO: 在此处添加实现代码.
	CDC *pDC = GetDC();
	CBrush brush(RGB(136, 158, 129));//覆盖背景区域
	*pDC->SelectObject(&brush);
	*pDC->SelectObject(&m_pen[1]);
	pDC->Rectangle(370,60,1200,640);//背景区域
	brush.DeleteObject();
	brush.CreateSolidBrush(RGB(255, 255, 255));//绘制顶点内容的参数
	*pDC->SelectObject(&brush);
	*pDC->SelectObject(&m_pen[0]);
	CFont font;
	font.CreatePointFont(120, _T("宋体"));
	pDC->SelectObject(&font);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(0, 0, 0));
	for (int i = 0; i < vexnum; i++)
	{
		pDC->Ellipse(&rect[vexnum - 1][i]);
		CPoint point = rect[vexnum - 1][i].CenterPoint();
		CString str = (CString)Graph.ch_vex[i];
		pDC->TextOut( point.x - 5,point.y -10 ,str);
	}
}

void CKruskalDlg::OnBnClickedAddedge()//增加边按钮
{
	// TODO: 在此添加控件通知处理程序代码
	int start = m_start.GetCurSel();
	int end = m_end.GetCurSel();
	CString wgt;
	m_weight.GetWindowText(wgt);
	int weight = _ttoi(wgt);

	if (start == LB_ERR || end == LB_ERR) {
		MessageBox("还没有选择结点！");
	}
	else if (Graph.Adjmatrix[start][end] != -1) {
		MessageBox("输入边已存在！");
	}
	else if (start == end) {
		MessageBox("应选择不同的结点！");
	}
	else if (weight == 0) {
		MessageBox("边的权值不应该为0！");
	}
	else {
		edges[edge_num].start = start;
		edges[edge_num].end = end;
		edges[edge_num++].weight = weight;
		Graph.Adjmatrix[start][end] = Graph.Adjmatrix[end][start] = weight;
		DrawEdge(false,start, end, weight);
	}
}



void CKruskalDlg::DrawEdge(bool flag, int start, int end, int weight)//画出指定顶点的边
{
	// TODO: 在此处添加实现代码.
	CDC *pDC = GetDC();
	CPoint CenterA = rect[vexnum - 1][start].CenterPoint();
	CPoint CenterB = rect[vexnum - 1][end].CenterPoint();
	if (flag == false) {
		*pDC->SelectObject(&m_pen[2]);
	}
	else{
		*pDC->SelectObject(&m_pen[3]);
	}
	pDC->MoveTo(CenterA);
	pDC->LineTo(CenterB);
	CString str;
	str.Format("%d", weight);
	int x = (CenterA.x + CenterB.x) / 2;
	int y = (CenterA.y + CenterB.y) / 2;
	CFont font;
	font.CreatePointFont(120, _T("宋体"));
	pDC->SelectObject(&font);
	pDC->SetBkMode(TRANSPARENT);
	pDC->TextOut(x, y - 11, str);
}


void CKruskalDlg::OnBnClickedRandommatrix()//随机生成
{
	// TODO: 在此添加控件通知处理程序代码
	edge_num = 0;
	vexnum = 0;
	cnt = 0;
	cnt_timer = 0;
	startflag = true;
	KillTimer(1);//防止bug

	for (int i = 0; i < Graph.vexnum - 1; i++) {
		min_edges[i].start = -1;
		min_edges[i].end = -1;
		min_edges[i].weight = -1;
	}
	srand(time(NULL));
	Graph.vexnum = vexnum = rand() % 9 + 2;
	for (int i = 0; i < 10; i++) {//初始化邻接矩阵
		Graph.ch_vex[i] = char('A' + i);
	}
	for (int i = 0; i < 10; i++) {//初始化邻接矩阵
		for (int j = 0; j < 10; j++) {
			if (i == j) {
				Graph.Adjmatrix[i][j] = Graph.Adjmatrix[j][i] = 0;
			}
			else {
				Graph.Adjmatrix[i][j] = Graph.Adjmatrix[j][i] = -1;
			}
		}
	}
	DrawVertex();
	CString str;
	str.Format("%d", vexnum);
	m_vexnum.SetWindowText(str);
	m_start.ResetContent();//更新ListBox
	m_end.ResetContent();
	for (int i = 0; i < vexnum; i++) {
		CString temp = (CString)Graph.ch_vex[i];
		m_start.AddString(temp);
		m_end.AddString(temp);
	}

	for (int i = 0; i < Graph.vexnum; i++) {
		for (int j = 0; j < Graph.vexnum; j++) {
			if (Graph.Adjmatrix[i][j] == -2) {//保证矩阵随机性
				continue;
			}
			else if (Graph.Adjmatrix[i][j] == -1) {
				int temp = rand() % 100;
				if (temp == 0 || temp % ((rand() % 2) + 2) == 0) {
					Graph.Adjmatrix[i][j] = Graph.Adjmatrix[j][i] = -2;//保证矩阵随机性
				}
				else {
					Graph.Adjmatrix[i][j] = Graph.Adjmatrix[j][i] = temp;
					edges[edge_num].start = i;
					edges[edge_num].end = j;
					edges[edge_num++].weight = temp;
					DrawEdge(false, i, j, temp);
				}
			}
		}
	}
	for (int i = 0; i < Graph.vexnum; i++) {//还原矩阵
		for (int j = 0; j < Graph.vexnum; j++) {
			if (Graph.Adjmatrix[i][j] == -2) {
				Graph.Adjmatrix[i][j] = -1;
			}
		}
	}
}




int CKruskalDlg::partition(EdgeNode *edge, int low, int high)//快排实现
{
	// TODO: 在此处添加实现代码
	int pivotkey = edge[low].weight;
	EdgeNode  temp;
	while (low < high) {
		while (low < high && edge[high].weight >= pivotkey) {
			high--;
		}
		temp = edge[low];
		edge[low] = edge[high];
		edge[high] = temp;
		while (low < high && edge[low].weight <= pivotkey) {
			low++;
		}
		temp = edge[high];
		edge[high] = edge[low];
		edge[low] = temp;
	}
	return low;

}

void CKruskalDlg::quikSort(EdgeNode *edge, int low, int high)//快速排序
{
	// TODO: 在此处添加实现代码.
	int pivot;
	if (low < high) {
		pivot = partition(edge, low, high);
		quikSort(edge, low, pivot - 1);
		quikSort(edge, pivot + 1, high);
	}
}

int CKruskalDlg::Find(int *parent, int f)//实现查并集
{
	// TODO: 在此处添加实现代码.
	while (parent[f] > 0) {
		f = parent[f];
	}
	return f;
}

void CKruskalDlg::Kruskal()//kruskal算法
{
	// TODO: 在此处添加实现代码.
	if (vexnum == 0) {  //判断当前创建图的情况
		MessageBox("还没有创建任何顶点！");
		return;
	}
	else if (edge_num == 0) {
		MessageBox("没有任何边!");
		return;
	}
	else if (startflag == false) {
		return;
	}

	quikSort(edges, 0, edge_num - 1);//使用快速排序

	CDC *pDC = GetDC();//在屏幕中绘制出排序后的边的信息
	CFont font;
	font.CreatePointFont(110, _T("宋体")); //字体格式设置
	pDC->SelectObject(&font);
	*pDC->SelectObject(&m_pen[2]);
	pDC->SetBkMode(TRANSPARENT);  
	pDC->SetTextColor(RGB(255, 255, 255));
	CPoint point(1020, 110);
	CPoint temp = point;
	pDC->TextOut(point.x + 30, point.y - 30, "图的边"); 
	temp.Offset(-15, 0);
	pDC->TextOut(temp.x, temp.y, "端点");
	temp.Offset(60, 0);
	pDC->TextOut(temp.x, temp.y, "端点");
	temp.Offset(60, 0);
	pDC->TextOut(temp.x, temp.y, "权值");
	for (int i = 0; i < edge_num; i++) {
		point.Offset(0, 20);
		temp = point;
		CString str;
		str.Format("%c", Graph.ch_vex[edges[i].start]);
		pDC->TextOut(temp.x, temp.y, str);
		temp.Offset(60, 0);
		str.Format("%c", Graph.ch_vex[edges[i].end]);
		pDC->TextOutA(temp.x, temp.y, str);
		temp.Offset(60, 0);
		str.Format("%d", edges[i].weight);
		pDC->TextOut(temp.x, temp.y, str);
	}

	for (int i = 0; i < Graph.vexnum; i++) {//初始化最小生成树的矩阵
		for (int j = 0; j < Graph.vexnum; j++) {
			if (i == j) {
				min_tree[i][j] = 0;
			}
			else {
				min_tree[i][j] = -1;
			}
		}
	}
	int parent[10];//并查集算法实现
	for (int i = 0; i < Graph.vexnum; i++) {
		parent[i] = 0;
	}
	for (int i = 0; i < edge_num; i++) {
		int min_start = Find(parent, edges[i].start);   //使用Find函数查找当前点的根
		int min_end = Find(parent, edges[i].end);
		if (min_start != min_end) {
			parent[min_start] = min_end;
			min_edges[cnt].start = edges[i].start;  //保存符合条件的边
			min_edges[cnt].end = edges[i].end;
			min_edges[cnt].weight = edges[i].weight;
			flag[cnt++] = i;
			min_tree[edges[i].start][edges[i].end] = min_tree[edges[i].end][edges[i].start] = edges[i].weight;
		}
	}
	startflag = false;  //防止重复调用算法
}

void CKruskalDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	Show();
}

void CKruskalDlg::Show()
{
	// TODO: 在此处添加实现代码.
	if (cnt_timer == cnt) {
		KillTimer(1);
		if (cnt != Graph.vexnum - 1) {
			MessageBox("没有找到最小生成树！");
		}
		else {
			DrawVertex();
			for (int i = 0; i < cnt; i++) {
				DrawEdge(true, min_edges[i].start, min_edges[i].end, min_edges[i].weight);
			}
			CDC *pDC = GetDC();

			CBrush brush(RGB(231, 234, 225));//解决超出区域
			CPen pen;
			pen.CreatePen(PS_SOLID, 3, RGB(231, 234, 225));
			*pDC->SelectObject(&brush);
			*pDC->SelectObject(&pen);
			pDC->Rectangle(1020,643, 1250, 750);

			CFont font;//绘制最终选取的边
			font.CreatePointFont(110, _T("宋体"));
			pDC->SelectObject(&font);
			*pDC->SelectObject(&m_pen[2]);
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(RGB(255, 255, 255));
			CPoint point(1020, 110);
			CPoint temp = point;
			pDC->TextOut(point.x + 45, point.y - 30, "MST");
			temp.Offset(-15, 0);
			pDC->TextOut(temp.x, temp.y, "端点");
			temp.Offset(60, 0);
			pDC->TextOut(temp.x, temp.y, "端点");
			temp.Offset(60, 0);
			pDC->TextOut(temp.x, temp.y, "权值");
			for (int i = 0; i < cnt; i++) {
				//char ch[10] = { 'A','B','C','D','E','F','G','H','I','J' };
				point.Offset(0, 20);
				temp = point;
				CString str;
				str.Format("%c", Graph.ch_vex[min_edges[i].start]);
				pDC->TextOut(temp.x, temp.y, str);
				temp.Offset(60, 0);
				str.Format("%c", Graph.ch_vex[min_edges[i].end]);
				pDC->TextOutA(temp.x, temp.y, str);
				temp.Offset(60, 0);
				str.Format("%d", min_edges[i].weight);
				pDC->TextOut(temp.x, temp.y, str);
			}
			MessageBox("已找到最小生成树！");
		}
		return;
	}
	CRect flagpoint(1000, 135, 1010, 145);//标记点的绘制
	CDC *pDC = GetDC();
	CBrush brush;
	brush.CreateSolidBrush(RGB(0,0,0));
	*pDC->SelectObject(&brush);
	*pDC->SelectObject(&m_pen[0]);
	flagpoint.OffsetRect(0, 20 * flag[cnt_timer]);
	pDC->Ellipse(&flagpoint);

	DrawEdge(true, min_edges[cnt_timer].start, min_edges[cnt_timer].end, min_edges[cnt_timer].weight);//绘制选择的边
	cnt_timer++;
}


void CKruskalDlg::OnBnClickedAutoshow()
{
	// TODO: 在此添加控件通知处理程序代码
	if (startflag == false) {
		return;
	}
	Kruskal();
	SetTimer(1, 1000, NULL);

}

void CKruskalDlg::OnBnClickedSlowdown()
{
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(1);
	Kruskal();
	SetTimer(1, 2000, NULL);
}

void CKruskalDlg::OnBnClickedSpeedup()
{
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(1);
	Kruskal();
	SetTimer(1, 500, NULL);
}

void CKruskalDlg::OnBnClickedPause()
{
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(1);
}


void CKruskalDlg::OnBnClickedStart()
{
	// TODO: 在此添加控件通知处理程序代码
	SetTimer(1, 1000, NULL);
}


void CKruskalDlg::OnBnClickedDefaultspeed()
{
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(1);
	Kruskal();
	SetTimer(1, 1000, NULL);
}

void CKruskalDlg::OnBnClickedManuelshow()
{
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(1);
	Kruskal();
}

void CKruskalDlg::OnBnClickedNextstep()
{
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(1);
	Kruskal();
	Show();
}

void CKruskalDlg::OnBnClickedResult()//直接显示结果
{
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(1);
	Kruskal();
	if (cnt != Graph.vexnum - 1) {
		MessageBox("没有找到最小生成树！");
	}
	else {
		DrawVertex();
		for (int i = 0; i < cnt; i++) {
			DrawEdge(true, min_edges[i].start, min_edges[i].end, min_edges[i].weight);
		}
		CDC *pDC = GetDC();

		CBrush brush(RGB(231, 234, 225));//解决超出区域
		CPen pen;
		pen.CreatePen(PS_SOLID, 3, RGB(231, 234, 225));
		*pDC->SelectObject(&brush);
		*pDC->SelectObject(&pen);
		pDC->Rectangle(1020, 643, 1250, 750);

		CFont font;//绘制最终边
		font.CreatePointFont(110, _T("宋体"));
		pDC->SelectObject(&font);
		*pDC->SelectObject(&m_pen[2]);
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255, 255, 255));
		CPoint point(1020, 110);
		CPoint temp = point;
		pDC->TextOut(point.x + 45, point.y - 30, "MST");
		temp.Offset(-15, 0);
		pDC->TextOut(temp.x, temp.y, "端点");
		temp.Offset(60, 0);
		pDC->TextOut(temp.x, temp.y, "端点");
		temp.Offset(60, 0);
		pDC->TextOut(temp.x, temp.y, "权值");
		for (int i = 0; i < cnt; i++) {
			point.Offset(0, 20);
			temp = point;
			CString str;
			str.Format("%c", Graph.ch_vex[min_edges[i].start]);
			pDC->TextOut(temp.x, temp.y, str);
			temp.Offset(60, 0);
			str.Format("%c", Graph.ch_vex[min_edges[i].end]);
			pDC->TextOutA(temp.x, temp.y, str);
			temp.Offset(60, 0);
			str.Format("%d", min_edges[i].weight);
			pDC->TextOut(temp.x, temp.y, str);
		}
		MessageBox("已找到最小生成树！");
	}
}

void CKruskalDlg::OnBnClickedTreematrix()//最小生成树的邻接矩阵
{
	// TODO: 在此添加控件通知处理程序代码

	CMinMatrixDlg *dlg;
	dlg = new CMinMatrixDlg(this);
	dlg->Create(IDD_DIALOG1, this);
	for (int i = 0; i < Graph.vexnum; i++) {
		for (int j = 0; j < Graph.vexnum; j++) {
			dlg->matrix[i][j] = min_tree[i][j];
		}
	}
	dlg->vexnum = vexnum;
	dlg->ShowWindow(1);
}

void CKruskalDlg::OnBnClickedGraphmatrix()//图的邻接矩阵
{
	// TODO: 在此添加控件通知处理程序代码
	CGraphMatrixDlg *dlg;
	dlg = new CGraphMatrixDlg(this);
	dlg->Create(IDD_DIALOG3, this);
	for (int i = 0; i < Graph.vexnum; i++) {
		for (int j = 0; j < Graph.vexnum; j++) {
			dlg->matrix[i][j] = Graph.Adjmatrix[i][j];
		}
	}
	dlg->vexnum = vexnum;
	dlg->ShowWindow(1);
}


void CKruskalDlg::OnBnClickedAlledges()//输入的所有边
{
	// TODO: 在此添加控件通知处理程序代码
	CAllEdgesDlg *dlg;
	dlg = new CAllEdgesDlg(this);
	dlg->Create(IDD_DIALOG2, this);
	for (int i = 0; i < edge_num; i++) {
		dlg->start[i] = edges[i].start;
		dlg->end[i] = edges[i].end;
		dlg->weight[i] = edges[i].weight;
	}
	dlg->edge_num = edge_num;
	dlg->ShowWindow(1);
}

void CKruskalDlg::OnBnClickedAbout()//关于
{
	// TODO: 在此添加控件通知处理程序代码
	CAboutDlg abtDlg;
	abtDlg.DoModal();
}

HBRUSH CKruskalDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)//标题美化
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd == this)   // 添加背景图片
	{
		return m_bgBrush;
	}

	if (IDC_STATIC_Title == pWnd->GetDlgCtrlID())//判断发出消息的空间是否是该静态文本框，静态文本美化 ， 标题
	{
		pDC->SetTextColor(RGB(255, 255, 255));//设置文本颜色为白色
		pDC->SetBkMode(OPAQUE);//设置文本背景模式为透明
		pDC->SetBkColor(RGB(105, 132, 116));//设置文本背景
		hbr = CreateSolidBrush(RGB(105, 132, 116));//控件的背景色
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


LRESULT CKruskalDlg::OnNcHitTest(CPoint point)//解决美化后窗口拖动
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	LRESULT ret = CDialogEx::OnNcHitTest(point);
	return (ret == HTCLIENT) ? HTCAPTION : ret;
	return CDialogEx::OnNcHitTest(point);
}


void CKruskalDlg::OnBnClickedExit()//退出按钮
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(0);
}


void CKruskalDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)//按钮美化
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct);

	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);
	ASSERT(lpDrawItemStruct->CtlType == ODT_BUTTON);

	CString strText;
	((CButton *)GetDlgItem(nIDCtl))->GetWindowText(strText);

	SetBkMode(lpDrawItemStruct->hDC, TRANSPARENT);
	{
		CBrush brush(RGB(186, 199, 167));
		dc.FillRect(&(lpDrawItemStruct->rcItem), &brush);
		DrawText(lpDrawItemStruct->hDC, strText, strText.GetLength(),
			&lpDrawItemStruct->rcItem, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
		SetBkMode(lpDrawItemStruct->hDC, TRANSPARENT);
	}
	dc.Detach();
}