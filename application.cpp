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
CRenderer* CApplication::m_pRenderer = nullptr;		//�����_���[
CInput* CApplication::m_pInputKeyboard = nullptr;	//�L�[�{�[�h
CPlayer* CApplication::m_pPlayer = nullptr;			//�v���C���[

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
CInput* CApplication::GetInputKeyboard()
{
	return m_pInputKeyboard;
}

//================================================
//�v���C���[�����擾
//================================================
CPlayer* CApplication::GetPlayer()
{
	return m_pPlayer;
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
	/* �L�[�{�[�h */

	if (m_pInputKeyboard == nullptr)
	{//NULL�`�F�b�N
		m_pInputKeyboard = new CInputKeyboard;	//�������̓��I�m��
	}

	if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
	{//���������������s�����ꍇ
		return E_FAIL;
	}

	/* �����_���[ */

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

	/* �v���C���[ */

	m_pPlayer = CPlayer::Create();	//����

	return S_OK;
}

//================================================
//�I��
//================================================
void CApplication::Uninit()
{
	/* �L�[�{�[�h */

	if (m_pInputKeyboard != nullptr)
	{//NULL�`�F�b�N
		m_pInputKeyboard->Uninit();	//�I������
		delete m_pInputKeyboard;	//�������̉��
		m_pInputKeyboard = nullptr;	//nullptr�ɂ���
	}

	/* �v���C���[ */

	if (m_pPlayer != nullptr)
	{//NULL�`�F�b�N
		m_pPlayer->Uninit();	//�I������
		delete m_pPlayer;		//�������̉��
		m_pPlayer = nullptr;	//nullptr�ɂ���
	}

	/* �I�u�W�F�N�g */

	CObject2D::ReleaseAll();	//�S�Ẳ��

	/* �����_���[ */

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
	if (m_pInputKeyboard != nullptr)
	{//NULL�`�F�b�N
		m_pInputKeyboard->Update();	//�L�[�{�[�h
	}

	if (m_pRenderer != nullptr)
	{//NULL�`�F�b�N
		m_pRenderer->Update();	//�����_���[
	}

	if (m_pPlayer != nullptr)
	{//NULL�`�F�b�N
		m_pPlayer->Update();	//�v���C���[
	}
}

//================================================
//�`��
//================================================
void CApplication::Draw()
{
	if (m_pRenderer != nullptr)
	{//NULL�`�F�b�N
		m_pRenderer->Draw();	//�����_���[
	}

	if (m_pPlayer != nullptr)
	{//NULL�`�F�b�N
		m_pPlayer->Draw();	//�v���C���[
	}
}