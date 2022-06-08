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
	const float ROTATION_SPEED = 0.05f;	//回転スピード
	const float POLYGON_SIZE = 100.0f;	//サイズ

public: /* コンストラクタ・デストラクタ */
	CObject();
	virtual ~CObject();

public: /* 純粋仮想関数 */
	virtual HRESULT Init() = 0;	//初期化
	virtual void Uninit() = 0;	//終了
	virtual void Update() = 0;	//更新
	virtual void Draw() = 0;	//描画

private: /* メンバ変数 */
	
};

#endif