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
CRenderer* CApplication::m_pRenderer = nullptr;				//レンダラー
CInputKeyboard* CApplication::m_pInputKeyboard = nullptr;	//キーボード

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
CInputKeyboard* CApplication::GetInputKeyboard()
{
	return m_pInputKeyboard;
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

	return S_OK;
}

//================================================
//終了
//================================================
void CApplication::Uninit()
{
	CObject2D::ReleaseAll();	//全ての解放

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
	m_pRenderer->Update();	//レンダラー
}

//================================================
//描画
//================================================
void CApplication::Draw()
{
	m_pRenderer->Draw();	//レンダラー
}