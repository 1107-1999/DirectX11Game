//=============================================================================
//
//  ���Ԍn�����@[Time.h]
//  Date  :     2021/1/31
//
//=============================================================================
#pragma once

#include <string>
#include "Singleton.h"

class Time : public Singleton<Time>
{
private:

	friend Singleton<Time>;
	float timeScale;//���Ԃ̐i�ޑ����FDEFAULTS 1.0

public:

	Time() :timeScale(1.0f) {}

	inline float GetTimeScale()const { return timeScale; }//�^�C���X�P�[����ݒ�
	inline void SetTimeScale(float _set) { timeScale = _set; }//�^�C���X�P�[�����擾

	int GetCurrentHour();//���݂̎��Ԃ�INT�Ŏ擾
	int GetCurrentMinute();//���݂̕���INT�Ŏ擾
	int GetCurrentSecond();//���݂̕b��INT�Ŏ擾
	double GetMilliSecond();//���݂̎��Ԃ��~���b�Ŏ擾
	std::string GetCurrentHourString();//���݂̎��Ԃ𕶎��Ŏ擾
	std::string GetCurrentMinuteString();//���݂̕��𕶎��Ŏ擾
	std::string GetCurrentSecondString();//���݂̕b�𕶎��Ŏ擾
};