//================================================
//
//制作実践基礎[input.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _INPUT_H_
#define _INPUT_H_

//***************************
//インクルード
//***************************
#include "main.h"

#include <dinput.h>

class CInputKeyboard;

//***************************
//インプットクラスの定義
//***************************
class CInput
{/* 基本クラス */
public: /* コンストラクタ・デストラクタ */
	CInput();
	virtual ~CInput();

public: /* 仮想関数 */
	virtual HRESULT Init(HINSTANCE hInstance,HWND hWnd);	//初期化
	virtual void Uninit();									//終了
	virtual void Update() = 0;								//更新

protected: /* 静的メンバ変数 */
	static LPDIRECTINPUT8 m_pInput;

protected: /* メンバ変数 */
	LPDIRECTINPUTDEVICE8 m_pDevice;	//デバイス
	int m_nKeyCnt;					//カウント

	CInputKeyboard* m_pInputKeyboard;	//キーボードのポインタ
};

#endif