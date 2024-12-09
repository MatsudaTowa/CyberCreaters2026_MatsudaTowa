//=============================================
//
//ボスのステートパターン[boss_state.h]
//Auther Matsuda Towa
//
//=============================================
#include "boss_state.h"
#include "player_test.h"

//=============================================
//最初に呼ばれる関数
//=============================================
void CBossState::Start(CBossEnemy* boss)
{
}

//=============================================
//ボスの追跡状態(基底では何もしない)
//=============================================
void CBossState::Chase(CBossEnemy* boss)
{
}

//=============================================
//スタン状態
//=============================================
void CBossState::Stan(CBossEnemy* boss)
{
}

//=============================================
//ボスの徘徊状態(基底では何もしない)
//=============================================
void CBossState::Wandering(CBossEnemy* boss)
{
}

//=============================================
//ボスの混乱状態(基底では何もしない)
//=============================================
void CBossState::Confusion(CBossEnemy* boss)
{
}

//=============================================
//ボスのタックル状態(基底では何もしない)
//=============================================
void CBossState::Tackle(CBossEnemy* boss)
{
}

//=============================================
//ボスのデバッグ情報
//=============================================
void CBossState::DrawDebug()
{
}

//=============================================
//コンストラクタ
//=============================================
CChaseState::CChaseState() : m_PlayTackleCnt(0)
{
}

//=============================================
//デストラクタ
//=============================================
CChaseState::~CChaseState()
{
}

//=============================================
//ボスの追跡状態
//=============================================
void CChaseState::Chase(CBossEnemy* boss)
{
	for (int nCnt = 0; nCnt < CObject::MAX_OBJECT; nCnt++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(CPlayer_test::PLAYER_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//ヌルポインタじゃなければ
			//タイプ取得
			CObject::OBJECT_TYPE type = pObj->GetType();

			//敵との当たり判定
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
			{
				if (boss->m_pChase != nullptr)
				{
					boss->m_pChase->Chase(boss, pObj);
				}
			}
		}
	}

	//TODO:ステートパターンで
	if (boss->GetLife() < HP_LOW)
	{//HPが低い状態だったら

		++m_PlayTackleCnt;

		if (m_PlayTackleCnt > PLAY_TACKLE_FLAME)
		{//タックル実行フレームに到達したら
			m_PlayTackleCnt = 0;
			//ステート切り替え
			boss->ChangeState(new CTackleState);
		}
	}

	boss->m_pGunAttack->GunAttack(CBullet::BULLET_ALLEGIANCE_ENEMY, CBullet::BULLET_TYPE_NORMAL, boss);
}

//=============================================
//ボスの追跡状態デバッグ
//=============================================
void CChaseState::DrawDebug()
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n\n追跡");
	//テキストの描画
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_CENTER, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}

//=============================================
//最初に呼ばれる関数
//=============================================
void CBossStanState::Start(CBossEnemy* boss)
{
	m_StanCnt = 0;
}

//=============================================
//ボスのスタン状態
//=============================================
void CBossStanState::Stan(CBossEnemy* boss)
{
	if (m_StanCnt < STAN_FRAME)
	{
		++m_StanCnt;

		if (boss->m_pStan != nullptr)
		{
			boss->m_pStan->Stan(boss);
		}
	}
	if (m_StanCnt >= STAN_FRAME)
	{
		m_StanCnt = 0;

		//射撃状態に遷移
		boss->ChangeState(new CChaseState);
	}
}

//=============================================
//ボスのスタン状態デバッグ
//=============================================
void CBossStanState::DrawDebug()
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n\nスタン");
	//テキストの描画
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_CENTER, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}

//=============================================
//ボスの徘徊状態
//=============================================
void CWanderingState::Wandering(CBossEnemy* boss)
{
	if (boss->GetState() == CCharacter::CHARACTER_DAMAGE)
	{
		boss->ChangeState(new CChaseState);
	}
	for (int nCnt = 0; nCnt < CObject::MAX_OBJECT; nCnt++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(CPlayer_test::PLAYER_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//ヌルポインタじゃなければ
			//タイプ取得
			CObject::OBJECT_TYPE type = pObj->GetType();

			//敵との当たり判定
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
			{
				CPlayer_test* pPlayer_test = dynamic_cast<CPlayer_test*>(pObj);

				//プレイヤーの位置への方向情報
				D3DXVECTOR3 Vector = pPlayer_test->GetPos() - boss->GetPos();

				// 目的地との距離を計算
				float distance = sqrtf(Vector.x * Vector.x + Vector.z * Vector.z);

				if (distance < boss->FIND_PLAYER_DISTANCE)
				{//近かったら
					boss->ChangeState(new CChaseState); //追跡状態に変更
				}
				else if (boss->m_pWandering != nullptr)
				{
					boss->m_pWandering->Wandering(boss);
				}
			}
		}
	}
}

//=============================================
//ボスの徘徊状態デバッグ
//=============================================
void CWanderingState::DrawDebug()
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n\n徘徊");
	//テキストの描画
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_CENTER, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}

//=============================================
//ボスのタックル処理
//=============================================
void CTackleState::Tackle(CBossEnemy* boss)
{
	if (boss->m_pTackle != nullptr)
	{
		boss->m_pTackle->Tackle(boss);
	}
}

//=============================================
//ボスのタックル状態デバッグ
//=============================================
void CTackleState::DrawDebug()
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n\n突進");
	//テキストの描画
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_CENTER, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}

//=============================================
//最初に呼ばれる関数
//=============================================
void CConfusionBossState::Start(CBossEnemy* boss)
{
	m_StartRot = boss->GetRot().y;
	if (m_StartRot < D3DX_PI * 0.5f && m_StartRot > -D3DX_PI * 0.5f)
	{
		m_isRight = false;
	}
	else if (m_StartRot > D3DX_PI * 0.5f && m_StartRot < -D3DX_PI * 0.5f)
	{
		m_isRight = true;
	}
}

//=============================================
//ボスの混乱処理
//=============================================
void CConfusionBossState::Confusion(CBossEnemy* boss)
{
	if (boss->GetState() == CCharacter::CHARACTER_DAMAGE)
	{
		boss->ChangeState(new CBossStanState);
	}
	if (boss->m_pConfusion != nullptr)
	{
		boss->m_pConfusion->Confusion(boss, m_StartRot);
	}
}

//=============================================
//ボスの混乱状態デバッグ
//=============================================
void CConfusionBossState::DrawDebug()
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n\n混乱");
	//テキストの描画
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_CENTER, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}
