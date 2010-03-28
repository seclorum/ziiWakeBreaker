#ifndef ZIIWAKEBREAKERAPP_H_
#define ZIIWAKEBREAKERAPP_H_

#include <skin.h>
#include "mainwindow.h"
#include "HUDWindow.h"

extern "C"
{
	int PlaszmaAppMain(int argc, char** argv);
}

using namespace nZiiLABS;

class CZiiWaveBreakerApp : public CSkinApp
{
public:
	static CZiiWaveBreakerApp* ZiiGetApp();
	virtual void OnDeleteChildWindow(CSkinWindow *pWindow);
	void AccelUpdate(int x, int y, int z, int roll, int pitch);
	// System Events
	virtual AppShutdownType OnShutdown();
	virtual AppCloseType OnCloseRequest();
	virtual bool OnSuspend();
	virtual void OnResume();
	virtual void OnMinimize();
	virtual void OnRestore();
	virtual void OnFocusLost();

public:
	~CZiiWaveBreakerApp();
	virtual bool OnRun();

private:
	CZiiWaveBreakerApp();

private:
	CMainWindow* mpMainWindow;
	CZWBHUDWindow* ZWBInfoWindow;

	CResourceStudio* mpResStudio;
	CResource* mpImageRes;
	CResource* mpStrRes;
    AccelerometerObj* mpAccelObj;
};

#endif // ZIIWAKEBREAKERAPP_H_
