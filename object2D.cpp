//================================================
//
//������H��b[object2D.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "object2D.h"
#include "renderer.h"

#include <assert.h>

//***************************
//�萔�̒�`
//***************************
const float CObject2D::ROTATION_SPEED = 0.05f;
const float CObject2D::POLYGON_SIZE = 100.0f;

//================================================
//����
//================================================
CObject* CObject2D::Create()
{
	CObject* pObject = nullptr;	//�|�C���^

	if (pObject != nullptr)
	{//NULL�`�F�b�N
		assert(false);
	}

	/* nullptr�̏ꍇ */

	pObject = new CObject2D;	//�������̓��I�m��

	pObject->Init();	//������

	return pObject;	//���I�m�ۂ������̂�Ԃ�
}

//================================================
//�R���X�g���N�^
//================================================
CObject2D::CObject2D() : 
	m_pTexture(nullptr),
	m_pVtxBuff(nullptr),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)), 
	m_fLength(0.0f), 
	m_fAngle(0.0f), 
	m_fSize(0.0f),
	m_fCol(0.0f)
{
}

//================================================
//�f�X�g���N�^
//================================================
CObject2D::~CObject2D()
{
	/* ����R��̊m�F */
	assert(m_pTexture == nullptr);
	assert(m_pVtxBuff == nullptr);
}

//================================================
//������
//================================================
HRESULT CObject2D::Init()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
								"data/TEXTURE/slack_icon.png",
								&m_pTexture);

	//�ʒu
	m_pos = D3DXVECTOR3((CRenderer::SCREEN_WIDTH * 0.5f), (CRenderer::SCREEN_HEIGHT * 0.5f), 0.0f);

	//����
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�T�C�Y
	m_fSize = POLYGON_SIZE;

	//�Ίp���̒������Z�o����
	m_fLength = sqrtf((m_fSize * m_fSize) + (m_fSize * m_fSize)) * 0.5f;

	//�Ίp���̊p�x���Z�o����
	m_fAngle = atan2f(m_fSize, m_fSize);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&m_pVtxBuff,
								NULL);

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_����ݒ�
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z + (m_fAngle * -D3DX_PI)) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z + (m_fAngle * -D3DX_PI)) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + (m_fAngle * D3DX_PI)) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + (m_fAngle * D3DX_PI)) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z + (m_fAngle * -1.0f)) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z + (m_fAngle * -1.0f)) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//================================================
//�I��
//================================================
void CObject2D::Uninit()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//�e�N�X�`���̔j��
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
}

//================================================
//�X�V
//================================================
void CObject2D::Update()
{
	m_rot.z -= ROTATION_SPEED;	//��]

	/* �p�x�̐��K�� */
	if (m_rot.z >= D3DX_PI)
	{// 3.14���傫��
		m_rot.z -= D3DX_PI * 2.0f;
	}
	else if (m_rot.z <= -D3DX_PI)
	{// -3.14��菬����
		m_rot.z += D3DX_PI * 2.0f;
	}

	//�T�C�Y�̊g��E�k��
	m_fSize += cosf(m_rot.z) * 2.0f;

	//�Ίp���̒������Čv�Z
	m_fLength = sqrtf((m_fSize * m_fSize) + (m_fSize * m_fSize)) * 0.5f;

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̍X�V
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z + (m_fAngle * -3.0f)) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z + (m_fAngle * -3.0f)) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + (m_fAngle * 3.0f)) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + (m_fAngle * 3.0f)) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z + (m_fAngle * -1.0f)) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z + (m_fAngle * -1.0f)) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	/* ���F�ŗV�񂾁� */

	m_fCol += 0.1f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(cosf(m_fCol * 0.7f), cosf(m_fCol * 0.2f), cosf(m_fCol * 0.9f), 1.0f);
	pVtx[1].col = D3DXCOLOR(cosf(m_fCol * 0.3f), cosf(m_fCol * 0.4f), cosf(m_fCol * 0.7f), 1.0f);
	pVtx[2].col = D3DXCOLOR(cosf(m_fCol * 0.9f), cosf(m_fCol * 0.6f), cosf(m_fCol * 0.5f), 1.0f);
	pVtx[3].col = D3DXCOLOR(cosf(m_fCol * 1.0f), cosf(m_fCol * 0.8f), cosf(m_fCol * 0.3f), 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================================
//�`��
//================================================
void CObject2D::Draw()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetRenderer()->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
							0,					//�`�悷��ŏ��̒��_�C���f�b�N�X
							2);					//�`�悷��v���~�e�B�u��
}

//================================================
//�ʒu��ݒ�
//================================================
void CObject2D::SetPos(const D3DXVECTOR3 &pos)
{
	m_pos = pos;
}

//================================================
//�ʒu���擾
//================================================
D3DXVECTOR3 CObject2D::GetPos()
{
	return m_pos;
}