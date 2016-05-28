
// LMSServerView.h : CLMSServerView ��Ľӿ�
//

#pragma once

#include "resource.h"
#include "afxcmn.h"
#include "CenterTabCtrl.h"

class CLMSServerView : public CFormView
{
protected: // �������л�����
	CLMSServerView();
	DECLARE_DYNCREATE(CLMSServerView)

public:
	enum{ IDD = IDD_LMSSERVER_FORM };

// ����
public:
	CLMSServerDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CLMSServerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	CCenterTabCtrl m_centerTabCtrl;

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnDraw(CDC* /*pDC*/);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTcnSelchangeCentertab(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDestroy();
};

#ifndef _DEBUG  // LMSServerView.cpp �еĵ��԰汾
inline CLMSServerDoc* CLMSServerView::GetDocument() const
   { return reinterpret_cast<CLMSServerDoc*>(m_pDocument); }
#endif

