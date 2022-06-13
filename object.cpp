//================================================
//
//制作実践基礎[object.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//インクルード
//***************************
#include "object2D.h"
#include "renderer.h"

//***************************
//静的メンバ変数
//***************************
CObject* CObject::m_apObject[MAX_POLYGON] = {};	//ポインタ

//================================================
//全ての生成
//================================================
void CObject::CreateAll()
{
	for (int i = 0; i < MAX_POLYGON; i++)
	{
		if (m_apObject[i] != nullptr)
		{//NULLチェック
			m_apObject[i] = nullptr;
		}

		//生成数が増える毎に位置をずらす
		float fPosX = (CRenderer::SCREEN_WIDTH * (0.1f * (i + 1)));
		float fPosY = (CRenderer::SCREEN_HEIGHT * 0.1f);

		//生成(同時に位置も設定)
		m_apObject[i] = CObject2D::Create(D3DXVECTOR3(fPosX, fPosY, 0));
	}
}

//================================================
//全ての解放
//================================================
void CObject::ReleaseAll()
{
	for (int i = 0; i < MAX_POLYGON; i++)
	{
		if (m_apObject[i] == nullptr)
		{//NULLチェック
			continue;
		}

		/* nullptrではない場合 */

		m_apObject[i]->Uninit();	//終了
		delete m_apObject[i];		//メモリの解放
		m_apObject[i] = nullptr;	//nullptrにする
	}
}

//================================================
//全ての更新
//================================================
void CObject::UpdateAll()
{
	for (int i = 0; i < MAX_POLYGON; i++)
	{
		m_apObject[i]->Update();	//更新
	}
}

//================================================
//全ての描画
//================================================
void CObject::DrawAll()
{
	for (int i = 0; i < MAX_POLYGON; i++)
	{
		m_apObject[i]->Draw();	//描画
	}
}

//================================================
//コンストラクタ
//================================================
CObject::CObject()
{
}

//================================================
//デストラクタ
//================================================
CObject::~CObject()
{
}