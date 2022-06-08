//================================================
//
//制作実践基礎[object2D.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

#include "main.h"
#include "object.h"

//***************************
//オブジェクトクラスの定義
//***************************
class CObject2D : public CObject
{/* CObjectの派生クラス */
private: /* 定数の定義 */
	const float ROTATION_SPEED = 0.05f;	//回転スピード
	const float POLYGON_SIZE = 100.0f;	//サイズ

public: /* コンストラクタ・デストラクタ */
	CObject2D();
	~CObject2D();

public: /* メンバ関数 */
	HRESULT Init()override;	//初期化
	void Uninit()override;	//終了
	void Update()override;	//更新
	void Draw()override;	//描画

private: /* メンバ変数 */
	LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;					//位置
	D3DXVECTOR3 m_rot;					//向き
	float m_fLength;					//対角線の長さ
	float m_fAngle;						//対角線の角度
	float m_fSize;						//サイズ
	float m_fCol;						//色
};

#endif