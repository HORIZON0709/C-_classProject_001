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
#include "renderer.h"
#include "input.h"

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

	pPlayer->Init();	//初期化

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
HRESULT CPlayer::Init()
{
	CObject2D::Init();	//親クラス

	//位置を設定
	D3DXVECTOR3 pos = D3DXVECTOR3((CRenderer::SCREEN_WIDTH * 0.5f), (CRenderer::SCREEN_HEIGHT * 0.5f), 0.0f);
	CObject2D::SetPos(pos);

	// テクスチャの設定
	CObject2D::SetTexture(CTexture::TEXTURE_百鬼あやめ_8);

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

	CInput* pInput = CInput::GetKey();	//キーボード
	D3DXVECTOR3 pos;					//位置設定用

	/* 移動 */

	if (pInput->Press(CInput::STANDARD_KEY::RIGHT))
	{//右
		pos.x += 50.0f;
	}
	else if (pInput->Press(CInput::STANDARD_KEY::LEFT))
	{//左
		pos.x -= 50.0f;
	}

	CObject2D::SetPos(pos);	//位置を更新
}

//================================================
//描画
//================================================
void CPlayer::Draw()
{
	CObject2D::Draw();	//親クラス
}