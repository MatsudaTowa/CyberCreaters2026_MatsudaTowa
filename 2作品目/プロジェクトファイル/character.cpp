//=============================================
//
//3DTemplate[character.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "character.h"
#include "block.h"
#include "player.h"
#include "enemy.h"
#include "field.h"
#include"bullet.h"
#include "colision.h"

//ボス戦のX座標
const float CCharacter::BOSS_FIELD_X = 600.0f;
//重力値
const float CCharacter::GRAVITY_MOVE = 1.5f;
//重力最大値
const float CCharacter::GRAVITY_MAX = 32.0f;

//=============================================
//コンストラクタ
//=============================================
CCharacter::CCharacter(int nPriority):CObjectX(nPriority),m_bLanding(false),m_bWay(false),m_move(D3DXVECTOR3(0.0f,0.0f,0.0f)),m_nLife(0)
,m_nStateCnt(0),m_oldpos(D3DXVECTOR3(0.0f,0.0f,0.0f)),m_State(CCharacter::CHARACTER_STATE::CHARACTER_NORMAL)
{//イニシャライザーでプライオリティ設定、各メンバ変数初期化
}

//=============================================
//デストラクタ
//=============================================
CCharacter::~CCharacter()
{
}

//=============================================
//初期化
//=============================================
HRESULT CCharacter::Init()
{
	CObjectX::Init();
    return S_OK;
}

//=============================================
//終了
//=============================================
void CCharacter::Uninit()
{
    CObjectX::Uninit();
}

//=============================================
//更新
//=============================================
void CCharacter::Update()
{
	D3DXVECTOR3 CharacterPos = GetPos();
	if (GetLaunding())
	{//着地してるなら
		//ジャンプ数リセット
		CharacterPos.y = m_oldpos.y;
		m_move.y = 0.0f;
	}
	SetPos(CharacterPos);
}

//=============================================
//描画
//=============================================
void CCharacter::Draw()
{
	switch (m_State)
	{
	case CCharacter::CHARACTER_STATE::CHARACTER_NORMAL:
		CObjectX::Draw();
		break;
	case CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE:
		//ダメージ状態の色に変更
		CObjectX::Draw(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		break;
	default:
		break;
	}
}


//=============================================
//重力処理
//=============================================
void CCharacter::Gravity()
{
    if (m_move.y < GRAVITY_MAX)
    {
        m_move.y -= GRAVITY_MOVE;
    }
}

//=============================================
//ブロックとの接触判定
//=============================================
void CCharacter::HitBlock()
{
	D3DXVECTOR3 CharacterPos = GetPos();

	//サイズ取得
	D3DXVECTOR3 CharacterMin = GetMinPos();
	D3DXVECTOR3 CharacterMax = GetMaxPos();

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(CBlock::BLOCK_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//ヌルポインタじゃなければ
			//タイプ取得
			CObject::OBJECT_TYPE type = pObj->GetType();

			//ブロックとの当たり判定
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_BLOCK)
			{
				CBlock* pBlock = (CBlock*)pObj;

				//当たり判定チェック
				CColision::COLISION Checkcolision_X = CColision::CheckColision_X(m_oldpos, CharacterPos,CharacterMin,CharacterMax,pBlock->GetPos(),pBlock->GetMinPos(),pBlock->GetMaxPos());
				
				CColision::COLISION Checkcolision_Y = CColision::CheckColision_Y(m_oldpos, CharacterPos, CharacterMin, CharacterMax, pBlock->GetPos(), pBlock->GetMinPos(), pBlock->GetMaxPos());

				CColision::COLISION Checkcolision_Z = CColision::CheckColision_Z(m_oldpos, CharacterPos, CharacterMin, CharacterMax, pBlock->GetPos(), pBlock->GetMinPos(), pBlock->GetMaxPos());

				if (Checkcolision_X == CColision::COLISION::COLISON_X)
				{//x方向に当たってたら
					CharacterPos.x = m_oldpos.x;
					m_move.x = 0.0f;
				}
				if (Checkcolision_Z == CColision::COLISION::COLISON_Z)
				{//z方向に当たってたら
					CharacterPos.z = m_oldpos.z;
					m_move.z = 0.0f;
				}
				if (Checkcolision_Y == CColision::COLISION::COLISON_UNDER_Y)
				{//y(下)方向に当たってたら
					CharacterPos.y = m_oldpos.y;
				}

				if (Checkcolision_Y == CColision::COLISION::COLISON_TOP_Y)
				{//y(上)方向に当たってたら
					CharacterPos.y = m_oldpos.y;
					m_move.y = 0.0f;
					m_bLanding = true; //着地
				}
			}
		}
	}
	SetPos(CharacterPos);
}


//=============================================
//床との接触判定
//=============================================
void CCharacter::HitField()
{
	D3DXVECTOR3 CharacterPos = GetPos();

	//サイズ取得
	D3DXVECTOR3 CharacterMin = GetMinPos();
	D3DXVECTOR3 CharacterMax = GetMaxPos();

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(CField::FIELD_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//ヌルポインタじゃなければ
			//タイプ取得
			CObject::OBJECT_TYPE type = pObj->GetType();

			//ブロックとの当たり判定
			//床との当たり判定
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_FIELD)
			{
				CField* pField = (CField*)pObj;

				//当たり判定チェック
				CColision::COLISION Checkcolision_Y = CColision::CheckColision_Y(m_oldpos, CharacterPos, CharacterMin, CharacterMax, pField->GetPos(), pField->GetSize());

				if (Checkcolision_Y == CColision::COLISION::COLISON_TOP_Y)
				{//y(上)方向に当たってたら
					CharacterPos.y = m_oldpos.y;
					m_move.y = 0.0f;
					m_bLanding = true; //着地
				}

				if (m_oldpos.x > pField->GetPos().x - pField->GetSize().x
					&& CharacterPos.x < pField->GetPos().x - pField->GetSize().x)
				{
					CharacterPos.x = m_oldpos.x;
					m_move.x = 0.0f;
				}

				if (m_oldpos.x < pField->GetPos().x + pField->GetSize().x
					&& CharacterPos.x > pField->GetPos().x + pField->GetSize().x)
				{
					CharacterPos.x = m_oldpos.x;
					m_move.x = 0.0f;
				}
			}
		}
	}
	SetPos(CharacterPos);
}

//=============================================
//プレイヤーとの当たり判定
//=============================================
void CCharacter::HitPlayer()
{
	D3DXVECTOR3 CharacterPos = GetPos();

	//サイズ取得
	D3DXVECTOR3 CharacterMin = GetMinPos();
	D3DXVECTOR3 CharacterMax = GetMaxPos();

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//ヌルポインタじゃなければ
			//タイプ取得
			CObject::OBJECT_TYPE type = pObj->GetType();

			//プレイヤーとの当たり判定
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
			{
				CPlayer* pPlayer = (CPlayer*)pObj;

				CColision::COLISION Checkcolision_X = CColision::CheckColision_X(m_oldpos, CharacterPos, CharacterMin, CharacterMax, pPlayer->GetPos(), pPlayer->GetMinPos(), pPlayer->GetMaxPos());

				CColision::COLISION Checkcolision_Y = CColision::CheckColision_Y(m_oldpos, CharacterPos, CharacterMin, CharacterMax, pPlayer->GetPos(), pPlayer->GetMinPos(), pPlayer->GetMaxPos());

				CColision::COLISION Checkcolision_Z = CColision::CheckColision_Z(m_oldpos, CharacterPos, CharacterMin, CharacterMax, pPlayer->GetPos(), pPlayer->GetMinPos(), pPlayer->GetMaxPos());

				if (Checkcolision_X == CColision::COLISION::COLISON_X)
				{//x方向に当たってたら
					CharacterPos.x = m_oldpos.x;
					m_move.x = 0.0f;
				}
				if (Checkcolision_Z == CColision::COLISION::COLISON_Z)
				{//z方向に当たってたら
					CharacterPos.z = m_oldpos.z;
					m_move.z = 0.0f;
				}
				if (Checkcolision_Y == CColision::COLISION::COLISON_UNDER_Y)
				{//y(下)方向に当たってたら
					CharacterPos.y = m_oldpos.y;
				}

				if (Checkcolision_Y == CColision::COLISION::COLISON_TOP_Y)
				{//y(上)方向に当たってたら
					CharacterPos.y = m_oldpos.y;
					m_move.y = 0.0f;
					m_bLanding = true; //着地
				}
			}
		}
	}
	SetPos(CharacterPos);
}

//=============================================
//敵との当たり判定
//=============================================
void CCharacter::HitEnemy()
{
	D3DXVECTOR3 CharacterPos = GetPos();

	//サイズ取得
	D3DXVECTOR3 CharacterMin = GetMinPos();
	D3DXVECTOR3 CharacterMax = GetMaxPos();

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(CEnemy::ENEMY_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//ヌルポインタじゃなければ
			//タイプ取得
			CObject::OBJECT_TYPE type = pObj->GetType();

			//敵との当たり判定
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_ENEMY)
			{
				CEnemy* pEnemy = (CEnemy*)pObj;
				CColision::COLISION Checkcolision_X = CColision::CheckColision_X(m_oldpos, CharacterPos, CharacterMin, CharacterMax, pEnemy->GetPos(), pEnemy->GetMinPos(), pEnemy->GetMaxPos());

				CColision::COLISION Checkcolision_Y = CColision::CheckColision_Y(m_oldpos, CharacterPos, CharacterMin, CharacterMax, pEnemy->GetPos(), pEnemy->GetMinPos(), pEnemy->GetMaxPos());

				CColision::COLISION Checkcolision_Z = CColision::CheckColision_Z(m_oldpos, CharacterPos, CharacterMin, CharacterMax, pEnemy->GetPos(), pEnemy->GetMinPos(), pEnemy->GetMaxPos());

				if (Checkcolision_X == CColision::COLISION::COLISON_X)
				{//x方向に当たってたら
					CharacterPos.x = m_oldpos.x;
					m_move.x = 0.0f;
				}
				if (Checkcolision_Z == CColision::COLISION::COLISON_Z)
				{//z方向に当たってたら
					CharacterPos.z = m_oldpos.z;
					m_move.z = 0.0f;
				}
				if (Checkcolision_Y == CColision::COLISION::COLISON_UNDER_Y)
				{//y(下)方向に当たってたら
					CharacterPos.y = m_oldpos.y;
				}
				if (Checkcolision_Y == CColision::COLISION::COLISON_TOP_Y)
				{//y(上)方向に当たってたら
					CharacterPos.y = m_oldpos.y;
					m_move.y = 0.0f;
					m_bLanding = true; //着地
				}
			}
		}
	}
	SetPos(CharacterPos);
}

//=============================================
//弾発射処理
//=============================================
void CCharacter::ShotBullet(D3DXVECTOR3 pos,float move, D3DXVECTOR3 size, bool bWay,int nDamage, CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type)
{
	if (bWay == true)
	{//右向き
		CBullet::Create(D3DXVECTOR3(pos.x, pos.y , pos.z), D3DXVECTOR3(sinf(GetRot().y + D3DX_PI) * move, 0.0f, cosf(GetRot().y + D3DX_PI) * move),
			D3DXVECTOR3(0.0f, 0.0f, GetRot().y * 2.0f), D3DXVECTOR3(size.x, size.y, 0.0f), 60, nDamage, Allegiance,type);
	}
	else if (bWay == false)
	{//左向き
		CBullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(sinf(GetRot().y + D3DX_PI) * move, 0.0f, cosf(GetRot().y + D3DX_PI) * move),
			D3DXVECTOR3(0.0f, 0.0f, GetRot().y * 4.0f), D3DXVECTOR3(size.x, size.y, 0.0f), 60, nDamage, Allegiance,type);
	}
}

//=============================================
//移動量取得
//=============================================
D3DXVECTOR3& CCharacter::GetMove()
{
    return m_move;
}

//=============================================
//過去の位置取得
//=============================================
D3DXVECTOR3& CCharacter::GetOldPos()
{
    return m_oldpos;
}

//=============================================
//着地してるかどうか取得
//=============================================
bool& CCharacter::GetLaunding()
{
    return m_bLanding;
}

//=============================================
//どっち向いてるかどうかを取得(true:右false:左)
//=============================================
bool& CCharacter::GetWay()
{
    return m_bWay;
}

//=============================================
//体力取得
//=============================================
int& CCharacter::GetLife()
{
	return m_nLife;
}


//=============================================
//状態取得
//=============================================
CCharacter::CHARACTER_STATE& CCharacter::GetState()
{
	return m_State;
}

//=============================================
//ステートカウント取得
//=============================================
int& CCharacter::GetStateCnt()
{
	return m_nStateCnt;
}
