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
private: /* �萔�̒�` */
	const float ROTATION_SPEED = 0.05f;	//��]�X�s�[�h
	const float POLYGON_SIZE = 100.0f;	//�T�C�Y

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CObject2D();
	~CObject2D();

public: /* �����o�֐� */
	HRESULT Init()override;	//������
	void Uninit()override;	//�I��
	void Update()override;	//�X�V
	void Draw()override;	//�`��

private: /* �����o�ϐ� */
	
};

#endif