//================================================
//
//制作実践基礎[bullet.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _BULLET_H_
#define _BULLET_H_

//***************************
//インクルード
//***************************
#include "object2D.h"

//***************************
//弾クラスの定義
//***************************
class CBullet : public CObject2D
{/* CObject2Dの派生クラス */
public: /* 静的メンバ関数 */
	static CBullet* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);	//生成

	static HRESULT Load();	//ロード
	static void Unload();	//アンロード

public: /* コンストラクタ・デストラクタ */
	CBullet();
	~CBullet() override;

public: /* メンバ関数 */
	HRESULT Init(const char* filePass) override;	//初期化

	void Uninit() override;	//終了
	void Update() override;	//更新
	void Draw() override;	//描画

private: /* 静的メンバ変数 */
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャのポインタ

private: /* メンバ変数 */
	D3DXVECTOR3 m_move;	//移動量
};
#endif