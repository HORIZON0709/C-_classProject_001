//================================================
//
//制作実践基礎[inputKeyboard.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _INPUTKEYBOARD_H_
#define _INPUTKEYBOARD_H_

//***************************
//インクルード
//***************************
#include "input.h"

//***************************
//キーボード入力クラスの定義
//***************************
class CInputKeyboard : public CInput
{/* CInputの派生クラス */
private: /* 定数の定義 */
	static const int MAX_KEY = 256;	//キーの最大数

public: /* コンストラクタ・デストラクタ */
	CInputKeyboard();
	~CInputKeyboard();

public: /* オーバーライド関数 */
	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;	//初期化
	void Uninit() override;									//終了
	void Update() override;									//更新

public: /* メンバ関数 */
	bool GetPress(int nKey);	//プレス
	bool GetTrigger(int nKey);	//トリガー

private: /* メンバ変数 */
	BYTE m_aKeyStatePress[MAX_KEY];		//プレス情報
	BYTE m_aKeyStateTrigger[MAX_KEY];	//トリガー情報
};

#endif