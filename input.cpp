//================================================
//
//制作実践基礎[input.h]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//インクルード
//***************************
#include "input.h"
#include "inputKeyboard.h"

//***************************
//静的メンバ変数
//***************************
LPDIRECTINPUT8 CInput::m_pInput = nullptr;

//================================================
//コンストラクタ
//================================================
CInput::CInput():
	m_pDevice(nullptr),
	m_nKeyCnt(0),
	m_pInputKeyboard(nullptr)
{
}

//================================================
//デストラクタ
//================================================
CInput::~CInput()
{
}

//================================================
//初期化
//================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	m_nKeyCnt = 0;	//カウントを初期化

	if (m_pInputKeyboard != nullptr)
	{//NULLチェック
		m_pInputKeyboard = nullptr;
	}

	/* nullptrの場合 */

	m_pInputKeyboard = new CInputKeyboard;	//メモリの動的確保

	//キーボードの初期化処理
	if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//================================================
//終了
//================================================
void CInput::Uninit()
{
	//キーボードの終了処理
	m_pInputKeyboard->Uninit();
}