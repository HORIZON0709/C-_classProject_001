//================================================
//
//������H��b[object2D.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

#include "main.h"
#include "object.h"

//***************************
//�I�u�W�F�N�g�N���X�̒�`
//***************************
class CObject2D : public CObject
{/* CObject�̔h���N���X */
public: /* �\���̂̒�` */
	struct VERTEX_2D
	{//���_�f�[�^
		D3DXVECTOR3 pos;	//�ʒu
		float rhw;			//�@��
		D3DCOLOR col;		//�F
	};

private: /* �萔�̒�` */
	const float ROTATION_SPEED = 0.05f;	//��]�X�s�[�h
	const float POLYGON_SIZE = 100.0f;	//�T�C�Y
public:
	static const int MAX_POLYGON = 5;	//�|���S���̍ő吔

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CObject2D();
	~CObject2D();

public: /* �����o�֐� */
	HRESULT Init()override;	//������
	void Uninit()override;	//�I��
	void Update()override;	//�X�V
	void Draw()override;	//�`��
public: /* Set,Get�n */
	void SetPos(const D3DXVECTOR3 &pos)override;	//�ʒu��ݒ�
	D3DXVECTOR3 GetPos()override;					//�ʒu���擾

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