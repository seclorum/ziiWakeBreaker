/*
 * HUDWindow.h
 *
 *  Created on: Sep 17, 2009
 *      Author: ibi
 *      Purpose: provide the 2D overlay window for a Headsup Display
 */

#ifndef HUDWINDOW_H_
#define HUDWINDOW_H_
//
// Info window
//
class CZWBHUDWindow: public CSkinWindow {
public:
	CZWBHUDWindow();
	virtual ~CZWBHUDWindow();

	void AccelUpdate(int x, int y, int z, int roll, int pitch);

protected:
	virtual void OnPaint(CSkinGuiResource* pGuiResource, CRect dirtyRect,
			CBuffer *pSurface, cairo_t* pCairoContext);
	virtual void OnCreate(void);

	virtual void OnTimer(uint32_t timerID);

protected:
	int mTimerPaint;
	int mX;
	int mY;
	int mZ;
	int mRoll;
	int mPitch;
};

#endif /* HUDWINDOW_H_ */
