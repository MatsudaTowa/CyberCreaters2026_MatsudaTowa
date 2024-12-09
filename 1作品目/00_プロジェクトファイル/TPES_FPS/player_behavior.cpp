//=============================================
//
//プレイヤーのストラテジーパターン[player_behavior.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "player_behavior.h"

//=============================================
//コンストラクタ
//=============================================
CPlayerMove::CPlayerMove()
{
}

//=============================================
//デストラクタ
//=============================================
CPlayerMove::~CPlayerMove()
{
}

//=============================================
//移動処理(プレイヤー)
//=============================================
void CPlayerMove::Move(CCharacter* character)
{
	//移動の方向の単位ベクトル変数
	D3DXVECTOR3 vecDirection(0.0f, 0.0f, 0.0f);
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();
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
	}
	if (pKeyboard->GetPress(DIK_D))
	{
		vecDirection.x += 1.0f;
	}

	float rotMoveY = CManager::GetInstance()->GetCamera()->GetRot().y + atan2f(vecDirection.x, vecDirection.z);

	CPlayer_test::Motion_Type Motion;

	if (vecDirection.x == 0.0f && vecDirection.z == 0.0f)
	{ // 動いてない。
		Motion = CPlayer_test::Motion_Type::MOTION_NEUTRAL;
	}
	else
	{
		Motion = CPlayer_test::Motion_Type::MOTION_MOVE;
	}

	D3DXVECTOR3 move = character->GetMove();
	if (vecDirection.x == 0.0f && vecDirection.z == 0.0f)
	{ // 動いてない。
		move.x = 0.0f;
		move.z = 0.0f;
	}
	else
	{
		move.x += sinf(rotMoveY) * character->GetSpeed();
		move.z += cosf(rotMoveY) * character->GetSpeed();
	}
	//親クラスからrotを取得
	D3DXVECTOR3 rot = character->GetRot();
	rot.y = rotMoveY + D3DX_PI;
	//rotを代入
	character->SetRot(rot);
	//移動量代入
	character->SetMove(move);
	//モーション代入
	character->SetMotion(Motion);

	int nJumpCnt = character->GetJumpCnt();
	if (nJumpCnt < MAX_JUMPCNT)
	{//ジャンプ数以下だったら
		if (pKeyboard->GetTrigger(DIK_SPACE))
		{
			//親クラスのジャンプ処理
			character->Jump();
			nJumpCnt++; //ジャンプ数加算
		}
	}
	character->SetJumpCnt(nJumpCnt);
}

//=============================================
//コンストラクタ
//=============================================
CPlayerSliding::CPlayerSliding()
{
}

//=============================================
//デストラクタ
//=============================================
CPlayerSliding::~CPlayerSliding()
{
}

//=============================================
//スライディング
//=============================================
void CPlayerSliding::Sliding(CPlayer_test* player)
{
	//スピードがあれば減速
	//if (move.x > 0.0f)
	//{
	//	move.x -= 0.001f;
	//}
	//else if (move.x < 0.0f)
	//{
	//	move.x += 0.001f;
	//}
	//if (move.z > 0.0f)
	//{
	//	move.z -= 0.001f;
	//}
	//else if (move.z < 0.0f)
	//{
	//	move.z += 0.001f;
	//}
	//player->SetMove(move);
}

//=============================================
//コンストラクタ
//=============================================
CPlayerAttack::CPlayerAttack()
{
}

//=============================================
//デストラクタ
//=============================================
CPlayerAttack::~CPlayerAttack()
{
}

//=============================================
//攻撃処理(プレイヤー)
//=============================================
void CPlayerAttack::GunAttack(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character)
{
	CInputMouse* pMouse = CManager::GetInstance()->GetMouse();

	CCamera* pCamera = CManager::GetInstance()->GetCamera();

	CPlayer_test::Motion_Type Motion;
	Motion = CPlayer_test::Motion_Type::MOTION_ATTACK;
	//モーション代入
	character->SetMotion(Motion);

	if (pMouse->GetPress(0))
	{//射撃ボタンが押されたら
		if (character->m_pGunAttack != nullptr)
		{
			character->m_pGun->m_nRateCnt++;
			if (character->m_pGun->m_nRateCnt >= character->m_pGun->GetFireRate())
			{
				character->m_pGun->m_nRateCnt = 0;
				//銃から発射 TODO:銃口と方向がおかしい
				D3DXVECTOR3 ShotPos = D3DXVECTOR3(character->m_apModel[14]->GetMtxWorld()._41,
					character->m_apModel[14]->GetMtxWorld()._42, character->m_apModel[14]->GetMtxWorld()._43 + cosf(character->GetRot().y + D3DX_PI));

				//移動量設定
				D3DXVECTOR3 ShotMove = D3DXVECTOR3(sinf(pCamera->GetRot().y + D3DX_PI) * -character->m_pGun->GetBulletSpeed(),
					sinf(pCamera->GetRot().x + D3DX_PI) * character->m_pGun->GetBulletSpeed(),
					cosf(pCamera->GetRot().y + D3DX_PI) * -character->m_pGun->GetBulletSpeed());
				//弾発射
				character->m_pGun->m_pShot->Shot(ShotPos, ShotMove, character->m_pGun->m_Size, character->m_pGun->m_nDamage, Allegiance, type, character->m_pGun);
			}
		}
	}
	if (pMouse->GetRelease(0))
	{
		character->m_pGun->m_nRateCnt = CAssultRifle::DEFAULT_AR_FIRE_RATE;
	}
	
}
