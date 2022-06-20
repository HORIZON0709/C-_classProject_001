//================================================
//
//������H��b[inputKeyboard.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _INPUTKEYBOARD_H_
#define _INPUTKEYBOARD_H_

//***************************
//�C���N���[�h
//***************************
#include "input.h"

//***************************
//�L�[�{�[�h���̓N���X�̒�`
//***************************
class CInputKeyboard : public CInput
{/* CInput�̔h���N���X */
private: /* �萔�̒�` */
	static const int MAX_KEY = 256;	//�L�[�̍ő吔

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CInputKeyboard();
	~CInputKeyboard();

public: /* �I�[�o�[���C�h�֐� */
	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;	//������
	void Uninit() override;									//�I��
	void Update() override;									//�X�V

public: /* �����o�֐� */
	bool GetPress(int nKey);	//�v���X
	bool GetTrigger(int nKey);	//�g���K�[

private: /* �����o�ϐ� */
	BYTE m_aKeyStatePress[MAX_KEY];		//�v���X���
	BYTE m_aKeyStateTrigger[MAX_KEY];	//�g���K�[���
};

#endif