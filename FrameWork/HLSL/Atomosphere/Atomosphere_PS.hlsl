//================================================
//
// ��C�U��
//
//================================================
#include "../Common/Common.hlsl"


// �����|�W�V���������߂�
float3 IntersectionPos(float3 rayPos, float3 rayDir, float sphereRadius)
{
	const float A = dot(rayDir, rayDir);
	const float B = 2.0*dot(rayPos, rayDir);
	const float C = dot(rayPos, rayPos) - sphereRadius * sphereRadius;

	return B * B - 4.0 * A * C < 0.000001 ? float3(0, 0, 0) : (rayPos + rayDir * (0.5 * (-B + sqrt(B * B - 4.0 * A * C)) / A));
}

// �ϕ��ߎ��l�����߂�
float IntegralApproximation(float cos)
{
	float x = 1.0 - cos;
	return ScaleDepth * exp(-0.00287 + x * (0.459 + x * (3.83 + x * (-6.80 + x * 5.25))));
}

float4 main(in PS_IN input) : SV_Target
{
	// UV�̌v�Z
	float2 uv = (input.Position.xy / float2(WindowSize));

	// ���C�̌v�Z
	float3 deltaX = (FrustumRayTR - FrustumRayTL) * uv.x;
	float3 deltaY = (FrustumRayBL - FrustumRayTL) * uv.y;
	float3 screenRay = normalize((FrustumRayTL + deltaX + deltaY).xyz);

	// �J�����|�W�V�����ɃC���i�[���f�B�E�X�����Z
	float3 cameraPos = CameraPosition.xyz;
	cameraPos.y = cameraPos.y + InnerRadius;
	float cameraLen = length(cameraPos);

	float3 skyPos = IntersectionPos(cameraPos.xyz, screenRay, OuterRadius);
	if (skyPos.x == 0)
	{
		//�J�������V�����o����s�N�Z����j��
		clip(-1);
	}

	float3 invWavelength = InvWavelength;

	float3 pos = skyPos;
	float3 ray = pos - cameraPos.xyz;
	float far = length(ray);
	ray /= far;

	// �U���I�t�Z�b�g�̌v�Z
	float3 start = cameraPos.xyz;
	float height = length(start);
	float depth = exp(ScaleOverScaleDepth * (InnerRadius - cameraLen));
	float startAngle = dot(ray, start) / height;
	float startOffset = depth * IntegralApproximation(startAngle);

	const int nSamples = 5;
	const float fSamples = nSamples;

	// �U�����[�v�ϐ��̏�����
	float sampleLength = far / fSamples;
	float scaledLength = sampleLength * Scale;
	float3 sampleRay = ray * sampleLength;
	float3 samplePoint = start + sampleRay * 0.5;

	// �T���v���_�����[�v
	float3 frontColor = float3(0.0, 0.0, 0.0);
	for (int i = 0; i < nSamples; ++i)
	{
		float heightS = length(samplePoint);
		float depthS = exp(ScaleOverScaleDepth * (InnerRadius - heightS));
		float lightAngle = dot(LightDirection, samplePoint) / heightS;
		float cameraAngle = dot(ray, samplePoint) / heightS;
		float scatter = (startOffset + depthS * (IntegralApproximation(lightAngle) - IntegralApproximation(cameraAngle)));
		float3 attenuate = exp(-scatter * (invWavelength * Kr4PI + Km4PI));
		frontColor += attenuate * (depthS * scaledLength);
		samplePoint += sampleRay;
	}

	// �~�[�ƃ��C���[�̐F���X�P�[��
	float4 primaryColor = float4(frontColor * (invWavelength * KrESun), 1.0);
	float4 secondaryColor = float4(frontColor * KmESun, 1.0);
	float3 direction = cameraPos.xyz - pos;

	float Cos = dot(LightDirection, direction) / length(direction);
	float rayPhase = 0.75 * (1.0 + Cos * Cos);

	const float g2 = g * g;
	float miePhase = 1.5 * ((1.0 - g2) / (2.0 + g2)) * (1.0 + Cos * Cos) / pow(abs(1.0 + g2 - 2.0 * g * Cos), 1.5);

	float3 raycolor = (primaryColor * rayPhase).xyz;
	float3 miecolor = (secondaryColor * miePhase).xyz;

	float3 c = float3(1.0, 1.0, 1.0) - exp(-exposure * (raycolor + miecolor));
	return float4(saturate(c), 1.0);
}