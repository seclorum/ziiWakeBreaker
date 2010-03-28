/*
 * *
 * * this is a quick and dirty port of WakeBreaker to the
 * zii egg platform, for the purposes of demonstration of
 * both plaszma and the wakebreaker codebase, two exceptional
 * bits of cooperative software-making.
 *
 *  * see w1xer.at/zii/wakebreaker/ for the latest version
 *
 *  License for the port stuff: 100% free to do whatever you like.
 *
 *  License for Wakebreaker: refer to wakebreaker codebase
 */


#include <libgen.h>
#include <unistd.h>
#include <iostream>
#include <syslog.h>

#include "ZiiWakeBreakerApp.h"

#include "wakebreaker/Game.h"

using namespace nZiiLABS;

int PlaszmaAppMain(int argc, char** argv) {


	CZiiWaveBreakerApp* w1App = CZiiWaveBreakerApp::ZiiGetApp();

	// Workaround when debugging applications:
	// Before calling the Run() method of the application
	// change the directory to the application directory.

	if (argv[0])
		chdir(dirname(argv[0]));

	// From this point on, you should be able to aceess any files in
	// your application directory using relative paths.


	if (w1App) {
		w1App->Run("at.w1xer.zii.ZiiWakeBreaker"); // TODO:
		delete w1App;
	}

	closelog();
	return 1;
}

//
// Accelerometer callback
//
void AccelerometerOnDataUpdate ( const AccelerometerData* pAccelData, void* pUserData )
{
	int RollAngle, PitchAngle;

	CZiiWaveBreakerApp* w1App = CZiiWaveBreakerApp::ZiiGetApp();
	if (w1App)
	{
		Accelerometer_GetTiltAngle(*pAccelData, &RollAngle, &PitchAngle);
		WB_LOGGER(LOG_ERR, "roll : %d pitch: %d", RollAngle, PitchAngle);
		w1App->AccelUpdate(pAccelData->x, pAccelData->y, pAccelData->z, RollAngle, PitchAngle);

	}
}

CZiiWaveBreakerApp* CZiiWaveBreakerApp::ZiiGetApp(void) {
	if (!CPlaszmaApp::mpAppSingleInstance)
		CPlaszmaApp::mpAppSingleInstance = new CZiiWaveBreakerApp();

	return (CZiiWaveBreakerApp*) CPlaszmaApp::mpAppSingleInstance;
}

CZiiWaveBreakerApp::CZiiWaveBreakerApp() :
	mpMainWindow(NULL), mpResStudio(NULL), mpImageRes(NULL), mpStrRes(NULL) {
}

CZiiWaveBreakerApp::~CZiiWaveBreakerApp() {
	if (mpStrRes)
		delete mpStrRes;

	if (mpImageRes)
		delete mpImageRes;

	if (mpResStudio)
		delete mpResStudio;
}

bool CZiiWaveBreakerApp::OnRun() {
	CSkinApp::OnRun();

	// Create Resource Factory
	mpResStudio = new CResourceStudio;
	WB_LOGGER(LOG_ERR, "App Running!");

	if (NULL == mpResStudio)
		return false;

	// Create Application Resource Handles
	mpImageRes = mpResStudio->Create((const char*) "./ZiiWakeBreaker.pir");
	if (NULL == mpImageRes) {
		WB_LOGGER(LOG_ERR, "Cannot load PIR resource");
		return false;
	}

	mpStrRes = mpResStudio->Create((const char*) "./ZiiWakeBreaker.plr");

	if (NULL == mpStrRes) {
		WB_LOGGER(LOG_ERR, "Cannot load PLR resource");
		return false;
	}

	mpStrRes->Set(STRINGRESOURCE_PROPERTY_LOCALE, "ENG", strlen("ENG"));

	const uint32_t DisplayId = 0;
	CRect CreateRect;

	GetDisplaySize(DisplayId, (uint32_t*) &CreateRect.W, (uint32_t*) &CreateRect.H);

	WB_LOGGER(LOG_ERR, "createrect size: %d x %d", CreateRect.W, CreateRect.H);
	mpMainWindow = new CMainWindow(mpImageRes);

	if (mpMainWindow)
		mpMainWindow->Create(CreateRect, SKIN_DEFAULT | SKIN_UNMANAGED, 100,
				DisplayId, ROTATE_0);

	 //
	    CreateRect.X = 0;
	    CreateRect.Y = 0;
	    CreateRect.W = 320;
	    CreateRect.H = 480;

	    ZWBInfoWindow = new CZWBHUDWindow();
	    //
	    // Create the info window with per pixel alpha blending so it can be blended on top of the GL window
	    //
	    if(ZWBInfoWindow)
	    	ZWBInfoWindow->Create(CreateRect, SKIN_DEFAULT | SKIN_PERPIXELALPHA, 101, DisplayId, ROTATE_0);

	    //
	    // Show the system tray.  Ensure this is done *after* the main window has been created.
	    //
	    //Desktop_SystrayShow(SHOW_ALL);

	    //
	    // Create the accelerometer object
	    //
	    mpAccelObj = Accelerometer_AcquireConnection();

	    if (ACCELEROMETER_OK != Accelerometer_RegisterForUpdates(mpAccelObj, ACCELERATION_UPDATE_FREQUENCY_NORMAL, AccelerometerOnDataUpdate, NULL))
	        return false;

	return true;
}
//
// Accelerometer update method
//
void CZiiWaveBreakerApp::AccelUpdate(int x, int y, int z, int roll, int pitch)
{
	mpMainWindow->AccelUpdate(x, y, z, roll, pitch);
	ZWBInfoWindow->AccelUpdate(x, y, z, roll, pitch);
}

void CZiiWaveBreakerApp::OnDeleteChildWindow(CSkinWindow *pWindow) {
	/*
	 * This is called when the child window of the
	 * application is slated to be closed.
	 * Simply delete the window in this case.
	 */
	if (pWindow == mpMainWindow) {
		delete mpMainWindow;
		mpMainWindow = NULL;
	}
}

AppCloseType CZiiWaveBreakerApp::OnCloseRequest() {
	/*
	 * Called when another application or the desktop is brought to the foreground.
	 * Return PLASZMA_APP_SHUTDOWN (default) to indicate that the application is going to
	 * shut down or return PLASZMA_APP_MINIMIZE to indicate that it is going to
	 * minimize.
	 * */
	return PLASZMA_APP_SHUTDOWN;
}

AppShutdownType CZiiWaveBreakerApp::OnShutdown() {
	/*
	 * Called when the application is being terminated.
	 * Return PLASZMA_APP_AUTOSTOP(default) or
	 * PLASZMA_APP_MANUALSTOP
	 */
	return PLASZMA_APP_AUTOSTOP;
}

bool CZiiWaveBreakerApp::OnSuspend() {
	/*
	 * Called when the system is entering a low power, standby state.
	 * Return true (default) to allow suspend, or false to reject suspend.
	 */
	return true;
}

void CZiiWaveBreakerApp::OnResume() {
	/*
	 * Called when the system comes out of the standby state and has resumed operation.
	 */
}

void CZiiWaveBreakerApp::OnMinimize() {
	/*
	 * Called when the application is minimized.
	 */
}

void CZiiWaveBreakerApp::OnRestore() {
	/*
	 * Called when the application is brought to the foreground again after it was minimized.
	 */
}

void CZiiWaveBreakerApp::OnFocusLost() {
	/**
	 * Called when another application is brought to the foreground in front of the application.
	 */
}

