//================================================
//
//制作実践基礎[object.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

//***************************
//インクルード
//***************************
#include <d3dx9.h>

//***************************
//定数の定義
//***************************
const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);	//頂点フォーマット

//***************************
//オブジェクトクラスの定義
//***************************
class CObject
{/* 基本クラス */
public: /* 列挙型の定義 */
	enum OBJ_TYPE
	{/* オブジェクトの種類 */
		PLAYER = 0,	//プレイヤー
		ENEMY,		//敵
		BULLET,		//弾
		MAX,
		NONE
	};

public: /* 定数の定義 */
	static const int MAX_POLYGON = 128;	//ポリゴンの最大数

public: /* 静的メンバ関数 */
	static void ReleaseAll();	//全ての解放
	static void UpdateAll();	//全ての更新
	static void DrawAll();		//全ての描画

public: /* コンストラクタ・デストラクタ */
	CObject();
	virtual ~CObject();

public: /* 純粋仮想関数 */
	virtual HRESULT Init() = 0;	//初期化
	virtual void Uninit() = 0;	//終了
	virtual void Update() = 0;	//更新
	virtual void Draw() = 0;	//描画
public: /* Set,Get系 */
	virtual void SetPos(const D3DXVECTOR3 &pos,const float &fSize) = 0;	//位置を設定
	virtual D3DXVECTOR3 GetPos() = 0;									//位置を取得

protected: /* メンバ関数 */
	void Release();	//解放

private: /* 静的メンバ変数 */
	static CObject* m_apObject[MAX_POLYGON];	//ポインタ
	static int m_nNumAll;						//最大数
	
private: /* メンバ変数 */
	int m_nID;		//格納先の番号
	OBJ_TYPE type;	//種類
};

#endif