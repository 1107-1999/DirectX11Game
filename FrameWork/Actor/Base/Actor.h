//=============================================================================
//
//  アクタークラス [Actor.h]
//  Date   : 2021/11/1
//
//=============================================================================
#pragma once

//=============================================================================
// インクルード
//=============================================================================
#include <vector>
#include "../../System/Main.h"
#include "../../System/Math.h"
#include "../../System/Exchanger.h"
#include "../../Manager/Manager_Drawer/Manager_ImGui.h"

//=============================================================================
// クラス定義
//=============================================================================
class Actor
{
public:

	//コンポーネント追加関数
	template <typename T>
	T* AddComponent(int _updatePriority)
	{
		T* component = new T(this, _updatePriority);
		component->Init();
		m_Components.push_back(component);
		return component;
	}

	//コンポーネント単体取得関数
	template<typename T>
	T* GetComponentByClass()
	{
		for (Component* component : m_Components)
		{
			if (typeid(*component) == typeid(T))
			{//型を調べる(RTTI動的型情報)
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

	//初期化・更新・終了
	virtual void Init() = 0;
	virtual void Update();
	virtual void Uninit();

	//名前設定
	inline void SetName(const char* _name) { name = _name; }
	//タグ設定
	inline void SetTag(const char* _tag)   { tag  = _tag;  }

	//名前取得
	inline const char* GetName() const { return name.c_str(); }
	//タグ取得
	inline const char* GetTag()  const { return tag.c_str();  }

private:

	std::vector<class Component*> m_Components;
	std::string tag;
	std::string name;
};