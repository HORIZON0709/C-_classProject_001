//================================================
//
//制作実践基礎[player.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//インクルード
//***************************
#include "player.h"
#include "application.h"

#include <assert.h>

//================================================
//生成
//================================================
CPlayer* CPlayer::Create()
{
	CPlayer* pPlayer = nullptr;	//ポインタ

	if (pPlayer != nullptr)
	{//NULLチェック
		assert(false);
	}

	/* nullptrの場合 */

	pPlayer = new CPlayer;	//メモリの動的確保

	pPlayer->Init("data/TEXTURE/百鬼あやめ_8.jpg");	//初期化

	return pPlayer;	//動的確保したものを返す
}

//================================================
//コンストラクタ
//================================================
CPlayer::CPlayer()
{
}

//================================================
//デストラクタ
//================================================
CPlayer::~CPlayer()
{
}

//================================================
//初期化
//================================================
HRESULT CPlayer::Init(const char* filePass)
{
	CObject2D::Init(filePass);	//親クラス

	//位置を設定
	D3DXVECTOR3 pos = D3DXVECTOR3((CRenderer::SCREEN_WIDTH * 0.5f), (CRenderer::SCREEN_HEIGHT * 0.5f), 0.0f);
	CObject2D::SetPos(pos);

	return S_OK;
}

//================================================
//終了
//================================================
void CPlayer::Uninit()
{
	CObject2D::Uninit();	//親クラス
}

//================================================
//更新
//================================================
void CPlayer::Update()
{
	CObject2D::Update();	//親クラス

	//CInputKeyboard input;	//キーボード
	//
	//if (input.GetPress(DIK_D))
	//{//右
	//	m_pos.x += 50.0f;
	//}
	//else if (input.GetPress(DIK_A))
	//{//左
	//	m_pos.x -= 50.0f;
	//}
}

//================================================
//描画
//================================================
void CPlayer::Draw()
{
	CObject2D::Draw();	//親クラス
}