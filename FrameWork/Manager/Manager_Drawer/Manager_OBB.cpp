//=============================================================================
//
//  OBB�R���|�[�l���g�}�l�[�W���[ [Manager_OBB.cpp]
//  Date   : 2021/11/10
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "Manager_OBB.h"
#include "Manager_ImGui.h"
#include "../Manager_Game.h"
#include "../../Actor/Base/Actor.h"
#include "../../Component/Component_OBB.h"
#include "../../Renderer/Renderer_Polygon.h"
#include "../../System/Math.h"
#include "../../System/Exchanger.h"

//=============================================================================
// OBB�R���|�[�l���g���X�g�o�^(�������̓R���W�����`�����l��)
//=============================================================================
void Manager_OBB::AddComponent(class Component_OBB* _add, int _layer)
{
	m_ComponentList[_layer].push_back(_add);
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void Manager_OBB::Update()
{
	//�v���C���[�̔���
	for (Component_OBB* OBB_Player : m_ComponentList[COLLISION_PLAYER])
	{

		//�L����
		if (OBB_Player->GetActive())
		{
			//�v���C���[�Əe�̔���
			for (Component_OBB* OBB_Gun : m_ComponentList[COLLISION_GUN])
			{
				if (OBB_Gun->GetActive())//�L����
				{
					if (OverlapJudgeOBB(OBB_Player, OBB_Gun))
					{
						OBB_Player->SetColor(Color{0.0f,0.0f,1.0f,1.0f});
						OBB_Gun->SetColor(Color{ 1.0f,0.0f,0.0f,1.0f });
						OBB_Gun->SetOverlap(true);
					}
				}
			}

			//�v���C���[�ƃS�[���̔���
			for (Component_OBB* OBB_Goal : m_ComponentList[COLLISION_GOAL])
			{
				if (OBB_Goal->GetActive())//�L����
				{
					if (OverlapJudgeOBB(OBB_Player, OBB_Goal))
					{
						OBB_Player->SetColor(Color{ 0.0f,0.0f,1.0f,1.0f });
						OBB_Goal->SetColor(Color{ 1.0f,0.0f,0.0f,1.0f });
						OBB_Goal->SetOverlap(true);
					}
				}
			}


			//�v���C���[�ƃu���b�N�̔���
			for (Component_OBB* OBB_Block : m_ComponentList[COLLISION_BLOCK])
			{
				if (OBB_Block->GetActive())//�L����
				{
					if (OverlapJudgeOBB(OBB_Player, OBB_Block))
					{
						OBB_Block->SetOverlap(true);
					}
				}
			}
		}


	}

	//���C�̕`�掞�ԉ��Z
	for (auto& i : m_DebugDrawRayList)
	{
		i.time++;
	}

	//���C�̕`��I��
	m_DebugDrawRayList.remove_if([](s_DrawData _data) {return _data.time >= _data.timeMax; });
}

//=============================================================================
// �`��֐�
//=============================================================================
void Manager_OBB::Draw()
{
	//OBB�R���|�[�l���g���X�g�̕`��
	for (int i = 0; i < MAX_ACTOR_TYPE; i++)
	{
		for (Component_OBB* component_OBB : m_ComponentList[i])
		{
			component_OBB->Draw();
		}
	}

	//���C�`��
	for (auto& i : m_DebugDrawRayList)
	{
		Renderer_Polygon::Instance()->DrawLine(i.startPos, i.endPos, i.color);
	}
}

//=============================================================================
// �I���֐�
//=============================================================================
void Manager_OBB::Uninit()
{
	//OBB�R���|�[�l���g���X�g�̃N���A
	for (int i = 0; i < MAX_ACTOR_TYPE; i++)
	{
		m_ComponentList[i].clear();
	}
}

//=============================================================================
// OBB��OBB�̃I�[�o�[���b�v����֐�
//=============================================================================
bool Manager_OBB::OverlapJudgeOBB(Component_OBB* _component_OBBA, Component_OBB* _component_OBBB)
{
	//�{�b�N�X���m�̋���
	Vector3 distance = _component_OBBB->GetPosition() - _component_OBBA->GetPosition();

	//��r�p�̍\����
	s_OBBCompData A = {};
	s_OBBCompData B = {};

	//���S����̊e���̒���
	A.lengthX = _component_OBBA->GetLengthX();
	A.lengthY = _component_OBBA->GetLengthY();
	A.lengthZ = _component_OBBA->GetLengthZ();
	B.lengthX = _component_OBBB->GetLengthX();
	B.lengthY = _component_OBBB->GetLengthY();
	B.lengthZ = _component_OBBB->GetLengthZ();

	//���[�J����ꎲ�x�N�g���ɂ��ꂼ��̉�]�𔽉f������
	D3DXMATRIX mtxRA;
	Vector3 tempCmpRotA = _component_OBBA->GetRotation();
	D3DXMatrixRotationYawPitchRoll(&mtxRA, tempCmpRotA.y, tempCmpRotA.x, tempCmpRotA.z);
	D3DXVec3TransformCoord(&A.axisX, &A.axisX, &mtxRA);
	D3DXVec3TransformCoord(&A.axisY, &A.axisY, &mtxRA);
	D3DXVec3TransformCoord(&A.axisZ, &A.axisZ, &mtxRA);

	D3DXMATRIX mtxRB;
	Vector3 tempCmpRotB = _component_OBBB->GetRotation();
	D3DXMatrixRotationYawPitchRoll(&mtxRB, tempCmpRotB.y, tempCmpRotB.x, tempCmpRotB.z);
	D3DXVec3TransformCoord(&B.axisX, &B.axisX, &mtxRB);
	D3DXVec3TransformCoord(&B.axisY, &B.axisY, &mtxRB);
	D3DXVec3TransformCoord(&B.axisZ, &B.axisZ, &mtxRB);

	//�{�b�N�XA��̃��[�J����ꎲ��̉e�Z�o
	if (!CompareLength(&A, &B, &A.axisX, &distance))return false;//X�𕪗�����
	if (!CompareLength(&A, &B, &A.axisY, &distance))return false;//Y�𕪗�����
	if (!CompareLength(&A, &B, &A.axisZ, &distance))return false;//Z�𕪗�����

	//�{�b�N�XB��̃��[�J����ꎲ��̉e�Z�o
	if (!CompareLength(&A, &B, &B.axisX, &distance))return false;//X�𕪗�����
	if (!CompareLength(&A, &B, &B.axisY, &distance))return false;//Y�𕪗�����
	if (!CompareLength(&A, &B, &B.axisZ, &distance))return false;//Z�𕪗�����

	Vector3 separate = {};
	//���݂��̊�ꎲ���m�̊O�ʃx�N�g����̉e�Z�o
	{
		//�{�b�N�XA��X
		{
			//�Ɓ@�{�b�N�XB��X���Ƃ̊O�σx�N�g���𕪗����Ƃ����ꍇ
			D3DXVec3Cross(&separate, &A.axisX, &B.axisX);
			if (!CompareLength(&A, &B, &separate, &distance)) return false;
			//�Ɓ@�{�b�N�XB��Y���Ƃ̊O�σx�N�g���𕪗����Ƃ����ꍇ
			D3DXVec3Cross(&separate, &A.axisX, &B.axisY);
			if (!CompareLength(&A, &B, &separate, &distance)) return false;
			//�Ɓ@�{�b�N�XB��Z���Ƃ̊O�σx�N�g���𕪗����Ƃ����ꍇ
			D3DXVec3Cross(&separate, &A.axisX, &B.axisZ);
			if (!CompareLength(&A, &B, &separate, &distance)) return false;
		}
		//�{�b�N�XAY
		{
			//�Ɓ@�{�b�N�XB��X���Ƃ̊O�σx�N�g���𕪗����Ƃ����ꍇ
			D3DXVec3Cross(&separate, &A.axisY, &B.axisX);
			if (!CompareLength(&A, &B, &separate, &distance)) return false;
			//�Ɓ@�{�b�N�XB��Y���Ƃ̊O�σx�N�g���𕪗����Ƃ����ꍇ
			D3DXVec3Cross(&separate, &A.axisY, &B.axisY);
			if (!CompareLength(&A, &B, &separate, &distance)) return false;
			//�Ɓ@�{�b�N�XB��Z���Ƃ̊O�σx�N�g���𕪗����Ƃ����ꍇ
			D3DXVec3Cross(&separate, &A.axisY, &B.axisZ);
			if (!CompareLength(&A, &B, &separate, &distance)) return false;
		}
		//�{�b�N�XAZ
		{
			//�Ɓ@�{�b�N�XB��X���Ƃ̊O�σx�N�g���𕪗����Ƃ����ꍇ
			D3DXVec3Cross(&separate, &A.axisZ, &B.axisX);
			if (!CompareLength(&A, &B, &separate, &distance)) return false;
			//�Ɓ@�{�b�N�XB��Y���Ƃ̊O�σx�N�g���𕪗����Ƃ����ꍇ
			D3DXVec3Cross(&separate, &A.axisZ, &B.axisY);
			if (!CompareLength(&A, &B, &separate, &distance)) return false;
			//�Ɓ@�{�b�N�XB��Z���Ƃ̊O�σx�N�g���𕪗����Ƃ����ꍇ
			D3DXVec3Cross(&separate, &A.axisZ, &B.axisZ);
			if (!CompareLength(&A, &B, &separate, &distance)) return false;
		}
	}

	//��������
	return true;
}

//=============================================================================
// OBB�Ɠ_�̃I�[�o�[���b�v����֐�
//=============================================================================
bool Manager_OBB::OverlapJudgeOBBandPoint(Component_OBB * _component_OBB, Vector3 _point)
{
	//�{�b�N�X���m�̋���
	Vector3 distance = _component_OBB->GetPosition() - _point;

	//��r�p�̍\����
	s_OBBCompData A = {};
	s_OBBCompData B = {};

	//�_�ɒ����������̂�0�B
	A.lengthX = 0.0f;
	A.lengthY = 0.0f;
	A.lengthZ = 0.0f;
	B.lengthX = _component_OBB->GetLengthX();
	B.lengthY = _component_OBB->GetLengthY();
	B.lengthZ = _component_OBB->GetLengthZ();

	//���[�J����ꎲ�x�N�g���ɂ��ꂼ��̉�]�𔽉f������
	D3DXMATRIX mtxRA;
	Vector3 tempCmpRotA = Vector3(0, 0, 0);
	D3DXMatrixRotationYawPitchRoll(&mtxRA, tempCmpRotA.y, tempCmpRotA.x, tempCmpRotA.z);
	D3DXVec3TransformCoord(&A.axisX, &A.axisX, &mtxRA);
	D3DXVec3TransformCoord(&A.axisY, &A.axisY, &mtxRA);
	D3DXVec3TransformCoord(&A.axisZ, &A.axisZ, &mtxRA);

	D3DXMATRIX mtxRB;
	Vector3 tempCmpRotB = _component_OBB->GetRotation();
	D3DXMatrixRotationYawPitchRoll(&mtxRB, tempCmpRotB.y, tempCmpRotB.x, tempCmpRotB.z);
	D3DXVec3TransformCoord(&B.axisX, &B.axisX, &mtxRB);
	D3DXVec3TransformCoord(&B.axisY, &B.axisY, &mtxRB);
	D3DXVec3TransformCoord(&B.axisZ, &B.axisZ, &mtxRB);

	//�{�b�N�XA��̃��[�J����ꎲ��̉e�Z�o
	if (!CompareLength(&A, &B, &A.axisX, &distance))return false;//X�𕪗�����
	if (!CompareLength(&A, &B, &A.axisY, &distance))return false;//Y�𕪗�����
	if (!CompareLength(&A, &B, &A.axisZ, &distance))return false;//Z�𕪗�����

	//�{�b�N�XB��̃��[�J����ꎲ��̉e�Z�o
	if (!CompareLength(&A, &B, &B.axisX, &distance))return false;//X�𕪗�����
	if (!CompareLength(&A, &B, &B.axisY, &distance))return false;//Y�𕪗�����
	if (!CompareLength(&A, &B, &B.axisZ, &distance))return false;//Z�𕪗�����

	Vector3 separate = {};
	//���݂��̊�ꎲ���m�̊O�ʃx�N�g����̉e�Z�o
	{
		//�{�b�N�XA��X
		{
			//�Ɓ@�{�b�N�XB��X���Ƃ̊O�σx�N�g���𕪗����Ƃ����ꍇ
			D3DXVec3Cross(&separate, &A.axisX, &B.axisX);
			if (!CompareLength(&A, &B, &separate, &distance)) return false;
			//�Ɓ@�{�b�N�XB��Y���Ƃ̊O�σx�N�g���𕪗����Ƃ����ꍇ
			D3DXVec3Cross(&separate, &A.axisX, &B.axisY);
			if (!CompareLength(&A, &B, &separate, &distance)) return false;
			//�Ɓ@�{�b�N�XB��Z���Ƃ̊O�σx�N�g���𕪗����Ƃ����ꍇ
			D3DXVec3Cross(&separate, &A.axisX, &B.axisZ);
			if (!CompareLength(&A, &B, &separate, &distance)) return false;
		}
		//�{�b�N�XAY
		{
			//�Ɓ@�{�b�N�XB��X���Ƃ̊O�σx�N�g���𕪗����Ƃ����ꍇ
			D3DXVec3Cross(&separate, &A.axisY, &B.axisX);
			if (!CompareLength(&A, &B, &separate, &distance)) return false;
			//�Ɓ@�{�b�N�XB��Y���Ƃ̊O�σx�N�g���𕪗����Ƃ����ꍇ
			D3DXVec3Cross(&separate, &A.axisY, &B.axisY);
			if (!CompareLength(&A, &B, &separate, &distance)) return false;
			//�Ɓ@�{�b�N�XB��Z���Ƃ̊O�σx�N�g���𕪗����Ƃ����ꍇ
			D3DXVec3Cross(&separate, &A.axisY, &B.axisZ);
			if (!CompareLength(&A, &B, &separate, &distance)) return false;
		}
		//�{�b�N�XAZ
		{
			//�Ɓ@�{�b�N�XB��X���Ƃ̊O�σx�N�g���𕪗����Ƃ����ꍇ
			D3DXVec3Cross(&separate, &A.axisZ, &B.axisX);
			if (!CompareLength(&A, &B, &separate, &distance)) return false;
			//�Ɓ@�{�b�N�XB��Y���Ƃ̊O�σx�N�g���𕪗����Ƃ����ꍇ
			D3DXVec3Cross(&separate, &A.axisZ, &B.axisY);
			if (!CompareLength(&A, &B, &separate, &distance)) return false;
			//�Ɓ@�{�b�N�XB��Z���Ƃ̊O�σx�N�g���𕪗����Ƃ����ꍇ
			D3DXVec3Cross(&separate, &A.axisZ, &B.axisZ);
			if (!CompareLength(&A, &B, &separate, &distance)) return false;
		}
	}

	//��������
	return true;
}

//=============================================================================
// �����̎����瓖�����Ă��邩�m�F
//=============================================================================
bool Manager_OBB::CompareLength(s_OBBCompData * _A, s_OBBCompData * _B, Vector3 * _separate, Vector3 * _distance)
{
	//��������ł̃{�b�N�XA�̒��S����{�b�N�XB�̒��S�܂ł̍��W
	float distance = fabsf(D3DXVec3Dot(_distance, _separate));
	//��������Ń{�b�N�XA�̒��S����ł������{�b�N�XA�̒��_�܂ł̋���
	float shadowA = 0.0f;
	//��������Ń{�b�N�XB�̒��S����ł������{�b�N�XB�̒��_�܂ł̋���
	float shadowB = 0.0f;
	//���ꂼ��̃{�b�N�X�̉e���Z�o
	shadowA = fabsf(D3DXVec3Dot(&_A->axisX, _separate) * _A->lengthX) +
		fabsf(D3DXVec3Dot(&_A->axisY, _separate) * _A->lengthY) +
		fabsf(D3DXVec3Dot(&_A->axisZ, _separate) * _A->lengthZ);

	shadowB = fabsf(D3DXVec3Dot(&_B->axisX, _separate) * _B->lengthX) +
		fabsf(D3DXVec3Dot(&_B->axisY, _separate) * _B->lengthY) +
		fabsf(D3DXVec3Dot(&_B->axisZ, _separate) * _B->lengthZ);

	if (distance > shadowA + shadowB) return false;
	return true;
}

//=============================================================================
// ���C����֐�
//=============================================================================
s_HIT_Result Manager_OBB::Raycast(Vector3 _startPos, Vector3 _endPos,
	Actor* _ignoreMySelf, bool _isDispRay, std::list<ACTOR_TYPE>_ignoreList,
	Color _drawRayColor,float _accuracy, int _drawRayLife)
{
	//���HIT���U���g
	s_HIT_Result hit_result;

	//�J�n�_����I���_�܂ł̋���
	const float length = D3DXVec3Length(&(_endPos - _startPos));

	//�J�n�_����I���_�܂ł̋����L���b�V��
	float tempLen = length;

	//�J��Ԃ��񐔏�����
	int tempRep = 0;

	//�J��Ԃ��񐔌v�Z
	while (tempLen < 1.0f)
	{
		tempLen *= 10.0f;
		tempRep++;
	}

	//�J��Ԃ���
	const int repeat = static_cast<int>(floor(length * (_accuracy * max(tempRep, 1))));

	//��x�̍X�V�Ői�ދ���
	const float addLen = static_cast<float>(length / repeat);

	//���݂̒T���ʒu
	Vector3 currentPos = _startPos;

	//�v���C���[����J�����̕���
	Vector3 dir;

	D3DXVec3Normalize(&dir, &(_endPos - _startPos));

	//�`��p�f�[�^����
	if (_isDispRay)
	{
		s_DrawData temp = {};
		temp.color = _drawRayColor;
		temp.startPos = _startPos;
		temp.endPos = _endPos;
		temp.time = 0;
		temp.timeMax = _drawRayLife;
		m_DebugDrawRayList.emplace_back(temp);
	}

	float currentLen = 0.0f;
	for (int i = 0; i < repeat; i++)
	{
		//OBB�̃��C���[���J��Ԃ�
		for (int k = 0; k < ACTOR_TYPE::MAX_ACTOR_TYPE; k++)
		{
			//�J�������m�͔��肵�Ȃ�
			if (k == ACTOR_TYPE::COLLISION_CAMERA)continue;

			bool isIgn = false;
			//�������X�g�ƌ��݂̃��C���[���r
			for (auto& ign : _ignoreList)
			{
				if (k == ign)
				{
					isIgn = true;
					break;
				}
			}
			if (isIgn)continue;

			//OBB�̌����J��Ԃ�
			std::list<Component_OBB*>::iterator itr = m_ComponentList[k].begin();
			for (; itr != m_ComponentList[k].end(); itr++)
			{
				//���g�𖳎�����ݒ�Ȃ疳������
				if (_ignoreMySelf && _ignoreMySelf == (*itr)->GetOwner())continue;

				//OBB�ɓ_���q�b�g
				if (OverlapJudgeOBBandPoint(*itr, currentPos))
				{
					//���������ǂ���
					hit_result.isHIT = true;

					//�����}�e���A���擾
					hit_result.physicsMaterial = (*itr)->GetPhysicsMaterial();

					//�������A�N�^�[
					hit_result.hitActor = (*itr)->GetOwner();

					//HIT���W
					hit_result.hitPos = currentPos;

					//����܂ł̃��C�̒���
					hit_result.length = currentLen;

				}
			}
		}
		//�X�^�[�g�n�_����T����������
		currentLen += addLen;

		//���݂̒T���ʒu
		currentPos += dir * currentLen;
	}

	return hit_result;
}

//=============================================================================
// �����x���C�L���X�g�֐�
//=============================================================================
s_HIT_Result Manager_OBB::RaycastHighAccuracy(Vector3 _startPos, Vector3 _endPos,
	Actor* _ignoreMySelf, bool _isDispRay, std::list<ACTOR_TYPE>_ignoreList,
	Color _drawRayColor, float _accuracy, int _drawRayLife)
{
	//���HIT���U���g
	s_HIT_Result hit_result;

	//�J�n�_����I���_�܂ł̋���
	const float length = D3DXVec3Length(&(_endPos - _startPos));

	//�J�n�_����I���_�܂ł̋����L���b�V��
	float tempLen = length;

	//�J��Ԃ��񐔏�����
	int tempRep = 0;

	//�J��Ԃ��񐔌v�Z
	while (tempLen < 1.0f)
	{
		tempLen *= 10.0f;
		tempRep++;
	}

	//�J��Ԃ���
	const int repeat = static_cast<int>(floor(length * (_accuracy * max(tempRep, 1))));

	//��x�̍X�V�Ői�ދ���
	constexpr float addLen = 0.0001f;

	//���݂̒T���ʒu
	Vector3 currentPos = _startPos;

	//�v���C���[����J�����̕���
	Vector3 dir;

	D3DXVec3Normalize(&dir, &(_endPos - _startPos));

	//�`��p�f�[�^����
	if (_isDispRay)
	{
		s_DrawData temp = {};
		temp.color = _drawRayColor;
		temp.startPos = _startPos;
		temp.endPos = _endPos;
		temp.time = 0;
		temp.timeMax = _drawRayLife;
		m_DebugDrawRayList.emplace_back(temp);
	}

	float currentLen = 0.0f;
	for (int i = 0; i < repeat; i++)
	{
		//OBB�̃��C���[���J��Ԃ�
		for (int k = 0; k < ACTOR_TYPE::MAX_ACTOR_TYPE; k++)
		{
			//�J�������m�͔��肵�Ȃ�
			if (k == ACTOR_TYPE::COLLISION_CAMERA)continue;

			bool isIgn = false;
			//�������X�g�ƌ��݂̃��C���[���r
			for (auto& ign : _ignoreList)
			{
				if (k == ign)
				{
					isIgn = true;
					break;
				}
			}
			if (isIgn)continue;

			//OBB�̌����J��Ԃ�
			std::list<Component_OBB*>::iterator itr = m_ComponentList[k].begin();
			for (; itr != m_ComponentList[k].end(); itr++)
			{
				//���g�𖳎�����ݒ�Ȃ疳������
				if (_ignoreMySelf && _ignoreMySelf == (*itr)->GetOwner())continue;

				//OBB�ɓ_���q�b�g
				if (OverlapJudgeOBBandPoint(*itr, currentPos))
				{
					//���������ǂ���
					hit_result.isHIT = true;

					//�����}�e���A���擾
					hit_result.physicsMaterial = (*itr)->GetPhysicsMaterial();

					//�������A�N�^�[
					hit_result.hitActor = (*itr)->GetOwner();

					//HIT���W
					hit_result.hitPos = currentPos;

					//����܂ł̃��C�̒���
					hit_result.length = currentLen;

				}
			}
		}
		//�X�^�[�g�n�_����T����������
		currentLen += addLen;

		//���݂̒T���ʒu
		currentPos += dir * currentLen;
	}

	return hit_result;
}

//=============================================================================
// ���C��������������S�Ĕz��ɂ܂Ƃ߂ĕԂ��֐�
//=============================================================================
std::vector<s_HIT_Result> Manager_OBB::RaycastGetHit(Vector3 _startPos, Vector3 _endPos,
	Actor* _ignoreMySelf, bool _isDispRay, std::list<ACTOR_TYPE>_ignoreList, Color _drawRayColor, float _accuracy, int _drawRayLife)
{
	//HIT���U���g�z��
	std::vector<s_HIT_Result>ret;

	//�J�n�_����I���_�܂ł̋���
	const float length = D3DXVec3Length(&(_endPos - _startPos));

	//�J��Ԃ���
	const int repeat = static_cast<int>(floor(length / _accuracy));

	//���݂̒T���ʒu
	Vector3 currentPos = _startPos;

	//�v���C���[����J�����̕���
	Vector3 dir;
	D3DXVec3Normalize(&dir, &(_endPos - _startPos));

	//�`��p�f�[�^����
	if (_isDispRay)
	{
		s_DrawData temp = {};
		temp.color = _drawRayColor;
		temp.startPos = _startPos;
		temp.endPos = _endPos;
		temp.time = 0;
		temp.timeMax = _drawRayLife;
		m_DebugDrawRayList.emplace_back(temp);
	}

	float currentLen = 0.0f;
	for (int i = 0; i < repeat; i++)
	{
		//OBB�̃��C���[���J��Ԃ�
		for (int k = 0; k < ACTOR_TYPE::MAX_ACTOR_TYPE; k++)
		{
			//�J�������m�͔��肵�Ȃ�
			if (k == ACTOR_TYPE::COLLISION_CAMERA)continue;

			bool isIgn = false;
			//�������X�g�ƌ��݂̃��C���[���r
			for (auto& ign : _ignoreList)
			{
				if (k == ign)
				{
					isIgn = true;
					break;
				}
			}
			if (isIgn)continue;

			auto itr = m_ComponentList[k].begin();
			//OBB�̌����J��Ԃ�
			for (; itr != m_ComponentList[k].end(); itr++)
			{
				//���g�𖳎�����ݒ�Ȃ疳������
				if (_ignoreMySelf && _ignoreMySelf == (*itr)->GetOwner())continue;

				//OBB�ɓ_���q�b�g
				if (OverlapJudgeOBBandPoint(*itr, currentPos))
				{
					//�����A�N�^�[�͓o�^���Ȃ�
					bool isContinue = false;
					for (auto& hitObjList : ret)
					{
						if (hitObjList.hitActor == (*itr)->GetOwner())
						{
							isContinue = true;
							break;
						}
					}
					if (isContinue)continue;

					//�V�K�q�b�g�A�N�^�[�o�^
					s_HIT_Result hit_result = {};

					//���������ǂ���
					hit_result.isHIT = true;

					//�����}�e���A���擾
					hit_result.physicsMaterial = (*itr)->GetPhysicsMaterial();

					//�������A�N�^�[
					hit_result.hitActor = (*itr)->GetOwner();

					//HIT���W
					hit_result.hitPos = currentPos;

					//����܂ł̃��C�̒���
					hit_result.length = currentLen;

					//�z���HIT���U���g�o�^
					ret.emplace_back(hit_result);

				}
			}
		}

		//�X�^�[�g�n�_����T����������
		currentLen += _accuracy;

		//���݂̒T���ʒu
		currentPos += dir * _accuracy;
	}

	return ret;
}
