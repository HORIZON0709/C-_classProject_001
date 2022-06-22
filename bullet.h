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
public: /* �ÓI�����o�֐� */
	static CBullet* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);	//����

	static HRESULT Load();	//���[�h
	static void Unload();	//�A�����[�h

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CBullet();
	~CBullet() override;

public: /* �����o�֐� */
	HRESULT Init(const char* filePass) override;	//������

	void Uninit() override;	//�I��
	void Update() override;	//�X�V
	void Draw() override;	//�`��

private: /* �ÓI�����o�ϐ� */
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���̃|�C���^

private: /* �����o�ϐ� */
	D3DXVECTOR3 m_move;	//�ړ���
};
#endif