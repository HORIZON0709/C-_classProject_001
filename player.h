//================================================
//
//������H��b[player.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//***************************
//�C���N���[�h
//***************************
#include "object2D.h"

//***************************
//�v���C���[�N���X�̒�`
//***************************
class CPlayer : public CObject2D
{/* CObject2D�̔h���N���X */
public: /* �ÓI�����o�֐� */
	static CPlayer* Create();	//����

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CPlayer();
	~CPlayer() override;

public: /* �����o�֐� */
	HRESULT Init(const char* filePass) override;	//������
	void Uninit() override;		//�I��
	void Update() override;		//�X�V
	void Draw() override;		//�`��
};

#endif