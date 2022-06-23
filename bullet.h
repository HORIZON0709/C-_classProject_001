//================================================
//
//������H��b[bullet.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _BULLET_H_
#define _BULLET_H_

//***************************
//�C���N���[�h
//***************************
#include "object2D.h"

//***************************
//�e�N���X�̒�`
//***************************
class CBullet : public CObject2D
{/* CObject2D�̔h���N���X */
private: /* �萔�̒�` */
	static const float BULLET_SIZE;	//�T�C�Y

public: /* �ÓI�����o�֐� */
	static CBullet* Create();	//����

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CBullet();
	~CBullet() override;

public: /* �����o�֐� */
	HRESULT Init() override;	//������
	void Uninit() override;		//�I��
	void Update() override;		//�X�V
	void Draw() override;		//�`��

private: /* �����o�ϐ� */
	D3DXVECTOR3 m_move;	//�ړ���
};
#endif