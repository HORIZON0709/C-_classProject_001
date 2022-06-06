//================================================
//
//制作実践基礎[renderer.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

//***************************
//ライブラリーリンク
//***************************
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"winmm.lib")

//***************************
//インクルード
//***************************
#include <Windows.h>
#include <tchar.h> //_T
#include <d3dx9.h>

//***************************
//レンダラークラスの定義
//***************************
class CRenderer
{/* 基本クラス */
public: /* 構造体の定義 */
	struct VERTEX_2D
	{//頂点データ
		D3DXVECTOR3 pos;	//位置
		float rhw;			//法線
		D3DCOLOR col;		//色
	};

public: /* 定数の定義 */
	static const int SCREEN_WIDTH = 1280;	//スクリーンの幅
	static const int SCREEN_HEIGHT = 720;	//スクリーンの高さ
	const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE);	//頂点フォーマット
private:
	/* 自分で追加したもの */
	const float ROTATION_SPEED = 0.05f;	//回転スピード

public: /* コンストラクタ・デストラクタ */
	CRenderer();
	~CRenderer();

public: /* メンバ関数 */
	HRESULT Init(HWND hWnd, BOOL bWindow);	//初期化
	void Uninit();							//終了
	void Update();							//更新
	void Draw();							//描画
private:
	HRESULT InitPolygon();	//ポリゴンの初期化
	void UninitPolygon();	//ポリゴンの終了
	void UpdatePolygon();	//ポリゴンの更新
	void DrawPolygon();		//ポリゴンの描画
	void DrawFPS();			//FPSの描画

public: /* 静的メンバ変数 */
#ifdef _DEBUG
	static int m_nCountFPS;	//FPSカウンタ
#endif //_DEBUG

private: /* メンバ変数 */
	LPDIRECT3D9 m_pD3D;					//Direct3Dオブジェクト
	LPDIRECT3DDEVICE9 m_pD3DDevice;		//Deviceオブジェクト
	LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;					//位置
	D3DXVECTOR3 m_rot;					//向き
	float m_fLength;					//対角線の長さ
	float m_fAngle;						//対角線の角度
	float m_fSize;						//サイズ
	LPD3DXFONT m_pFont;					//フォント
};

#endif