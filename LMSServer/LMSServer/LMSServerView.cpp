
// LMSServerView.cpp : CLMSServerView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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

// CLMSServerView ����/����

CLMSServerView::CLMSServerView()
	: CFormView(CLMSServerView::IDD)
{
	// TODO:  �ڴ˴���ӹ������

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
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

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


// CLMSServerView ���

#ifdef _DEBUG
void CLMSServerView::AssertValid() const
{
	CFormView::AssertValid();
}

void CLMSServerView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CLMSServerDoc* CLMSServerView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLMSServerDoc)));
	return (CLMSServerDoc*)m_pDocument;
}
#endif //_DEBUG


// CLMSServerView ��Ϣ�������


int CLMSServerView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������

	return 0;
}


void CLMSServerView::OnDraw(CDC* /*pDC*/)
{
	// TODO:  �ڴ����ר�ô����/����û���

}

void CLMSServerView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
	if (m_centerTabCtrl.m_hWnd !=NULL)
		m_centerTabCtrl.MoveWindow(0, 0, cx, cy);
}


void CLMSServerView::OnTcnSelchangeCentertab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_centerTabCtrl.OnTcnSelchangeCentertab(pNMHDR, pResult);
}

void CLMSServerView::OnDestroy()
{
	CFormView::OnDestroy();

	// TODO:  �ڴ˴������Ϣ����������
}
