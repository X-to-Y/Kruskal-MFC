// CDialog2.cpp: 实现文件
//

#include "stdafx.h"
#include "Kruskal.h"
#include "CDialog2.h"
#include "afxdialogex.h"


// CDialog2 对话框

IMPLEMENT_DYNAMIC(CDialog2, CDialogEx)

CDialog2::CDialog2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CDialog2::~CDialog2()
{
}

void CDialog2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialog2, CDialogEx)
END_MESSAGE_MAP()


// CDialog2 消息处理程序
