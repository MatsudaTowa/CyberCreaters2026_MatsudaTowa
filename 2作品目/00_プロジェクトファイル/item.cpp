//=============================================
//
//アイテム処理[item.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "item.h"
#include "effect.h"
#include "manager.h"
#include "player.h"
#include "colision.h"
#include "score.h"
#include "game.h"

//テクスチャ初期化
LPDIRECT3DTEXTURE9 CItem::m_pTextureTemp = nullptr;
const std::string CItem::SLASH_TEXTURE_NAME = "data\\TEXTURE\\item_book000.png";
const std::string CItem::FLOW_TEXTURE_NAME = "data\\TEXTURE\\item_book001.png";

//=============================================
//コンストラクタ
//=============================================
CItem::CItem(int nPriority):CBillboard(nPriority)
{
}
//=============================================
//デストラクタ
//=============================================
CItem::~CItem()
{
}

//=============================================
//初期化
//=============================================
HRESULT CItem::Init()
{
	//親クラスの初期化
	CBillboard::Init();

	//頂点座標
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	m_pButton_UI = nullptr;

	return S_OK;
}

//=============================================
//終了
//=============================================
void CItem::Uninit()
{
	if (m_pButton_UI != nullptr)
	{
		//アイテムの削除
		m_pButton_UI->Uninit();
		m_pButton_UI = nullptr;
	}
	//親クラスの終了
	CBillboard::Uninit();
}

//=============================================
//更新
//=============================================
void CItem::Update()
{
	//親クラスの更新
	CBillboard::Update();

	HitItem();

}

//=============================================
//描画
//=============================================
void CItem::Draw()
{
	//親クラスの描画
	CBillboard::Draw();
}

//=============================================
//生成
//=============================================
CItem* CItem::Create(ITEMTYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	CItem* pItem = new CItem;

	if (pItem == nullptr) { return nullptr; }
	CTexture* pTexture = CManager::GetTexture();

	pItem->m_ItemType = type; //アイテムタイプ設定

	pItem->SetPos(pos); //pos設定
	pItem->SetSize(size); //size設定
	pItem->SetRot(rot); //rot設定
	switch (pItem->m_ItemType)
	{
	case CItem::ITEMTYPE::ITEMTYPE_PANETRARING_SLASH:
		pItem->BindTexture(pTexture->GetAddress(pTexture->Regist(&SLASH_TEXTURE_NAME))); //テクスチャの設定
		break;
	case CItem::ITEMTYPE::ITEMTYPE_FLOW:
		pItem->BindTexture(pTexture->GetAddress(pTexture->Regist(&FLOW_TEXTURE_NAME)));	//テクスチャの設定
		break;
	default:
		break;
	}

	pItem->SetType(OBJECT_TYPE_ITEM); //タイプ設定

	pItem->Init();

	return pItem;
}

//=============================================
//当たり判定
//=============================================
void CItem::HitItem()
{
	//位置取得
	D3DXVECTOR3 Itempos = GetPos();
	//サイズ取得
	D3DXVECTOR3 Itemsize = GetSize();

	//キーボード情報取得
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	CInputPad* pPad = CManager::GetPad();

	//プレイヤーアタックタイプのポインタ初期化
	CPlayer::PLAYER_ATTACK pPlayerAttack = CPlayer::PLAYER_ATTACK::PLAYER_ATTACK_MELEE; 

	switch (m_ItemType)
	{//タイプに応じてプレイヤーのアタックタイプ変更
	case CItem::ITEMTYPE::ITEMTYPE_PANETRARING_SLASH:
		pPlayerAttack = CPlayer::PLAYER_ATTACK::PLAYER_ATTACK_PANETRARING_SLASH;
		break;

	case CItem::ITEMTYPE::ITEMTYPE_FLOW:
		pPlayerAttack = CPlayer::PLAYER_ATTACK::PLAYER_ATTACK_FLOW;
		break;
	default:
		break;
	}

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
				CPlayer* pPlayer = (CPlayer*)pObj;

				CColision::COLISION colision = CColision::CheckItemColision(Itempos, Itemsize,pPlayer->GetPos(),pPlayer->GetMinPos(),pPlayer->GetMaxPos());

				if (colision != CColision::COLISION::COLISON_NONE)
				{//当たってたら
					//攻撃の削除
					if (m_pButton_UI == nullptr)
					{
						m_pButton_UI = CButton_UI::Create(D3DXVECTOR3(Itempos.x, Itempos.y + 20.0f, Itempos.z - 15.0f), D3DXVECTOR3(40.0f, 10.0f, 0.0f));
					}
					if (pKeyboard->GetTrigger(DIK_F) || pPad->GetTrigger(CInputPad::JOYKEY::JOYKEY_Y))
					{
						if (pPlayer->m_Attack != pPlayerAttack)
						{
							pPlayer->m_Attack = pPlayerAttack;
						}
						else if (pPlayer->m_Attack == pPlayerAttack)
						{
							CScore* pScore = CGame::GetScore();

							pScore->AddScore(100);
						}

						if (m_pButton_UI != nullptr)
						{
							//アイテムの削除
							m_pButton_UI->Uninit();
							m_pButton_UI = nullptr;
						}

						Uninit();
					}
				}
				else
				{
					if (m_pButton_UI != nullptr)
					{
						m_pButton_UI->Uninit();
						m_pButton_UI = nullptr;
					}
				}
			}
		}
	}
}
