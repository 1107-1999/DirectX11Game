//=============================================================================
//
//  [Common.hlsl]
//  Date   : 2021/12/08
//
//=============================================================================


// ���[���h�}�g���N�X�o�b�t�@
cbuffer WorldBuffer : register(b0)
{
	matrix World;
}

// �r���[�o�b�t�@
cbuffer ViewBuffer : register(b1)
{
	matrix View;
}

// �v���W�F�N�V�����o�b�t�@
cbuffer ProjectionBuffer : register(b2)
{
	matrix Projection;
}


// �}�e���A���\����
struct MATERIAL
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;
	float4 Emission;
	float  Shininess;
	float3 Dummy;
};

// �}�e���A���o�b�t�@
cbuffer MaterialBuffer : register(b3)
{
	MATERIAL Material;
}

// ���C�g�\����
struct LIGHT
{
	float4 Direction;
	float4 Diffuse;
	float4 Ambient;
	bool   Enable;
	bool3  Dummy;
	matrix View;
	matrix Projection;
};

// ���C�g�o�b�t�@
cbuffer LightBuffer : register(b4)
{
	LIGHT Light;
}

// �J�����o�b�t�@
cbuffer CameraBuffer : register(b5)
{
	float4 CameraPosition;
	float CameraLength;
	float3 Dummy;
}

// �o�[�e�b�N�X�V�F�[�_�[�\����
struct VS_IN
{
	float4 Position		: POSITION0;
	float4 Normal		: NORMAL0;
	float4 Diffuse		: COLOR0;
	float2 TexCoord		: TEXCOORD0;
};

// �s�N�Z���V�F�[�_�[�\����
struct PS_IN
{
	float4 Position		 : SV_POSITION;
	float4 WorldPosition : POSITION0;
	float4 Normal        : NORMAL0;
	float4 Diffuse		 : COLOR0;
	float2 TexCoord		 : TEXCOORD0;
	float4 ShadowPosition : POSITION1;
};


// �X�N���[���̃��C�\����
cbuffer CB : register(b6)
{
	float4 FrustumRayTL;// �X�N���[���̍���Ɍ������J�����̃��C
	float4 FrustumRayTR;// �X�N���[���̉E��Ɍ������J�����̃��C
	float4 FrustumRayBL;// �X�N���[���̍����Ɍ������J�����̃��C
	float2 WindowSize;   // �E�B���h�E�T�C�Y
	float2 Enable;
};

// ��C�U���p�o�b�t�@�\����
cbuffer SkyCB : register(b7)
{
	float3 CameraPos;		// �J�����̃|�W�V����
	float  CameraHeight;	// �J�����̍���

	float3 LightDirection;	// ���C�g�̌���
	float  Scale;			// ��C�̑傫��

	float3 InvWavelength;	// ���̔g���̒���
	float exposure;

	float OuterRadius;		// ��C�̑傫��
	float InnerRadius;		// �n���̑傫��

	float KrESun;			// ���z�̖��邳*���q�̑傫��(���C���[�U��)
	float KmESun;			// ���z�̖��邳*���q�̑傫��(�~�[�U��)
	float Kr4PI;			// ���q�̑傫��(���C���[�U��)*�~����
	float Km4PI;			// ���q�̑傫��(�~�[�U��)*�~����

	float ScaleDepth;		// ��C�̕��ϓI�Ȗ��x
	float ScaleOverScaleDepth;	// fScale / fScaleDepth
	float g;

	float3 dummy;// �o�C�g�����킹
};