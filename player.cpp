//================================================
//
//������H��b[player.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "player.h"
#include "application.h"
#include "renderer.h"

#include <assert.h>

//================================================
//����
//================================================
CPlayer* CPlayer::Create()
{
	CPlayer* pPlayer = nullptr;	//�|�C���^

	if (pPlayer != nullptr)
	{//NULL�`�F�b�N
		assert(false);
	}

	/* nullptr�̏ꍇ */

	pPlayer = new CPlayer;	//�������̓��I�m��

	pPlayer->Init();	//������

	return pPlayer;	//���I�m�ۂ������̂�Ԃ�
}

//================================================
//�R���X�g���N�^
//================================================
CPlayer::CPlayer()
{
}

//================================================
//�f�X�g���N�^
//================================================
CPlayer::~CPlayer()
{
}

//================================================
//������
//================================================
HRESULT CPlayer::Init()
{
	CObject2D::Init();	//�e�N���X

	//�ʒu��ݒ�
	D3DXVECTOR3 pos = D3DXVECTOR3((CRenderer::SCREEN_WIDTH * 0.5f), (CRenderer::SCREEN_HEIGHT * 0.5f), 0.0f);
	CObject2D::SetPos(pos);

	// �e�N�X�`���̐ݒ�
	CObject2D::SetTexture(CTexture::TEXTURE_�S�S�����_8);

	return S_OK;
}

//================================================
//�I��
//================================================
void CPlayer::Uninit()
{
	CObject2D::Uninit();	//�e�N���X
}

//================================================
//�X�V
//================================================
void CPlayer::Update()
{
	CObject2D::Update();	//�e�N���X

	//CInputKeyboard input;	//�L�[�{�[�h
	//
	//if (input.GetPress(DIK_D))
	//{//�E
	//	m_pos.x += 50.0f;
	//}
	//else if (input.GetPress(DIK_A))
	//{//��
	//	m_pos.x -= 50.0f;
	//}
}

//================================================
//�`��
//================================================
void CPlayer::Draw()
{
	CObject2D::Draw();	//�e�N���X
}