//================================================
//
//������H��b[renderer.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"

//***************************
//�����_�����O�N���X�̒�`
//***************************
class CRenderer
{/* ��{�N���X */
public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CRenderer();
	~CRenderer();

public: /* �����o�֐� */
	HRESULT Init(HWND hWnd, BOOL bWindow);	//������
	void Uninit();							//�I��
	void Update();							//�X�V
	void Draw();							//�`��
private:
	void DrawFPS();			//FPS�̕`��
public: /* Get�n */
	LPDIRECT3DDEVICE9 GetDevice();	//�f�o�C�X�̎擾
	/*
	LPDIRECT3DDEVICE9 GetDevice() {return m_pD3DDevice;}
	1�s�Ŋ������鏈���̏ꍇ�A�w�b�_�[�ɏ������Ƃ��ł���B
	*/

private: /* �����o�ϐ� */
	LPDIRECT3D9 m_pD3D;					//Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9 m_pD3DDevice;		//Device�I�u�W�F�N�g
	LPD3DXFONT m_pFont;					//�t�H���g
};

#endif