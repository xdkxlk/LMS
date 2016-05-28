
// LMSServerView.cpp : CLMSServerView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "LMSServer.h"
#endif

#include "LMSServerDoc.h"
#include "LMSServerView.h"
#include "Controller.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLMSServerView

IMPLEMENT_DYNCREATE(CLMSServerView, CFormView)

BEGIN_MESSAGE_MAP(CLMSServerView, CFormView)
	
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_CENTERTAB, &CLMSServerView::OnTcnSelchangeCentertab)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CLMSServerView 构造/析构

CLMSServerView::CLMSServerView()
	: CFormView(CLMSServerView::IDD)
{
	// TODO:  在此处添加构造代码

}

CLMSServerView::~CLMSServerView()
{
}

void CLMSServerView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CENTERTAB, m_centerTabCtrl);
}

BOOL CLMSServerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CFormView::PreCreateWindow(cs);
}

void CLMSServerView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	m_centerTabCtrl.OnInitial();
	CTCPServer::getInstance()->startServer();
}


// CLMSServerView 诊断

#ifdef _DEBUG
void CLMSServerView::AssertValid() const
{
	CFormView::AssertValid();
}

void CLMSServerView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CLMSServerDoc* CLMSServerView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLMSServerDoc)));
	return (CLMSServerDoc*)m_pDocument;
}
#endif //_DEBUG


// CLMSServerView 消息处理程序


int CLMSServerView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	return 0;
}


void CLMSServerView::OnDraw(CDC* /*pDC*/)
{
	// TODO:  在此添加专用代码和/或调用基类

}

void CLMSServerView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
	if (m_centerTabCtrl.m_hWnd !=NULL)
		m_centerTabCtrl.MoveWindow(0, 0, cx, cy);
}


void CLMSServerView::OnTcnSelchangeCentertab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	m_centerTabCtrl.OnTcnSelchangeCentertab(pNMHDR, pResult);
}

void CLMSServerView::OnDestroy()
{
	CFormView::OnDestroy();

	// TODO:  在此处添加消息处理程序代码
}
