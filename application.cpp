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
#include "renderer.h"
#include "inputKeyboard.h"
#include "player.h"
#include "texture.h"
#include "object2D.h"

//***************************
//�ÓI�����o�ϐ�
//***************************
CRenderer* CApplication::m_pRenderer = nullptr;		//�����_���[
CInput* CApplication::m_pInputKeyboard = nullptr;	//�L�[�{�[�h
CPlayer* CApplication::m_pPlayer = nullptr;			//�v���C���[
CTexture* CApplication::m_pTexture = nullptr;		//�e�N�X�`��

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
// �e�N�X�`�������擾
//================================================
CTexture* CApplication::GetTexture()
{
	return m_pTexture;
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

	/* �e�N�X�`�� */

	if (m_pTexture == nullptr)
	{//NULL�`�F�b�N
		m_pTexture = new CTexture;	//�������̓��I�m��
	}

	/* �v���C���[ */

	m_pPlayer = CPlayer::Create();	//����

	return S_OK;
}

//================================================
//�I��
//================================================
void CApplication::Uninit()
{
	/* �I�u�W�F�N�g */

	CObject2D::ReleaseAll();	//�S�Ẳ��
	
	/* �v���C���[ */
	m_pPlayer = nullptr;	//nullptr�ɂ���

	/* �L�[�{�[�h */

	if (m_pInputKeyboard != nullptr)
	{//NULL�`�F�b�N
		m_pInputKeyboard->Uninit();	//�I������
		delete m_pInputKeyboard;	//�������̉��
		m_pInputKeyboard = nullptr;	//nullptr�ɂ���
	}

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
}