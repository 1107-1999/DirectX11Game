//=============================================================================
//
//  レベル [Level.h]
//  Date   : 2021/11/03
//
//=============================================================================
#pragma once

//=============================================================================
// インクルード
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
// クラス定義
//=============================================================================
class Level
{
private:

	//所有アクター
	std::list<Actor*> m_Actors;

	//所有アクターマネージャー
	std::list<Manager_Actor*> m_Manager_Actors;

	//描画マネージャー
	class Manager_Drawer* m_Manager_Drawer;


public:

	//=============================================================================
	// 初期化関数
	//=============================================================================
	virtual void Init()
	{
		//描画マネージャー生成
		m_Manager_Drawer = new Manager_Drawer;
		m_Manager_Drawer->Init();
	}

	//=============================================================================
	// 更新関数
	//=============================================================================
	virtual void Update()
	{
		//描画マネージャー更新
		if (m_Manager_Drawer != nullptr)
		{
			//描画マネージャーアクター更新前更新
			m_Manager_Drawer->UpdateBefore();

			//所有アクター更新
			for (Actor* actor : m_Actors)
			{
				actor->Update();
			}

			//描画マネージャーアクター更新後更新
			m_Manager_Drawer->UpdateAfter();
		}

	}

	//=============================================================================
	// 描画関数
	//=============================================================================
	void Draw()
	{
	
		//描画マネージャー描画
		if (m_Manager_Drawer != nullptr)
		{
			//描画
			m_Manager_Drawer->Draw();
		}

	}

	//=============================================================================
	// 終了関数
	//=============================================================================
	virtual void Uninit()
	{
		//所有アクター終了
		for (Actor* actor : m_Actors)
		{
			actor->Uninit();//終了
			delete actor;   //削除
			actor = nullptr;//nullptr代入
		}
		
		//アクター配列クリア
		m_Actors.clear();

		//所有アクターマネージャー終了
		for (Manager_Actor* manager_actor : m_Manager_Actors)
		{
			manager_actor->Uninit();//終了
			delete manager_actor;   //削除
			manager_actor = nullptr;//nullptr代入
		}

		//アクターマネージャー配列クリア
		m_Manager_Actors.clear();

		//描画マネージャー終了
		if (m_Manager_Drawer != nullptr)
		{
			m_Manager_Drawer->Uninit();//終了
			delete m_Manager_Drawer;   //削除
			m_Manager_Drawer = nullptr;//nullptr代入
		}
	}

	//=============================================================================
    // アクター追加関数
	//=============================================================================
	template<typename T>
	T* AddActor()
	{
		T* actor = new T();       //作成
		m_Actors.push_back(actor);//配列に登録
		actor->Init();            //初期化

		return actor;
	}

	//=============================================================================
	// アクターマネージャー追加関数
	//=============================================================================
	template<typename T>
	T* AddManager_Actor()
	{
		T* manager_actor = new T();               //作成
		m_Manager_Actors.push_back(manager_actor);//配列に登録
		manager_actor->Init();                    //初期化

		return manager_actor;
	}

	//=============================================================================
	// アクター単体取得関数(クラス)
	//=============================================================================
	template<typename T>
	T* GetActor()
	{
		//アクター配列
		for (Actor* actor : m_Actors)
		{
			//型を調べる
			if (typeid(*actor) == typeid(T))
			{
				return (T*)actor;
			}
		}

		//取得失敗時にnullを返す
		return nullptr;
	}

	//=============================================================================
	// アクター単体取得関数(クラス&名前)
	//=============================================================================
	template<typename T>
	T* GetActorByName(const char* _name)
	{
		//アクター配列
		for (Actor* actor : m_Actors)
		{
			//型を調べる
			if (typeid(*actor) == typeid(T))
			{
				//名前を調べる
				if (strcmp(actor->GetName(), _name) == 0)
				{
					return (T*)actor;
				}
			}
		}

		//取得失敗時にnullを返す
		return nullptr;
	}

	//=============================================================================
	// アクター単体取得関数(クラス&名前&タグ)
	//=============================================================================
	template<typename T>
	T* GetActorByString(const char* _name, const char* _tag)
	{
		//アクター配列
		for (Actor* actor : m_Actors)
		{
			//型を調べる
			if (typeid(*actor) == typeid(T))
			{
				//名前とタグを調べる
				if (actor->GetName() == _name && actor->GetTag() == _tag)
				{
					return (T*)actor;
				}
			}
		}

		//取得失敗時にnullを返す
		return nullptr;
	}

	//=============================================================================
	// アクター複数取得関数(クラス)
	//=============================================================================
	template<typename T>
	std::vector<T*> GetActors()
	{
		//空のアクター配列
		std::vector<T*> actors;

		//アクター配列
		for (Actor* actor : m_Actors)
		{
			//型を調べる
			if (typeid(*actor) == typeid(T))
			{
				actors.push_back((T*)actor);
			}
		}

		return actors;
	}

	//=============================================================================
	// アクター複数取得関数(クラス&タグ)
	//=============================================================================
	template<typename T>
	std::vector<T*> GetActorsByTag(const char* _tag)
	{
		//空のアクター配列
		std::vector<T*>actors;

		//アクター配列
		for (Actor* actor : m_Actors)
		{
			//型を調べる
			if (typeid(*actor) == typeid(T))
			{
				actors.push_back(actor);
			}
		}

		return actors;
	}


	//=============================================================================
	// アクターマネージャー取得関数(クラス)
	//=============================================================================
	template<typename T>
	T* GetManager_Actor()
	{
		//アクターマネージャー配列
		for (Manager_Actor* manager_Actor : m_Manager_Actors)
		{
			//型を調べる
			if (typeid(*manager_Actor) == typeid(T))
			{
				return (T*)manager_Actor;
			}
		}

		return nullptr;
	}


	//=============================================================================
	// 描画マネージャー取得関数
	//=============================================================================
	inline class Manager_Drawer* GetManager_Drawer() { return m_Manager_Drawer; }


	//=============================================================================
	// フェード関数
	//=============================================================================
	void SetFade(float _time)
	{
		//フェードマネージャー取得
		if (Manager_Fade* manager_Fade = GetManager_Drawer()->GetManager_Fade())
		{
			manager_Fade->SetFade(Manager_Fade::FADE_OUT, _time);
		}
	}
};


