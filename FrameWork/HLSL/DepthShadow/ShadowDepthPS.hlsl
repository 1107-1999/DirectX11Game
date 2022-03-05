//================================================
//
//�@�f�v�X�V���h�E
//
//================================================
#include "../Common/Common.hlsl"

Texture2D g_Texture : register(t0);//�ʏ�e�N�X�`��
Texture2D g_TextureShadowDepth : register(t1);//�V���h�E�}�b�v

SamplerState g_SamplerState : register(s0);
SamplerState g_ShadowSamplerState : register(s1);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	//�����ł̐F�����ʂ̃e�N�X�`�������_�F���쐬���Ă���
	outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
	outDiffuse *= In.Diffuse;


	In.ShadowPosition.xyz /= In.ShadowPosition.w; //���e�ʂł̃s�N�Z���̍��W����
	In.ShadowPosition.x = In.ShadowPosition.x * 0.5 + 0.5; //�e�N�X�`�����W�ɕϊ�
	In.ShadowPosition.y = -In.ShadowPosition.y * 0.5 + 0.5; //

	if (In.ShadowPosition.x > 0.0f&&In.ShadowPosition.x<1.0f
		&&In.ShadowPosition.y>0.0f&&In.ShadowPosition.y < 1.0f) {
		//�V���h�E�}�b�v�e�N�X�`�����A���C�g�J��������s�N�Z���܂ł̋����i�[�x�l�j���擾
		float depth = g_TextureShadowDepth.Sample(g_ShadowSamplerState,
			In.ShadowPosition.xy);
		//�擾�l���ʏ�J��������s�N�Z���ւ̋�����菬����
		if (depth < In.ShadowPosition.z - 0.01) //0.01��Z�t�@�C�e�B���O�␳�l�i��q�j
		{
			outDiffuse.rgb *= 0.5; //�F���Â�����
		}
	}
}