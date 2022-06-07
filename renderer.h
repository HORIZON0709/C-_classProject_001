//================================================
//
//制作実践基礎[renderer.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"

//***************************
//レンダリングクラスの定義
//***************************
class CRenderer
{/* 基本クラス */
public: /* コンストラクタ・デストラクタ */
	CRenderer();
	~CRenderer();

public: /* メンバ関数 */
	HRESULT Init(HWND hWnd, BOOL bWindow);	//初期化
	void Uninit();							//終了
	void Update();							//更新
	void Draw();							//描画
private:
	void DrawFPS();			//FPSの描画
public: /* Get系 */
	LPDIRECT3DDEVICE9 GetDevice();	//デバイスの取得
	/*
	LPDIRECT3DDEVICE9 GetDevice() {return m_pD3DDevice;}
	1行で完結する処理の場合、ヘッダーに書くこともできる。
	*/

private: /* メンバ変数 */
	LPDIRECT3D9 m_pD3D;					//Direct3Dオブジェクト
	LPDIRECT3DDEVICE9 m_pD3DDevice;		//Deviceオブジェクト
	LPD3DXFONT m_pFont;					//フォント
};

#endif