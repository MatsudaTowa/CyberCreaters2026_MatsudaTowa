//=============================================
//
//2ウェーブ処理[wave_two.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "wave_two.h"

const std::string CWave_Two::WAVE_2_ENEMY_FILE = "data\\FILE\\enemy_001.txt";
const std::string CWave_Two::WAVE_2_BLOCK_FILE = "data\\FILE\\block_001.txt";
const std::string CWave_Two::WAVE_2_WALL_FILE = "data\\FILE\\wall_001.txt";

//=============================================
//コンストラクタ
//=============================================
CWave_Two::CWave_Two()
{
}

//=============================================
//デストラクタ
//=============================================
CWave_Two::~CWave_Two()
{
}

//=============================================
//初期化
//=============================================
HRESULT CWave_Two::Init()
{
	CWave::LoadBlock(&WAVE_2_BLOCK_FILE);
	CWave::LoadEnemy(&WAVE_2_ENEMY_FILE);
	return S_OK;
}

//=============================================
//終了
//=============================================
void CWave_Two::Uninit()
{
	CWave::Uninit();
}

//=============================================
//更新
//=============================================
void CWave_Two::Update()
{
	CWave::Update();
}
