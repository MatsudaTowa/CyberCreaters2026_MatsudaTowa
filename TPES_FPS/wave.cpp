//=============================================
//
//ウェーブ処理[wave.h]
//Auther Matsuda Towa
//
//=============================================
#include "wave.h"
#include "enemy_test.h"
#include "manager.h"
#include "wave_one.h"
#include "wave_two.h"
#include "wave_three.h"
#include "wave_boss.h"
#include "wave_result.h"
#include "game_score.h"
#include "wave_score.h"
#include"player_test.h"
#include"field.h"
#include "wall.h"

CWave::WAVE CWave::m_CurrentWave = WAVE::NONE;
CWave::WAVE CWave::m_next = WAVE::NONE;
const char* CWave::m_ResultFile = nullptr;
//スコア
CScore* CWave::m_pScore = nullptr;

//=============================================
//コンストラクタ
//=============================================
CWave::CWave()
{
}

//=============================================
//デストラクタ
//=============================================
CWave::~CWave()
{
}

//=============================================
//初期化
//=============================================
HRESULT CWave::Init()
{
	return S_OK;
}

//=============================================
//終了
//=============================================
void CWave::Uninit()
{
	if (m_pScore != nullptr)
	{
		m_pScore->Uninit();
		m_pScore = nullptr;
	}
	CObject::ReleaseAll();

}

//=============================================
//更新
//=============================================
void CWave::Update()
{
	if (m_pScore != nullptr)
	{
		m_pScore->Update();
	}
}

//=============================================
//ウェーブ設定
//=============================================
CWave* CWave::Create(WAVE wave)
{
	// インスタンス生成
	CWave* pWave = new CWave;

	// 条件分岐
	switch (wave)
	{
	case WAVE::ONE: // ウェーブ1
		delete pWave;
		pWave = new CWave_One;
		break;

	case WAVE::TWO: //ウェーブ2
		delete pWave;
		pWave = new CWave_Two;
		break;

	case WAVE::THREE: // ウェーブ3

		delete pWave;
		pWave = new CWave_Three;
		break;
	case WAVE::BOSS: //ウェーブboss

		delete pWave;
		pWave = new CWave_Boss;
		break;
	case WAVE::RESULT: //ウェーブリザルト

		delete pWave;
		pWave = new CWave_Boss;
		break;
	default:
		break;
	}

	//スコア初期化
	if (m_pScore == nullptr)
	{
		if (wave != WAVE::RESULT)
		{
			m_pScore = new CGameScore;
			//プレイヤー生成
			CPlayer_test* pPlayer_test = CPlayer_test::Create(D3DXVECTOR3(0.0f, 0.5f, -400.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f), 100);
			//地面生成
			CField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(500.0f, 0.0f, 1000.0f));
		}
		else if (wave == WAVE::RESULT)
		{
			m_pScore = new CWaveScore;
		}
		m_pScore->Init();
	}


	if (pWave != nullptr)
	{
		pWave->m_CurrentWave = wave;
	}
	//今のシーンの初期化
	pWave->Init();

	return pWave;
}

//=============================================
//ウェーブ設定
//=============================================
CWave* CWave::Create(WAVE wave, WAVE next_wave,const char* ResultFile)
{
	// インスタンス生成
	CWave* pWave = nullptr;

	m_next = next_wave;

	m_ResultFile = ResultFile;

	// 条件分岐
	switch (wave)
	{
	case WAVE::ONE: // ウェーブ1
		delete pWave;
		pWave = new CWave_One;
		break;

	case WAVE::TWO: //ウェーブ2
		delete pWave;
		pWave = new CWave_Two;
		break;

	case WAVE::THREE: // ウェーブ3

		delete pWave;
		pWave = new CWave_Three;
		break;
	case WAVE::BOSS: //ウェーブboss

		delete pWave;
		pWave = new CWave_Boss;
		break;
	case WAVE::RESULT: //ウェーブリザルト

		delete pWave;
		pWave = new CWave_Result;
		break;
	default:
		break;
	}

	//スコア初期化
	if (m_pScore == nullptr)
	{
		if (wave != WAVE::RESULT)
		{
			m_pScore = new CGameScore;
			//プレイヤー生成
			CPlayer_test* pPlayer_test = CPlayer_test::Create(D3DXVECTOR3(0.0f, 0.5f, -70.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f), 100);
		}
		else if (wave == WAVE::RESULT)
		{
			m_pScore = new CWaveScore;
		}
		m_pScore->Init();
	}

	if (pWave != nullptr)
	{
		pWave->m_CurrentWave = wave;
	}
	//今のシーンの初期化
	pWave->Init();

	return pWave;
}

//=============================================
//現在のウェーブを取得
//=============================================
CWave::WAVE CWave::GetCurrentWave()
{
	return m_CurrentWave;
}

//=============================================
//スコア取得
//=============================================
CScore* CWave::GetScore()
{
	return m_pScore;
}

//=============================================
//ブロックをロード
//=============================================
void CWave::LoadBlock(const std::string* pFileName)
{
	char aDataSearch[TXT_MAX];
	char aEqual[TXT_MAX]; //[＝]読み込み用
	int nNumBlock; //ブロックの数

	//ファイルの読み込み
	FILE* pFile = fopen(pFileName->c_str(), "r");

	if (pFile == NULL)
	{//種類の情報のデータファイルが開けなかった場合
		//処理を終了する
		return;
	}
	//ENDが見つかるまで読み込みを繰り返す
	while (1)
	{
		fscanf(pFile, "%s", aDataSearch); //検索

		if (!strcmp(aDataSearch, "END"))
		{//読み込みを終了
			fclose(pFile);
			break;
		}
		if (aDataSearch[0] == '#')
		{
			continue;
		}

		if (!strcmp(aDataSearch, "NUM_BLOCK"))
		{//モデル数読み込み
			fscanf(pFile, "%s", &aEqual[0]);
			fscanf(pFile, "%d", &nNumBlock);
		}
		if (!strcmp(aDataSearch, "BLOCKSET"))
		{
			//項目ごとのデータを代入
			while (1)
			{
				fscanf(pFile, "%s", aDataSearch); //検索

				if (!strcmp(aDataSearch, "END_BLOCKSET"))
				{
					//エネミー生成
					CBlock::Create(m_LoadBlock.type, m_LoadBlock.pos, m_LoadBlock.rot, 1, false);
					break;
				}
				else if (!strcmp(aDataSearch, "POS"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f %f %f",
						&m_LoadBlock.pos.x,
						&m_LoadBlock.pos.y,
						&m_LoadBlock.pos.z);
				}
				else if (!strcmp(aDataSearch, "ROT"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f %f %f",
						&m_LoadBlock.rot.x,
						&m_LoadBlock.rot.y,
						&m_LoadBlock.rot.z);
				}
				else if (!strcmp(aDataSearch, "TYPE"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%d", &m_LoadBlock.type);
				}
			}
		}
	}
}

//=============================================
//壁をロード
//=============================================
void CWave::LoadWall(const std::string* pFileName)
{
	char aDataSearch[TXT_MAX];
	char aEqual[TXT_MAX]; //[＝]読み込み用
	int nNumWall; //壁の数

	//ファイルの読み込み
	FILE* pFile = fopen(pFileName->c_str(), "r");

	if (pFile == NULL)
	{//種類の情報のデータファイルが開けなかった場合
		//処理を終了する
		return;
	}
	//ENDが見つかるまで読み込みを繰り返す
	while (1)
	{
		fscanf(pFile, "%s", aDataSearch); //検索

		if (!strcmp(aDataSearch, "END"))
		{//読み込みを終了
			fclose(pFile);
			break;
		}
		if (aDataSearch[0] == '#')
		{
			continue;
		}

		if (!strcmp(aDataSearch, "NUM_WALL"))
		{//モデル数読み込み
			fscanf(pFile, "%s", &aEqual[0]);
			fscanf(pFile, "%d", &nNumWall);
		}
		if (!strcmp(aDataSearch, "WALLSET"))
		{
			//項目ごとのデータを代入
			while (1)
			{
				fscanf(pFile, "%s", aDataSearch); //検索

				if (!strcmp(aDataSearch, "END_WALLSET"))
				{
					//ブロック生成
					CWall::Create(m_LoadWall.pos, m_LoadWall.rot,m_LoadWall.size);
					break;
				}
				else if (!strcmp(aDataSearch, "POS"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f %f %f",
						&m_LoadWall.pos.x,
						&m_LoadWall.pos.y,
						&m_LoadWall.pos.z);
				}
				else if (!strcmp(aDataSearch, "ROT"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f %f %f",
						&m_LoadWall.rot.x,
						&m_LoadWall.rot.y,
						&m_LoadWall.rot.z);
				}
				else if (!strcmp(aDataSearch, "SIZE"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f %f %f",
						&m_LoadWall.size.x,
						&m_LoadWall.size.y,
						&m_LoadWall.size.z);
				}
			}
		}
	}
}

//=============================================
//エネミーをロード
//=============================================
void CWave::LoadEnemy(const std::string* pFileName)
{
	char aDataSearch[TXT_MAX];
	char aEqual[TXT_MAX]; //[＝]読み込み用
	int nNumEnemy; //エネミーの数

	//ファイルの読み込み
	FILE* pFile = fopen(pFileName->c_str(), "r");

	if (pFile == NULL)
	{//種類の情報のデータファイルが開けなかった場合
		//処理を終了する
		return;
	}
	//ENDが見つかるまで読み込みを繰り返す
	while (1)
	{
		fscanf(pFile, "%s", aDataSearch); //検索

		if (!strcmp(aDataSearch, "END"))
		{//読み込みを終了
			fclose(pFile);
			break;
		}
		if (aDataSearch[0] == '#')
		{
			continue;
		}

		if (!strcmp(aDataSearch, "NUM_ENEMY"))
		{//モデル数読み込み
			fscanf(pFile, "%s", &aEqual[0]);
			fscanf(pFile, "%d", &nNumEnemy);
		}
		if (!strcmp(aDataSearch, "ENEMYSET"))
		{
			//項目ごとのデータを代入
			while (1)
			{
				fscanf(pFile, "%s", aDataSearch); //検索

				if (!strcmp(aDataSearch, "END_ENEMYSET"))
				{
					//エネミー生成
					CEnemy::Create(m_LoadEnemy.pos, m_LoadEnemy.rot, m_LoadEnemy.type);
					break;
				}
				else if (!strcmp(aDataSearch, "POS"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f %f %f",
						&m_LoadEnemy.pos.x,
						&m_LoadEnemy.pos.y,
						&m_LoadEnemy.pos.z);
				}
				else if (!strcmp(aDataSearch, "ROT"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f %f %f",
						&m_LoadEnemy.rot.x,
						&m_LoadEnemy.rot.y,
						&m_LoadEnemy.rot.z);
				}
				else if (!strcmp(aDataSearch, "TYPE"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%d", &m_LoadEnemy.type);
				}
			}
		}
	}
}

void CWave::SetWaveScore(int nScore)
{
	m_nScore = nScore;
}

int CWave::GetWaveScore()
{
	return m_nScore;
}

