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
#include "inputKeyboard.h"

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

	pPlayer->Init("data/TEXTURE/�S�S�����_8.jpg");	//������

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
HRESULT CPlayer::Init(const char* filePass)
{
	CObject2D::Init(filePass);	//�e�N���X

	m_pos = D3DXVECTOR3((CRenderer::SCREEN_WIDTH * 0.5f), (CRenderer::SCREEN_HEIGHT * 0.5f), 0.0f);

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

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//��������Z������
	float fLeft		= (m_pos.x - m_fSize);
	float fRight	= (m_pos.x + m_fSize);
	float fTop		= (m_pos.y + m_fSize);
	float fBottom	= (m_pos.y - m_fSize);

	//���_�����X�V
	pVtx[0].pos = D3DXVECTOR3(fLeft, fTop, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(fRight, fTop, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(fLeft, fBottom, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(fRight, fBottom, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================================
//�`��
//================================================
void CPlayer::Draw()
{
	CObject2D::Draw();	//�e�N���X
}