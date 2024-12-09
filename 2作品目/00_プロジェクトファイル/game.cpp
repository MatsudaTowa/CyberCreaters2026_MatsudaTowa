//=============================================
//
//3DTemplate[game.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "game.h"
#include "object.h"
#include "object2D.h"
#include "object3D.h"
#include "objectX.h"
#include "player_test.h"
#include "bullet.h"
#include "effect.h"
#include "gauge_fream.h"
#include "colision.h"
#include "block.h"
#include "field.h"
#include "manager.h"

//エネミーのファイル
const std::string CGame::ENEMY_FILE = "data\\FILE\\enemy.txt";
const std::string CGame::BLOCK_FILE = "data\\FILE\\block.txt";

//エディット設定
CEdit* CGame::m_pEdit = nullptr;

//タイム設定
CTimer* CGame::m_pTimer = nullptr;

//スコア設定
CScore* CGame::m_pScore = nullptr;

//プレイヤー
CPlayer*CGame::m_pPlayer = nullptr;

CGame::GAME_STATE CGame::m_GameState = CGame::GAME_STATE::GAME_STATE_NORMAL;

//=============================================
//コンストラクタ
//=============================================
CGame::CGame():m_nResultDelay(0),m_bEdit(false)
{//イニシャライザーでプライオリティ設定、エディットしてない状態に変更

	//読み込むエネミーの情報初期化
	m_LoadEnemy.pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_LoadEnemy.rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_LoadEnemy.type = CEnemy::ENEMY_TYPE::ENEMY_TYPE_NORMAL;

	//読み込むブロックの情報初期化
	m_LoadBlock.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_LoadBlock.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_LoadBlock.type = CBlock::BLOCKTYPE::BLOCKTYPE_DEFAULT;
}

//=============================================
//デストラクタ
//=============================================
CGame::~CGame()
{
}

//=============================================
//初期化
//=============================================
HRESULT CGame::Init()
{

	if (m_pEdit == nullptr)
	{
		m_pEdit = new CEdit;
	}

	//タイマー初期化
	if (m_pTimer == nullptr)
	{
		m_pTimer = new CTimer;

		m_pTimer->Init();
	}

	//スコア初期化
	if (m_pScore == nullptr)
	{
		m_pScore = new CScore;

		m_pScore->Init();
	}

	m_GameState = CGame::GAME_STATE::GAME_STATE_NORMAL;

	////ブロック生成
	//CBlock* pBlock = CBlock::Create(CBlock::BLOCKTYPE_DEFAULT, D3DXVECTOR3(0.0, 0.0f, 0.0f),
	//	D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3, false);

	//pBlock = CBlock::Create(CBlock::BLOCKTYPE_DEFAULT, D3DXVECTOR3(10.0f, 0.0f, 0.0f),
	//	D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3, false);

	//pBlock = CBlock::Create(CBlock::BLOCKTYPE_DEFAULT, D3DXVECTOR3(5.0f, 50.0f, 0.0f),
	//	D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3, false);

	//ブロック生成
	LoadBlock(&CGame::BLOCK_FILE);

	//ゲージのフレームUI生成
	CGauge_Fream::Create(D3DXVECTOR3(250.0f,150.0f,0.0f),D3DXVECTOR2(280.0f,120.0f));

	//地面生成
	CField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 0.0f, 1000.0f));

	//プレイヤー生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(-900.0f, 0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),5);

	//プレイヤー生成
	//CPlayer_test* pPlayer_test = CPlayer_test::Create(D3DXVECTOR3(-450.0f, 0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 5);

	//エネミー生成
	LoadEnemy(&CGame::ENEMY_FILE);

	CSound* pSound = CManager::GetSound();

	pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_BGM_GAME);

	return S_OK;
}

//=============================================
//終了
//=============================================
void CGame::Uninit()
{
	m_GameState = GAME_STATE_NORMAL;
	if (m_pTimer != nullptr)
	{
		m_pTimer->Uninit();
		m_pTimer = nullptr;
	}

	if (m_pScore != nullptr)
	{
		m_pScore->Uninit();
		m_pScore = nullptr;
	}
	if (m_pPlayer != nullptr)
	{
		m_pPlayer = nullptr;
	}

	CSound* pSound = CManager::GetSound();
	//サウンドの停止
	pSound->StopSound();

	CObject::ReleaseAll();
}

//=============================================
//更新
//=============================================
void CGame::Update()
{
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	
	if (pKeyboard->GetTrigger(DIK_F5))
	{
		m_bEdit = m_bEdit ? false : true;

		CCamera*pCamera = CManager::GetCamera();

		pCamera->ResetCamera();
	}

	if (m_bEdit)
	{
		m_pEdit->Update();
	}
	
	//if (m_bEdit == false)
	//{
	CObject::UpdateAll();

	if (m_pTimer != nullptr)
	{
		m_pTimer->Update();
	}
	//}

	if (m_pScore != nullptr)
	{
		m_pScore->Update();
	}
	if (CPlayer::m_PlayerDeath|| CBossEnemy::m_BossDeath || CEnemy::m_nNumEnemy <= 0)
	{//プレイヤーが死ぬかエネミーを全部殺したら
		//カウント加算
		m_nResultDelay++;
		if (m_nResultDelay >= DELAY_CNT)
		{
			//ディレイカウントリセット
			m_nResultDelay = 0;

			m_pScore->SaveScore(m_pScore->m_nScore);

			//リザルト遷移
			CManager::SetMode(CScene::MODE::MODE_RESULT);
		}
	}

#ifdef _DEBUG
	if (pKeyboard->GetTrigger(DIK_RETURN))
	{
		CManager::SetMode(CScene::MODE::MODE_RESULT);
	}
#endif // DEBUG


}

//=============================================
//描画
//=============================================
void CGame::Draw()
{
}

//=============================================
//スコア取得
//=============================================
CScore* CGame::GetScore()
{
	return m_pScore;
}

//=============================================
//プレイヤー取得
//=============================================
CPlayer* CGame::GetPlayer()
{
	return m_pPlayer;
}

CGame::GAME_STATE& CGame::GetState()
{
	return m_GameState;
}

//=============================================
//敵の読み込み
//=============================================
void CGame::LoadEnemy(const std::string* pFileName)
{
	char aDataSearch[ENEMY_TXT_MAX];
	char aEqual[ENEMY_TXT_MAX]; //[＝]読み込み用
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

//=============================================
//ブロック読み込み
//=============================================
void CGame::LoadBlock(const std::string* pFileName)
{
	char aDataSearch[BLOCK_TXT_MAX];
	char aEqual[BLOCK_TXT_MAX]; //[＝]読み込み用
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
					CBlock::Create(m_LoadBlock.type, m_LoadBlock.pos, m_LoadBlock.rot,1,false);
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
