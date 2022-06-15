//================================================
//
//制作実践基礎[main.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _MAIN_H_
#define _MAIN_H_

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
//前方宣言
//***************************
class CRenderer;

//***************************
//プロトタイプ宣言
//***************************
/* FPSの取得 */
int GetFPS();

/* レンダリング情報の取得 */
CRenderer* GetRenderer();

#endif