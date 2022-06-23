//================================================
//
//������H��b[explosion.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "explosion.h"
#include "renderer.h"

#include <assert.h>

//***************************
//�萔�̒�`
//***************************
const float CExplosion::EXPLOSION_SIZE = 30.0f;	//�T�C�Y

//================================================
//����
//================================================
CExplosion* CExplosion::Create(D3DXVECTOR3 pos)
{
	CExplosion* pExplosion = nullptr;	//�|�C���^

	if (pExplosion != nullptr)
	{//NULL�`�F�b�N
		assert(false);
	}

	/* nullptr�̏ꍇ */

	pExplosion = new CExplosion;	//�������̓��I�m��

	pExplosion->Init();	//������

	pExplosion->SetPos(pos, EXPLOSION_SIZE);	//�ʒu��ݒ�

	return pExplosion;	//���I�m�ۂ������̂�Ԃ�
}

//================================================
//�R���X�g���N�^
//================================================
CExplosion::CExplosion()
{
}

//================================================
//�f�X�g���N�^
//================================================
CExplosion::~CExplosion()
{
}

//================================================
//������
//================================================
HRESULT CExplosion::Init()
{
	CObject2D::Init();	//�e�N���X

	//�ʒu��ݒ�
	D3DXVECTOR3 pos = D3DXVECTOR3((CRenderer::SCREEN_WIDTH * 0.8f), (CRenderer::SCREEN_HEIGHT * 0.5f), 0.0f);
	CObject2D::SetPos(pos, EXPLOSION_SIZE);

	// �e�N�X�`���̐ݒ�
	CObject2D::SetTexture(CTexture::TEXTURE_explosion000);

	return S_OK;
}

//================================================
//�I��
//================================================
void CExplosion::Uninit()
{
	CObject2D::Uninit();	//�e�N���X
}

//================================================
//�X�V
//================================================
void CExplosion::Update()
{
	CObject2D::Update();	//�e�N���X

	m_nCntAnim++;

	if (m_nCntAnim % 10 == 0)
	{//���Ԋu
		//�p�^�[���ԍ����X�V����
		m_nPtnAnim = (m_nPtnAnim + 1) % DIVIDE_TEX_U;

		//�e�N�X�`�����W�̐ݒ�
		CObject2D::SetAnimTexUV(DIVIDE_TEX_U, m_nPtnAnim);

		Release();	//���
	}
}

//================================================
//�`��
//================================================
void CExplosion::Draw()
{
	CObject2D::Draw();	//�e�N���X
}