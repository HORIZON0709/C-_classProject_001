//================================================
//
//制作実践基礎[bullet.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//インクルード
//***************************
#include "bullet.h"
#include "renderer.h"
#include "explosion.h"

#include <assert.h>

//***************************
//定数の定義
//***************************
const float CBullet::BULLET_SIZE = 50.0f;	//サイズ

//================================================
//生成
//================================================
CBullet* CBullet::Create(D3DXVECTOR3 pos)
{
	CBullet* pBullet = nullptr;	//ポインタ

	if (pBullet != nullptr)
	{//NULLチェック
		assert(false);
	}

	/* nullptrの場合 */

	pBullet = new CBullet;	//メモリの動的確保

	pBullet->Init();	//初期化

	pBullet->SetPos(pos, BULLET_SIZE);	//位置を設定

	return pBullet;	//動的確保したものを返す
}

//================================================
//コンストラクタ
//================================================
CBullet::CBullet()
{
}

//================================================
//デストラクタ
//================================================
CBullet::~CBullet()
{
}

//================================================
//初期化
//================================================
HRESULT CBullet::Init()
{
	CObject2D::Init();	//親クラス

	//位置を設定
	D3DXVECTOR3 pos = D3DXVECTOR3((CRenderer::SCREEN_WIDTH * 0.8f), (CRenderer::SCREEN_HEIGHT * 0.5f), 0.0f);
	CObject2D::SetPos(pos, BULLET_SIZE);

	//移動量を設定
	m_move = D3DXVECTOR3(0.0f, 10.0f, 0.0f);

	// テクスチャの設定
	CObject2D::SetTexture(CTexture::TEXTURE_circle_sakura2);

	return S_OK;
}

//================================================
//終了
//================================================
void CBullet::Uninit()
{
	CObject2D::Uninit();	//親クラス
}

//================================================
//更新
//================================================
void CBullet::Update()
{
	CObject2D::Update();	//親クラス

	D3DXVECTOR3 pos = CObject2D::GetPos();	//位置設定用

	pos.y -= m_move.y;	//位置を更新

	CObject2D::SetPos(pos, BULLET_SIZE);	//更新した位置を設定

	if ((pos.x < 0) || (pos.x > CRenderer::SCREEN_WIDTH) ||
		(pos.y < 0) || (pos.y > CRenderer::SCREEN_HEIGHT))
	{//画面外に出たら
		Release();	//解放

		CExplosion* pExplosion = CExplosion::Create(pos);	//爆発の生成

		pExplosion->Update();	//爆発の更新
	}
}

//================================================
//描画
//================================================
void CBullet::Draw()
{
	CObject2D::Draw();	//親クラス
}