
#ifndef GDI_DRAW_DEVICE_H
#define GDI_DRAW_DEVICE_H

#include "tp_stub.h"
#include "BasicDrawDevice.h"

//---------------------------------------------------------------------------
//! @brief		�uGDI�v�f�o�C�X
//---------------------------------------------------------------------------
class tTVPGDIDrawDevice : public tTVPDrawDevice
{
	typedef tTVPDrawDevice inherited;

	HWND TargetWindow;
	bool IsMainWindow;
	HDRAWDIB DrawDibHandle;
	bool DrawUpdateRectangle;
	HDC TargetDC;
	HBITMAP OffScreenBitmap; //!< �I�t�X�N���[���r�b�g�}�b�v
	HDC OffScreenDC; //!< �I�t�X�N���[�� DC
	HBITMAP OldOffScreenBitmap; //!< OffScreenDC �ɈȑO�I������Ă��� �r�b�g�}�b�v
	bool ShouldShow; //!< show �Ŏ��ۂɉ�ʂɉ摜��]�����ׂ���


public:
	tTVPGDIDrawDevice(); //!< �R���X�g���N�^

private:
	~tTVPGDIDrawDevice(); //!< �f�X�g���N�^

	bool IsTargetWindowActive() const;

	void EnsureDrawer();
	void DestroyBitmap();
	void CreateBitmap();

public:
	void SetToRecreateDrawer() { DestroyBitmap(); }

public:
	void EnsureDevice();

//---- LayerManager �̊Ǘ��֘A
	virtual void TJS_INTF_METHOD AddLayerManager(iTVPLayerManager * manager);

//---- �`��ʒu�E�T�C�Y�֘A
	virtual void TJS_INTF_METHOD SetTargetWindow(HWND wnd, bool is_main);
	virtual void TJS_INTF_METHOD SetDestRectangle(const tTVPRect & rect);
	virtual void TJS_INTF_METHOD NotifyLayerResize(iTVPLayerManager * manager);

//---- �ĕ`��֘A
	virtual void TJS_INTF_METHOD Show();

//---- LayerManager ����̉摜�󂯓n���֘A
	virtual void TJS_INTF_METHOD StartBitmapCompletion(iTVPLayerManager * manager);
	virtual void TJS_INTF_METHOD NotifyBitmapCompleted(iTVPLayerManager * manager,
		tjs_int x, tjs_int y, const void * bits, const BITMAPINFO * bitmapinfo,
		const tTVPRect &cliprect, tTVPLayerType type, tjs_int opacity);
	virtual void TJS_INTF_METHOD EndBitmapCompletion(iTVPLayerManager * manager);

//---- �f�o�b�O�x��
	virtual void TJS_INTF_METHOD SetShowUpdateRect(bool b);
};
//---------------------------------------------------------------------------



#endif // GDI_DRAW_DEVICE_H