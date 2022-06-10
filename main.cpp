//=============================================================================
//
//���C��
//Author : 
//
//=============================================================================
//***************************
//�C���N���[�h
//***************************
#include "renderer.h"
#include "object2D.h"

#include <assert.h>

//***************************
//�萔��`
//***************************
namespace
{
//�E�C���h�E�̃N���X��
LPCTSTR CLASS_NAME = _T("AppClass");
//�E�C���h�E�̃L���v�V������
LPCTSTR WINDOW_NAME = _T("�|���S���̕`��");
}

//*****************************************************************************
//�v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//***************************
//�X�^�e�B�b�N�ϐ�
//***************************
namespace
{
int s_nCountFPS;	//FPS�J�E���^
CRenderer* s_pRenderer = nullptr;					//�����_�����O�̃|�C���^
CObject* s_apObject[CRenderer::MAX_POLYGON] = {};	//�I�u�W�F�N�g�̃|�C���^
}//namespace�͂����܂�

 //=============================================================================
//���C���֐�
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};

	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	RECT rect = { 0, 0, CRenderer::SCREEN_WIDTH, CRenderer::SCREEN_HEIGHT };
	//�w�肵���N���C�A���g�̈���m�ۂ��邽�߂ɕK�v�ȃE�B���h�E���W���v�Z
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�B���h�E�̍쐬
	HWND hWnd = CreateWindow(CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(rect.right - rect.left),
		(rect.bottom - rect.top),
		NULL,
		NULL,
		hInstance,
		NULL);

	if (s_pRenderer == nullptr)
	{//NULL�`�F�b�N
		s_pRenderer = new CRenderer;	//�������̓��I�m��
	}

	for (int i = 0; i < CRenderer::MAX_POLYGON; i++)
	{
		if (s_apObject[i] != nullptr)
		{//NULL�`�F�b�N
			continue;
		}

		/* nullptr�̏ꍇ */

		s_apObject[i] = new CObject2D;	//�������̓��I�m��
	}

	//����������
	if (FAILED(s_pRenderer->Init(hWnd, TRUE)))
	{//���������������s�����ꍇ
		return -1;
	}

	//�I�u�W�F�N�g�̏�����
	for (int i = 0; i < CRenderer::MAX_POLYGON; i++)
	{
		if (FAILED(s_apObject[i]->Init()))
		{//���������������s�����ꍇ
			assert(false);
			return -1;
		}

		//�������������閈�Ɉʒu�����炷
		D3DXVECTOR3 pos = D3DXVECTOR3((CRenderer::SCREEN_WIDTH * (0.1f * (i + 1))), (CRenderer::SCREEN_HEIGHT * 0.1f), 0.0f);
		s_apObject[i]->SetPos(pos);
	}

	//����\��ݒ�
	timeBeginPeriod(1);

	//�t���[���J�E���g������
	DWORD dwCurrentTime = 0;
	DWORD dwExecLastTime = timeGetTime();
#ifdef _DEBUG
	DWORD dwFrameCount = 0;
	DWORD dwFPSLastTime = dwExecLastTime;
#endif //_DEBUG

	//�E�C���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;

	//���b�Z�[�W���[�v
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{ //PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				//���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();	//���݂̎��Ԃ��擾
#ifdef _DEBUG
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5�b���ƂɎ��s
				//FPS���Z�o
				s_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;	//���݂̎��Ԃ�ۑ�
				dwFrameCount = 0;
			}
#endif //_DEBUG

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{ //1/60�b�o��
				//���݂̎��Ԃ�ۑ�
				dwExecLastTime = dwCurrentTime;

				//�X�V����
				s_pRenderer->Update();

				//�`�揈��
				s_pRenderer->Draw();

#ifdef _DEBUG
				dwFrameCount++;
#endif //_DEBUG
			}
		}
	}

	for (int i = 0; i < CRenderer::MAX_POLYGON; i++)
	{
		if (s_apObject[i] != nullptr)
		{//NULL�`�F�b�N
			s_apObject[i]->Uninit();	//�I������
			delete s_apObject[i];	//�������̉��
			s_apObject[i] = nullptr;	//nullptr�ɂ���
		}
	}

	if (s_pRenderer != nullptr)
	{//NULL�`�F�b�N
		s_pRenderer->Uninit();	//�I������
		delete s_pRenderer;		//�������̉��
		s_pRenderer = nullptr;	//nullptr�ɂ���
	}

	//�E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	//����\��߂�
	timeEndPeriod(1);

	return (int)msg.wParam;
}

//=============================================================================
//�E�C���h�E�v���V�[�W��
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE: //[ESC]�L�[�������ꂽ
			//�E�B���h�E��j��
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//================================================
//FPS�̎擾
//================================================
int GetFPS()
{
	return s_nCountFPS;
}

//================================================
//�����_�����O���̎擾
//================================================
CRenderer* GetRenderer()
{
	return s_pRenderer;
}

//================================================
//�I�u�W�F�N�g���̎擾
//================================================
CObject** GetObjects()
{
	return &s_apObject[0];
}