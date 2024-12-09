//=============================================
//
//ボスの敵の処理[boss_enemy.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "boss_enemy.h"
#include "boss_behavior.h"

const float CBossEnemy::FIND_PLAYER_DISTANCE = 300.0f; //この値までだったら追いかける
const float CBossEnemy::LOST_PLAYER_DISTANCE = 100.0f; //この値以上だったら見失う

//=============================================
//コンストラクタ
//=============================================
CBossEnemy::CBossEnemy(int nPriority)
{
	m_pBossState = nullptr;

	if (m_pWandering == nullptr)
	{
		m_pWandering = new CBossWandering;
	}
	if (m_pChase == nullptr)
	{
		m_pChase = new CBossChase;
	}
	if (m_pConfusion == nullptr)
	{
		m_pConfusion = new CBossConfusion;
	}
	if (m_pStan == nullptr)
	{
		m_pStan = new CEnemyStan;
	}
	if (m_pGunAttack == nullptr)
	{
		m_pGunAttack = new CBossGunAttack;
	}
	if (m_pTackle == nullptr)
	{
		m_pTackle = new CBossTackle;
	}
}

//=============================================
//デストラクタ
//=============================================
CBossEnemy::~CBossEnemy()
{
	if (m_pBossState != nullptr)
	{
		delete m_pBossState;
	}
	if (m_pWandering != nullptr)
	{
		delete m_pWandering;
	}
	if (m_pChase != nullptr)
	{
		delete m_pChase;
	}
	if (m_pConfusion != nullptr)
	{
		delete m_pConfusion;
	}
	if (m_pTackle != nullptr)
	{
		delete m_pTackle;
	}
}

//=============================================
//初期化
//=============================================
HRESULT CBossEnemy::Init()
{
	if (m_pBossState == nullptr)
	{
		m_pBossState = new CWanderingState;
	}
	//銃初期化
	if (m_pGun == nullptr)
	{
		m_pGun = new CMiniGun;

		m_pGun->Init();
	}

	SetLife(DEFAULT_LIFE);
	//親クラスの初期化を呼ぶ
	CEnemy::Init();
	return S_OK;
}

//=============================================
//終了
//=============================================
void CBossEnemy::Uninit()
{
	//親クラスの終了処理を呼ぶ
	CEnemy::Uninit();
}

//=============================================
//更新
//=============================================
void CBossEnemy::Update()
{
	CEnemy::Update();

	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_0))
	{
		int nLife = 10;
		SetLife(nLife);
	}

	//TODO:無駄な処理多い気が...
	m_pBossState->Chase(this);

	m_pBossState->Wandering(this);

	m_pBossState->Stan(this);

	m_pBossState->Confusion(this);

	m_pBossState->Tackle(this);

	Motion(NUM_PARTS); //モーション処理

}

//=============================================
//描画
//=============================================
void CBossEnemy::Draw()
{
	//デバッグ表示
	DrawDebug();
	CEnemy::Draw();
}

//=============================================
//ボスの状態切り替え
//=============================================
void CBossEnemy::ChangeState(CBossState* state)
{
	//今のステートを消し引数のステートに切り替える
	if (m_pBossState != nullptr)
	{
		delete m_pBossState;
		m_pBossState = state;
		m_pBossState->Start(this);
	}
}

//=============================================
//プレイヤーとの当たり判定
//=============================================
void CBossEnemy::ColisionPlayer()
{
	for (int nPartsCnt = 0; nPartsCnt < GetNumParts(); ++nPartsCnt)
	{
		D3DXVECTOR3 pos = { m_apModel[nPartsCnt]->GetMtxWorld()._41,m_apModel[nPartsCnt]->GetMtxWorld()._42,m_apModel[nPartsCnt]->GetMtxWorld()._43 };
		D3DXVECTOR3 Minpos = m_apModel[nPartsCnt]->GetMin();
		D3DXVECTOR3 Maxpos = m_apModel[nPartsCnt]->GetMax();
		for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
		{
			//オブジェクト取得
			CObject* pObj = CObject::Getobject(CPlayer_test::PLAYER_PRIORITY, nCnt);
			if (pObj != nullptr)
			{//オブジェクトに要素が入っていたら
				//タイプ取得
				CObject::OBJECT_TYPE type = pObj->GetType();

				//ブロックとの当たり判定
				if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
				{
					//安全にダウンキャスト
					CPlayer_test* pPlayer = dynamic_cast<CPlayer_test*>(pObj);

					CheckColisionPlayer(pPlayer, nPartsCnt, pos, Minpos, Maxpos);
				}
			}
		}
	}
}

//=============================================
//プレイヤーとの当たり判定チェック
//=============================================
void CBossEnemy::CheckColisionPlayer(CPlayer_test* pPlayer, int nPartsCnt, const D3DXVECTOR3& pos, const D3DXVECTOR3& Minpos, const D3DXVECTOR3& Maxpos)
{
	for (int nPartsCnt = 0; nPartsCnt < pPlayer->GetNumParts(); nPartsCnt++)
	{
		D3DXVECTOR3 playerpos = { pPlayer->m_apModel[nPartsCnt]->GetMtxWorld()._41,
			pPlayer->m_apModel[nPartsCnt]->GetMtxWorld()._42,
			pPlayer->m_apModel[nPartsCnt]->GetMtxWorld()._43 };

		D3DXVECTOR3 PlayerMinpos = pPlayer->m_apModel[nPartsCnt]->GetMin();
		D3DXVECTOR3 PlayerMaxpos = pPlayer->m_apModel[nPartsCnt]->GetMax();
		CColision::COLISION colision = CManager::GetInstance()->GetColision()->CheckColisionSphere(pos, Minpos, Maxpos,
			playerpos, PlayerMinpos, PlayerMaxpos);

		if (colision == CColision::COLISION::COLISON_Z || colision == CColision::COLISION::COLISON_X)
		{
			// X軸衝突時の処理
			pPlayer->SetMove({0.0f,20.0f,0.0f});
			pPlayer->Damage(m_pTackle->TACKLE_DAMAGE);
		}
	}
}

//=============================================
//ボスのデバッグ表示
//=============================================
void CBossEnemy::DrawDebug()
{
#ifdef _DEBUG
	m_pWandering->DrawDebug();
	m_pBossState->DrawDebug();
	m_pChase->DrawDebug();
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	switch (GetColision())
	{
	case CColision::COLISION::COLISON_X:
		sprintf(&aStr[0], "\n\n\n\n\n当たり判定:X");
		break;
	case CColision::COLISION::COLISON_Z:
		sprintf(&aStr[0], "\n\n\n\n\n当たり判定:Z");
		break;
	case CColision::COLISION::COLISON_NONE:
		sprintf(&aStr[0], "\n\n\n\n\n当たり判定:当たってない");
		break;
	default:
		break;
	}
	sprintf(&aStr[0], "\n\n\n\n\n\nHP:%d\n0キーでHP10に",GetLife());

	//テキストの描画
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_CENTER, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}
