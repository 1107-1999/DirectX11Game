//=============================================================================
//
//  �V���O���g�� [Singleton.h]
//  Date   : 2021/11/2
//
//=============================================================================
#pragma once

//=============================================================================
// �N���X��`
//=============================================================================
template <typename T>
class Singleton
{
protected:

	Singleton() {};
	virtual ~Singleton() {};
	Singleton(const Singleton& singleton) {};
	Singleton& operator=(const Singleton& singleton) {};

public:

	static T* Instance()
	{
		static T instance;
		return &instance;
	}

};
