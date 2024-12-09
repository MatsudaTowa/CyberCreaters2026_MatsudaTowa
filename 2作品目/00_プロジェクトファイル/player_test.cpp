//=============================================
//
//3DTemplate[player.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "player_test.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "block.h"
#include "effect.h"
#include "field.h"
#include "camera.h"
#include "melee.h"
#include "gauge.h"
#include "game.h"

//親のインデント
const int PARTS_PARENT[CPlayer_test::PLAYER_PARTS] =
{
	-1,
	0,
	0,
	1,
	0,
	3,
	0,
	5,
	0,
	7,
};

//モデルパス
const std::string CPlayer_test:: PLAYERPARTS_NAME[CPlayer_test::PLAYER_PARTS] =
{
	"data\\MODEL\\player\\body.x",
	"data\\MODEL\\player\\head.x",
	"data\\MODEL\\player\\Larm.x",
	"data\\MODEL\\player\\Lhand.x",
	"data\\MODEL\\player\\Rarm.x",
	"data\\MODEL\\player\\Rhand.x",
	"data\\MODEL\\player\\Lleg.x",
	"data\\MODEL\\player\\Lfoot.x",
	"data\\MODEL\\player\\Rleg.x",
	"data\\MODEL\\player\\Rfoot.x"
};
//通常の移動速度
const float CPlayer_test::DEFAULT_MOVE = 1.0f;
//通常の移動速度
const float CPlayer_test::DAMPING_COEFFICIENT = 0.3f;

//通常のジャンプ力
const float CPlayer_test::DEFAULT_JUMP = 25.0f;

//ジャンプ回数
const int CPlayer_test::MAX_JUMPCNT = 2;

//プレイヤーをリスポーンされる座標
const float CPlayer_test::DEADZONE_Y = -100.0f;

//テクスチャ初期化
LPDIRECT3DTEXTURE9 CPlayer_test::m_pTextureTemp = nullptr;

LPD3DXBUFFER CPlayer_test::m_pBuffMat = nullptr;

LPD3DXMESH CPlayer_test::m_pMesh = nullptr;

DWORD CPlayer_test::m_dwNumMat = 0;

//最終段階
const int CPlayer_test::MAX_CHARGE = CGauge::MAX_GAUGE_WIDE / CHARGE_INTERVAL / SLASH_COST;

bool CPlayer_test::m_PlayerDeath = false;

//=============================================
//コンストラクタ
//=============================================
CPlayer_test::CPlayer_test(int nPriority) :CCharacter(nPriority), m_nJumpCnt(0), m_OldPress(false), m_nChargeCnt(0), m_nSlashDamage(0)
{//イニシャライザーでジャンプカウント、プレス情報,チャージ段階,斬撃のダメージ初期化
	m_PlayerDeath = false;
	//斬撃の初期サイズ
	m_SlashSize = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
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
	CRenderer* pRender = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();

	m_bSize = false;

	for (int nCnt = 0; nCnt < CPlayer_test::PLAYER_PARTS; nCnt++)
	{
		m_apModel[nCnt] = CModel_Parts::Create(GetPos(),GetRot(), &PLAYERPARTS_NAME[nCnt]);
		//m_ CModel_Parts::SetParent()
	}

	//移動量初期化
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//ゲージ生成
	CGauge::Create(D3DXVECTOR3(0.0f, 70.0f, 0.0f), D3DXVECTOR2(500.0f, 30.0f), CGauge::GAUGE_TYPE_LIFE, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));

	//ムーブ値代入
	SetMove(move);

	return S_OK;
}

//=============================================
//終了
//=============================================
void CPlayer_test::Uninit()
{
	//親クラスの終了処理を呼ぶ
	CObjectX::Uninit();

}

//=============================================
//更新
//=============================================
void CPlayer_test::Update()
{
	////重力処理
	//Gravity();

	////移動処理
	//PlayerMove();

	////位置取得
	//D3DXVECTOR3 pos = GetPos();

	////過去の位置
	//D3DXVECTOR3 oldpos = GetOldPos();

	////移動量取得
	//D3DXVECTOR3 move = GetMove();

	////移動量を更新(減速）
	//move *= 1.0f - DAMPING_COEFFICIENT;

	////移動量代入
	//SetMove(move);

	////過去の位置に今の位置を代入
	//oldpos = pos;

	////過去の位置代入
	//SetOldPos(oldpos);

	////エフェクト生成
	//CEffect* pEffect = CEffect::Create(D3DXVECTOR3(pos.x, pos.y + 8.0f, pos.z), D3DXVECTOR3(10.0f, 10.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f), 30);

	////移動量追加
	//pos += move;

	////座標を更新
	//SetPos(pos);

	////最大最小値取得
	//D3DXVECTOR3 minpos = GetMinPos();
	//D3DXVECTOR3 maxpos = GetMaxPos();

	////ブロックとの接触処理
	//HitBlock();

	////エネミーとの接触処理
	//HitEnemy();

	//if (GetLaunding())
	//{//着地してるなら
	//	//ジャンプ数リセット
	//	m_nJumpCnt = 0;
	//}

	//if (pos.y < DEADZONE_Y)
	//{//リスポーン処理
	//	ReSpawn();
	//}

	////マウスの情報取得
	//CInputMouse* pMouse = CManager::GetMouse();

	////どっち向いてるか取得
	//bool bWay = GetWay();

	//for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	//{
	//	//オブジェクト取得
	//	CObject* pObj = CObject::Getobject(CGauge_Slash::GAUGE_PRIORITY, nCnt);
	//	if (pObj != nullptr)
	//	{//ヌルポインタじゃなければ
	//		//タイプ取得
	//		CObject::OBJECT_TYPE type = pObj->GetType();

	//		//敵との当たり判定
	//		if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_GAUGE_SLASH)
	//		{
	//			CGauge_Slash* pGauge = (CGauge_Slash*)pObj;

	//			if (pGauge->GetSize().x > 0.0f)
	//			{//ゲージがあったら
	//				if (pMouse->GetPress(0))
	//				{//左クリックが押されてる間
	//					//ゲージ消費(後に押された時間に応じて消費量変更)
	//					m_PressCnt++;
	//					if (m_PressCnt >= CHARGE_INTERVAL)
	//					{//押されたらサイズ増加
	//						m_SlashSize.x += 3.0f;
	//						m_SlashSize.y += 3.0f;
	//						m_SlashSize.z += 0.0f;

	//						//カウントリセット
	//						m_PressCnt = 0;

	//						m_nChargeCnt++;
	//					}

	//					//ゲージ減少
	//					pGauge->SubGauge(SLASH_COST);
	//					m_OldPress = true;

	//				}
	//			}
	//			if (pMouse->GetRelease(0) && m_OldPress)
	//			{//左クリックが離されたら
	//				if (m_nChargeCnt >= MAX_CHARGE)
	//				{//マックスチャージ量だったら
	//					m_nSlashDamage = 5;
	//				}
	//				else if (m_nChargeCnt >= MAX_CHARGE * 0.5f && m_nChargeCnt < MAX_CHARGE)
	//				{//半分より上だったら
	//					m_nSlashDamage = 3;
	//				}
	//				else
	//				{//それ以下だったら
	//					m_nSlashDamage = 1;
	//				}
	//				//弾発射
	//				ShotBullet(pos, m_SlashSize, bWay, m_nSlashDamage, CBullet::BULLET_TYPE_PLAYER);

	//				//斬撃のサイズリセット
	//				m_SlashSize = D3DXVECTOR3(10.0f, 10.0f, 0.0f);

	//				//何も押されてない状態に
	//				m_OldPress = false;

	//				//カウントリセット
	//				m_PressCnt = 0;

	//			}
	//		}
	//	}
	//}

	//if (pMouse->GetTrigger(1))
	//{//左クリックが入力されたら
	//	//近接攻撃処理
	//	PerformMelee(pos, bWay);
	//}

}

//=============================================
//描画
//=============================================
void CPlayer_test::Draw()
{
	for (int nCnt = 0; nCnt < CPlayer_test::PLAYER_PARTS; nCnt++)
	{
		m_apModel[nCnt]->Draw();
	}
}

//=============================================
//生成
//=============================================
CPlayer_test* CPlayer_test::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife)
{
	CModel* pModel = CManager::GetModel();

	CPlayer_test* pPlayer = new CPlayer_test;

	// nullならnullを返す
	if (pPlayer == nullptr) { return nullptr; }

	pPlayer->SetPos(pos); //pos設定
	pPlayer->SetRot(rot); //rot設定
	pPlayer->SetLife(nLife); //体力代入

	pPlayer->SetType(OBJECT_TYPE_NONE); //タイプ設定

	pPlayer->Init(); //初期化処理

	return pPlayer;
}

//=============================================
//ダメージを受けたとき
//=============================================
void CPlayer_test::Damage(int nDamage)
{
	//体力取得
	int nLife = GetLife();

	if (nLife > 0)
	{//HPが残ってたら
		nLife -= nDamage;

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
//リスポーン
//=============================================
void CPlayer_test::ReSpawn()
{
	//自分自身のpos取得
	D3DXVECTOR3 PlayerPos = GetPos();

	PlayerPos = D3DXVECTOR3(-450.0f, 0.5f, 0.0f);

	//pos代入
	SetPos(PlayerPos);
}

//=============================================
//移動処理
//=============================================
void CPlayer_test::PlayerMove()
{
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	D3DXVECTOR3 vecDirection(0.0f, 0.0f, 0.0f);

	//カメラタイプ取得
	CCamera::CANERA_TYPE pCameraType = CCamera::GetType();

	//どっち向いてるか取得
	bool bWay = GetWay();

	switch (pCameraType)
	{//サイドビューの時は横にしか動かないように設定
	case CCamera::CANERA_TYPE::TYPE_SIDEVIEW:
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
	case CCamera::CANERA_TYPE::TYPE_PARALLEL_SIDEVIEW:
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

		move.x += sinf(rotMoveY) * DEFAULT_MOVE;
		move.z += cosf(rotMoveY) * DEFAULT_MOVE;
		rot.y = rotMoveY + D3DX_PI;
		//rotを代入
		SetRot(rot);
	}
	if (m_nJumpCnt < MAX_JUMPCNT)
	{//ジャンプ数以下だったら
		if (pKeyboard->GetTrigger(DIK_SPACE))
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
void CPlayer_test::PerformMelee(D3DXVECTOR3 pos, bool bWay)
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
