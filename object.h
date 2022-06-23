//================================================
//
//������H��b[object.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

//***************************
//�C���N���[�h
//***************************
#include <d3dx9.h>

//***************************
//�萔�̒�`
//***************************
const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);	//���_�t�H�[�}�b�g

//***************************
//�I�u�W�F�N�g�N���X�̒�`
//***************************
class CObject
{/* ��{�N���X */
public: /* �萔�̒�` */
	static const int MAX_POLYGON = 256;	//�|���S���̍ő吔

public: /* �ÓI�����o�֐� */
	static void ReleaseAll();	//�S�Ẳ��
	static void UpdateAll();	//�S�Ă̍X�V
	static void DrawAll();		//�S�Ă̕`��

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CObject();
	virtual ~CObject();

public: /* �������z�֐� */
	virtual HRESULT Init() = 0;	//������
	virtual void Uninit() = 0;	//�I��
	virtual void Update() = 0;	//�X�V
	virtual void Draw() = 0;	//�`��
public: /* Set,Get�n */
	virtual void SetPos(const D3DXVECTOR3 &pos) = 0;	//�ʒu��ݒ�
	virtual D3DXVECTOR3 GetPos() = 0;					//�ʒu���擾

protected: /* �����o�֐� */
	void Release();	//���

private: /* �ÓI�����o�ϐ� */
	static CObject* m_apObject[MAX_POLYGON];	//�|�C���^
	static int m_nNumAll;						//�ő吔
	
private: /* �����o�ϐ� */
	int m_nID;	//�i�[��̔ԍ�
};

#endif