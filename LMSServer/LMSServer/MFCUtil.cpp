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

CLMSServerView* CMFCUtil::getActiveView()
{
	CMainFrame* fram = CMFCUtil::getMainFrame();
	if (fram != NULL)
	{
		CLMSServerView*   pView = (CLMSServerView*)fram->GetActiveView();
		return pView;
	}
	return NULL;
}

CLMSServerDoc* CMFCUtil::getActiveDoc()
{
	CLMSServerView*   pView = CMFCUtil::getActiveView();
	if (pView != NULL)
		return pView->GetDocument();
	return NULL;
}
