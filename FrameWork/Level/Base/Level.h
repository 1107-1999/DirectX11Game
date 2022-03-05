//=============================================================================
//
//  ���x�� [Level.h]
//  Date   : 2021/11/03
//
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h
//=============================================================================
#include <vector>
#include <typeinfo>
#include <type_traits>
#include "../../Actor/Base/Actor.h"
#include "../../Actor/3D/Camera.h"
#include "../../Manager/Manager_Drawer/Owner/Manager_Drawer.h"
#include "../../Manager/Manager_Actor/Base/Manager_Actor.h"
#include "../../Manager/Manager_Drawer/Manager_Fade.h"
#include "../../Manager/Manager_Drawer/Manager_ImGui.h"


//=============================================================================
// �N���X��`
//=============================================================================
class Level
{
private:

	//���L�A�N�^�[
	std::list<Actor*> m_Actors;

	//���L�A�N�^�[�}�l�[�W���[
	std::list<Manager_Actor*> m_Manager_Actors;

	//�`��}�l�[�W���[
	class Manager_Drawer* m_Manager_Drawer;


public:

	//=============================================================================
	// �������֐�
	//=============================================================================
	virtual void Init()
	{
		//�`��}�l�[�W���[����
		m_Manager_Drawer = new Manager_Drawer;
		m_Manager_Drawer->Init();
	}

	//=============================================================================
	// �X�V�֐�
	//=============================================================================
	virtual void Update()
	{
		//�`��}�l�[�W���[�X�V
		if (m_Manager_Drawer != nullptr)
		{
			//�`��}�l�[�W���[�A�N�^�[�X�V�O�X�V
			m_Manager_Drawer->UpdateBefore();

			//���L�A�N�^�[�X�V
			for (Actor* actor : m_Actors)
			{
				actor->Update();
			}

			//�`��}�l�[�W���[�A�N�^�[�X�V��X�V
			m_Manager_Drawer->UpdateAfter();
		}

	}

	//=============================================================================
	// �`��֐�
	//=============================================================================
	void Draw()
	{
	
		//�`��}�l�[�W���[�`��
		if (m_Manager_Drawer != nullptr)
		{
			//�`��
			m_Manager_Drawer->Draw();
		}

	}

	//=============================================================================
	// �I���֐�
	//=============================================================================
	virtual void Uninit()
	{
		//���L�A�N�^�[�I��
		for (Actor* actor : m_Actors)
		{
			actor->Uninit();//�I��
			delete actor;   //�폜
			actor = nullptr;//nullptr���
		}
		
		//�A�N�^�[�z��N���A
		m_Actors.clear();

		//���L�A�N�^�[�}�l�[�W���[�I��
		for (Manager_Actor* manager_actor : m_Manager_Actors)
		{
			manager_actor->Uninit();//�I��
			delete manager_actor;   //�폜
			manager_actor = nullptr;//nullptr���
		}

		//�A�N�^�[�}�l�[�W���[�z��N���A
		m_Manager_Actors.clear();

		//�`��}�l�[�W���[�I��
		if (m_Manager_Drawer != nullptr)
		{
			m_Manager_Drawer->Uninit();//�I��
			delete m_Manager_Drawer;   //�폜
			m_Manager_Drawer = nullptr;//nullptr���
		}
	}

	//=============================================================================
    // �A�N�^�[�ǉ��֐�
	//=============================================================================
	template<typename T>
	T* AddActor()
	{
		T* actor = new T();       //�쐬
		m_Actors.push_back(actor);//�z��ɓo�^
		actor->Init();            //������

		return actor;
	}

	//=============================================================================
	// �A�N�^�[�}�l�[�W���[�ǉ��֐�
	//=============================================================================
	template<typename T>
	T* AddManager_Actor()
	{
		T* manager_actor = new T();               //�쐬
		m_Manager_Actors.push_back(manager_actor);//�z��ɓo�^
		manager_actor->Init();                    //������

		return manager_actor;
	}

	//=============================================================================
	// �A�N�^�[�P�̎擾�֐�(�N���X)
	//=============================================================================
	template<typename T>
	T* GetActor()
	{
		//�A�N�^�[�z��
		for (Actor* actor : m_Actors)
		{
			//�^�𒲂ׂ�
			if (typeid(*actor) == typeid(T))
			{
				return (T*)actor;
			}
		}

		//�擾���s����null��Ԃ�
		return nullptr;
	}

	//=============================================================================
	// �A�N�^�[�P�̎擾�֐�(�N���X&���O)
	//=============================================================================
	template<typename T>
	T* GetActorByName(const char* _name)
	{
		//�A�N�^�[�z��
		for (Actor* actor : m_Actors)
		{
			//�^�𒲂ׂ�
			if (typeid(*actor) == typeid(T))
			{
				//���O�𒲂ׂ�
				if (strcmp(actor->GetName(), _name) == 0)
				{
					return (T*)actor;
				}
			}
		}

		//�擾���s����null��Ԃ�
		return nullptr;
	}

	//=============================================================================
	// �A�N�^�[�P�̎擾�֐�(�N���X&���O&�^�O)
	//=============================================================================
	template<typename T>
	T* GetActorByString(const char* _name, const char* _tag)
	{
		//�A�N�^�[�z��
		for (Actor* actor : m_Actors)
		{
			//�^�𒲂ׂ�
			if (typeid(*actor) == typeid(T))
			{
				//���O�ƃ^�O�𒲂ׂ�
				if (actor->GetName() == _name && actor->GetTag() == _tag)
				{
					return (T*)actor;
				}
			}
		}

		//�擾���s����null��Ԃ�
		return nullptr;
	}

	//=============================================================================
	// �A�N�^�[�����擾�֐�(�N���X)
	//=============================================================================
	template<typename T>
	std::vector<T*> GetActors()
	{
		//��̃A�N�^�[�z��
		std::vector<T*> actors;

		//�A�N�^�[�z��
		for (Actor* actor : m_Actors)
		{
			//�^�𒲂ׂ�
			if (typeid(*actor) == typeid(T))
			{
				actors.push_back((T*)actor);
			}
		}

		return actors;
	}

	//=============================================================================
	// �A�N�^�[�����擾�֐�(�N���X&�^�O)
	//=============================================================================
	template<typename T>
	std::vector<T*> GetActorsByTag(const char* _tag)
	{
		//��̃A�N�^�[�z��
		std::vector<T*>actors;

		//�A�N�^�[�z��
		for (Actor* actor : m_Actors)
		{
			//�^�𒲂ׂ�
			if (typeid(*actor) == typeid(T))
			{
				actors.push_back(actor);
			}
		}

		return actors;
	}


	//=============================================================================
	// �A�N�^�[�}�l�[�W���[�擾�֐�(�N���X)
	//=============================================================================
	template<typename T>
	T* GetManager_Actor()
	{
		//�A�N�^�[�}�l�[�W���[�z��
		for (Manager_Actor* manager_Actor : m_Manager_Actors)
		{
			//�^�𒲂ׂ�
			if (typeid(*manager_Actor) == typeid(T))
			{
				return (T*)manager_Actor;
			}
		}

		return nullptr;
	}


	//=============================================================================
	// �`��}�l�[�W���[�擾�֐�
	//=============================================================================
	inline class Manager_Drawer* GetManager_Drawer() { return m_Manager_Drawer; }


	//=============================================================================
	// �t�F�[�h�֐�
	//=============================================================================
	void SetFade(float _time)
	{
		//�t�F�[�h�}�l�[�W���[�擾
		if (Manager_Fade* manager_Fade = GetManager_Drawer()->GetManager_Fade())
		{
			manager_Fade->SetFade(Manager_Fade::FADE_OUT, _time);
		}
	}
};


