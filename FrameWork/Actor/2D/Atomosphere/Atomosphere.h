//=============================================================================
//
//  ��C�N���X [Atomosphere.h]
//  Date   : 2021/12/10
//
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "../../2D/Base/Actor2D.h"
#include "../Atomosphere/Atomosphere.h"

//=============================================================================
// �\���̒�`
//=============================================================================
// ��C�U���p�o�b�t�@�\����
struct SKY_RAY
{
	D3DXVECTOR4 frustumRayTL;  // �X�N���[���̍���̃��C
	D3DXVECTOR4 frustumRayTR;  // �X�N���[���̉E��̃��C
	D3DXVECTOR4 frustumRayBL;  // �X�N���[���̍����̃��C
	D3DXVECTOR2 windowSize;	   // �E�B���h�E�̃T�C�Y
	D3DXVECTOR2	Enable;		   // �o�b�t�@�T�C�Y���킹
};

struct SKY
{
	Vector3 CameraPos;        // �J�����̃|�W�V����
	float   CameraHeight;	    // �J�����̍���

	Vector3 LightDirection;	// ���C�g�̌���
	float Scale;			    // ��C�̑傫��

	Vector3 InvWavelength;    // ���̔g���̒���
	float exposure;

	float OuterRadius;		    // ��C�̑傫��
	float InnerRadius;		    // �n���̑傫��

	float KrESun;			    // ���z�̖��邳*���q�̑傫��(���C���[�U��)
	float KmESun;			    // ���z�̖��邳*���q�̑傫��(�~�[�U��)
	float Kr4PI;			    // ���q�̑傫��(���C���[�U��)*�~����
	float Km4PI;			    // ���q�̑傫��(�~�[�U��)*�~����

	float ScaleDepth;		    // ��C�̕��ϓI�Ȗ��x
	float ScaleOverScaleDepth;	// fScale / fScaleDepth
	float g;
	Vector3 dammy;
};

//=============================================================================
// �N���X��`
//=============================================================================
class Atomosphere : public Actor2D
{
private:

	class Component_Sprite*    m_Component_Sprite;   //�X�v���C�g�R���|�[�l���g

	//DirectX11�`��N���X�L���b�V��
	class Renderer_DirectX11* m_Renderer_DirectX11 = nullptr;


	ID3D11Buffer* m_SkyRayBuffer; // ��C�U���p�X�N���[�����C�\����
	ID3D11Buffer* m_SkyBuffer;    // ��C�U���p�p�����[�^�\����

	//����
	double m_Time;

	//�V��
	class SkySphere* m_SkySphere;

public:

	//���\�[�X�ǂݍ��݁E�폜
	static void Load();
	static void Unload();

	//�������E�I���E�X�V
	void Init()override;
	void Uninit()override;
	void Update()override;

	// ���C�̃Z�b�g
	void SetSkyRay(SKY_RAY _skyray);

	// ��C�U���\���̂̃Z�b�g
	void SetSky(SKY _sky);

private:

	// ���z�̌����̌v�Z
	Vector3 SunDirection(int _day, double _time, double _eastLongitude, double _northLatitude);

	// �X�N���[���̃��C�̌v�Z
	void RayCalculation(D3DXMATRIX view, D3DXMATRIX proj);

	// ��C�U���̌v�Z
	void AtomosphereCalculation();
};