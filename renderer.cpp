//================================================
//
//������H��b[renderer.cpp]
//Author:Kishimoto Eiji
//
//================================================
#include "renderer.h"

//================================================
//�R���X�g���N�^
//================================================
CRenderer::CRenderer()
{
	//�����o�ϐ��̃N���A
	m_pD3D = nullptr;
	m_pD3DDevice = nullptr;
	m_pTexture = nullptr;
	m_pVtxBuff = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fLength = 0.0f;
	m_fAngle = 0.0f;
	m_fSize = 0.0f;
	m_pFont = nullptr;
}

//================================================
//�f�X�g���N�^
//================================================
CRenderer::~CRenderer()
{
	/* �������� */
}

//================================================
//������
//================================================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	//Direct3D�I�u�W�F�N�g�̍쐬
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == nullptr)
	{
		return E_FAIL;
	}

	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));				//���[�N���[���N���A
	d3dpp.BackBufferCount = 1;						//�o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth = SCREEN_WIDTH;			//�Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;			//�Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;			//�J���[���[�h�̎w��
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;		//�f���M���ɓ������ăt���b�v����
	d3dpp.EnableAutoDepthStencil = TRUE;			//�f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;		//�f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;						//�E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	//���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	//�C���^�[�o��

	//�f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
	//�`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if ((FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice))) &&
		//��L�̐ݒ肪���s������
		//�`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice))) &&
		//��L�̐ݒ肪���s������
		//�`��ƒ��_������CPU�ōs�Ȃ�
		(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice))))
	{
		//�������s
		return E_FAIL;
	}

	//�����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�T���v���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

#ifdef _DEBUG
	//�f�o�b�O���\���p�t�H���g�̐���
	D3DXCreateFont(m_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &m_pFont);
#endif

	//�|���S���̏���������
	InitPolygon();

	return S_OK;
}

//================================================
//�I��
//================================================
void CRenderer::Uninit()
{
	//�|���S���̏I������
	UninitPolygon();

#ifdef _DEBUG
	//�f�o�b�O���\���p�t�H���g�̔j��
	if (m_pFont != nullptr)
	{
		m_pFont->Release();
		m_pFont = nullptr;
	}
#endif //_DEBUG

	//�f�o�C�X�̔j��
	if (m_pD3DDevice != nullptr)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = nullptr;
	}

	//Direct3D�I�u�W�F�N�g�̔j��
	if (m_pD3D != nullptr)
	{
		m_pD3D->Release();
		m_pD3D = nullptr;
	}
}

//================================================
//�X�V
//================================================
void CRenderer::Update()
{
	//�|���S���̍X�V����
	UpdatePolygon();
}

//================================================
//�`��
//================================================
void CRenderer::Draw()
{
	//�o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	m_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		//�|���S���̕`�揈��
		DrawPolygon();

#ifdef _DEBUG
		//FPS�\��
		DrawFPS();
#endif //_DEBUG

		//Direct3D�ɂ��`��̏I��
		m_pD3DDevice->EndScene();
	}

	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//================================================
//�|���S���̏�����
//================================================
HRESULT CRenderer::InitPolygon()
{
	//�ʒu
	m_pos = D3DXVECTOR3((SCREEN_WIDTH * 0.5f), (SCREEN_HEIGHT * 0.5f), 0.0f);

	//����
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�T�C�Y
	m_fSize = 100.0f;

	//�Ίp���̒������Z�o����
	m_fLength = sqrtf((m_fSize * m_fSize) + (m_fSize * m_fSize)) * 0.5f;

	//�Ίp���̊p�x���Z�o����
	m_fAngle = atan2f(m_fSize, m_fSize);

	//���_�o�b�t�@�̐���
	m_pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&m_pVtxBuff,
								NULL);

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_����ݒ�
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z + (m_fAngle * -3.0f)) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z + (m_fAngle * -3.0f)) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + (m_fAngle * 3.0f)) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + (m_fAngle * 3.0f)) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z + (m_fAngle * -1.0f)) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z + (m_fAngle * -1.0f)) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.z = 0.0f;

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
	m_pVtxBuff->Unlock();

	return S_OK;
}

//================================================
//�|���S���̏I��
//================================================
void CRenderer::UninitPolygon()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//================================================
//�|���S���̍X�V
//================================================
void CRenderer::UpdatePolygon()
{
	m_rot.z -= ROTATION_SPEED;	//��]

	/* �p�x�̐��K�� */
	if (m_rot.z >= D3DX_PI)
	{// 3.14���傫��
		m_rot.z -= D3DX_PI * 2.0f;
	}
	else if (m_rot.z <= -D3DX_PI)
	{// -3.14��菬����
		m_rot.z += D3DX_PI * 2.0f;
	}

	//�T�C�Y�̊g��E�k��
	m_fSize += cosf(m_rot.z) * 2.0f;

	//�Ίp���̒������Čv�Z
	m_fLength = sqrtf((m_fSize * m_fSize) + (m_fSize * m_fSize)) * 0.5f;

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̍X�V
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z + (m_fAngle * -3.0f)) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z + (m_fAngle * -3.0f)) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + (m_fAngle * 3.0f)) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + (m_fAngle * 3.0f)) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z + (m_fAngle * -1.0f)) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z + (m_fAngle * -1.0f)) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.z = 0.0f;
}

//================================================
//�|���S���̕`��
//================================================
void CRenderer::DrawPolygon()
{
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	m_pD3DDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	m_pD3DDevice->SetFVF(FVF_VERTEX_2D);

	//�|���S���̕`��
	m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
								0,						//�`�悷��ŏ��̒��_�C���f�b�N�X
								2);						//�`�悷��v���~�e�B�u��
}

#ifdef _DEBUG
//================================================
//FPS�̕`��
//================================================
void CRenderer::DrawFPS()
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	TCHAR str[256];

	wsprintf(str, _T("FPS : %d\n"), m_nCountFPS);

	//�e�L�X�g�`��
	m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
#endif //_DEBUG