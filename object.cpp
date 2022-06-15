//================================================
//
//������H��b[object.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "object2D.h"
#include "renderer.h"

//***************************
//�ÓI�����o�ϐ�
//***************************
CObject* CObject::m_apObject[MAX_POLYGON] = {};	//�|�C���^
int CObject::m_nNumAll = 0;

//================================================
//�S�Ă̐���
//================================================
void CObject::CreateAll()
{
	for (int i = 0; i < MAX_POLYGON; i++)
	{
		if (m_apObject[i] != nullptr)
		{//NULL�`�F�b�N
			m_apObject[i] = nullptr;
		}

		//����
		CObject2D::Create();

		//�������������閈�Ɉʒu�����炷
		float fPosX = (CRenderer::SCREEN_WIDTH * (0.1f * (i + 1)));
		float fPosY = (CRenderer::SCREEN_HEIGHT * 0.1f);

		//�ʒu�̐ݒ�
		m_apObject[i]->SetPos(D3DXVECTOR3(fPosX, fPosY, 0));
	}
}

//================================================
//�S�Ẳ��
//================================================
void CObject::ReleaseAll()
{
	for (int i = 0; i < MAX_POLYGON; i++)
	{
		if (m_apObject[i] == nullptr)
		{//NULL�`�F�b�N
			continue;
		}

		/* nullptr�ł͂Ȃ��ꍇ */

		m_apObject[i]->Uninit();	//�I��
		delete m_apObject[i];		//�������̉��
		m_apObject[i] = nullptr;	//nullptr�ɂ���
	}
}

//================================================
//�S�Ă̍X�V
//================================================
void CObject::UpdateAll()
{
	for (int i = 0; i < MAX_POLYGON; i++)
	{
		if (m_apObject[i] == nullptr)
		{//NULL�`�F�b�N
			continue;
		}

		/* nullptr�ł͂Ȃ��ꍇ */

		m_apObject[i]->Update();	//�X�V
	}
}

//================================================
//�S�Ă̕`��
//================================================
void CObject::DrawAll()
{
	for (int i = 0; i < MAX_POLYGON; i++)
	{
		if (m_apObject[i] == nullptr)
		{//NULL�`�F�b�N
			continue;
		}

		/* nullptr�ł͂Ȃ��ꍇ */

		m_apObject[i]->Draw();	//�`��
	}
}

//================================================
//�R���X�g���N�^
//================================================
CObject::CObject()
{
	for (int i = 0; i < MAX_POLYGON; i++)
	{
		if (m_apObject[i] != nullptr)
		{//NULL�`�F�b�N
			continue;
		}

		/* nullptr�̏ꍇ */

		m_apObject[i] = this;	//���g�̃|�C���^��Ԃ�
		m_nNumAll++;
		break;
	}
}

//================================================
//�f�X�g���N�^
//================================================
CObject::~CObject()
{
}