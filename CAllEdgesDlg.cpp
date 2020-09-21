// CAllEdgesDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Kruskal.h"
#include "CAllEdgesDlg.h"
#include "afxdialogex.h"


// CAllEdgesDlg 对话框

IMPLEMENT_DYNAMIC(CAllEdgesDlg, CDialogEx)

CAllEdgesDlg::CAllEdgesDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{
	edge_num = 0;
}

CAllEdgesDlg::~CAllEdgesDlg()
{
}

void CAllEdgesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAllEdgesDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CAllEdgesDlg 消息处理程序


void CAllEdgesDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	CBrush brush(RGB(136, 158, 129));//画刷
	CPen m_pen;
	m_pen.CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
	dc.SelectObject(&brush);//将画刷选入DC
	dc.Rectangle(0, 0, 500, 800);
	CFont font;
	font.CreatePointFont(120, _T("宋体"));
	dc.SelectObject(&font);
	dc.SelectObject(m_pen);
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(255, 255, 255));
	dc.TextOutA(20, 20, "所有边的信息");
	CPoint point(160, 55);
	CPoint temp = point;
	temp.Offset(-15, 0);
	dc.TextOut(temp.x, temp.y, "端点");
	temp.Offset(60, 0);
	dc.TextOut(temp.x, temp.y, "端点");
	temp.Offset(60, 0);
	dc.TextOut(temp.x, temp.y, "权值");
	for (int i = 0; i < edge_num; i++) {
		char ch[10] = { 'A','B','C','D','E','F','G','H','I','J' };
		point.Offset(0, 20);
		temp = point;
		CString str;
		str.Format("%c", ch[start[i]]);
		dc.TextOut(temp.x, temp.y, str);
		temp.Offset(60, 0);
		str.Format("%c", ch[end[i]]);
		dc.TextOutA(temp.x, temp.y, str);
		temp.Offset(60, 0);
		str.Format("%d", weight[i]);
		dc.TextOut(temp.x, temp.y, str);
	}
}
