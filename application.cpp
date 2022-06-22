//================================================
//
//制作実践基礎[application.h]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//インクルード
//***************************
#include "application.h"
#include "object2D.h"

//***************************
//静的メンバ変数
//***************************
CRenderer* CApplication::m_pRenderer = nullptr;		//レンダラー
CInput* CApplication::m_pInputKeyboard = nullptr;	//キーボード
CPlayer* CApplication::m_pPlayer = nullptr;			//プレイヤー

//================================================
//レンダラー情報を取得
//================================================
CRenderer* CApplication::GetRenderer()
{
	return m_pRenderer;
}

//================================================
//キーボード情報を取得
//================================================
CInput* CApplication::GetInputKeyboard()
{
	return m_pInputKeyboard;
}

//================================================
//プレイヤー情報を取得
//================================================
CPlayer* CApplication::GetPlayer()
{
	return m_pPlayer;
}

//================================================
//コンストラクタ
//================================================
CApplication::CApplication()
{
}

//================================================
//デストラクタ
//================================================
CApplication::~CApplication()
{
}

//================================================
//初期化
//================================================
HRESULT CApplication::Init(HWND hWnd, BOOL bWindow, HINSTANCE hInstance)
{
	/* キーボード */

	if (m_pInputKeyboard == nullptr)
	{//NULLチェック
		m_pInputKeyboard = new CInputKeyboard;	//メモリの動的確保
	}

	if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
	{//初期化処理が失敗した場合
		return E_FAIL;
	}

	/* レンダラー */

	if (m_pRenderer == nullptr)
	{//NULLチェック
		m_pRenderer = new CRenderer;	//メモリの動的確保
	}

	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{//初期化処理が失敗した場合
		return E_FAIL;
	}

	/* オブジェクト */

	CObject2D::CreateAll();	//全ての生成

	/* プレイヤー */

	m_pPlayer = CPlayer::Create();	//生成

	return S_OK;
}

//================================================
//終了
//================================================
void CApplication::Uninit()
{
	/* キーボード */

	if (m_pInputKeyboard != nullptr)
	{//NULLチェック
		m_pInputKeyboard->Uninit();	//終了処理
		delete m_pInputKeyboard;	//メモリの解放
		m_pInputKeyboard = nullptr;	//nullptrにする
	}

	/* プレイヤー */

	if (m_pPlayer != nullptr)
	{//NULLチェック
		m_pPlayer->Uninit();	//終了処理
		delete m_pPlayer;		//メモリの解放
		m_pPlayer = nullptr;	//nullptrにする
	}

	/* オブジェクト */

	CObject2D::ReleaseAll();	//全ての解放

	/* レンダラー */

	if (m_pRenderer != nullptr)
	{//NULLチェック
		m_pRenderer->Uninit();	//終了処理
		delete m_pRenderer;		//メモリの解放
		m_pRenderer = nullptr;	//nullptrにする
	}
}

//================================================
//更新
//================================================
void CApplication::Update()
{
	if (m_pInputKeyboard != nullptr)
	{//NULLチェック
		m_pInputKeyboard->Update();	//キーボード
	}

	if (m_pRenderer != nullptr)
	{//NULLチェック
		m_pRenderer->Update();	//レンダラー
	}

	if (m_pPlayer != nullptr)
	{//NULLチェック
		m_pPlayer->Update();	//プレイヤー
	}
}

//================================================
//描画
//================================================
void CApplication::Draw()
{
	if (m_pRenderer != nullptr)
	{//NULLチェック
		m_pRenderer->Draw();	//レンダラー
	}

	if (m_pPlayer != nullptr)
	{//NULLチェック
		m_pPlayer->Draw();	//プレイヤー
	}
}