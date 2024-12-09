//=============================================
//
//3DTemplate[enemy.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "enemy.h"
#include "manager.h"
#include "input.h"
#include "block.h"
#include "field.h"
#include "camera.h"
#include "game.h"
#include "wave.h"
#include "player_test.h"
#include "normal_enemy.h"
#include "boss_enemy.h"

//エネミー総数
int CEnemy::m_NumEnemy = 0;

//通常の移動速度
const float CEnemy::DEFAULT_MOVE = 1.0f;
//通常の移動速度
const float CEnemy::DAMPING_COEFFICIENT = 0.3f;

//通常のジャンプ力
const float CEnemy::DEFAULT_JUMP = 25.0f;

//これより下に行ったら死ぬ座標
const float CEnemy::DEADZONE_Y = -100.0f;

//=============================================
//コンストラクタ
//=============================================
CEnemy::CEnemy(int nPriority) :CCharacter(nPriority),m_Type()
{//イニシャライザーでメンバ変数初期化

	//総数追加
	m_NumEnemy++;
}

//=============================================
//デストラクタ
//=============================================
CEnemy::~CEnemy()
{
	//総数減少
	m_NumEnemy--;
}

//=============================================
//初期化
//=============================================
HRESULT CEnemy::Init()
{
	CCharacter::Init();

	//移動量初期化
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//ムーブ値代入
	SetMove(move);

	m_Motion = CEnemy::Motion_Type::MOTION_MAX; //ニュートラルに設定

	SetMotion(MOTION_NEUTRAL);

	return S_OK;
}

//=============================================
//終了
//=============================================
void CEnemy::Uninit()
{
	//親クラスの終了処理を呼ぶ
	CCharacter::Uninit();
}

//=============================================
//更新
//=============================================
void CEnemy::Update()
{
	CCharacter::Update();

	m_pCharacterState->Move(this);

	m_pCharacterState->Stan(this);

	m_pCharacterState->Confusion(this);

	m_pCharacterState->Shot(CBullet::BULLET_ALLEGIANCE_ENEMY, CBullet::BULLET_TYPE_NORMAL,this);

	//現在のシーンを取得
	CScene::MODE pScene = CScene::GetSceneMode();

	if (pScene != CScene::MODE::MODE_TITLE)
	{
		//ダメージステートの切り替えTODO:これもステートパターンで
		ChangeDamageState();

		//ゲームの状態取得
		CGame::GAME_STATE Game_state = CGame::GetState();

		if (GetPos().y < DEADZONE_Y)
		{//リスポーン処理
			ReSpawn();
		}

		//どっち向いてるか取得
		bool bWay = GetWay();
	}
}

//=============================================
//描画
//=============================================
void CEnemy::Draw()
{
	//親クラスのモーション用の描画を呼ぶ
	MotionDraw();
}

//=============================================
//生成
//=============================================
CEnemy* CEnemy::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const ENEMY_TYPE& type)
{
	CEnemy* pEnemy = nullptr;

	switch (type)
	{
	case ENEMY_TYPE::ENEMY_TYPE_NORMAL:
		pEnemy = new CNormalEnemy;
		pEnemy->Load_Parts("data\\Motion.txt");
		break;
	case ENEMY_TYPE::ENEMY_TYPE_BOSS:
		pEnemy = new CBossEnemy;
		pEnemy->Load_Parts("data\\motion_boss.txt");
		break;
	default:
		assert(false);
		break;
	}

	// nullならnullを返す
	if (pEnemy == nullptr) { return nullptr; }

	pEnemy->m_Type = type;
	pEnemy->SetPos(pos); //pos設定
	pEnemy->SetRot(rot); //rot設定

	pEnemy->Init(); //初期化処理

	pEnemy->SetType(OBJECT_TYPE_ENEMY); //タイプ設定

	return pEnemy;
}

//=============================================
//ダメージを受けたとき
//=============================================
void CEnemy::Damage(int nDamage)
{
	//体力取得
	int nLife = GetLife();
	//状態を取得
	CCharacter::CHARACTER_STATE state = GetState();

	if (nLife > 0 && state != CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE)
	{//ダメージ状態以外でHPが残ってたら
		nLife -= nDamage;

		//ダメージ状態に変更
		state = CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE;

		//状態代入
		SetState(state);

		//体力代入
		SetLife(nLife);
	}
	if (nLife <= 0)
	{//HPが0以下だったら
		CScore* pScore = CWave::GetScore();

		int nAddScore = 0;
		//TODO:これもストラテジーでやるべき
		switch (m_Type)
		{
		case CEnemy::ENEMY_TYPE::ENEMY_TYPE_NORMAL:
			nAddScore = 300;
			break;
		case CEnemy::ENEMY_TYPE::ENEMY_TYPE_BOSS:
			nAddScore = 1000;
			break;
		default:
			assert(false);
			break;
		}
		pScore->AddScore(nAddScore);
		//終了
		Uninit();
	}
}

//=============================================
//リスポーン
//=============================================
void CEnemy::ReSpawn()
{
	//自分自身のpos取得
	D3DXVECTOR3 EnemyPos = GetPos();

	EnemyPos = D3DXVECTOR3(-450.0f, 0.5f, 0.0f);

	//pos代入
	SetPos(EnemyPos);
}

//=============================================
//ダメージステートの切り替え
//=============================================
void CEnemy::ChangeDamageState()
{
	//状態を取得
	CCharacter::CHARACTER_STATE state = GetState();

	if (state == CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE)
	{
		//状態のカウント数取得
		int nStateCnt = GetStateCnt();

		//ステート変更カウント進める
		nStateCnt++;

		if (nStateCnt >= 10)
		{
			//通常に戻す
			state = CCharacter::CHARACTER_STATE::CHARACTER_NORMAL;

			//ステートカウントリセット
			nStateCnt = 0;

			//状態代入
			SetState(state);
		}
		//ステートカウント代入
		SetStateCnt(nStateCnt);
	}
}