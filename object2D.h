//================================================
//
//制作実践基礎[object2D.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

//***************************
//インクルード
//***************************
#include "object.h"
#include "texture.h"

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
		D3DXVECTOR2 tex;	//テクスチャ座標
	};

protected: /* 定数の定義 */
	static const float ROTATION_SPEED;	//回転スピード

public: /* 静的メンバ関数 */
	static CObject2D* Create();	//生成

public: /* コンストラクタ・デストラクタ */
	CObject2D();
	~CObject2D() override;

public: /* オーバーライド関数 */
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
	void Draw() override;		//描画

	/* Pos */
	void SetPos(const D3DXVECTOR3 &pos) override;	//位置を設定
	D3DXVECTOR3 GetPos() override;					//位置を取得

	/* Size */
	void SetSize(const float &fSize) override;	//サイズを設定
	float GetSize() override;					//サイズを取得

public: /* メンバ関数 */
	void SetTexture(CTexture::TEXTURE texture);				//テクスチャの設定
	void SetTexUV(const int &nDivNum,const int &nPtnAnim);	//テクスチャ座標の設定(アニメーション対応)

private: /* メンバ変数 */
	LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//頂点バッファへのポインタ
	CTexture::TEXTURE m_texture;		//テクスチャの列挙型

	D3DXVECTOR3 m_pos;	//位置
	D3DXVECTOR3 m_rot;	//向き
	float m_fSize;		//サイズ
};

#endif