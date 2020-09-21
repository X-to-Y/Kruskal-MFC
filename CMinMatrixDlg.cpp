﻿// CMinMatrixDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Kruskal.h"
#include "CMinMatrixDlg.h"
#include "afxdialogex.h"


// CMinMatrixDlg 对话框

IMPLEMENT_DYNAMIC(CMinMatrixDlg, CDialogEx)

CMinMatrixDlg::CMinMatrixDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	vexnum = 0;
}

CMinMatrixDlg::~CMinMatrixDlg()
{
}

void CMinMatrixDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMinMatrixDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CMinMatrixDlg 消息处理程序


void CMinMatrixDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	CBrush brush(RGB(136, 158, 129));//画刷
	CPen m_pen;
	m_pen.CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
	dc.SelectObject(&brush);//将画刷选入DC
	dc.Rectangle(0, 0, 700, 450);
	CFont font;
	font.CreatePointFont(120, _T("宋体"));
	dc.SelectObject(&font);
	dc.SelectObject(m_pen);
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(255, 255, 255));
	dc.TextOutA(20,20,"最小生成树的邻接矩阵");
	CPoint point(100, 40);
	for (int i = 0; i < vexnum; i++) {
		point.Offset(0, 30);
		CPoint temp = point;
		for (int j = 0; j < vexnum; j++) {
			CString str;
			if (matrix[i][j] == -1) {
				str = "*";
			}
			else {
				str.Format("%d", matrix[i][j]);
			}
			dc.TextOutA(temp.x, temp.y, str);
			temp.Offset(40, 0);
		}
	}
}
