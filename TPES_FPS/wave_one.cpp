//=============================================
//
//1ウェーブ処理[wave_one.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "wave_one.h"

const std::string CWave_One::WAVE_1_ENEMY_FILE = "data\\FILE\\enemy_000.txt";
const std::string CWave_One::WAVE_1_BLOCK_FILE = "data\\FILE\\block_000.txt";
const std::string CWave_One::WAVE_1_WALL_FILE = "data\\FILE\\wall_000.txt";

//=============================================
//コンストラクタ
//=============================================
CWave_One::CWave_One()
{
}

//=============================================
//デストラクタ
//=============================================
CWave_One::~CWave_One()
{
}

//=============================================
//初期化
//=============================================
HRESULT CWave_One::Init()
{
	CWave::LoadBlock(&WAVE_1_BLOCK_FILE);
	CWave::LoadEnemy(&WAVE_1_ENEMY_FILE);
	return S_OK;
}

//=============================================
//終了
//=============================================
void CWave_One::Uninit()
{
	CWave::Uninit();
}

//=============================================
//更新
//=============================================
void CWave_One::Update()
{
	CWave::Update();
}
