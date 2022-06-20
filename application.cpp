//================================================
//
//������H��b[application.h]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "application.h"
#include "object2D.h"

//***************************
//�ÓI�����o�ϐ�
//***************************
CRenderer* CApplication::m_pRenderer = nullptr;				//�����_���[
CInputKeyboard* CApplication::m_pInputKeyboard = nullptr;	//�L�[�{�[�h

//================================================
//�����_���[�����擾
//================================================
CRenderer* CApplication::GetRenderer()
{
	return m_pRenderer;
}

//================================================
//�L�[�{�[�h�����擾
//================================================
CInputKeyboard* CApplication::GetInputKeyboard()
{
	return m_pInputKeyboard;
}

//================================================
//�R���X�g���N�^
//================================================
CApplication::CApplication()
{
}

//================================================
//�f�X�g���N�^
//================================================
CApplication::~CApplication()
{
}

//================================================
//������
//================================================
HRESULT CApplication::Init(HWND hWnd, BOOL bWindow, HINSTANCE hInstance)
{
	if (m_pRenderer == nullptr)
	{//NULL�`�F�b�N
		m_pRenderer = new CRenderer;	//�������̓��I�m��
	}

	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{//���������������s�����ꍇ
		return E_FAIL;
	}

	/* �I�u�W�F�N�g */

	CObject2D::CreateAll();	//�S�Ă̐���

	return S_OK;
}

//================================================
//�I��
//================================================
void CApplication::Uninit()
{
	CObject2D::ReleaseAll();	//�S�Ẳ��

	if (m_pRenderer != nullptr)
	{//NULL�`�F�b�N
		m_pRenderer->Uninit();	//�I������
		delete m_pRenderer;		//�������̉��
		m_pRenderer = nullptr;	//nullptr�ɂ���
	}
}

//================================================
//�X�V
//================================================
void CApplication::Update()
{
	m_pRenderer->Update();	//�����_���[
}

//================================================
//�`��
//================================================
void CApplication::Draw()
{
	m_pRenderer->Draw();	//�����_���[
}