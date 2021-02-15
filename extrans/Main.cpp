//---------------------------------------------------------------------------
#if 0
#include <windows.h>

#include "tp_stub.h"
	// tp_stub.h と tp_stub.cpp は必ずプロジェクトに追加する
#define EXPORT(hr) extern "C" __declspec(dllexport) hr __stdcall
#endif
#include "tp_stub.h"
#include "wave.h"
#include "mosaic.h"
#include "turn.h"
#include "rotatetrans.h"
#include "ripple.h"

#if 0
//---------------------------------------------------------------------------
#pragma argsused
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
	// DLL エントリポイント
	return 1;
}
//---------------------------------------------------------------------------
// V2Link は DLL がリンクされるときに実行される
EXPORT(HRESULT) V2Link(iTVPFunctionExporter *exporter)
{
	// スタブの初期化
	TVPInitImportStub(exporter); // 必ずこれは記述
	/*
		TVPInitImpotStub を実行した後は吉里吉里内部の各関数や tTJSVariant 等の
		基本的な型が使用可能になる。
	*/

	// トランジションハンドラプロバイダの登録
	RegisterWaveTransHandlerProvider();
	RegisterMosaicTransHandlerProvider();
	RegisterTurnTransHandlerProvider();
	RegisterRotateTransHandlerProvider();
	RegisterRippleTransHandlerProvider();

	return S_OK;
}
//---------------------------------------------------------------------------
// V2Unlink は DLL がアンリンクされるときに実行される
EXPORT(HRESULT) V2Unlink()
{
	// トランジションハンドラプロバイダの登録削除
	UnregisterWaveTransHandlerProvider();
	UnregisterMosaicTransHandlerProvider();
	UnregisterTurnTransHandlerProvider();
	UnregisterRotateTransHandlerProvider();
	UnregisterRippleTransHandlerProvider();

	// スタブの使用終了
	TVPUninitImportStub(); // 必ずこれは記述
	/*
		TVPUninitImpotStub は TVPInitImportStub で確保したメモリを解放する
		ので必ず記述する。
	*/
	return S_OK;
}
//---------------------------------------------------------------------------
/*
	V2Link と V2Unlink は DLL からエクスポートされている必要がある。
	従って、.def ファイルを作成し

EXPORTS
	V2Link
	V2Unlink

	と記述してプロジェクトに追加する必要がある。
*/
//---------------------------------------------------------------------------
#endif

//---------------------------------------------------------------------------
// tTJSNC_ExtransInternal : extrans internal class
//---------------------------------------------------------------------------
class tTJSNC_ExtransInternal : public tTJSNativeClass
{
public:
	tTJSNC_ExtransInternal();

	static tjs_uint32 ClassID;

protected:
	tTJSNativeInstance * CreateNativeInstance();
};

//---------------------------------------------------------------------------
// tTJSNC_ExtransInternal
//---------------------------------------------------------------------------
tjs_uint32 tTJSNC_ExtransInternal::ClassID = -1;
tTJSNC_ExtransInternal::tTJSNC_ExtransInternal() : tTJSNativeClass(TJS_W("ExtransInternal"))
{
	TJS_BEGIN_NATIVE_MEMBERS(ExtransInternal)
	TJS_DECL_EMPTY_FINALIZE_METHOD
//----------------------------------------------------------------------
TJS_BEGIN_NATIVE_CONSTRUCTOR_DECL_NO_INSTANCE(/*TJS class name*/ExtransInternal)
{
	return TJS_S_OK;
}
TJS_END_NATIVE_CONSTRUCTOR_DECL(/*TJS class name*/ExtransInternal)
//----------------------------------------------------------------------

//----------------------------------------------------------------------
	TJS_END_NATIVE_MEMBERS

} // end of tTJSNC_ExtransInternal::tTJSNC_ExtransInternal
//---------------------------------------------------------------------------
tTJSNativeInstance *tTJSNC_ExtransInternal::CreateNativeInstance()
{
	return NULL;
}
static iTJSDispatch2 * TVPCreateNativeClass_ExtransInternal(iTJSDispatch2* global)
{
	// トランジションハンドラプロバイダの登録
	RegisterWaveTransHandlerProvider();
	RegisterMosaicTransHandlerProvider();
	RegisterTurnTransHandlerProvider();
	RegisterRotateTransHandlerProvider();
	RegisterRippleTransHandlerProvider();
	iTJSDispatch2 *cls = new tTJSNC_ExtransInternal();
	return cls;
}

static tTVPAtInstallClass TVPInstallClassExtransInternal(TJS_W("ExtransInternal"), TVPCreateNativeClass_ExtransInternal, TJS_W(""));
