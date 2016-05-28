#pragma once
#include "MainFrm.h"
#include "ClientDoc.h"
#include "ClientView.h"

class CMFCUtil
{
public:
	CMFCUtil();
	~CMFCUtil();

	static CMainFrame* getMainFrame();

	static CClientDoc* getActiveDoc();

	static CClientView* getActiveView();
};

