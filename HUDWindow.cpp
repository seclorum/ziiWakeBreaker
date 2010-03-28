/*
 * infowindow.cpp
 *
 *  Created on: Sep 17, 2009
 *      Author: ibi
 */

#include <skin.h>
#include <plaszma.h>

#include <syslog.h>
#include "Game.h"

#include "HUDWindow.h"

CZWBHUDWindow::CZWBHUDWindow() {
	mTimerPaint = 11;
	mX = mY = mZ = 0;
}

CZWBHUDWindow::~CZWBHUDWindow() {
}

void CZWBHUDWindow::OnCreate(void) {

	WB_LOGGER(LOG_ERR, "info window oncreate");
	// 5 fps
	SetTimer(mTimerPaint, uint32_t(200));
}

void CZWBHUDWindow::OnTimer(uint32_t timerID) {
	WB_LOGGER(LOG_ERR, "info window ontimer");

	if (timerID == mTimerPaint)
		RequestPaint(NULL);
}

void CZWBHUDWindow::AccelUpdate(int x, int y, int z, int roll, int pitch) {
#ifdef DO_ACCEL_UPDATES
	WB_LOGGER(LOG_ERR, "accel: x %d y %d z %d r %d p %d", x, y, z, roll, pitch);
	mX = x;
	mY = y;
	mZ = z;
	mRoll = roll;
	mPitch = pitch;
#endif
}

void CZWBHUDWindow::OnPaint(CSkinGuiResource* pGuiResource, CRect dirtyRect,
		CBuffer *pSurface, cairo_t* pCairoContext) {
	//
	// Use Cairo to render the text for this simple example
	//
	char str[128];
	int fontHeight = 16;
	int y = fontHeight;
	WB_LOGGER(LOG_ERR, "info window onpaint");

#define DO_HUD 1

#ifdef DO_HUD
	//
	// Clear the background with 0 alpha
	//
	cairo_set_source_rgba(pCairoContext, 0.0f, 0.0f, 0.0f, 0.0f);
	cairo_rectangle(pCairoContext, dirtyRect.X, dirtyRect.Y, dirtyRect.W,
			dirtyRect.H);
	cairo_fill(pCairoContext);

	//
	// Set the font white
	//
	cairo_set_source_rgba(pCairoContext, 1.0f, 1.0f, 1.0f, 1.0f);
	cairo_set_font_size(pCairoContext, fontHeight);

	//
	// Render the accelerometer text
	//
	cairo_move_to(pCairoContext, 0, y);
	sprintf(str, "X:%5d", mX);
	cairo_show_text(pCairoContext, str);
	y += fontHeight;

	cairo_move_to(pCairoContext, 0, y);
	sprintf(str, "Y:%5d", mY);
	cairo_show_text(pCairoContext, str);
	y += fontHeight;

	cairo_move_to(pCairoContext, 0, y);
	sprintf(str, "Z:%5d", mZ);
	cairo_show_text(pCairoContext, str);
	y += fontHeight;

	cairo_move_to(pCairoContext, 0, y);
	sprintf(str, "R:%5d", mRoll);
	cairo_show_text(pCairoContext, str);
	y += fontHeight;

	cairo_move_to(pCairoContext, 0, y);
	sprintf(str, "P:%5d", mPitch);
	cairo_show_text(pCairoContext, str);



	/* Code for ID = '#HUD_Group' */
	/* ID = #HUD_Group */

	//cairo_image_surface_create_for_data(0xb7068008, 0, 320, 480, 1280) = 0x81b0310;
	//cairo_create(0x81b0310) = pCairoContext;
	//cairo_surface_destroy(0x81b0310);
	//cairo_get_matrix(pCairoContext, 0xbf8e7bb8);
	//cairo_matrix_transform_point(0xbf8e7bb8, 0xbf8e7c38, 0xbf8e7c18);
	//cairo_matrix_transform_point(0xbf8e7bb8, 0xbf8e7c30, 0xbf8e7c10);
	//cairo_matrix_transform_point(0xbf8e7bb8, 0xbf8e7c28, 0xbf8e7c08);
	//cairo_matrix_transform_point(0xbf8e7bb8, 0xbf8e7c20, 0xbf8e7c00);
	cairo_save(pCairoContext);
	cairo_set_antialias(pCairoContext,(cairo_antialias_t)0);
	//cairo_matrix_init(0xbf8e7668, 1.563, 0, 0, 1.30975, -72.0202, -73.6117);
	//cairo_set_matrix(pCairoContext, 0xbf8e7668);
	cairo_set_line_width(pCairoContext, 1.72188);
	cairo_set_miter_limit(pCairoContext, 4);
	cairo_set_line_cap(pCairoContext, (cairo_line_cap_t)0);
	cairo_set_line_join(pCairoContext, (cairo_line_join_t)0);
	cairo_set_dash(pCairoContext, NULL, 0, 0);
	cairo_move_to(pCairoContext, 92.6417, 333.679);
	cairo_line_to(pCairoContext, 131.123, 333.679);
	cairo_line_to(pCairoContext, 131.123, 375.506);
	cairo_line_to(pCairoContext, 92.6417, 375.506);
	cairo_line_to(pCairoContext, 92.6417, 333.679);
	cairo_close_path(pCairoContext);
	cairo_move_to(pCairoContext, 92.6417, 333.679);
	//cairo_fill_extents(pCairoContext, 0xbf8e7738, 0xbf8e7740, 0xbf8e7748, 0xbf8e7750);
	cairo_set_fill_rule(pCairoContext, (cairo_fill_rule_t)1);
	cairo_set_source_rgb(pCairoContext, 0.501961, 0, 0);
	cairo_fill(pCairoContext);
	cairo_set_antialias(pCairoContext, (cairo_antialias_t)0);
	//cairo_matrix_init(0xbf8e7668, 1.563, 0, 0, 1.30975, -72.0202, -73.6117);
	//cairo_set_matrix(pCairoContext, 0xbf8e7668);
	cairo_set_line_width(pCairoContext, 1);
	cairo_set_miter_limit(pCairoContext, 4);
	cairo_set_line_cap(pCairoContext, (cairo_line_cap_t)0);
	cairo_set_line_join(pCairoContext, (cairo_line_join_t)0);
	cairo_set_dash(pCairoContext, NULL, 0, 0);
	cairo_move_to(pCairoContext, 164.289, 334.881);
	cairo_line_to(pCairoContext, 199.487, 334.881);
	cairo_line_to(pCairoContext, 199.487, 374.304);
	cairo_line_to(pCairoContext, 164.289, 374.304);
	cairo_line_to(pCairoContext, 164.289, 334.881);
	cairo_close_path(pCairoContext);
	cairo_move_to(pCairoContext, 164.289, 334.881);
	//cairo_fill_extents(pCairoContext, 0xbf8e7738, 0xbf8e7740, 0xbf8e7748, 0xbf8e7750);
	cairo_set_fill_rule(pCairoContext, (cairo_fill_rule_t)0);
	cairo_set_source_rgb(pCairoContext, 0, 0, 0.501961);
	cairo_fill(pCairoContext);
	cairo_set_antialias(pCairoContext, (cairo_antialias_t)0);
	//cairo_matrix_init(0xbf8e7668, 1.563, 0, 0, 1.30975, -72.0202, -73.6117);
	//cairo_set_matrix(pCairoContext, 0xbf8e7668);
	cairo_set_line_width(pCairoContext, 1);
	cairo_set_miter_limit(pCairoContext, 4);
	cairo_set_line_cap(pCairoContext, (cairo_line_cap_t)0);
	cairo_set_line_join(pCairoContext, (cairo_line_join_t)0);
	cairo_set_dash(pCairoContext, NULL, 0, 0);
	cairo_move_to(pCairoContext, 130.785, 296.571);
	cairo_line_to(pCairoContext, 164.342, 296.571);
	cairo_line_to(pCairoContext, 164.342, 334.211);
	cairo_line_to(pCairoContext, 130.785, 334.211);
	cairo_line_to(pCairoContext, 130.785, 296.571);
	cairo_close_path(pCairoContext);
	cairo_move_to(pCairoContext, 130.785, 296.571);
	//cairo_fill_extents(pCairoContext, 0xbf8e7738, 0xbf8e7740, 0xbf8e7748, 0xbf8e7750);
	cairo_set_fill_rule(pCairoContext, (cairo_fill_rule_t)0);
	cairo_set_source_rgb(pCairoContext, 0, 1, 0);
	cairo_fill(pCairoContext);
	cairo_set_antialias(pCairoContext, (cairo_antialias_t)0);
	//cairo_matrix_init(0xbf8e7668, 1.563, 0, 0, 1.30975, -72.0202, -73.6117);
	//cairo_set_matrix(pCairoContext, 0xbf8e7668);
	cairo_set_line_width(pCairoContext, 1);
	cairo_set_miter_limit(pCairoContext, 4);
	cairo_set_line_cap(pCairoContext, (cairo_line_cap_t)0);
	cairo_set_line_join(pCairoContext, (cairo_line_join_t)0);
	cairo_set_dash(pCairoContext, NULL, 0, 0);
	cairo_move_to(pCairoContext, 131.485, 374.888);
	cairo_line_to(pCairoContext, 163.643, 374.888);
	cairo_line_to(pCairoContext, 163.643, 415.038);
	cairo_line_to(pCairoContext, 131.485, 415.038);
	cairo_line_to(pCairoContext, 131.485, 374.888);
	cairo_close_path(pCairoContext);
	cairo_move_to(pCairoContext, 131.485, 374.888);
	//cairo_fill_extents(pCairoContext, 0xbf8e7738, 0xbf8e7740, 0xbf8e7748, 0xbf8e7750);
	cairo_set_fill_rule(pCairoContext, (cairo_fill_rule_t)0);
	cairo_set_source_rgb(pCairoContext, 1, 1, 0);
	cairo_fill(pCairoContext);

	/* End of Code for ID = '#HUD_Group' */



#endif

}
