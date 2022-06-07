//================================================
//
//������H��b[object.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "main.h"

//***************************
//�萔�̒�`
//***************************
const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE);	//���_�t�H�[�}�b�g

//***************************
//�I�u�W�F�N�g�N���X�̒�`
//***************************
class CObject
{/* ��{�N���X */
public: /* �\���̂̒�` */
	struct VERTEX_2D
	{//���_�f�[�^
		D3DXVECTOR3 pos;	//�ʒu
		float rhw;			//�@��
		D3DCOLOR col;		//�F
	};

private: /* �萔�̒�` */
	/* �����Œǉ��������� */
	const float ROTATION_SPEED = 0.05f;	//��]�X�s�[�h
	const float POLYGON_SIZE = 100.0f;	//�T�C�Y

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CObject();
	~CObject();

public: /* �����o�֐� */
	HRESULT Init();		//������
	void Uninit();		//�I��
	void Update();		//�X�V
	void Draw();		//�`��

private: /* �����o�ϐ� */
	LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;					//�ʒu
	D3DXVECTOR3 m_rot;					//����
	float m_fLength;					//�Ίp���̒���
	float m_fAngle;						//�Ίp���̊p�x
	float m_fSize;						//�T�C�Y
	float m_fCol;						//�F
};

#endif