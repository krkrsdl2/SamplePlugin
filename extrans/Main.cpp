//---------------------------------------------------------------------------
#if 0
#include <windows.h>

#include "tp_stub.h"
	// tp_stub.h と tp_stub.cpp は必ずプロジェクトに追加する
#define EXPORT(hr) extern "C" __declspec(dllexport) hr __stdcall
#endif
#include "ncbind/ncbind.hpp"
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

static void init_extrans()
{
	// トランジションハンドラプロバイダの登録
	RegisterWaveTransHandlerProvider();
	RegisterMosaicTransHandlerProvider();
	RegisterTurnTransHandlerProvider();
	RegisterRotateTransHandlerProvider();
	RegisterRippleTransHandlerProvider();
}

NCB_PRE_REGIST_CALLBACK(init_extrans);
