//================================================
//
//制作実践基礎[application.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _APPLICATION_H_
#define _APPLICATION_H_

//***************************
//インクルード
//***************************
#include "renderer.h"
#include "inputKeyboard.h"

//***************************
//アプリケーションクラスの定義
//***************************
class CApplication
{/* 基本クラス */
public: /* 静的メンバ関数 */
	static CRenderer* GetRenderer();			//レンダラー情報を取得
	static CInputKeyboard* GetInputKeyboard();	//キーボード情報を取得

public: /* コンストラクタ・デストラクタ */
	CApplication();
	~CApplication();

public: /* メンバ関数 */
	HRESULT Init(HWND hWnd, BOOL bWindow,HINSTANCE hInstance);	//初期化
	void Uninit();							//終了
	void Update();							//更新
	void Draw();							//描画

private: /* 静的メンバ関数 */
	static CRenderer* m_pRenderer;				//レンダラーのポインタ
	static CInputKeyboard* m_pInputKeyboard;	//キーボードのポインタ
};

#endif