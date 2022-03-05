//=============================================================================
//
//  Wave読み込み [WaveLoder.h]
//  Date   : 2021/11/2
//
//=============================================================================
#pragma once

//=============================================================================
// インクルード
//=============================================================================
#include <XAudio2.h>

//=============================================================================
// マクロ定義
//=============================================================================
#define FOURCCRIFF 'FFIR'
#define FOURCCFMT ' tmf'
#define FOURCCDATA 'atad'
#define FOURCCWAVE 'EVAW'

//=============================================================================
// クラス定義
//=============================================================================
class WaveLoader
{
public:
	static HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD &dwChuncSize, DWORD &dwChuncPosition);
	static HRESULT ReadChunk(HANDLE hFile, void* type, DWORD bufferSize, DWORD bufferOffset);
	static HRESULT ReadRiff(HANDLE hFile, DWORD &dwChunkSize, DWORD &dwChunkDataPosition);
	static HRESULT ReadWfx(HANDLE hFile, WAVEFORMATEX &Wfx, DWORD &dwChunkSize, DWORD &dwChunkPosition);
	static HRESULT ReadData(HANDLE hFile, BYTE* &buffer, DWORD &dwChunkSize, DWORD &dwChunkPosition);
};