//================================================
//
//������H��b[input.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _INPUT_H_
#define _INPUT_H_

//***************************
//�}�N����`
//***************************
#define DIRECTINPUT_VERSION		(0x0800)	//�r���h���̌x���΍��p�}�N��(���̈ʒu���瓮�����Ȃ�)

//***************************
//���C�u�����[�����N
//***************************
#pragma comment(lib,"dinput8.lib")	//���͏����ɕK�v(�L�[�{�[�h)
//#pragma comment(lib,"xinput.lib")	//���͏����ɕK�v�i�W���C�p�b�g�j
#pragma comment(lib,"dxguid.lib")	//DirectX�R���|�[�l���g�Ɏg�p

//***************************
//�C���N���[�h
//***************************
#include "main.h"

#include <dinput.h>

//***************************
//�O���錾
//***************************
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