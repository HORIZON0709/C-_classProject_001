//=============================================================================
//
//メイン
//Author : 
//
//=============================================================================
//***************************
//インクルード
//***************************
#include "renderer.h"
#include "object2D.h"

#include <assert.h>

//***************************
//定数定義
//***************************
namespace
{
//ウインドウのクラス名
LPCTSTR CLASS_NAME = _T("AppClass");
//ウインドウのキャプション名
LPCTSTR WINDOW_NAME = _T("ポリゴンの描画");
}

//*****************************************************************************
//プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//***************************
//スタティック変数
//***************************
namespace
{
int s_nCountFPS;	//FPSカウンタ
CRenderer* s_pRenderer = nullptr;					//レンダリングのポインタ
CObject* s_apObject[CRenderer::MAX_POLYGON] = {};	//オブジェクトのポインタ
}//namespaceはここまで

 //=============================================================================
//メイン関数
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};

	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	RECT rect = { 0, 0, CRenderer::SCREEN_WIDTH, CRenderer::SCREEN_HEIGHT };
	//指定したクライアント領域を確保するために必要なウィンドウ座標を計算
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウィンドウの作成
	HWND hWnd = CreateWindow(CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(rect.right - rect.left),
		(rect.bottom - rect.top),
		NULL,
		NULL,
		hInstance,
		NULL);

	if (s_pRenderer == nullptr)
	{//NULLチェック
		s_pRenderer = new CRenderer;	//メモリの動的確保
	}

	for (int i = 0; i < CRenderer::MAX_POLYGON; i++)
	{
		if (s_apObject[i] != nullptr)
		{//NULLチェック
			continue;
		}

		/* nullptrの場合 */

		s_apObject[i] = new CObject2D;	//メモリの動的確保
	}

	//初期化処理
	if (FAILED(s_pRenderer->Init(hWnd, TRUE)))
	{//初期化処理が失敗した場合
		return -1;
	}

	//オブジェクトの初期化
	for (int i = 0; i < CRenderer::MAX_POLYGON; i++)
	{
		if (FAILED(s_apObject[i]->Init()))
		{//初期化処理が失敗した場合
			assert(false);
			return -1;
		}

		//生成数が増える毎に位置をずらす
		D3DXVECTOR3 pos = D3DXVECTOR3((CRenderer::SCREEN_WIDTH * (0.1f * (i + 1))), (CRenderer::SCREEN_HEIGHT * 0.1f), 0.0f);
		s_apObject[i]->SetPos(pos);
	}

	//分解能を設定
	timeBeginPeriod(1);

	//フレームカウント初期化
	DWORD dwCurrentTime = 0;
	DWORD dwExecLastTime = timeGetTime();
#ifdef _DEBUG
	DWORD dwFrameCount = 0;
	DWORD dwFPSLastTime = dwExecLastTime;
#endif //_DEBUG

	//ウインドウの表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;

	//メッセージループ
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{ //PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				//メッセージの翻訳とディスパッチ
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();	//現在の時間を取得
#ifdef _DEBUG
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5秒ごとに実行
				//FPSを算出
				s_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;	//現在の時間を保存
				dwFrameCount = 0;
			}
#endif //_DEBUG

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{ //1/60秒経過
				//現在の時間を保存
				dwExecLastTime = dwCurrentTime;

				//更新処理
				s_pRenderer->Update();

				//描画処理
				s_pRenderer->Draw();

#ifdef _DEBUG
				dwFrameCount++;
#endif //_DEBUG
			}
		}
	}

	for (int i = 0; i < CRenderer::MAX_POLYGON; i++)
	{
		if (s_apObject[i] != nullptr)
		{//NULLチェック
			s_apObject[i]->Uninit();	//終了処理
			delete s_apObject[i];	//メモリの解放
			s_apObject[i] = nullptr;	//nullptrにする
		}
	}

	if (s_pRenderer != nullptr)
	{//NULLチェック
		s_pRenderer->Uninit();	//終了処理
		delete s_pRenderer;		//メモリの解放
		s_pRenderer = nullptr;	//nullptrにする
	}

	//ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	//分解能を戻す
	timeEndPeriod(1);

	return (int)msg.wParam;
}

//=============================================================================
//ウインドウプロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE: //[ESC]キーが押された
			//ウィンドウを破棄
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//================================================
//FPSの取得
//================================================
int GetFPS()
{
	return s_nCountFPS;
}

//================================================
//レンダリング情報の取得
//================================================
CRenderer* GetRenderer()
{
	return s_pRenderer;
}

//================================================
//オブジェクト情報の取得
//================================================
CObject** GetObjects()
{
	return &s_apObject[0];
}