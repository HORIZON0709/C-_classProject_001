//================================================
//
//������H��b[input.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _INPUT_H_
#define _INPUT_H_

//***************************
//�C���N���[�h
//***************************
#include "main.h"

#include <dinput.h>

class CInputKeyboard;

//***************************
//�C���v�b�g�N���X�̒�`
//***************************
class CInput
{/* ��{�N���X */
public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CInput();
	virtual ~CInput();

public: /* ���z�֐� */
	virtual HRESULT Init(HINSTANCE hInstance,HWND hWnd);	//������
	virtual void Uninit();									//�I��
	virtual void Update() = 0;								//�X�V

protected: /* �ÓI�����o�ϐ� */
	static LPDIRECTINPUT8 m_pInput;

protected: /* �����o�ϐ� */
	LPDIRECTINPUTDEVICE8 m_pDevice;	//�f�o�C�X
	int m_nKeyCnt;					//�J�E���g

	CInputKeyboard* m_pInputKeyboard;	//�L�[�{�[�h�̃|�C���^
};

#endif