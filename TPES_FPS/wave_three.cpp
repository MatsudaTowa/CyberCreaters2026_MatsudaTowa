//=============================================
//
//3ウェーブ処理[wave_three.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "wave_three.h"

const std::string CWave_Three::WAVE_3_ENEMY_FILE = "data\\FILE\\enemy_002.txt";
const std::string CWave_Three::WAVE_3_BLOCK_FILE = "data\\FILE\\block_002.txt";
const std::string CWave_Three::WAVE_3_WALL_FILE = "data\\FILE\\wall_002.txt";

//=============================================
//コンストラクタ
//=============================================
CWave_Three::CWave_Three()
{
}

//=============================================
//デストラクタ
//=============================================
CWave_Three::~CWave_Three()
{
}

//=============================================
//初期化
//=============================================
HRESULT CWave_Three::Init()
{
	CWave::LoadBlock(&WAVE_3_BLOCK_FILE);
	CWave::LoadEnemy(&WAVE_3_ENEMY_FILE);
	return S_OK;
}

//=============================================
//終了
//=============================================
void CWave_Three::Uninit()
{
	CWave::Uninit();
}

//=============================================
//更新
//=============================================
void CWave_Three::Update()
{
	CWave::Update();
}
