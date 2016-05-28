
// LMSServerView.h : CLMSServerView 类的接口
//

#pragma once

#include "resource.h"
#include "afxcmn.h"
#include "CenterTabCtrl.h"

class CLMSServerView : public CFormView
{
protected: // 仅从序列化创建
	CLMSServerView();
	DECLARE_DYNCREATE(CLMSServerView)

public:
	enum{ IDD = IDD_LMSSERVER_FORM };

// 特性
public:
	CLMSServerDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CLMSServerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // LMSServerView.cpp 中的调试版本
inline CLMSServerDoc* CLMSServerView::GetDocument() const
   { return reinterpret_cast<CLMSServerDoc*>(m_pDocument); }
#endif

