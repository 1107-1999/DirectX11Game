//=============================================================================
//
//  時間系処理　[Time.h]
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
	float timeScale;//時間の進む速さ：DEFAULTS 1.0

public:

	Time() :timeScale(1.0f) {}

	inline float GetTimeScale()const { return timeScale; }//タイムスケールを設定
	inline void SetTimeScale(float _set) { timeScale = _set; }//タイムスケールを取得

	int GetCurrentHour();//現在の時間をINTで取得
	int GetCurrentMinute();//現在の分をINTで取得
	int GetCurrentSecond();//現在の秒をINTで取得
	double GetMilliSecond();//現在の時間をミリ秒で取得
	std::string GetCurrentHourString();//現在の時間を文字で取得
	std::string GetCurrentMinuteString();//現在の分を文字で取得
	std::string GetCurrentSecondString();//現在の秒を文字で取得
};