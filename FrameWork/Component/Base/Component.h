//=============================================================================
//
//  コンポーネント[Component.h]
//  Date   : 2021/11/1
//
//=============================================================================
#pragma once

//=============================================================================
// インクルード
//=============================================================================
#include "../../System/Main.h"

//=============================================================================
// クラス定義
//=============================================================================
class Component
{
public:

	Component(class Actor* _owner, int _updatePriority) : m_Owner(_owner), m_UpdatePriority(_updatePriority) {}

	//初期化・更新・終了純粋仮想関数
	virtual void Init()   = 0;
	virtual void Update() = 0;
	virtual void Uninit() = 0;

	//優先順取得
	int GetPriority()const  { return m_UpdatePriority; }

	//有効フラグを取得・設定
	inline bool GetActive() { return m_Active; }
	inline void SetActive(bool _flag) { m_Active = _flag; }

	//このコンポーネントを所持しているアクター取得
	inline class Actor* GetOwner() { return m_Owner; }

protected:

	//このコンポーネントを所持しているアクター
	class Actor* m_Owner;

	//更新優先順
	int m_UpdatePriority;

	//有効か
	bool m_Active;
};
