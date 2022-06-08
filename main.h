//================================================
//
//������H��b[main.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _MAIN_H_
#define _MAIN_H_

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
//�O���錾
//***************************
class CRenderer;
class CObject;

//***************************
//�萔�̒�`
//***************************
const int SCREEN_WIDTH = 1280;	//�X�N���[���̕�
const int SCREEN_HEIGHT = 720;	//�X�N���[���̍���

//***************************
//�v���g�^�C�v�錾
//***************************
/* FPS�̎擾 */
int GetFPS();

/* �����_�����O���̎擾 */
CRenderer* GetRenderer();

/* �I�u�W�F�N�g���̎擾 */
CObject** GetObjects();

#endif