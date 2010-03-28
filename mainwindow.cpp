#include <syslog.h>

#include "mainwindow.h"

#include <math.h>
#include <assert.h>

using namespace nZiiLABS;

static void reportEGLError() {
	switch (eglGetError()) {

	case EGL_BAD_DISPLAY:
		WB_LOGGER(LOG_ERR, "EGL_BAD_DISPLAY\n");
		break;

	case EGL_NOT_INITIALIZED:
		WB_LOGGER(LOG_ERR, "EGL_NOT_INITIALIZED\n");
		break;

	case EGL_BAD_CONFIG:
		WB_LOGGER(LOG_ERR, "EGL_BAD_CONFIG\n");
		break;

	case EGL_BAD_CONTEXT:
		WB_LOGGER(LOG_ERR, "EGL_BAD_CONTEXT\n");
		break;

	case EGL_BAD_ATTRIBUTE:
		WB_LOGGER(LOG_ERR, "EGL_BAD_ATTRIBUTE\n");
		break;

	case EGL_BAD_ALLOC:
		WB_LOGGER(LOG_ERR, "EGL_BAD_ALLOC\n");
		break;

	default:
		WB_LOGGER(LOG_ERR, "alien error\n");
		break;
	}
}

CMainWindow::CMainWindow(CResource* imageRes) :
	mBufferIndex(0), mTimerPaint(42) {
	for (unsigned i = 0; i < sizeof(mPixmapSurface) / sizeof(mPixmapSurface[0]); i++)
		mPixmapSurface[i] = EGL_NO_SURFACE;

	for (unsigned i = 0; i < sizeof(m_pBuffer) / sizeof(m_pBuffer[0]); i++)
		m_pBuffer[i] = NULL;

	for (unsigned i = 0; i < sizeof(mImage) / sizeof(mImage[0]); i++)
		mImage[i] = NULL;

}

CMainWindow::~CMainWindow() {
}

void CMainWindow::OnCreate() {
	CSkinBaseWAbstract::OnCreate();


}

void CMainWindow::OnPreDestroy() {
	CSkinBaseWAbstract::OnPreDestroy();

	for (unsigned i = 0; i < sizeof(mImage) / sizeof(mImage[0]); i++)
		if (NULL != mImage[i]) {
			mpImageRes->Unload(mImage[i]);
			mImage[i] = NULL;
		}
}

// the context's configuration.
void CMainWindow::showconfigProperties(EGLConfig cfg) {
	for (int name = 0x3020; name <= 0x304F; ++name) {
		EGLint value;
		if ((name != EGL_NONE) && eglGetConfigAttrib(e_display, cfg, name, &value))
			j_dumpEGLConfig(name, value);
	}
	eglGetError(); // Clear the error state.

}

// Dump all of the EGL configurations supported by the system.
void CMainWindow::dumpAllConfigs()
{
    EGLint count = 0;
    if (!eglGetConfigs(e_display, 0, 0, &count) || count < 1)
        return;
    EGLConfig *configs = new EGLConfig [count];

    eglGetConfigs(e_display, configs, count, &count);

    WB_LOGGER(LOG_ERR, "# configs: %d, count: %d", configs, count);

    for (EGLint index = 0; index < count; ++index) {
    	WB_LOGGER(LOG_ERR, "Config #%d", index);
        showconfigProperties(configs[index]);
    }
    delete [] configs;
}



void CMainWindow::j_dumpEGLConfig(int var, int value) {
	switch (var) {
	case 0x3020: {
		WB_LOGGER (LOG_ERR, "%s = %d", "EGL_BUFFER_SIZE", value);
	}
		break; //EGL_BUFFER_SIZE/
	case 0x3021: {
		WB_LOGGER (LOG_ERR, "%s = %d", "EGL_ALPHA_SIZE", value);
	}
		break; //EGL_ALPHA_SIZE/
	case 0x3022: {
		WB_LOGGER (LOG_ERR, "%s = %d", "EGL_BLUE_SIZE ", value);
	}
		break; //EGL_BLUE_SIZE/
	case 0x3023: {
		WB_LOGGER (LOG_ERR, "%s = %d", "EGL_GREEN_SIZE", value);
	}
		break; //EGL_GREEN_SIZE/
	case 0x3024: {
		WB_LOGGER (LOG_ERR, "%s = %d", "EGL_RED_SIZE", value);
	}
		break; //EGL_RED_SIZE/
	case 0x3025: {
		WB_LOGGER (LOG_ERR, "%s = %d", "EGL_DEPTH_SIZE ", value);
	}
		break; //EGL_DEPTH_SIZE/
	case 0x3026: {
		WB_LOGGER (LOG_ERR, "%s = %d", "EGL_STENCIL_SIZE ", value);
	}
		break; //EGL_STENCIL_SIZE/
	case 0x3027: {
		WB_LOGGER (LOG_ERR, "%s = %d", "EGL_CONFIG_CAVEAT ", value);
	}
		break; //EGL_CONFIG_CAVEAT/
	case 0x3028: {
		WB_LOGGER (LOG_ERR, "%s = %d", "EGL_CONFIG_ID ", value);
	}
		break; //EGL_CONFIG_ID/
	case 0x3029: {
		WB_LOGGER (LOG_ERR, "%s = %d", "EGL_LEVEL ", value);
	}
		break; //EGL_LEVEL/
	case 0x302A: {
		WB_LOGGER (LOG_ERR, "%s = %d", "EGL_MAX_PBUFFER_HEIGHT ", value);
	}
		break; //EGL_MAX_PBUFFER_HEIGHT/
	case 0x302B: {
		WB_LOGGER (LOG_ERR, "%s = %d", "EGL_MAX_PBUFFER_PIXELS", value);
	}
		break; //EGL_MAX_PBUFFER_PIXELS/
	case 0x302C: {
		WB_LOGGER (LOG_ERR, "%s = %d", "EGL_MAX_PBUFFER_WIDTH", value);
	}
		break; //EGL_MAX_PBUFFER_WIDTH/
	case 0x302D: {
		WB_LOGGER (LOG_ERR, "%s = %d", "EGL_NATIVE_RENDERABLE", value);
	}
		break; //EGL_NATIVE_RENDERABLE/
	case 0x302E: {
		WB_LOGGER (LOG_ERR, "%s = %d", "EGL_NATIVE_VISUAL_ID", value);
	}
		break; //EGL_NATIVE_VISUAL_ID/
	case 0x302F: {
		WB_LOGGER (LOG_ERR, "%s = %d", "EGL_NATIVE_VISUAL_TYPE", value);
	}
		break; //EGL_NATIVE_VISUAL_TYPE/
	case 0x3030: {
		WB_LOGGER (LOG_ERR, "%s = %d", "EGL_PRESERVED_RESOURCES", value);
	}
		break; //EGL_PRESERVED_RESOURCES/
	case 0x3031: {
		WB_LOGGER (LOG_ERR, "%s = %d", "EGL_SAMPLES", value);
	}
		break; //EGL_SAMPLES/
	case 0x3032: {
		WB_LOGGER (LOG_ERR, "%s = %d", "EGL_SAMPLE_BUFFERS", value);
	}
		break; //EGL_SAMPLE_BUFFERS/
	case 0x3033: {
		WB_LOGGER (LOG_ERR, "%s = %d", "EGL_SURFACE_TYPE", value);
	}
		break; //EGL_SURFACE_TYPE/
	case 0x3034: {
		WB_LOGGER (LOG_ERR, "%s = %d", "EGL_TRANSPARENT_TYPE", value);
	}
		break; //EGL_TRANSPARENT_TYPE/
	case 0x3035: {
		WB_LOGGER (LOG_ERR, "%s = %d", "EGL_TRANSPARENT_BLUE_VALUE", value);
	}
		break; //EGL_TRANSPARENT_BLUE_VALUE/
	case 0x3036: {
		WB_LOGGER (LOG_ERR, "%s = %d", "EGL_TRANSPARENT_GREEN_VALUE", value);
	}
		break; //EGL_TRANSPARENT_GREEN_VALUE/
	case 0x3037: {
		WB_LOGGER (LOG_ERR, "%s = %d", "EGL_TRANSPARENT_RED_VALUE", value);
	}
		break; //EGL_TRANSPARENT_RED_VALUE/
	case 0x3038: {
		WB_LOGGER (LOG_ERR, "%s = %d", "EGL_NONE", value);
	}
		break; //EGL_NONE/
	case 0x3039: {
		WB_LOGGER (LOG_ERR, "%s = %d", "EGL_BIND_TO_TEXTURE_RGB", value);
	}
		break; //EGL_BIND_TO_TEXTURE_RGB/
	case 0x303A: {
		WB_LOGGER (LOG_ERR, "%s = %d", "EGL_BIND_TO_TEXTURE_RGBA", value);
	}
		break; //EGL_BIND_TO_TEXTURE_RGBA/
	case 0x303B: {
		WB_LOGGER (LOG_ERR, "%s = %d", "EGL_MIN_SWAP_INTERVAL", value);
	}
		break; //EGL_MIN_SWAP_INTERVAL/
	case 0x303C: {
		WB_LOGGER (LOG_ERR, "%s = %d", "EGL_MAX_SWAP_INTERVAL", value);
	}
		break; //EGL_MAX_SWAP_INTERVAL/
	default: {
		WB_LOGGER (LOG_ERR, "%s = %d", "<unknown>", value);
	}
		break;
	}
}

void CMainWindow::OnCreateFrameBuffer(int NumBuffer) {
	CRect WindowRect;
	GetRect(&WindowRect);

	// Create CBuffers for the windows
	m_pBuffer[0] = mpAppUi->CreateDefaultBuffer(WindowRect.W, WindowRect.H);
	m_pBuffer[1] = mpAppUi->CreateDefaultBuffer(WindowRect.W, WindowRect.H);

/*
  ABGR1555
    32bpp 4x 8bit color components
ABGR8888
	 */

	// Push the buffers into a list
	mBufferList.push_back(m_pBuffer[0]);
	mBufferList.push_back(m_pBuffer[1]);

	// EGL Init
	pEglHelper = mpAppUi->GetEglHelper();
	WB_LOGGER(LOG_ERR, "Egl Helper is : %s", (pEglHelper != NULL) ? "being used" : "not available");

	//	dumpAllConfigs();

	EGLint major;
	EGLint minor;

	WB_LOGGER(LOG_ERR, "display setup::");

	e_display = eglGetCurrentDisplay();

	dumpAllConfigs();

    EGLint s_configAttribs[] =
	    {
            EGL_RED_SIZE,       5,
            EGL_GREEN_SIZE,     5,
            EGL_BLUE_SIZE,      5,
	        EGL_ALPHA_SIZE,     EGL_DONT_CARE,
	        EGL_DEPTH_SIZE,     16,
	        EGL_STENCIL_SIZE,   EGL_DONT_CARE,
	        EGL_SURFACE_TYPE,   EGL_PIXMAP_BIT,
	        EGL_NONE
	    };

	    EGLint numConfigs;

	    eglGetConfigs(e_display, NULL, 0, &numConfigs);

	if (EGL_TRUE == eglInitialize(e_display, &major, &minor)) {
		WB_LOGGER(LOG_ERR, "eglInitialize() succeeded; major, minor: %d, %d.\n", major,
				minor);

		const char *pcVendor = eglQueryString(e_display, EGL_VENDOR);
		const char *pcVersion = eglQueryString(e_display, EGL_VERSION);
		const char *pcExtensions = eglQueryString(e_display, EGL_EXTENSIONS);

		WB_LOGGER(LOG_ERR, "egl vendor, version, extensions:\n"
				"\t%s\n\t%s\n\t%s\n", pcVendor, pcVersion, pcExtensions);

		eglChooseConfig(e_display, s_configAttribs, &e_config, 1, &numConfigs);
		// .. we cannot get context with plaszma - already attributed to our thread.
		//e_context = eglCreateContext(e_display, e_config, NULL, NULL);

		if (pEglHelper) {
			WB_LOGGER(LOG_ERR, "pEglHelper *IS* being used");
			// Create Pixmap surfaces that are to be used by EGL for rendering
			mPixmapSurface[0] = pEglHelper->CreatePixmapSurface(m_pBuffer[0]);
			mPixmapSurface[1] = pEglHelper->CreatePixmapSurface(m_pBuffer[1]);
			WB_LOGGER(LOG_ERR, "Surfaces created.");
			// .. likewise, makeCurrent is not possible for us - assume the helper does work!
			// eglMakeCurrent(e_display, m_pBuffer[0], m_pBuffer[1], e_context);
		}
	}
	reportEGLError();
}

void CMainWindow::OnDestroyFrameBuffer() {
	CEglHelper* pEglHelper = mpAppUi->GetEglHelper();

	// Remove CBuffer’s binding to EGL if there are any existing bindings
	if (pEglHelper) {
		if (mPixmapSurface[0] != EGL_NO_SURFACE) {
			pEglHelper->DestroyPixmapSurface(mPixmapSurface[0]);
			mPixmapSurface[0] = EGL_NO_SURFACE;
		}
		if (mPixmapSurface[1] != EGL_NO_SURFACE) {
			pEglHelper->DestroyPixmapSurface(mPixmapSurface[1]);
			mPixmapSurface[1] = EGL_NO_SURFACE;
		}
	}

	// Releases the CBuffers created
	if (m_pBuffer[0]) {
		m_pBuffer[0]->Release();
		m_pBuffer[0] = NULL;
	}
	if (m_pBuffer[1]) {
		m_pBuffer[1]->Release();
		m_pBuffer[1] = NULL;
	}

	// Clear the list containing created CBuffers
	if (!mBufferList.empty())
		mBufferList.clear();

//	eglDestroyContext(e_display, context);
	eglTerminate(e_display);

	g_game.Destroy();

}

/*
 *
To achieve good CPU/Array overlap, you should program your main loop as such :

start loop
    render code;  // perform this first to fully load the array with work
    physics/maths code; //whilst the array is busy with rendering code, use the ARM for extra processing
    glFinish/swapBuffers; // this will flush the array, stalling the arm until the array has finished.
goto start

 When you call glFinish or swapbuffers, the arm will go idle whilst it waits
 for the array to finish the work. You should utilise these arm cycles by
 performing as much work as possible on the arm *after* making your gl calls
 and *before* calling glFinish() or swapBuffers.
 */
void CMainWindow::OnPaint(CSkinGuiResource* pGuiResource, CRect DirtyRect,
		CBuffer* pSurface, cairo_t* pCairoContext) {
	CEglHelper* pEglHelper = mpAppUi->GetEglHelper();

	if (NULL == pEglHelper) {
		cairo_set_source_rgba(pCairoContext, 1, 1, 1, 1);
		cairo_rectangle(pCairoContext, DirtyRect.X, DirtyRect.Y, DirtyRect.W,
				DirtyRect.H);
		cairo_fill(pCairoContext);

		return;
	}

	// Get the active surface which can be updated
	CBuffer* pActiveBuffer = GetActiveBuffer();

	if (pActiveBuffer == m_pBuffer[0])
		mBufferIndex = 0;
	else
		mBufferIndex = 1;

	// Bind the surface to EGL for updating
	pEglHelper->BindSurface(mPixmapSurface[mBufferIndex]);

	if (!g_game.isGameCreated()) {
		WB_LOGGER(LOG_ERR, "First paint, must make Game");
		g_game.Create(DirtyRect.W, DirtyRect.H);
		WB_LOGGER(LOG_ERR, "Game created.");
	}
	////////////////////////////////////////////////////////////////////////////////////////////
	// Draw a frame
	////////////////////////////////////////////////////////////////////////////////////////////

	static unsigned frame_count;
	static unsigned image_idx;
#define TEXTURE_PERIOD 42
	if (frame_count % TEXTURE_PERIOD == 0) {

	}



#if 0
	glClearColor(.5f, .5f, .5f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

//#define USE_ORTHO_PROJECTION 0
#ifdef USE_ORTHO_PROJECTION
		glOrthof(-1.f, 1.f, -1.5f, 1.5f, 1.f, 3.f);
#else
		glFrustumf(-.5f, .5f, -.75f, .75f, 1.f, 3.f);
#endif
#endif

	static GLfloat angle = 0.f;

	// draw frame

	WB_LOGGER(LOG_ERR, "g_game->Menu");
	g_game.Menu();
	WB_LOGGER(LOG_ERR, "g_game->Menu Done");

	angle = fmodf(angle + 1.f, 360.f);
	frame_count++;

	////////////////////////////////////////////////////////////////////////////////////////////
	// Frame drawn
	////////////////////////////////////////////////////////////////////////////////////////////

	// Unbind the surface to be ready to display
	pEglHelper->BindSurface(NULL);

	RequestPaint(NULL); /* debug: alternative to the timer-driven paint requests */
	// Swap the display buffer with the one that has just been updated
	SwapBuffer();
}


void CMainWindow::AccelUpdate(int x, int y, int z, int roll, int pitch) {
#ifdef DO_ACCEL_UPDATE
	WB_LOGGER(LOG_ERR, "accel: x %d y %d z %d", x, y, z);
	mX = x;
	mY = y;
	mZ = z;
	mRoll = roll;
	mPitch = pitch;

	if ((roll >= 300) && (roll <= 360))
		g_game.KeyDown(G_LEFT);

	if ((roll >= 0) && (roll <= 60))
		g_game.KeyDown(G_RIGHT);

	if ((pitch >=0) && (pitch <=30))
		g_game.KeyDown(G_UP);

	if ((pitch >=30) && (pitch <=90) )
			g_game.KeyDown(G_DOWN);
#endif

}

EventReturnType CMainWindow::OnMouseUp(SharedEventPtr pEvent, int X, int Y) {
	g_game.KeyUp(G_LEFT);
	g_game.KeyUp(G_RIGHT);
	g_game.KeyUp(G_UP);
	g_game.KeyUp(G_DOWN);
}

EventReturnType CMainWindow::OnMouseDown(SharedEventPtr pEvent, int X, int Y) {
	//mUseCube = !mUseCube;

	// perhaps Plaszma presents a better way to calculate bounding-box
	// for a mouse hit-test but for now we'll just do it the cruddy way ..

	// leftred
	if ((X >= 92) && (X <= (92 + 38)) &&
	    (Y >= 333) && ((Y <= 333 + 41)))
		g_game.KeyDown(G_LEFT);

	// rightblue
	if ((X >= 164) && (X <= (164 + 35)) &&
	    (Y >= 334) && ((Y <= 334 + 39)))
		g_game.KeyDown(G_RIGHT);


	// upgreen
	if ((X >= 130) && (X <= (130 + 33)) &&
	    (Y >= 296) && ((Y <= 296 + 38)))
		g_game.KeyDown(G_UP);

	// downyellow
	if ((X >= 131) && (X <= (131 + 32)) &&
	    (Y >= 374) && (Y <= 374 + 40))
		g_game.KeyDown(G_DOWN);

		WB_LOGGER(LOG_ERR, "onmousedown x %d y %d!", X, Y);
//		g_game.KeyDown(G_OK);
		return EVENT_RETURN_CONSUMED;
}

EventReturnType CMainWindow::OnClick(CWidgetEventData* pEvData) {
	//... body of event handler
	return EVENT_RETURN_UNCONSUMED;
}

void CMainWindow::OnTimer(uint32_t TimerID) {
	if (TimerID == mTimerPaint)
		RequestPaint(NULL);
	else
		CSkinBaseWAbstract::OnTimer(TimerID);
}

static bool decodeImage(const char* filename, CBuffer*& pBuffer) {
	ImageDecoderReturnType DecodeReturn;
	CFileStream* pStreamSourceFile;

	ImageFormatType ImageType;
	int ImageWidth;
	int ImageHeight;

	// Create an ImageDecoder
	CImageDecoder* pImageDecoder = CImageDecoder::Create();

	if (NULL == pImageDecoder)
		return false;

	// Load a file stream source for use by the CImageDecoder
	pStreamSourceFile = CFileStream::Open(filename, O_RDONLY);

	if (NULL == pStreamSourceFile) {

		delete pImageDecoder;
		return false;
	}

	DecodeReturn = pImageDecoder->GetImageType(pStreamSourceFile, &ImageType);

	if (DecodeReturn != IMAGE_RETURN_OK) {

		delete pStreamSourceFile;
		delete pImageDecoder;
		return false;
	}

	// Retrieves the image dimensions
	DecodeReturn = pImageDecoder->GetImageDimension(pStreamSourceFile,
			&ImageWidth, &ImageHeight);

	if (DecodeReturn != IMAGE_RETURN_OK) {

		delete pStreamSourceFile;
		delete pImageDecoder;
		return false;
	}

	pBuffer = CBuffer::CreateRectBuffer(ImageWidth, ImageHeight,
			CBuffer::BGR888);

	if (!pBuffer) {

		// Error in allocating the CBuffer for decoding:
		// free up the ImageDecoder and the file stream object
		// then return/exit
		delete pStreamSourceFile;
		delete pImageDecoder;
		return false;
	}

	pStreamSourceFile->Seek(0, 0);

	// Decode the full image and store it in the CBuffer (pBuffer) supplied
	DecodeReturn = pImageDecoder->Decode(pStreamSourceFile, ImageType, 0, 0, 0,
			0, pBuffer, 0);

	if (DecodeReturn != IMAGE_RETURN_OK) {

		pBuffer->Release();
		pBuffer = NULL;
		delete pStreamSourceFile;
		delete pImageDecoder;
		return false;
	}

	// Cleanup and free memory
	pStreamSourceFile->Close();
	delete pStreamSourceFile;
	delete pImageDecoder;

	return true;
}

