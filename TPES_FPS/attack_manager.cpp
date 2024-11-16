//=============================================
//
//攻撃管理クラス[attack_manager.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "attack_manager.h"
#include "colision.h"
#include "player.h"
#include "enemy_test.h"
#include "model_parts.h"
#include "block.h"
#include "field.h"
#include"game.h"
#include "player_test.h"
//=============================================
//コンストラクタ
//=============================================
CAttack_Manager::CAttack_Manager(int nPriority) : CBillboard(nPriority),m_nLife(0),m_nDamage(0),m_nNumkill(0)
{//イニシャライザーでプライオリティ設定、体力とダメージ初期化
}

//=============================================
//デストラクタ
//=============================================
CAttack_Manager::~CAttack_Manager()
{
}

//=============================================
//初期化
//=============================================
HRESULT CAttack_Manager::Init()
{
	//親クラスの初期化
	CObject3D::Init();

	return S_OK;
}

//=============================================
//終了
//=============================================
void CAttack_Manager::Uninit()
{
	//親クラスの終了処理
	CObject3D::Uninit();
}

//=============================================
//更新
//=============================================
void CAttack_Manager::Update()
{
	//親クラスの更新処理
	CObject3D::Update();

	if (m_nLife > 0)
	{//寿命があるなら減らす
		m_nLife--;
	}
}

//=============================================
//描画
//=============================================
void CAttack_Manager::Draw()
{
	//親クラスの描画処理
	CBillboard::Draw();
}

//=============================================
//攻撃当たり判定(エネミー)
//=============================================
bool CAttack_Manager::HitEnemy()
{
	//位置取得
	D3DXVECTOR3 Attackpos = GetPos();
	//サイズ取得
	D3DXVECTOR3 Attacksize = GetSize();

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
				CEnemy* pEnemy = dynamic_cast<CEnemy*>(pObj);

				CColision::COLISION ColisionCheck;
				for (int nCnt = 0; nCnt < pEnemy->NUM_PARTS; nCnt++)
				{
					//パーツのオフセットpos
					D3DXVECTOR3 PartsPos = { pEnemy->m_apModel[nCnt]->GetMtxWorld()._41
					,pEnemy->m_apModel[nCnt]->GetMtxWorld()._42
					,pEnemy->m_apModel[nCnt]->GetMtxWorld()._43 };

					ColisionCheck = CColision::CheckPolygonModelColisionCircle(Attackpos, Attacksize, PartsPos, pEnemy->m_apModel[nCnt]->m_minpos, pEnemy->m_apModel[nCnt]->m_maxpos);

					if (ColisionCheck != CColision::COLISION::COLISON_NONE)
					{//当たってたら
						pEnemy->Damage(m_nDamage);
						int nCurrentLife = pEnemy->GetLife();
						return true;
					}
				}
			}
		}
	}
	return false;
}

//=============================================
//攻撃当たり判定(プレイヤー)
//=============================================
bool CAttack_Manager::HitPlayer()
{
	//位置取得
	D3DXVECTOR3 Attackpos = GetPos();
	//サイズ取得
	D3DXVECTOR3 Attacksize = GetSize();

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//ヌルポインタじゃなければ
			//タイプ取得
			CObject::OBJECT_TYPE type = pObj->GetType();

			//敵との当たり判定
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
			{
				CPlayer_test* pPlayer_test = dynamic_cast<CPlayer_test*>(pObj);

				CColision::COLISION ColisionCheck;
				for (int nCnt = 0; nCnt < pPlayer_test->NUM_PARTS; nCnt++)
				{
					//パーツのオフセットpos
					D3DXVECTOR3 PartsPos = { pPlayer_test->m_apModel[nCnt]->GetMtxWorld()._41
					,pPlayer_test->m_apModel[nCnt]->GetMtxWorld()._42
					,pPlayer_test->m_apModel[nCnt]->GetMtxWorld()._43 };

					ColisionCheck = CColision::CheckPolygonModelColisionCircle(Attackpos, Attacksize, PartsPos, pPlayer_test->m_apModel[nCnt]->m_minpos, pPlayer_test->m_apModel[nCnt]->m_maxpos);

					if (ColisionCheck != CColision::COLISION::COLISON_NONE)
					{//当たってたら
						pPlayer_test->Damage(m_nDamage);
						int nCurrentLife = pPlayer_test->GetLife();
						return true;
					}
				}
			}
		}
	}
}

//=============================================
//攻撃当たり判定(ブロック)
//=============================================
bool CAttack_Manager::HitBlock()
{
	//位置取得
	D3DXVECTOR3 Attackpos = GetPos();
	//サイズ取得
	D3DXVECTOR3 Attacksize = GetSize();

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(CBlock::BLOCK_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//ヌルポインタじゃなければ
			//タイプ取得
			CObject::OBJECT_TYPE type = pObj->GetType();

			//敵との当たり判定
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_BLOCK)
			{
				CBlock* pBlock = dynamic_cast<CBlock*>(pObj);

				CColision::COLISION ColisionCheck_X = CColision::CheckPolygonModelColision_X(Attackpos, Attacksize, pBlock->GetPos(), pBlock->GetMinPos(), pBlock->GetMaxPos());
				CColision::COLISION ColisionCheck_Z = CColision::CheckPolygonModelColision_Z(Attackpos, Attacksize, pBlock->GetPos(), pBlock->GetMinPos(), pBlock->GetMaxPos());

				if (ColisionCheck_X != CColision::COLISION::COLISON_NONE || ColisionCheck_Z != CColision::COLISION::COLISON_NONE)
				{//当たってたら
					//攻撃の削除
					return true;
				}
			}
		}
	}
	return false;
}

//=============================================
//攻撃当たり判定(床)
//=============================================
bool CAttack_Manager::HitGround()
{
	//位置取得
	D3DXVECTOR3 Attackpos = GetPos();
	//サイズ取得
	D3DXVECTOR3 Attacksize = GetSize();

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(CField::FIELD_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//ヌルポインタじゃなければ
			//タイプ取得
			CObject::OBJECT_TYPE type = pObj->GetType();

			//敵との当たり判定
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_FIELD)
			{
				CField* pField = dynamic_cast<CField*>(pObj);

				CColision::COLISION ColisionCheck = CColision::CheckItemFillColision(Attackpos, Attacksize, pField->GetPos(),
				D3DXVECTOR3(-pField->GetSize().x, -pField->GetSize().y, -pField->GetSize().z), 
				D3DXVECTOR3(pField->GetSize().x, pField->GetSize().y, pField->GetSize().z));

				if (ColisionCheck == CColision::COLISION::COLISON_TOP_Y)
				{//当たってたら
					//埋まってる分を足す
					Attackpos.y += pField->GetPos().y - (Attackpos.y - Attacksize.y);

					SetPos(Attackpos);
					return true;

				}
				else
				{
					return false;
				}
				break;
			}
		}
	}

}

//=============================================
//体力取得
//=============================================
int CAttack_Manager::GetLife()
{
	return m_nLife;
}

//=============================================
//ダメージ取得
//=============================================
int CAttack_Manager::GetDamage()
{
	return m_nDamage;
}
