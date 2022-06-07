//================================================
//
//制作実践基礎[object.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "main.h"

//***************************
//定数の定義
//***************************
const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE);	//頂点フォーマット

//***************************
//オブジェクトクラスの定義
//***************************
class CObject
{/* 基本クラス */
public: /* 構造体の定義 */
	struct VERTEX_2D
	{//頂点データ
		D3DXVECTOR3 pos;	//位置
		float rhw;			//法線
		D3DCOLOR col;		//色
	};

private: /* 定数の定義 */
	/* 自分で追加したもの */
	const float ROTATION_SPEED = 0.05f;	//回転スピード
	const float POLYGON_SIZE = 100.0f;	//サイズ

public: /* コンストラクタ・デストラクタ */
	CObject();
	~CObject();

public: /* メンバ関数 */
	HRESULT Init();		//初期化
	void Uninit();		//終了
	void Update();		//更新
	void Draw();		//描画

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