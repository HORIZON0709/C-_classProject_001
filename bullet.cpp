//================================================
//
//������H��b[bullet.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "bullet.h"
#include "renderer.h"
#include "explosion.h"

#include <assert.h>

//***************************
//�萔�̒�`
//***************************
const float CBullet::BULLET_SIZE = 50.0f;	//�T�C�Y

//================================================
//����
//================================================
CBullet* CBullet::Create(D3DXVECTOR3 pos)
{
	CBullet* pBullet = nullptr;	//�|�C���^

	if (pBullet != nullptr)
	{//NULL�`�F�b�N
		assert(false);
	}

	/* nullptr�̏ꍇ */

	pBullet = new CBullet;	//�������̓��I�m��

	pBullet->Init();	//������

	pBullet->SetPos(pos, BULLET_SIZE);	//�ʒu��ݒ�

	return pBullet;	//���I�m�ۂ������̂�Ԃ�
}

//================================================
//�R���X�g���N�^
//================================================
CBullet::CBullet()
{
}

//================================================
//�f�X�g���N�^
//================================================
CBullet::~CBullet()
{
}

//================================================
//������
//================================================
HRESULT CBullet::Init()
{
	CObject2D::Init();	//�e�N���X

	//�ʒu��ݒ�
	D3DXVECTOR3 pos = D3DXVECTOR3((CRenderer::SCREEN_WIDTH * 0.8f), (CRenderer::SCREEN_HEIGHT * 0.5f), 0.0f);
	CObject2D::SetPos(pos, BULLET_SIZE);

	//�ړ��ʂ�ݒ�
	m_move = D3DXVECTOR3(0.0f, 10.0f, 0.0f);

	// �e�N�X�`���̐ݒ�
	CObject2D::SetTexture(CTexture::TEXTURE_circle_sakura2);

	return S_OK;
}

//================================================
//�I��
//================================================
void CBullet::Uninit()
{
	CObject2D::Uninit();	//�e�N���X
}

//================================================
//�X�V
//================================================
void CBullet::Update()
{
	CObject2D::Update();	//�e�N���X

	D3DXVECTOR3 pos = CObject2D::GetPos();	//�ʒu�ݒ�p

	pos.y -= m_move.y;	//�ʒu���X�V

	CObject2D::SetPos(pos, BULLET_SIZE);	//�X�V�����ʒu��ݒ�

	if ((pos.x < 0) || (pos.x > CRenderer::SCREEN_WIDTH) ||
		(pos.y < 0) || (pos.y > CRenderer::SCREEN_HEIGHT))
	{//��ʊO�ɏo����
		Release();	//���

		CExplosion* pExplosion = CExplosion::Create(pos);	//�����̐���

		pExplosion->Update();	//�����̍X�V
	}
}

//================================================
//�`��
//================================================
void CBullet::Draw()
{
	CObject2D::Draw();	//�e�N���X
}