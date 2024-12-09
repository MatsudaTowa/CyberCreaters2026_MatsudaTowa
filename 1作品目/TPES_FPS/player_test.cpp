//=============================================
//
//3DTemplate[player.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "player_test.h"
#include "manager.h"
#include "input.h"
#include "block.h"
#include "field.h"
#include "camera.h"
#include "game.h"
#include "smoke_grenade.h"

//スポーン位置
const D3DXVECTOR3 CPlayer_test::PLAYER_SPAWN_POS = { 0.0f, 0.5f, -400.0f };

//スポーン方向
const D3DXVECTOR3 CPlayer_test::PLAYER_SPAWN_ROT = { 0.0f, 3.14f, 0.0f};

//通常の移動速度
const float CPlayer_test::DAMPING_COEFFICIENT = 0.3f;

//プレイヤーをリスポーンされる座標
const float CPlayer_test::DEADZONE_Y = -100.0f;

CAmmo_UI* CPlayer_test::m_pAmmoUI = nullptr;
CLife_UI* CPlayer_test::m_pLifeUI = nullptr;

//テクスチャ初期化
LPDIRECT3DTEXTURE9 CPlayer_test::m_pTextureTemp = nullptr;

//=============================================
//コンストラクタ
//=============================================
CPlayer_test::CPlayer_test(int nPriority) :CCharacter(nPriority),m_Raticle(), m_bSmoke(), m_pHitCameraEffect()
{//イニシャライザーでメンバ変数初期化
	if (m_pSliding == nullptr)
	{
		m_pSliding = new CPlayerSliding;
	}
	if (m_pMove == nullptr)
	{
		m_pMove = new CPlayerMove;
	}
	if (m_pGunAttack == nullptr)
	{
		m_pGunAttack = new CPlayerAttack;
	}
}

//=============================================
//デストラクタ
//=============================================
CPlayer_test::~CPlayer_test()
{
}

//=============================================
//初期化
//=============================================
HRESULT CPlayer_test::Init()
{
	CCharacter::Init();

	//銃初期化
	if (m_pGun == nullptr)
	{
		m_pGun = new CAssultRifle;

		m_pGun->Init();
	}

	//現在のシーンを取得 TODO:シーン参照するな
	CScene::MODE pScene = CScene::GetSceneMode();
	if (pScene != CScene::MODE::MODE_TITLE)
	{
		//残弾数初期化
		if (m_pAmmoUI == nullptr)
		{
			m_pAmmoUI = new CAmmo_UI;

			m_pAmmoUI->Init();
		}
		//体力UI初期化
		if (m_pLifeUI == nullptr)
		{
			m_pLifeUI = new CLife_UI;

			m_pLifeUI->Init();
		}
	}

	m_pHitCameraEffect = nullptr;

	m_Raticle = nullptr;

	m_bSmoke = false;

	m_bRelorad = false;

	CRenderer* pRender = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();

	//移動量初期化
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int nCnt = 0; nCnt < NUM_PARTS; nCnt++)
	{
		CModel* pModel = CManager::GetInstance()->GetModel();
	}

	//カメラ情報取得
	CCamera* pCamera = CManager::GetInstance()->GetCamera();

	pCamera->SetRot({0.0f,0.0f,0.0f});

	//ムーブ値代入
	SetMove(move);

	//パーツ読み込み
	Load_Parts("data\\motion_soldier.txt");

	SetMotion(MOTION_NEUTRAL);

	return S_OK;
}

//=============================================
//終了
//=============================================
void CPlayer_test::Uninit()
{
	if (m_pAmmoUI != nullptr)
	{
		m_pAmmoUI->Uninit();
		m_pAmmoUI = nullptr;
	}
	if (m_pLifeUI != nullptr)
	{
		m_pLifeUI->Uninit();
		m_pLifeUI = nullptr;
	}
	if (m_pSliding != nullptr)
	{
		delete m_pSliding;
		m_pSliding = nullptr;
	}

	//親クラスの終了処理を呼ぶ
	CCharacter::Uninit();
}

//=============================================
//更新
//=============================================
void CPlayer_test::Update()
{
	//現在のシーンを取得
	CScene::MODE pScene = CScene::GetSceneMode();

	//ダメージステートの切り替えTODO:これもステートパターンで
	ChangeDamageState();

	if (m_pHitCameraEffect != nullptr)
	{//使われていたら
		m_pHitCameraEffect->SubAlpha();

		if (m_pHitCameraEffect->GetAlpha() < 0.0f)
		{
			m_pHitCameraEffect->Uninit();
			m_pHitCameraEffect = nullptr;
		}
	}

	for (int nCnt = 0; nCnt < NUM_PARTS; nCnt++)
	{
		m_apModel[nCnt]->SetOldPos(m_apModel[nCnt]->GetPos());
	}
	CCharacter::Update();
	ColisionEnemy();

	if (m_bRelorad == true)
	{//リロード中だったら
		m_bRelorad = m_pGun->Reload(); //リロードし終わったらfalseが返ってくる
	}

	if (m_pAmmoUI != nullptr)
	{
		m_pAmmoUI->SetAmmo_UI(m_pGun->GetAmmo());
	}

	if (m_pLifeUI != nullptr)
	{
		m_pLifeUI->SetLife_UI(GetLife());
	}

	if (pScene != CScene::MODE::MODE_TITLE)
	{
		//状態を取得
		CCharacter::CHARACTER_STATE state = GetState();

		if (state == CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE)
		{
			//状態のカウント数取得
			int nStateCnt = GetStateCnt();

			//ステート変更カウント進める
			++nStateCnt;

			//ステートカウント代入
			SetStateCnt(nStateCnt);
		}

		if (GetFinish())
		{
			//入力処理
			Input();

			if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_LSHIFT))
			{
				m_pSliding->Sliding(this);
			}
			else
			{
				m_pCharacterState->Move(this);
			}
		}

		//カメラ情報取得
		CCamera* pCamera = CManager::GetInstance()->GetCamera();

		if(m_Raticle != nullptr)
		{
			m_Raticle->SetPos(D3DXVECTOR3(pCamera->GetPosR().x + sinf(GetRot().y + D3DX_PI), pCamera->GetPosR().y - 20.0f, pCamera->GetPosR().z + cosf(GetRot().y + D3DX_PI)));
		}

		//どっち向いてるか取得
		bool bWay = GetWay();

		Motion(NUM_PARTS); //モーション処理
	}

	//CCharacter::HitBlock(NUM_PARTS);
}

//=============================================
//描画
//=============================================
void CPlayer_test::Draw()
{
	CInputMouse* pMouse = CManager::GetInstance()->GetMouse() ;
	pMouse->Debug();
	//親クラスのモーション用の描画を呼ぶ
	MotionDraw();
	//プレイヤーのデバッグ表示
	DebugPos();
}

//=============================================
//生成
//=============================================
CPlayer_test* CPlayer_test::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife)
{
	CModel* pModel = CManager::GetInstance()->GetModel();

	CPlayer_test* pPlayer = new CPlayer_test;

	// nullならnullを返す
	if (pPlayer == nullptr) { return nullptr; }

	pPlayer->SetPos(pos); //pos設定
	pPlayer->SetRot(rot); //rot設定
	pPlayer->SetLife(nLife); //体力代入

	pPlayer->Init(); //初期化処理

	pPlayer->SetType(OBJECT_TYPE_PLAYER); //タイプ設定

	return pPlayer;
}

//=============================================
//ダメージを受けたとき
//=============================================
void CPlayer_test::Damage(int nDamage)
{
	//体力取得
	int nLife = GetLife();

	//状態を取得
	CCharacter::CHARACTER_STATE state = GetState();

	if (nLife > 0 && state != CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE)
	{//ダメージ状態以外でHPが残ってたら

		if (m_pHitCameraEffect == nullptr)
		{
			if (nLife >= CPlayer_test::PLAYER_LIFE * 0.6f)
			{
				m_pHitCameraEffect = CHitCameraEffect::Create({ SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f,0.0f }, CHitCameraEffect::HIT_EFFECT_STAGE::MILD);
			}
			else if (nLife >= CPlayer_test::PLAYER_LIFE * 0.3f && nLife < CPlayer_test::PLAYER_LIFE * 0.6f)
			{
				m_pHitCameraEffect = CHitCameraEffect::Create({ SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f,0.0f }, CHitCameraEffect::HIT_EFFECT_STAGE::MODERATE);
			}
			else if (nLife < CPlayer_test::PLAYER_LIFE * 0.3f)
			{
				m_pHitCameraEffect = CHitCameraEffect::Create({ SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f,0.0f }, CHitCameraEffect::HIT_EFFECT_STAGE::SEVERE);
			}
		}

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
		//リスポーン
		ReSpawn();
	}
}

//=============================================
//リスポーン
//=============================================
void CPlayer_test::ReSpawn()
{
	//自分自身のpos取得
	D3DXVECTOR3 PlayerPos = GetPos();

	//スポーン時の設定にもどす
	SetPos(CPlayer_test::PLAYER_SPAWN_POS);
	SetRot(CPlayer_test::PLAYER_SPAWN_ROT);
	SetLife(CPlayer_test::PLAYER_LIFE);
	//TODO:キャラが違う場合は子クラスで実装
	m_pGun->SetAmmo(CAssultRifle::DEFAULT_AR_MAG_SIZE);
}

//=============================================
//移動処理
//=============================================
void CPlayer_test::Input()
{
	CInputMouse* pMouse = CManager::GetInstance()->GetMouse();

	CCamera* pCamera = CManager::GetInstance()->GetCamera();

	if (pMouse->GetPress(1))
	{//マウスが押されてる間は
		//射撃状態に変更
		ChangeState(new CShotState);

		//モーションを変更 TODO:覗きこむモーションに
		SetMotion(MOTION_NEUTRAL);

		ResetRot(); //レティクルのほうを向きたいので

		if (m_Raticle == nullptr)
		{//使われていなかったら
			m_Raticle = CReticle::Create(D3DXVECTOR3(pCamera->GetPosR().x + sinf(GetRot().y + D3DX_PI), pCamera->GetPosR().y - 20.0f, pCamera->GetPosR().z + cosf(GetRot().y + D3DX_PI)),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f));
		}
		m_pCharacterState->Shot(CBullet::BULLET_ALLEGIANCE_PLAYER, CBullet::BULLET_TYPE_NORMAL, this);
	}

	if (pMouse->GetRelease(1))
	{//マウスが離されたら
		//移動状態に変更
		ChangeState(new CMoveState);

		if(m_Raticle != nullptr)
		{//使われていたら
			m_Raticle->Uninit();
			m_Raticle = nullptr;
		}
	}

	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();

	if (pKeyboard->GetTrigger(DIK_R) && !pMouse->GetPress(0))
	{
		if (m_pGun->GetAmmo() < CAssultRifle::DEFAULT_AR_MAG_SIZE)
		{
			//リロード
			m_bRelorad = true;
		}
	}

	if (!m_bSmoke)
	{
		if (pKeyboard->GetTrigger(DIK_Q))
		{
			m_bSmoke = true;
			CSmokeGrenade::Create({ GetPos().x,GetPos().y + 50.0f,GetPos().z }, { sinf(pCamera->GetRot().y + D3DX_PI) * -10.0f,
					sinf(pCamera->GetRot().x + D3DX_PI) * 10.0f,
					cosf(pCamera->GetRot().y + D3DX_PI) * -10.0f }, { 0.0f,0.0f,0.0f });
		}
	}
}

//=============================================
//プレイヤーの方向をカメラのほうへ
//=============================================
void CPlayer_test::ResetRot()
{
	float rotMoveY = CManager::GetInstance()->GetCamera()->GetRot().y;

	//親クラスからrotを取得
	D3DXVECTOR3 rot = GetRot();

	rot.y = rotMoveY + D3DX_PI;

	SetRot(rot);
}

//=============================================
//エネミーとの当たり判定
//=============================================
void CPlayer_test::ColisionEnemy()
{
	for (int nPartsCnt = 0; nPartsCnt < GetNumParts(); ++nPartsCnt)
	{
		D3DXVECTOR3 pos = { m_apModel[nPartsCnt]->GetMtxWorld()._41,m_apModel[nPartsCnt]->GetMtxWorld()._42,m_apModel[nPartsCnt]->GetMtxWorld()._43 };
		D3DXVECTOR3 Minpos = m_apModel[nPartsCnt]->GetMin();
		D3DXVECTOR3 Maxpos = m_apModel[nPartsCnt]->GetMax();
		for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
		{
			//オブジェクト取得
			CObject* pObj = CObject::Getobject(CEnemy::ENEMY_PRIORITY, nCnt);
			if (pObj != nullptr)
			{//オブジェクトに要素が入っていたら
				//タイプ取得
				CObject::OBJECT_TYPE type = pObj->GetType();

				//ブロックとの当たり判定
				if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_ENEMY)
				{
					//安全にダウンキャスト
					CEnemy* pEnemy = dynamic_cast<CEnemy*>(pObj);

					CheckColisionEnemy(pEnemy, nPartsCnt, pos, Minpos, Maxpos);
				}
			}
		}
	}
}

void CPlayer_test::ChangeDamageState()
{
	// 状態を取得
	CCharacter::CHARACTER_STATE state = GetState();

	if (state == CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE)
	{
		//状態のカウント数取得
		int nStateCnt = GetStateCnt();

		//ステート変更カウント進める
		nStateCnt++;

		if (nStateCnt >= 30)
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

void CPlayer_test::CheckColisionEnemy(CEnemy* pEnemy, int nPartsCnt, const D3DXVECTOR3& pos, const D3DXVECTOR3& Minpos, const D3DXVECTOR3& Maxpos)
{
	for (int nEnemyPartsCnt = 0; nEnemyPartsCnt < pEnemy->GetNumParts(); nEnemyPartsCnt++)
	{
		D3DXVECTOR3 Enemypos = { pEnemy->m_apModel[nEnemyPartsCnt]->GetMtxWorld()._41,
			pEnemy->m_apModel[nEnemyPartsCnt]->GetMtxWorld()._42,
			pEnemy->m_apModel[nEnemyPartsCnt]->GetMtxWorld()._43 };

		D3DXVECTOR3 EnemyMinpos = pEnemy->m_apModel[nEnemyPartsCnt]->GetMin();
		D3DXVECTOR3 EnemyMaxpos = pEnemy->m_apModel[nEnemyPartsCnt]->GetMax();
		CColision::COLISION colision = CManager::GetInstance()->GetColision()->CheckColisionSphere(pos, Minpos, Maxpos,
			Enemypos, EnemyMinpos, EnemyMaxpos);

		if (colision == CColision::COLISION::COLISON_X)
		{
			// X軸衝突時の処理
			SetPos({ GetOldPos().x, GetPos().y, GetPos().z });
		}
		if (colision == CColision::COLISION::COLISON_TOP_Y)
		{
			// X軸衝突時の処理
			SetPos({ GetPos().x, GetOldPos().y, GetPos().z });
		}
		if (colision == CColision::COLISION::COLISON_Z)
		{
			// X軸衝突時の処理
			SetPos({ GetPos().x, GetPos().y, GetOldPos().z });
		}
	}
}

//=============================================
//プレイヤーのデバッグ表示
//=============================================
void CPlayer_test::DebugPos()
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n\n[player]\npos:%.1f,%.1f,%.1f\nrot:%.1f,%.1f,%.1f\nmove:%.1f,%.1f,%.1f\n弾数:%d\n体力:%d"
		, GetPos().x, GetPos().y, GetPos().z, GetRot().x, GetRot().y, GetRot().z, GetMove().x, GetMove().y, GetMove().z, m_pGun->GetAmmo(),GetLife());
	//テキストの描画
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}
