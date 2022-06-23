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
#include "input.h"

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

	CInput* pInput = CInput::GetKey();	//�L�[�{�[�h
	D3DXVECTOR3 pos;					//�ʒu�ݒ�p

	/* �ړ� */

	if (pInput->Press(CInput::STANDARD_KEY::RIGHT))
	{//�E
		pos.x += 50.0f;
	}
	else if (pInput->Press(CInput::STANDARD_KEY::LEFT))
	{//��
		pos.x -= 50.0f;
	}

	CObject2D::SetPos(pos);	//�ʒu���X�V
}

//================================================
//�`��
//================================================
void CPlayer::Draw()
{
	CObject2D::Draw();	//�e�N���X
}