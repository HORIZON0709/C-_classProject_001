//================================================
//
//制作実践基礎[object2D.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//インクルード
//***************************
#include "object2D.h"
#include "renderer.h"

#include <assert.h>

//***************************
//定数の定義
//***************************
const float CObject2D::ROTATION_SPEED = 0.05f;
const float CObject2D::POLYGON_SIZE = 100.0f;

//================================================
//生成
//================================================
CObject* CObject2D::Create()
{
	CObject* pObject = nullptr;	//ポインタ

	if (pObject != nullptr)
	{//NULLチェック
		assert(false);
	}

	/* nullptrの場合 */

	pObject = new CObject2D;	//メモリの動的確保

	pObject->Init();	//初期化

	return pObject;	//動的確保したものを返す
}

//================================================
//コンストラクタ
//================================================
CObject2D::CObject2D() : 
	m_pTexture(nullptr),
	m_pVtxBuff(nullptr),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)), 
	m_fLength(0.0f), 
	m_fAngle(0.0f), 
	m_fSize(0.0f),
	m_fCol(0.0f)
{
}

//================================================
//デストラクタ
//================================================
CObject2D::~CObject2D()
{
	/* 解放漏れの確認 */
	assert(m_pTexture == nullptr);
	assert(m_pVtxBuff == nullptr);
}

//================================================
//初期化
//================================================
HRESULT CObject2D::Init()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
								"data/TEXTURE/slack_icon.png",
								&m_pTexture);

	//位置
	m_pos = D3DXVECTOR3((CRenderer::SCREEN_WIDTH * 0.5f), (CRenderer::SCREEN_HEIGHT * 0.5f), 0.0f);

	//向き
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//サイズ
	m_fSize = POLYGON_SIZE;

	//対角線の長さを算出する
	m_fLength = sqrtf((m_fSize * m_fSize) + (m_fSize * m_fSize)) * 0.5f;

	//対角線の角度を算出する
	m_fAngle = atan2f(m_fSize, m_fSize);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&m_pVtxBuff,
								NULL);

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点情報を設定
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z + (m_fAngle * -D3DX_PI)) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z + (m_fAngle * -D3DX_PI)) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + (m_fAngle * D3DX_PI)) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + (m_fAngle * D3DX_PI)) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z + (m_fAngle * -1.0f)) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z + (m_fAngle * -1.0f)) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.z = 0.0f;

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

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//================================================
//終了
//================================================
void CObject2D::Uninit()
{
	//頂点バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//テクスチャの破棄
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
}

//================================================
//更新
//================================================
void CObject2D::Update()
{
	m_rot.z -= ROTATION_SPEED;	//回転

	/* 角度の正規化 */
	if (m_rot.z >= D3DX_PI)
	{// 3.14より大きい
		m_rot.z -= D3DX_PI * 2.0f;
	}
	else if (m_rot.z <= -D3DX_PI)
	{// -3.14より小さい
		m_rot.z += D3DX_PI * 2.0f;
	}

	//サイズの拡大・縮小
	m_fSize += cosf(m_rot.z) * 2.0f;

	//対角線の長さを再計算
	m_fLength = sqrtf((m_fSize * m_fSize) + (m_fSize * m_fSize)) * 0.5f;

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の更新
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z + (m_fAngle * -3.0f)) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z + (m_fAngle * -3.0f)) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + (m_fAngle * 3.0f)) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + (m_fAngle * 3.0f)) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z + (m_fAngle * -1.0f)) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z + (m_fAngle * -1.0f)) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	/* ↓色で遊んだ↓ */

	m_fCol += 0.1f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(cosf(m_fCol * 0.7f), cosf(m_fCol * 0.2f), cosf(m_fCol * 0.9f), 1.0f);
	pVtx[1].col = D3DXCOLOR(cosf(m_fCol * 0.3f), cosf(m_fCol * 0.4f), cosf(m_fCol * 0.7f), 1.0f);
	pVtx[2].col = D3DXCOLOR(cosf(m_fCol * 0.9f), cosf(m_fCol * 0.6f), cosf(m_fCol * 0.5f), 1.0f);
	pVtx[3].col = D3DXCOLOR(cosf(m_fCol * 1.0f), cosf(m_fCol * 0.8f), cosf(m_fCol * 0.3f), 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================
//描画
//================================================
void CObject2D::Draw()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetRenderer()->GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
							0,					//描画する最初の頂点インデックス
							2);					//描画するプリミティブ数
}

//================================================
//位置を設定
//================================================
void CObject2D::SetPos(const D3DXVECTOR3 &pos)
{
	m_pos = pos;
}

//================================================
//位置を取得
//================================================
D3DXVECTOR3 CObject2D::GetPos()
{
	return m_pos;
}