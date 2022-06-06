//=============================================================================
//
//メイン
//Author : 
//
//=============================================================================

//*****************************************************************************
//ライブラリーリンク
//*****************************************************************************
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"winmm.lib")

//*****************************************************************************
//インクルード
//*****************************************************************************
#include <Windows.h>
#include <tchar.h> //_T
#include <d3dx9.h>

//*****************************************************************************
//定数定義
//*****************************************************************************
namespace
{
	//ウインドウのクラス名
	LPCTSTR CLASS_NAME = _T("AppClass");
	//ウインドウのキャプション名
	LPCTSTR WINDOW_NAME = _T("ポリゴンの描画");
}

//スクリーンの幅
const int SCREEN_WIDTH = 1280;
//スクリーンの高さ
const int SCREEN_HEIGHT = 720;
//頂点フォーマット
const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

//*****************************************************************************
//構造体定義
//*****************************************************************************
//頂点データ
struct VERTEX_2D
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
};

//*****************************************************************************
//プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HWND hWnd, bool bWindow);
void Uninit();
void Update();
void Draw();

HRESULT InitPolygon();
void UninitPolygon();
void UpdatePolygon();
void DrawPolygon();

#ifdef _DEBUG
void DrawFPS();
#endif //_DEBUG

//*****************************************************************************
//グローバル変数
//*****************************************************************************
//Direct3Dオブジェクト
LPDIRECT3D9 g_pD3D = nullptr;
//Deviceオブジェクト
LPDIRECT3DDEVICE9 g_pD3DDevice = nullptr;
//頂点バッファ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff = nullptr;

//頂点情報
VERTEX_2D g_aVertex[4];


#ifdef _DEBUG
//フォント
LPD3DXFONT g_pFont = nullptr;
#endif //_DEBUG

#ifdef _DEBUG
//FPSカウンタ
int g_nCountFPS;
#endif //_DEBUG

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

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
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

	//初期化処理
	if (FAILED(Init(hWnd, TRUE)))
	{//初期化処理が失敗した場合
		return -1;
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
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;	//現在の時間を保存
				dwFrameCount = 0;
			}
#endif //_DEBUG

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{ //1/60秒経過
				//現在の時間を保存
				dwExecLastTime = dwCurrentTime;

				//更新処理
				Update();

				//描画処理
				Draw();

#ifdef _DEBUG
				dwFrameCount++;
#endif //_DEBUG
			}
		}
	}

	//終了処理
	Uninit();

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

//=============================================================================
//初期化
//=============================================================================
HRESULT Init(HWND hWnd, bool bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	//Direct3Dオブジェクトの作成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == nullptr)
	{
		return E_FAIL;
	}

	//現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));								//ワークをゼロクリア
	d3dpp.BackBufferCount = 1;							//バックバッファの数
	d3dpp.BackBufferWidth = SCREEN_WIDTH;				//ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;				//ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;				//カラーモードの指定
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;		//映像信号に同期してフリップする
	d3dpp.EnableAutoDepthStencil = TRUE;						//デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					//デプスバッファとして16bitを使う
	d3dpp.Windowed = bWindow;						//ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	//インターバル

	//ディスプレイアダプタを表すためのデバイスを作成
	//描画と頂点処理をハードウェアで行なう
	if ((FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice))) &&
		//上記の設定が失敗したら
		//描画をハードウェアで行い、頂点処理はCPUで行なう
		(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice))) &&
		//上記の設定が失敗したら
		//描画と頂点処理をCPUで行なう
		(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice))))
	{
		//生成失敗
		return E_FAIL;
	}

	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

#ifdef _DEBUG
	//デバッグ情報表示用フォントの生成
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &g_pFont);
#endif

	//ポリゴンの初期化処理
	InitPolygon();

	return S_OK;
}

//=============================================================================
//終了
//=============================================================================
void Uninit()
{
	//ポリゴンの終了処理
	UninitPolygon();

#ifdef _DEBUG
	//デバッグ情報表示用フォントの破棄
	if (g_pFont != nullptr)
	{
		g_pFont->Release();
		g_pFont = nullptr;
	}
#endif //_DEBUG

	//デバイスの破棄
	if (g_pD3DDevice != nullptr)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = nullptr;
	}

	//Direct3Dオブジェクトの破棄
	if (g_pD3D != nullptr)
	{
		g_pD3D->Release();
		g_pD3D = nullptr;
	}
}

//=============================================================================
//更新
//=============================================================================
void Update()
{
	//ポリゴンの更新処理
	UpdatePolygon();
}

//=============================================================================
//描画
//=============================================================================
void Draw()
{
	//バックバッファ＆Ｚバッファのクリア
	g_pD3DDevice->Clear(0, NULL,
						(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
						D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//Direct3Dによる描画の開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		//ポリゴンの描画処理
		DrawPolygon();

#ifdef _DEBUG
		//FPS表示
		DrawFPS();
#endif //_DEBUG

		//Direct3Dによる描画の終了
		g_pD3DDevice->EndScene();
	}

	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
//ポリゴンの初期化
//=============================================================================
HRESULT InitPolygon()
{
	//頂点バッファの生成
	g_pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&g_pVtxBuff,
								NULL);

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	D3DXVECTOR3 pos = D3DXVECTOR3((SCREEN_WIDTH * 0.5f), (SCREEN_HEIGHT * 0.5f), 0.0f);
	const float POLYGON_SIZE = 25.0f;

	//頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - POLYGON_SIZE, pos.y - POLYGON_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + POLYGON_SIZE, pos.y - POLYGON_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - POLYGON_SIZE, pos.y + POLYGON_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + POLYGON_SIZE, pos.y + POLYGON_SIZE, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
//ポリゴンの終了
//=============================================================================
void UninitPolygon()
{
	//頂点バッファの破棄
	if (g_pVtxBuff != nullptr)
	{
		g_pVtxBuff->Release();
		g_pVtxBuff = NULL;
	}
}

//=============================================================================
//ポリゴンの更新
//=============================================================================
void UpdatePolygon()
{
}

//=============================================================================
//ポリゴンの描画
//=============================================================================
void DrawPolygon()
{
	//頂点バッファをデータストリームに設定
	g_pD3DDevice->SetStreamSource(0, g_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	g_pD3DDevice->SetFVF(FVF_VERTEX_2D);

	//ポリゴンの描画
	g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
								0,						//描画する最初の頂点インデックス
								2);						//描画するプリミティブ数
}

#ifdef _DEBUG
//=============================================================================
//FPS表示
//=============================================================================
void DrawFPS()
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	TCHAR str[256];

	wsprintf(str, _T("FPS : %d\n"), g_nCountFPS);

	//テキスト描画
	g_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
#endif //_DEBUG
