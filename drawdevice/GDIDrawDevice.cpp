
#define NOMINMAX

#include <windows.h>
#include <stdio.h>
#include <vfw.h>
#include "tp_stub.h"
#include "GDIDrawDevice.h"

//---------------------------------------------------------------------------
// �I�v�V����
//---------------------------------------------------------------------------
static tjs_int TVPPassThroughOptionsGeneration = 0;
bool TVPZoomInterpolation = true;
//---------------------------------------------------------------------------
static void TVPInitGDIOptions()
{
	if(TVPPassThroughOptionsGeneration == TVPGetCommandLineArgumentGeneration()) return;
	TVPPassThroughOptionsGeneration = TVPGetCommandLineArgumentGeneration();

	tTJSVariant val;
	TVPZoomInterpolation = true;
	if(TVPGetCommandLine(TJS_W("-smoothzoom"), &val))
	{
		ttstr str(val);
		if(str == TJS_W("no"))
			TVPZoomInterpolation = false;
		else
			TVPZoomInterpolation = true;
	}
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
tTVPGDIDrawDevice::tTVPGDIDrawDevice()
{
	TVPInitGDIOptions(); // read and initialize options
	TargetWindow = NULL;

	DrawDibHandle = NULL;
	DrawUpdateRectangle = false;
	TargetDC = NULL;
	OffScreenBitmap = NULL;
	OffScreenDC = NULL;
	OldOffScreenBitmap = NULL;
	ShouldShow = false;
}
//---------------------------------------------------------------------------
tTVPGDIDrawDevice::~tTVPGDIDrawDevice()
{
	DestroyBitmap();
	if(TargetDC && TargetWindow) ::ReleaseDC(TargetWindow, TargetDC);
	if(DrawDibHandle) ::DrawDibClose(DrawDibHandle), DrawDibHandle = NULL;
}
//---------------------------------------------------------------------------
void tTVPGDIDrawDevice::DestroyBitmap()
{
	if(OffScreenBitmap && OffScreenDC) {
		::SelectObject(OffScreenDC, OldOffScreenBitmap), OldOffScreenBitmap = NULL;
		if(OffScreenBitmap) ::DeleteObject(OffScreenBitmap), OffScreenBitmap = NULL;
		if(OffScreenDC)     ::DeleteDC(OffScreenDC), OffScreenDC = NULL;
	}
}
//---------------------------------------------------------------------------
void tTVPGDIDrawDevice::CreateBitmap()
{
	// �X�N���[���݊��� DDB ���쐬����B
	// ����͂����Ă��̏ꍇ�A�r�f�I��������ɍ쐬�����B
	DestroyBitmap();
	tjs_int w, h;
	GetSrcSize( w, h );
	if(TargetWindow && w > 0 && h > 0) {
		try {
			HDC screendc = ::GetDC(TargetWindow);
			if(!screendc) TVPThrowExceptionMessage(TJS_W("Failed to create screen DC"));
			OffScreenBitmap = ::CreateCompatibleBitmap(screendc, w, h);
			if(!OffScreenBitmap) TVPThrowExceptionMessage(TJS_W("Failed to create offscreen bitmap"));
			OffScreenDC     = ::CreateCompatibleDC(screendc);
			if(!OffScreenDC) TVPThrowExceptionMessage(TJS_W("Failed to create offscreen DC"));
			::ReleaseDC(TargetWindow, screendc);
			OldOffScreenBitmap = (HBITMAP)::SelectObject(OffScreenDC, OffScreenBitmap);
		} catch(...) {
			DestroyBitmap();
			throw;
		}
	}
}
//---------------------------------------------------------------------------
bool tTVPGDIDrawDevice::IsTargetWindowActive() const {
	if( TargetWindow == NULL ) return false;
	return ::GetForegroundWindow() == TargetWindow;
}
//---------------------------------------------------------------------------
void tTVPGDIDrawDevice::EnsureDrawer()
{
	TVPInitGDIOptions();
	if(!OffScreenBitmap || !OffScreenDC){
		CreateBitmap();
	}
}
//---------------------------------------------------------------------------
void TJS_INTF_METHOD tTVPGDIDrawDevice::AddLayerManager(iTVPLayerManager * manager)
{
	if(inherited::Managers.size() > 0)
	{
		// "GDI" �f�o�C�X�ł͂Q�ȏ��Layer Manager��o�^�ł��Ȃ�
		TVPThrowExceptionMessage(TJS_W("\"GDI\" device does not support layer manager more than 1"));
	}
	inherited::AddLayerManager(manager);

	manager->SetDesiredLayerType(ltOpaque); // ltOpaque �ȏo�͂��󂯎�肽��
}
//---------------------------------------------------------------------------
void TJS_INTF_METHOD tTVPGDIDrawDevice::SetTargetWindow(HWND wnd, bool is_main)
{
	TVPInitGDIOptions();
	if( wnd ) {
		// �`��p DC ���擾����
		TargetDC = ::GetDC(wnd);
	} else {
		// �`��p DC ���J������
		if(TargetDC) ::ReleaseDC(TargetWindow, TargetDC), TargetDC = NULL;
	}

	if(DrawDibHandle) ::DrawDibClose(DrawDibHandle), DrawDibHandle = NULL;
	TargetWindow = wnd;
	IsMainWindow = is_main;
	DrawDibHandle = DrawDibOpen();

	CreateBitmap();
}
//---------------------------------------------------------------------------
void TJS_INTF_METHOD tTVPGDIDrawDevice::SetDestRectangle(const tTVPRect & rect)
{
	// �ʒu�����̕ύX�̏ꍇ���ǂ������`�F�b�N����
	if(rect.get_width() == DestRect.get_width() && rect.get_height() == DestRect.get_height()) {
		// �ʒu�����̕ύX��
		inherited::SetDestRectangle(rect);
	} else {
		// �T�C�Y���Ⴄ
		inherited::SetDestRectangle(rect);
		DestroyBitmap();
		EnsureDrawer();
	}
}
//---------------------------------------------------------------------------
void TJS_INTF_METHOD tTVPGDIDrawDevice::NotifyLayerResize(iTVPLayerManager * manager)
{
	inherited::NotifyLayerResize(manager);
	CreateBitmap();
}
//---------------------------------------------------------------------------
void TJS_INTF_METHOD tTVPGDIDrawDevice::Show()
{
	// TODO ClipRect �̍l���������Ă���
	if(TargetDC && OffScreenDC && ShouldShow) {
		// �I�t�X�N���[���r�b�g�}�b�v�� TargetDC �ɓ]������
		tjs_int srcw, srch;
		GetSrcSize( srcw, srch );
		tjs_int dstw = DestRect.get_width();
		tjs_int dsth = DestRect.get_height();
		if(dstw == srcw && dsth == srch) {
			// �g��E�k���͕K�v�Ȃ�
			::BitBlt(TargetDC,
				DestRect.left,
				DestRect.top,
				dstw,
				dsth,
				OffScreenDC,
				0,
				0,
				SRCCOPY);
		} else {
			// �g��E�k�����K�v
			if(TVPZoomInterpolation)
				SetStretchBltMode(TargetDC, HALFTONE);
			else
				SetStretchBltMode(TargetDC, COLORONCOLOR);
			::SetBrushOrgEx(TargetDC, 0, 0, NULL);

			::StretchBlt(TargetDC,
				DestRect.left,
				DestRect.top,
				dstw,
				dsth,
				OffScreenDC,
				0,
				0,
				srcw,
				srch,
				SRCCOPY);
		}
		ShouldShow = false;
	}
}
//---------------------------------------------------------------------------
void TJS_INTF_METHOD tTVPGDIDrawDevice::StartBitmapCompletion(iTVPLayerManager * manager)
{
	EnsureDrawer();
}
//---------------------------------------------------------------------------
void TJS_INTF_METHOD tTVPGDIDrawDevice::NotifyBitmapCompleted(iTVPLayerManager * manager,
	tjs_int x, tjs_int y, const void * bits, const BITMAPINFO * bitmapinfo,
	const tTVPRect &cliprect, tTVPLayerType type, tjs_int opacity)
{
	TVPInitGDIOptions();
	// DrawDibDraw �ɂ� OffScreenDC �ɕ`����s��
	if(DrawDibHandle && OffScreenDC) {
		ShouldShow = true;
		::DrawDibDraw(DrawDibHandle,
			OffScreenDC,
			x,
			y,
			cliprect.get_width(),
			cliprect.get_height(),
			const_cast<BITMAPINFOHEADER*>(reinterpret_cast<const BITMAPINFOHEADER*>(bitmapinfo)),
			const_cast<void*>(bits),
			cliprect.left,
			cliprect.top,
			cliprect.get_width(),
			cliprect.get_height(),
			0);
	}
}
//---------------------------------------------------------------------------
void TJS_INTF_METHOD tTVPGDIDrawDevice::EndBitmapCompletion(iTVPLayerManager * manager)
{
	// ��邱�ƂȂ�
}
//---------------------------------------------------------------------------
void TJS_INTF_METHOD tTVPGDIDrawDevice::SetShowUpdateRect(bool b)
{
	DrawUpdateRectangle = b;
}
//---------------------------------------------------------------------------

