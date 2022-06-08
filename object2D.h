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
public: /* 構造体の定義 */
	struct VERTEX_2D
	{//頂点データ
		D3DXVECTOR3 pos;	//位置
		float rhw;			//法線
		D3DCOLOR col;		//色
	};

private: /* 定数の定義 */
	const float ROTATION_SPEED = 0.05f;	//回転スピード
	const float POLYGON_SIZE = 100.0f;	//サイズ
public:
	static const int MAX_POLYGON = 5;	//ポリゴンの最大数

public: /* コンストラクタ・デストラクタ */
	CObject2D();
	~CObject2D();

public: /* メンバ関数 */
	HRESULT Init()override;	//初期化
	void Uninit()override;	//終了
	void Update()override;	//更新
	void Draw()override;	//描画
public: /* Set,Get系 */
	void SetPos(const D3DXVECTOR3 &pos)override;	//位置を設定
	D3DXVECTOR3 GetPos()override;					//位置を取得

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