//================================================
//
//������H��b[renderer.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

//***************************
//���C�u�����[�����N
//***************************
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"winmm.lib")

//***************************
//�C���N���[�h
//***************************
#include <Windows.h>
#include <tchar.h> //_T
#include <d3dx9.h>

//***************************
//�����_���[�N���X�̒�`
//***************************
class CRenderer
{/* ��{�N���X */
public: /* �\���̂̒�` */
	struct VERTEX_2D
	{//���_�f�[�^
		D3DXVECTOR3 pos;	//�ʒu
		float rhw;			//�@��
		D3DCOLOR col;		//�F
	};

public: /* �萔�̒�` */
	static const int SCREEN_WIDTH = 1280;	//�X�N���[���̕�
	static const int SCREEN_HEIGHT = 720;	//�X�N���[���̍���
	const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE);	//���_�t�H�[�}�b�g
private:
	/* �����Œǉ��������� */
	const float ROTATION_SPEED = 0.05f;	//��]�X�s�[�h

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CRenderer();
	~CRenderer();

public: /* �����o�֐� */
	HRESULT Init(HWND hWnd, BOOL bWindow);	//������
	void Uninit();							//�I��
	void Update();							//�X�V
	void Draw();							//�`��
private:
	HRESULT InitPolygon();	//�|���S���̏�����
	void UninitPolygon();	//�|���S���̏I��
	void UpdatePolygon();	//�|���S���̍X�V
	void DrawPolygon();		//�|���S���̕`��
	void DrawFPS();			//FPS�̕`��

public: /* �ÓI�����o�ϐ� */
#ifdef _DEBUG
	static int m_nCountFPS;	//FPS�J�E���^
#endif //_DEBUG

private: /* �����o�ϐ� */
	LPDIRECT3D9 m_pD3D;					//Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9 m_pD3DDevice;		//Device�I�u�W�F�N�g
	LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;					//�ʒu
	D3DXVECTOR3 m_rot;					//����
	float m_fLength;					//�Ίp���̒���
	float m_fAngle;						//�Ίp���̊p�x
	float m_fSize;						//�T�C�Y
	LPD3DXFONT m_pFont;					//�t�H���g
};

#endif