//================================================
//
//�@�f�v�X�V���h�E
//
//================================================
#include "../Common/Common.hlsl"

void main(in VS_IN In, out PS_IN Out)
{
	// ���_�ϊ�
	matrix  wvp;
	wvp = mul(World, View);
	wvp = mul(wvp, Projection);

	// �����v�Z
	float4 worldNormal, normal;
	normal = float4(In.Normal.xyz, 0.0);
	worldNormal = mul(normal, World);
	worldNormal = normalize(worldNormal);

	// ���C�g�̌v�Z(�n�[�t�����o�[�g)
	float light = 0.5f - 0.5f * dot(Light.Direction.xyz, worldNormal.xyz);
	light = saturate(light);
	Out.Diffuse = light;
	Out.Diffuse.a = In.Diffuse.a;

	//���_���W�����[���h�ϊ����ďo��
	Out.Position = mul(In.Position, wvp);
	Out.Normal = worldNormal;
	Out.TexCoord = In.TexCoord;

	// ���C�g�̌v�Z�}�g���N�X���v�Z
	matrix lightwvp;

	lightwvp = mul(World, Light.View);//���[���h�s�񁖃��C�g�r���[�s��
	lightwvp = mul(lightwvp, Light.Projection);//����Ɂ����C�g�v���W�F�N�V�����s��

	//���C�g����݂����_���W���o��
	Out.ShadowPosition = mul(In.Position, lightwvp);
}