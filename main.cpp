//=============================================================================
//
//���C��
//Author : 
//
//=============================================================================

//*****************************************************************************
//���C�u�����[�����N
//*****************************************************************************
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"winmm.lib")

//*****************************************************************************
//�C���N���[�h
//*****************************************************************************
#include <Windows.h>
#include <tchar.h> //_T
#include <d3dx9.h>

//*****************************************************************************
//�萔��`
//*****************************************************************************
namespace
{
	//�E�C���h�E�̃N���X��
	LPCTSTR CLASS_NAME = _T("AppClass");
	//�E�C���h�E�̃L���v�V������
	LPCTSTR WINDOW_NAME = _T("�|���S���̕`��");
}

//�X�N���[���̕�
const int SCREEN_WIDTH = 1280;
//�X�N���[���̍���
const int SCREEN_HEIGHT = 720;
//���_�t�H�[�}�b�g
const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

//*****************************************************************************
//�\���̒�`
//*****************************************************************************
//���_�f�[�^
struct VERTEX_2D
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
};

//*****************************************************************************
//�v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HWND hWnd, bool bWindow);
void Uninit();
void Update();
void Draw();

HRESULT InitPolygon();
void UninitPolygon();
void UpdatePolygon();
void DrawPolygon();

#ifdef _DEBUG
void DrawFPS();
#endif //_DEBUG

//*****************************************************************************
//�O���[�o���ϐ�
//*****************************************************************************
//Direct3D�I�u�W�F�N�g
LPDIRECT3D9 g_pD3D = nullptr;
//Device�I�u�W�F�N�g
LPDIRECT3DDEVICE9 g_pD3DDevice = nullptr;
//���_�o�b�t�@
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff = nullptr;

//���_���
VERTEX_2D g_aVertex[4];


#ifdef _DEBUG
//�t�H���g
LPD3DXFONT g_pFont = nullptr;
#endif //_DEBUG

#ifdef _DEBUG
//FPS�J�E���^
int g_nCountFPS;
#endif //_DEBUG

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

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
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

	//����������
	if (FAILED(Init(hWnd, TRUE)))
	{//���������������s�����ꍇ
		return -1;
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
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;	//���݂̎��Ԃ�ۑ�
				dwFrameCount = 0;
			}
#endif //_DEBUG

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{ //1/60�b�o��
				//���݂̎��Ԃ�ۑ�
				dwExecLastTime = dwCurrentTime;

				//�X�V����
				Update();

				//�`�揈��
				Draw();

#ifdef _DEBUG
				dwFrameCount++;
#endif //_DEBUG
			}
		}
	}

	//�I������
	Uninit();

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

//=============================================================================
//������
//=============================================================================
HRESULT Init(HWND hWnd, bool bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	//Direct3D�I�u�W�F�N�g�̍쐬
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == nullptr)
	{
		return E_FAIL;
	}

	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));								//���[�N���[���N���A
	d3dpp.BackBufferCount = 1;							//�o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth = SCREEN_WIDTH;				//�Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;				//�Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;				//�J���[���[�h�̎w��
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;		//�f���M���ɓ������ăt���b�v����
	d3dpp.EnableAutoDepthStencil = TRUE;						//�f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					//�f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;						//�E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	//�C���^�[�o��

	//�f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
	//�`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if ((FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice))) &&
		//��L�̐ݒ肪���s������
		//�`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice))) &&
		//��L�̐ݒ肪���s������
		//�`��ƒ��_������CPU�ōs�Ȃ�
		(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice))))
	{
		//�������s
		return E_FAIL;
	}

	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

#ifdef _DEBUG
	//�f�o�b�O���\���p�t�H���g�̐���
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &g_pFont);
#endif

	//�|���S���̏���������
	InitPolygon();

	return S_OK;
}

//=============================================================================
//�I��
//=============================================================================
void Uninit()
{
	//�|���S���̏I������
	UninitPolygon();

#ifdef _DEBUG
	//�f�o�b�O���\���p�t�H���g�̔j��
	if (g_pFont != nullptr)
	{
		g_pFont->Release();
		g_pFont = nullptr;
	}
#endif //_DEBUG

	//�f�o�C�X�̔j��
	if (g_pD3DDevice != nullptr)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = nullptr;
	}

	//Direct3D�I�u�W�F�N�g�̔j��
	if (g_pD3D != nullptr)
	{
		g_pD3D->Release();
		g_pD3D = nullptr;
	}
}

//=============================================================================
//�X�V
//=============================================================================
void Update()
{
	//�|���S���̍X�V����
	UpdatePolygon();
}

//=============================================================================
//�`��
//=============================================================================
void Draw()
{
	//�o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	g_pD3DDevice->Clear(0, NULL,
						(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
						D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		//�|���S���̕`�揈��
		DrawPolygon();

#ifdef _DEBUG
		//FPS�\��
		DrawFPS();
#endif //_DEBUG

		//Direct3D�ɂ��`��̏I��
		g_pD3DDevice->EndScene();
	}

	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
//�|���S���̏�����
//=============================================================================
HRESULT InitPolygon()
{
	//���_�o�b�t�@�̐���
	g_pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&g_pVtxBuff,
								NULL);

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	D3DXVECTOR3 pos = D3DXVECTOR3((SCREEN_WIDTH * 0.5f), (SCREEN_HEIGHT * 0.5f), 0.0f);
	const float POLYGON_SIZE = 25.0f;

	//���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(pos.x - POLYGON_SIZE, pos.y - POLYGON_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + POLYGON_SIZE, pos.y - POLYGON_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - POLYGON_SIZE, pos.y + POLYGON_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + POLYGON_SIZE, pos.y + POLYGON_SIZE, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
//�|���S���̏I��
//=============================================================================
void UninitPolygon()
{
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff != nullptr)
	{
		g_pVtxBuff->Release();
		g_pVtxBuff = NULL;
	}
}

//=============================================================================
//�|���S���̍X�V
//=============================================================================
void UpdatePolygon()
{
}

//=============================================================================
//�|���S���̕`��
//=============================================================================
void DrawPolygon()
{
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	g_pD3DDevice->SetStreamSource(0, g_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	g_pD3DDevice->SetFVF(FVF_VERTEX_2D);

	//�|���S���̕`��
	g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
								0,						//�`�悷��ŏ��̒��_�C���f�b�N�X
								2);						//�`�悷��v���~�e�B�u��
}

#ifdef _DEBUG
//=============================================================================
//FPS�\��
//=============================================================================
void DrawFPS()
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	TCHAR str[256];

	wsprintf(str, _T("FPS : %d\n"), g_nCountFPS);

	//�e�L�X�g�`��
	g_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
#endif //_DEBUG
