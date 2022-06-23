//================================================
//
//制作実践基礎[explosion.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//インクルード
//***************************
#include "explosion.h"
#include "renderer.h"

#include <assert.h>

//***************************
//定数の定義
//***************************
const float CExplosion::EXPLOSION_SIZE = 30.0f;	//サイズ

//================================================
//生成
//================================================
CExplosion* CExplosion::Create(D3DXVECTOR3 pos)
{
	CExplosion* pExplosion = nullptr;	//ポインタ

	if (pExplosion != nullptr)
	{//NULLチェック
		assert(false);
	}

	/* nullptrの場合 */

	pExplosion = new CExplosion;	//メモリの動的確保

	pExplosion->Init();	//初期化

	pExplosion->SetPos(pos, EXPLOSION_SIZE);	//位置を設定

	return pExplosion;	//動的確保したものを返す
}

//================================================
//コンストラクタ
//================================================
CExplosion::CExplosion()
{
}

//================================================
//デストラクタ
//================================================
CExplosion::~CExplosion()
{
}

//================================================
//初期化
//================================================
HRESULT CExplosion::Init()
{
	CObject2D::Init();	//親クラス

	//位置を設定
	D3DXVECTOR3 pos = D3DXVECTOR3((CRenderer::SCREEN_WIDTH * 0.8f), (CRenderer::SCREEN_HEIGHT * 0.5f), 0.0f);
	CObject2D::SetPos(pos, EXPLOSION_SIZE);

	// テクスチャの設定
	CObject2D::SetTexture(CTexture::TEXTURE_explosion000);

	return S_OK;
}

//================================================
//終了
//================================================
void CExplosion::Uninit()
{
	CObject2D::Uninit();	//親クラス
}

//================================================
//更新
//================================================
void CExplosion::Update()
{
	CObject2D::Update();	//親クラス

	m_nCntAnim++;

	if (m_nCntAnim % 10 == 0)
	{//一定間隔
		//パターン番号を更新する
		m_nPtnAnim = (m_nPtnAnim + 1) % DIVIDE_TEX_U;

		//テクスチャ座標の設定
		CObject2D::SetAnimTexUV(DIVIDE_TEX_U, m_nPtnAnim);

		Release();	//解放
	}
}

//================================================
//描画
//================================================
void CExplosion::Draw()
{
	CObject2D::Draw();	//親クラス
}