//=============================================================================
//
//  オーディオマネージャー [Manager_Audio.h]
//  Date   : 2021/12/19
//
//=============================================================================
#pragma once

//=============================================================================
// インクルード
//=============================================================================
#include <Windows.h>
#include <vector>
#include <unordered_map>
#include "../System/WavePlayer.h"
#include "../System/Singleton.h"

//=============================================================================
// 定数宣言
//=============================================================================
constexpr int MAX_AUDIO        = 100; //最大数
constexpr int ALL_USE_AUDIO    = -1;  //全て使用中

//=============================================================================
// クラス定義
//=============================================================================
class Manager_Audio : public Singleton<Manager_Audio>
{
public:

	//初期化・更新・終了
	void Init();
	void Update();
	void Uninit();

	//サウンド再生関数(第2引数はループ回数※XAUDIO2_LOOP_INFINITEで無限ループ)
	int Play(const char* _key, int loop);

	//指定のサウンドの再生終了
	void End(int _num) { m_Player[_num]->Destroy(); }

	//音量設定
	inline void SetVolume(int _num, float volume) { m_Player[_num]->SetVolume(volume); }

	//使用していない要素を検索
	int IsUsePlayer();

	//引数の要素が使われているかの確認
	bool IsInElement(int _num);

	//フェード
	void Fade(int _num, float _time, float _volume);

	//リソース読み込み
	void Load_Resource(const char* _key, LPCSTR _fileName);

	//指定要素のリソース解放
	void Unload_Resource(const char* _key);

	//全リソース解放
	void Unload_Resource_All();

	//指定要素の取得
	inline LPCSTR GetResource(const char* _key) { return m_Resource[_key]; }


private:

	//XAudio2クラス
	IXAudio2* m_XAudio2;

	//マスターボイス
	IXAudio2MasteringVoice* m_MasterVoice;

	//サウンドの実体配列
	std::vector<WavePlayer*> m_Player;

	//リソース管理配列
	std::unordered_map<std::string, LPCSTR> m_Resource;


};