//================================================
//
//������H��b[input.h]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "input.h"
#include "inputKeyboard.h"

//***************************
//�ÓI�����o�ϐ�
//***************************
LPDIRECTINPUT8 CInput::m_pInput = nullptr;

//================================================
//�R���X�g���N�^
//================================================
CInput::CInput():
	m_pDevice(nullptr),
	m_nKeyCnt(0),
	m_pInputKeyboard(nullptr)
{
}

//================================================
//�f�X�g���N�^
//================================================
CInput::~CInput()
{
}

//================================================
//������
//================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	m_nKeyCnt = 0;	//�J�E���g��������

	if (m_pInputKeyboard != nullptr)
	{//NULL�`�F�b�N
		m_pInputKeyboard = nullptr;
	}

	/* nullptr�̏ꍇ */

	m_pInputKeyboard = new CInputKeyboard;	//�������̓��I�m��

	//�L�[�{�[�h�̏���������
	if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//================================================
//�I��
//================================================
void CInput::Uninit()
{
	//�L�[�{�[�h�̏I������
	m_pInputKeyboard->Uninit();
}