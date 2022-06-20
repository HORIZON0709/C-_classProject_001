//================================================
//
//������H��b[application.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _APPLICATION_H_
#define _APPLICATION_H_

//***************************
//�C���N���[�h
//***************************
#include "renderer.h"
#include "inputKeyboard.h"

//***************************
//�A�v���P�[�V�����N���X�̒�`
//***************************
class CApplication
{/* ��{�N���X */
public: /* �ÓI�����o�֐� */
	static CRenderer* GetRenderer();			//�����_���[�����擾
	static CInputKeyboard* GetInputKeyboard();	//�L�[�{�[�h�����擾

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CApplication();
	~CApplication();

public: /* �����o�֐� */
	HRESULT Init(HWND hWnd, BOOL bWindow,HINSTANCE hInstance);	//������
	void Uninit();							//�I��
	void Update();							//�X�V
	void Draw();							//�`��

private: /* �ÓI�����o�֐� */
	static CRenderer* m_pRenderer;				//�����_���[�̃|�C���^
	static CInputKeyboard* m_pInputKeyboard;	//�L�[�{�[�h�̃|�C���^
};

#endif