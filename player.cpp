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
#include "inputKeyboard.h"

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

	m_pos = D3DXVECTOR3((CRenderer::SCREEN_WIDTH * 0.5f), (CRenderer::SCREEN_HEIGHT * 0.5f), 0.0f);

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

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//長いから短くする
	float fLeft		= (m_pos.x - m_fSize);
	float fRight	= (m_pos.x + m_fSize);
	float fTop		= (m_pos.y + m_fSize);
	float fBottom	= (m_pos.y - m_fSize);

	//頂点情報を更新
	pVtx[0].pos = D3DXVECTOR3(fLeft, fTop, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(fRight, fTop, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(fLeft, fBottom, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(fRight, fBottom, 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================
//描画
//================================================
void CPlayer::Draw()
{
	CObject2D::Draw();	//親クラス
}