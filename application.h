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
#include "player.h"

//***************************
//�A�v���P�[�V�����N���X�̒�`
//***************************
class CApplication
{/* ��{�N���X */
public: /* �ÓI�����o�֐� */
	static CRenderer* GetRenderer();	//�����_���[�����擾
	static CInput* GetInputKeyboard();	//�L�[�{�[�h�����擾
	static CPlayer* GetPlayer();		//�v���C���[�����擾

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CApplication();
	~CApplication();

public: /* �����o�֐� */
	HRESULT Init(HWND hWnd, BOOL bWindow,HINSTANCE hInstance);	//������

	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��

private: /* �ÓI�����o�֐� */
	static CRenderer* m_pRenderer;		//�����_���[�̃|�C���^
	static CInput* m_pInputKeyboard;	//�L�[�{�[�h�̃|�C���^
	static CPlayer* m_pPlayer;			//�v���C���[�̃|�C���^
};

#endif