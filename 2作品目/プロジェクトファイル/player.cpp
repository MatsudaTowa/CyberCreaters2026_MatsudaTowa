//=============================================
//
//プレイヤー処理[player.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "block.h"
#include "effect.h"
#include "field.h"
#include "camera.h"
#include "melee.h"
#include "game.h"
#include"renderer.h"
#include "flow_range.h"
#include "flow.h"
#include "scene.h"

//モデルパス
const std::string CPlayer::MODEL_NAME = "data\\MODEL\\face.x";

//通常の移動速度
const float CPlayer::DEFAULT_MOVE = 1.0f;

//移動抵抗
const float CPlayer::DAMPING_COEFFICIENT = 0.3f;

//通常のジャンプ力
const float CPlayer::DEFAULT_JUMP = 30.0f;

//ジャンプ回数
const int CPlayer::MAX_JUMPCNT = 2;

//ステート切り替えフレーム
const int CPlayer::STATE_FRAME = 60;

//プレイヤーをリスポーンされる座標
const float CPlayer::DEADZONE_Y = -100.0f;

//テクスチャ初期化
LPDIRECT3DTEXTURE9 CPlayer::m_pTextureTemp = nullptr;

LPD3DXBUFFER CPlayer::m_pBuffMat = nullptr;

LPD3DXMESH CPlayer::m_pMesh = nullptr;

DWORD CPlayer::m_dwNumMat = 0;

//最終段階
const int CPlayer::MAX_CHARGE = CGauge::MAX_GAUGE_WIDE / CHARGE_INTERVAL / SLASH_COST;

bool CPlayer::m_PlayerDeath = false;

//=============================================
//コンストラクタ
//=============================================
CPlayer::CPlayer(int nPriority):CCharacter(nPriority),m_nJumpCnt(0),m_OldPress(false), m_OldRelease(true), m_PressCnt(0),
m_ReleaseCnt(0),m_nChargeCnt(0),m_nSlashDamage(0), m_bFlow(false)
{//イニシャライザーで各メンバ変数初期化

	//プレイヤーの攻撃を近距離のみにする
	m_Attack = PLAYER_ATTACK_MELEE;

	//ステートを通常に
	SetState(CCharacter::CHARACTER_STATE::CHARACTER_NORMAL);

	//死んでない状態に
	m_PlayerDeath = false;

	//斬撃の初期サイズ
	m_SlashSize = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
}

//=============================================
//デストラクタ
//=============================================
CPlayer::~CPlayer()
{
}

//=============================================
//初期化
//=============================================
HRESULT CPlayer::Init()
{
	CRenderer* pRender = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();

	m_bSize = false;

	//移動量初期化
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f,0.0f,0.0f);

	//ゲージ生成
	CGauge* pGauge = CGauge::Create(D3DXVECTOR3(0.0f, 40.0f, 0.0f), D3DXVECTOR2(500.0f, 30.0f), CGauge::GAUGE_TYPE_LIFE, D3DXCOLOR(0.0f, 0.7f, 0.3f, 1.0f));
	
	//ムーブ値代入
	SetMove(move);

	m_pItemUI = nullptr;

	if (m_pItemUI == nullptr)
	{
		m_pItemUI = CItem_UI::Create(D3DXVECTOR3(1000.0f, 600.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f));
	}

	m_pLockOn = nullptr;

	return S_OK;
}

//=============================================
//初期化(セット用)
//=============================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife)
{
	CModel* pModel = CManager::GetModel();

	SetPos(pos); //pos設定
	SetRot(rot); //rot設定
	SetLife(nLife); //体力代入

	//xファイル読み込み
	BindXFile(pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).pBuffMat,
		pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).dwNumMat,
		pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).pMesh);

	SetType(OBJECT_TYPE_PLAYER); //タイプ設定

	CRenderer* pRender = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();

	m_bSize = false;

	//移動量初期化
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//シーンのポインタ取得
	CScene* pScene = CManager::GetScene();

	//CScene::MODE mode = pScene->GetSceneMode();

	//ムーブ値代入
	SetMove(move);

	m_pItemUI = nullptr;

	if (m_pItemUI == nullptr)
	{
		m_pItemUI = CItem_UI::Create(D3DXVECTOR3(1000.0f, 600.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f));
	}

	m_pLockOn = nullptr;

	return S_OK;
}


//=============================================
//終了
//=============================================
void CPlayer::Uninit()
{
	//親クラスの終了処理を呼ぶ
	CObjectX::Uninit();

}

//=============================================
//更新
//=============================================
void CPlayer::Update()
{
	//SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	//現在のシーンを取得
	CScene::MODE pScene = CScene::GetSceneMode();

	if (pScene != CScene::MODE::MODE_TITLE)
	{
		//状態を取得
		CCharacter::CHARACTER_STATE state = GetState();

		if (m_pItemUI != nullptr)
		{
			switch (m_Attack)
			{
			case CPlayer::PLAYER_ATTACK_MELEE:
				m_pItemUI->SetTex(CItem_UI::ITEM_UI_TYPE_NONE);
				break;
			case CPlayer::PLAYER_ATTACK_PANETRARING_SLASH:
				m_pItemUI->SetTex(CItem_UI::ITEM_UI_TYPE_PANETRARING_SLASH);

				for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
				{
					//オブジェクト取得
					CObject* pObj = CObject::Getobject(CFlow_Range::FLOW_RANGE_PRIORITY, nCnt);
					if (pObj != nullptr)
					{//ヌルポインタじゃなければ
						//タイプ取得
						CObject::OBJECT_TYPE type = pObj->GetType();

						//敵との当たり判定
						if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_FLOW_RANGE)
						{
							CFlow_Range* pFlow_Range = (CFlow_Range*)pObj;

							if (pFlow_Range != nullptr)
							{
								pFlow_Range->Uninit();
							}
						}
					}
				}
				m_bFlow = false;
				break;
			case CPlayer::PLAYER_ATTACK_FLOW:
				m_pItemUI->SetTex(CItem_UI::ITEM_UI_TYPE_FLOW);
				break;
			default:
				break;
			}
		}


		if (state == CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE)
		{
			//状態のカウント数取得
			int nStateCnt = GetStateCnt();

			//ステート変更カウント進める
			nStateCnt++;

			if (nStateCnt >= STATE_FRAME)
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

		//重力処理
		Gravity();

		if (m_bFlow == false)
		{
			//移動処理
			PlayerMove();
		}
		//位置取得
		D3DXVECTOR3 pos = GetPos();

		//過去の位置
		D3DXVECTOR3 oldpos = GetOldPos();

		//移動量取得
		D3DXVECTOR3 move = GetMove();

		//移動量を更新(減速）
		move *= 1.0f - DAMPING_COEFFICIENT;

		//移動量代入
		SetMove(move);

		//過去の位置に今の位置を代入
		oldpos = pos;

		//過去の位置代入
		SetOldPos(oldpos);

		//移動量追加
		pos += move;

		//座標を更新
		SetPos(pos);

		if (m_pLockOn != nullptr)
		{//照準をエネミーに合わせて動かす
			m_pLockOn->SetPos(D3DXVECTOR3(GetPos().x, GetPos().y + 5.0f, -10.0f));
		}

		//最大最小値取得
		D3DXVECTOR3 minpos = GetMinPos();
		D3DXVECTOR3 maxpos = GetMaxPos();

		if (pScene == CScene::MODE::MODE_TUTORIAL)
		{
			if (GetOldPos().x < -180.0f
				&& GetPos().x > -180.0f)
			{
				SetPos(D3DXVECTOR3(GetOldPos().x, GetPos().y, GetPos().z));
				SetMove(D3DXVECTOR3(0.0f,GetMove().y,GetMove().z));
			}
		}

		//ブロックとの接触処理
		HitBlock();

		//床との接触処理
		HitField();

		//エネミーとの接触処理
		HitEnemy();

		//ゲームの状態取得
		CGame::GAME_STATE Game_state = CGame::GetState();

		if (pScene == CScene::MODE::MODE_GAME &&Game_state == CGame::GAME_STATE::GAME_STATE_NORMAL && GetPos().x > CCharacter::BOSS_FIELD_X)
		{//ボス戦状態に移行
			Game_state = CGame::GAME_STATE::GAME_STATE_BOSS;

			CSound* pSound = CManager::GetSound();
			//サウンドの停止
			pSound->StopSound();

			pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_BGM_GAME_BOSS);

			CGame::SetState(Game_state);

		}

		if (GetLaunding())
		{//着地してるなら
			//ジャンプ数リセット
			m_nJumpCnt = 0;
		}

		if (pos.y < DEADZONE_Y)
		{//リスポーン処理
			ReSpawn();
		}

		//マウスの情報取得
		CInputMouse* pMouse = CManager::GetMouse();
		CInputPad* pPad = CManager::GetPad();

		//どっち向いてるか取得
		bool bWay = GetWay();

		for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
		{
			//オブジェクト取得
			CObject* pObj = CObject::Getobject(CGauge_Slash::GAUGE_PRIORITY, nCnt);
			if (pObj != nullptr)
			{//ヌルポインタじゃなければ
				//タイプ取得
				CObject::OBJECT_TYPE type = pObj->GetType();

				//敵との当たり判定
				if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_GAUGE_SLASH)
				{
					CGauge_Slash* pGauge = (CGauge_Slash*)pObj;

					//ゲージ処理
					Gauge(pGauge);
				}
			}
		}

		if (pMouse->GetTrigger(1) || pPad->GetTrigger(CInputPad::JOYKEY::JOYKEY_B))
		{//右クリックが入力されたら
			//近接攻撃処理
			PerformMelee(pos, bWay);
		}
	}
}

//=============================================
//描画
//=============================================
void CPlayer::Draw()
{
	//親クラスの描画を呼ぶ
	CCharacter::Draw();
}

//=============================================
//lock-on処理
//=============================================
void CPlayer::LockOn()
{
	if (m_bLockOn != true)
	{
		m_pLockOn = CLockOn::Create(D3DXVECTOR3(GetPos().x, GetPos().y + 5.0f, -10.0f),
			D3DXVECTOR3(70.0f, 70.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	m_bLockOn = true;
}

//=============================================
//lock-onサイズ変更
//=============================================
void CPlayer::LockOn_ChangeSize(float fRatioFrame)
{
	m_pLockOn->ChangeSize(fRatioFrame);
}

//=============================================
//集中斬撃を照準に合わせて出す
//=============================================
void CPlayer::LockOn_Flow()
{
	if (m_pLockOn != nullptr)
	{
		int nFlowLife = 0;
		if (m_pLockOn->GetSize().x <= m_pLockOn->MIN_DAMAGE_LOCKON_SIZE
			&& m_pLockOn->GetSize().x > m_pLockOn->MEDIUM_DAMAGE_LOCKON_SIZE)
		{//最小ダメージのとき
			nFlowLife = 30;
		}
		else if (m_pLockOn->GetSize().x <= m_pLockOn->MEDIUM_DAMAGE_LOCKON_SIZE
			&& m_pLockOn->GetSize().x > m_pLockOn->MAX_DAMAGE_LOCKON_SIZE)
		{//中ダメージのとき
			nFlowLife = 60;
		}
		else if (m_pLockOn->GetSize().x <= m_pLockOn->MAX_DAMAGE_LOCKON_SIZE)
		{//中ダメージのとき
			nFlowLife = 90;
		}
		CFlow* pFlow = CFlow::Create(D3DXVECTOR3(m_pLockOn->GetPos().x, m_pLockOn->GetPos().y + 5.0f, -10.0f),
			D3DXVECTOR3(10.0f, 10.0f, 0.0f), nFlowLife, 1, CFlow::FLOW_TYPE::FLOW_TYPE_ENEMY);
	}
	Delete_LockOn();
}

//=============================================
//照準を削除
//=============================================
void CPlayer::Delete_LockOn()
{
	if (m_pLockOn != nullptr)
	{
		m_pLockOn->Uninit();
		m_pLockOn = nullptr;
		m_bLockOn = false;
	}
}

//=============================================
//生成
//=============================================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot, int nLife)
{
	CModel* pModel = CManager::GetModel();

	CPlayer* pPlayer = new CPlayer;

	// nullならnullを返す
	if (pPlayer == nullptr) {return nullptr;}

	pPlayer->SetPos(pos); //pos設定
	pPlayer->SetRot(rot); //rot設定
	pPlayer->SetLife(nLife); //体力代入

	//xファイル読み込み
	pPlayer->BindXFile(pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).pBuffMat,
					pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).dwNumMat,
					pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).pMesh);

	pPlayer->SetType(OBJECT_TYPE_PLAYER); //タイプ設定

	pPlayer->Init(); //初期化処理
	
	return pPlayer;
}

//=============================================
//ダメージを受けたとき
//=============================================
void CPlayer::Damage(int nDamage)
{
	//体力取得
	int nLife = GetLife();

	//状態を取得
	CCharacter::CHARACTER_STATE state = GetState();

	if (m_pLockOn != nullptr)
	{//照準破棄
		m_pLockOn->Uninit();
		m_pLockOn = nullptr;
		m_bLockOn = false;
	}

	if (nLife > 0)
	{//HPが残ってたら

		nLife -= nDamage;

		//ダメージ状態に変更
		state = CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE;

		//現在の状態を代入
		SetState(state);

		for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
		{
			//オブジェクト取得
			CObject* pObj = CObject::Getobject(CGauge_Life::GAUGE_PRIORITY, nCnt);
			if (pObj != nullptr)
			{//ヌルポインタじゃなければ
				//タイプ取得
				CObject::OBJECT_TYPE type = pObj->GetType();

				//敵との当たり判定
				if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_GAUGE_LIFE)
				{
					CGauge_Life* pGauge = (CGauge_Life*)pObj;

					//ゲージ減少
					pGauge->SubGauge(100);
				}
			}
		}

		//体力代入
		SetLife(nLife);
	}
	if (nLife <= 0)
	{//HPが0以下だったら
		//終了
		Uninit();
		//死んだ状態に
		m_PlayerDeath = true;
	}
}

//=============================================
//ゲージ処理
//=============================================
void CPlayer::Gauge(CGauge* pGauge)
{
	//どっち向いてるか取得
	bool bWay = GetWay();

	//マウスの情報取得
	CInputMouse* pMouse = CManager::GetMouse();
	CInputPad* pPad = CManager::GetPad();

	//位置取得
	D3DXVECTOR3 pos = GetPos();

	//貫通斬撃
	if (m_ReleaseCnt > SLASH_COOLTIME &&pGauge->GetSize().x > (float)SLASH_COST && m_Attack == PLAYER_ATTACK_PANETRARING_SLASH)
	{//ゲージがあり攻撃方法が貫通斬撃だったら
		if (pMouse->GetPress(0) || pPad->GetPress(CInputPad::JOYKEY::JOYKEY_X))
		{//左クリックが押されてる間
			//ゲージ消費(後に押された時間に応じて消費量変更)
			m_PressCnt++;
			if (m_PressCnt >= CHARGE_INTERVAL)
			{//押されたらサイズ増加
				m_SlashSize.x += 1.0f;
				m_SlashSize.y += 4.0f;
				m_SlashSize.z += 0.0f;

				//カウントリセット
				m_PressCnt = 0;

				m_nChargeCnt++;
			}

			//ゲージ減少
			pGauge->SubGauge((float)SLASH_COST);

			//キー入力情報変更
			m_OldPress = true;
			m_OldRelease = false;

		}
	}
	if ((pMouse->GetRelease(0) ||pPad->GetRelease(CInputPad::JOYKEY::JOYKEY_X)) && m_OldPress && m_Attack == PLAYER_ATTACK_PANETRARING_SLASH)
	{//左クリックが離されたら
		if (m_nChargeCnt >= MAX_CHARGE)
		{//マックスチャージ量だったら
			m_nSlashDamage = 5;
		}
		else if (m_nChargeCnt >= MAX_CHARGE * 0.5f && m_nChargeCnt < MAX_CHARGE)
		{//半分より上だったら
			m_nSlashDamage = 3;
		}
		else
		{//それ以下だったら
			m_nSlashDamage = 1;
		}
		CSound* pSound = CManager::GetSound();

		pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_SHOT);
		//弾発射
		ShotBullet(pos,4.0f, m_SlashSize, bWay, m_nSlashDamage, CBullet::BULLET_ALLEGIANCE_PLAYER,CBullet::BULLET_TYPE_PANETRARING_SLASH);

		//斬撃のサイズリセット
		m_SlashSize = D3DXVECTOR3(10.0f, 10.0f, 0.0f);

		//何も押されてない状態に
		m_OldPress = false;

		//離した状態に
		m_OldRelease = true;

		//カウントリセット
		m_PressCnt = 0;
		m_nChargeCnt= 0;
		//離されてからのカウントリセット
		m_ReleaseCnt = 0;
	}

	//集中斬撃
	if (m_ReleaseCnt > SLASH_COOLTIME && pGauge->GetSize().x > SLASH_COST && (pMouse->GetTrigger(0) || pPad->GetTrigger(CInputPad::JOYKEY::JOYKEY_X)) && m_Attack == PLAYER_ATTACK_FLOW)
	{
		//集中状態の範囲のポインタ初期化
		CFlow_Range* pFlow_Range = nullptr;
		if (bWay == true)
		{//右向き
			pFlow_Range = CFlow_Range::Create(D3DXVECTOR3(pos.x + GetMaxPos().x, pos.y, pos.z),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 70.0f, 0.0f));
		}
		else if (bWay == false)
		{//左向き
			pFlow_Range = CFlow_Range::Create(D3DXVECTOR3(pos.x + GetMinPos().x, pos.y, pos.z),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-10.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 70.0f, 0.0f));
		}
	}

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(CFlow_Range::FLOW_RANGE_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//ヌルポインタじゃなければ
			//タイプ取得
			CObject::OBJECT_TYPE type = pObj->GetType();

			//敵との当たり判定
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_FLOW_RANGE)
			{
				CFlow_Range* pFlow_Range = (CFlow_Range*)pObj;

				if (pGauge->GetSize().x > 0.0f && (pMouse->GetPress(0) || pPad->GetPress(CInputPad::JOYKEY::JOYKEY_X)) && (pFlow_Range->GetMaxPos().x < 300.0f || pFlow_Range->GetMinPos().x > -300.0f) && m_Attack == PLAYER_ATTACK_FLOW)
				{//左クリックが押されてる間
					pFlow_Range->SizeUp(GetWay());

					m_bFlow = true;

					//ゲージ減少
					pGauge->SubGauge(SLASH_COST);

					//キー入力情報変更
					m_OldPress = true;
					m_OldRelease = false;
				}
			}
		}
	}

	if (m_OldPress && (pMouse->GetRelease(0) || pPad->GetRelease(CInputPad::JOYKEY::JOYKEY_X)) && m_Attack == PLAYER_ATTACK_FLOW)
	{
		m_bFlow = false;
		m_OldPress = false;
		//離した状態に
		m_OldRelease = true;
		//離されてからのカウントリセット
		m_ReleaseCnt = 0;
	}

	if (m_OldRelease)
	{//離された状態の時
		m_ReleaseCnt++;
	}
}

//=============================================
//リスポーン
//=============================================
void CPlayer::ReSpawn()
{
	//自分自身のpos取得
	D3DXVECTOR3 PlayerPos = GetPos();

	PlayerPos = D3DXVECTOR3(-900.0f, 0.5f, 0.0f);

	//pos代入
	SetPos(PlayerPos);
}

//=============================================
//移動処理
//=============================================
void CPlayer::PlayerMove()
{
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	CInputPad* pPad = CManager::GetPad();
	D3DXVECTOR3 vecDirection(0.0f, 0.0f, 0.0f);

	//カメラタイプ取得
	CCamera::CANERA_TYPE pCameraType = CCamera::GetType();

	//どっち向いてるか取得
	bool bWay = GetWay();

	switch (pCameraType)
	{//サイドビューの時は横にしか動かないように設定
	case CCamera::CANERA_TYPE::TYPE_SIDEVIEW:
		if (pKeyboard->GetPress(DIK_A) || pPad->GetPress(CInputPad::JOYKEY::JOYKEY_LEFT))
		{
			vecDirection.x -= 1.0f;
			bWay = false;
		}
		else if (pKeyboard->GetPress(DIK_D) || pPad->GetPress(CInputPad::JOYKEY::JOYKEY_RIGHT))
		{
			vecDirection.x += 1.0f;
			bWay = true;
		}
		break;
	case CCamera::CANERA_TYPE::TYPE_PARALLEL_SIDEVIEW:
		if (pKeyboard->GetPress(DIK_A) || pPad->GetPress(CInputPad::JOYKEY::JOYKEY_LEFT))
		{
			vecDirection.x -= 1.0f;
			bWay = false;
		}
		else if (pKeyboard->GetPress(DIK_D) || pPad->GetPress(CInputPad::JOYKEY::JOYKEY_RIGHT))
		{
			vecDirection.x += 1.0f;
			bWay = true;
		}
		break;
	default:
		if (pKeyboard->GetPress(DIK_W))
		{
			vecDirection.z += 1.0f;
		}
		if (pKeyboard->GetPress(DIK_S))
		{
			vecDirection.z -= 1.0f;
		}
		if (pKeyboard->GetPress(DIK_A))
		{
			vecDirection.x -= 1.0f;
			bWay = false;
		}
		else if (pKeyboard->GetPress(DIK_D))
		{
			vecDirection.x += 1.0f;
			bWay = true;
		}
		break;
	}

	//どっち向いてるか代入
	SetWay(bWay);

	//移動量取得
	D3DXVECTOR3 move = GetMove();

	//着地してるか取得
	bool bLanding = GetLaunding();

	if (vecDirection.x == 0.0f && vecDirection.z == 0.0f)
	{ // 動いてない。
		move.x = 0.0f;
		move.z = 0.0f;
	}
	else
	{
		float rotMoveY = atan2f(vecDirection.x, vecDirection.z);

		//オブジェクト2Dからrotを取得
		D3DXVECTOR3 rot = GetRot();

		//状態を取得
		CCharacter::CHARACTER_STATE state = GetState();

		if (state == CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE)
		{
			move.x += sinf(rotMoveY) * DEFAULT_MOVE * 0.5f;
			move.z += cosf(rotMoveY) * DEFAULT_MOVE * 0.5f;
		}
		else
		{
			move.x += sinf(rotMoveY) * DEFAULT_MOVE;
			move.z += cosf(rotMoveY) * DEFAULT_MOVE;
		}

		rot.y = rotMoveY + D3DX_PI;
		//rotを代入
		SetRot(rot);
	}
	if (m_nJumpCnt < MAX_JUMPCNT)
	{//ジャンプ数以下だったら
		if (pKeyboard->GetTrigger(DIK_SPACE) || pPad->GetTrigger(CInputPad::JOYKEY::JOYKEY_A))
		{
			move.y = DEFAULT_JUMP;
			bLanding = false; //空中
			m_nJumpCnt++; //ジャンプ数加算
		}
	}

	//移動量代入
	SetMove(move);

	//着地してるか代入
	SetLanding(bLanding);

}

//=============================================
//近接攻撃処理
//=============================================
void CPlayer::PerformMelee(D3DXVECTOR3 pos, bool bWay)
{
	if (bWay == true)
	{//右向き
		CMelee::Create(D3DXVECTOR3(pos.x + GetMaxPos().x, pos.y + 10.0f, pos.z),
			D3DXVECTOR3(0.0f, 0.0f, GetRot().y * 2.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), 30, MELEE_DAMAGE);
	}
	else if (bWay == false)
	{//左向き
		CMelee::Create(D3DXVECTOR3(pos.x + GetMinPos().x, pos.y + 10.0f, pos.z),
			D3DXVECTOR3(0.0f, 0.0f, GetRot().y * 4.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), 30, MELEE_DAMAGE);
	}
}

