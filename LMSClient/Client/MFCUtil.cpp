#include "stdafx.h"
#include "MFCUtil.h"


CMFCUtil::CMFCUtil()
{
}


CMFCUtil::~CMFCUtil()
{
}


CMainFrame* CMFCUtil::getMainFrame()
{
	return (CMainFrame*)AfxGetMainWnd();
}

CClientView* CMFCUtil::getActiveView()
{
	CMainFrame* fram = CMFCUtil::getMainFrame();
	if (fram != NULL)
	{
		CClientView*   pView = (CClientView*)fram->GetActiveView();
		return pView;
	}
	return NULL;
}

CClientDoc* CMFCUtil::getActiveDoc()
{
	CMainFrame* fram = CMFCUtil::getMainFrame();
	if (fram != NULL)
	{
		CClientDoc*   doc = (CClientDoc*)fram->GetActiveDocument();
		return doc;
	}
	return NULL;
}
