#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <plaszma.h>
#include <skin.h>

#include "wakebreaker/Game.h"

using namespace nZiiLABS;

class CMainWindow : public CSkinWindow
{
public:
	CMainWindow(CResource* imageRes);
	virtual ~CMainWindow();
	void AccelUpdate(int x, int y, int z, int roll, int pitch);

protected:
	virtual void OnCreate();
	virtual void OnCreateFrameBuffer(int numBuffer);
	virtual void OnDestroyFrameBuffer();
	virtual EventReturnType OnClick(CWidgetEventData* pEvData);
	virtual EventReturnType OnMouseDown(SharedEventPtr pEvent, int X, int Y);
	virtual EventReturnType OnMouseUp(SharedEventPtr pEvent, int X, int Y);

	virtual void OnPaint(
		CSkinGuiResource*	pGuiResource,
		CRect				DirtyRect,
		CBuffer*			pSurface,
		cairo_t*			pCairoContext);

	virtual void OnTimer(uint32_t timerID);
	virtual void OnPreDestroy();

	virtual float GetTickCount() { return m_tickcount ; } ;
	void j_dumpEGLConfig(int var, int value);

	void showconfigProperties(EGLConfig cfg);
	void dumpAllConfigs();

	int mX;
	int mY;
	int mZ;
	int mRoll;
	int mPitch;

	Game g_game;
	CEglHelper* pEglHelper;
	EGLDisplay e_display;
	EGLConfig  e_config;
	EGLContext e_context;
	EGLSurface mPixmapSurface[2];
	CBuffer* m_pBuffer[2];
	unsigned mBufferIndex;
	const uint32_t mTimerPaint;
	float m_tickcount;
	CResource* mpImageRes;
	CResourceHandle mImage[4];

};

#endif // MAINWINDOW_H_
