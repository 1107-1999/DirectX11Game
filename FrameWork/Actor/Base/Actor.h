//=============================================================================
//
//  �A�N�^�[�N���X [Actor.h]
//  Date   : 2021/11/1
//
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h
//=============================================================================
#include <vector>
#include "../../System/Main.h"
#include "../../System/Math.h"
#include "../../System/Exchanger.h"
#include "../../Manager/Manager_Drawer/Manager_ImGui.h"

//=============================================================================
// �N���X��`
//=============================================================================
class Actor
{
public:

	//�R���|�[�l���g�ǉ��֐�
	template <typename T>
	T* AddComponent(int _updatePriority)
	{
		T* component = new T(this, _updatePriority);
		component->Init();
		m_Components.push_back(component);
		return component;
	}

	//�R���|�[�l���g�P�̎擾�֐�
	template<typename T>
	T* GetComponentByClass()
	{
		for (Component* component : m_Components)
		{
			if (typeid(*component) == typeid(T))
			{//�^�𒲂ׂ�(RTTI���I�^���)
				return (T*)component;
			}
		}
		return nullptr;
	}

	class Component* GetComponentByIndex(int _index)
	{
		int cnt = 0;
		for (auto& i : m_Components)
		{
			if (cnt == _index)
			{
				return i;
			}
			cnt++;
		}
	}

	//�������E�X�V�E�I��
	virtual void Init() = 0;
	virtual void Update();
	virtual void Uninit();

	//���O�ݒ�
	inline void SetName(const char* _name) { name = _name; }
	//�^�O�ݒ�
	inline void SetTag(const char* _tag)   { tag  = _tag;  }

	//���O�擾
	inline const char* GetName() const { return name.c_str(); }
	//�^�O�擾
	inline const char* GetTag()  const { return tag.c_str();  }

private:

	std::vector<class Component*> m_Components;
	std::string tag;
	std::string name;
};