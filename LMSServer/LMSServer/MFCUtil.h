#pragma once
#include "MainFrm.h"
#include "LMSServerDoc.h"
#include "LMSServerView.h"

class CMFCUtil
{
public:
	CMFCUtil();
	~CMFCUtil();

	static CMainFrame* getMainFrame();

	static CLMSServerDoc* getActiveDoc();

	static CLMSServerView* getActiveView();
};

