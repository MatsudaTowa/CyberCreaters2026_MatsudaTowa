//=============================================
//
//近接攻撃[melee.h]
//Auther Matsuda Towa
//
//=============================================
#include "melee.h"
#include "manager.h"
#include "enemy.h"
#include "player.h"

const std::string CMelee::TEXTURE_NAME = "data\\TEXTURE\\melee_effect.png";

//=============================================
//コンストラクタ
//=============================================
CMelee::CMelee(int nPriority) :CAttack_Manager(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CMelee::~CMelee()
{
}

//=============================================
//初期化
//=============================================
HRESULT CMelee::Init()
{
	//親クラスの初期化
	CAttack_Manager::Init();

	//頂点設定
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	return S_OK;
}


//=============================================
//終了
//=============================================
void CMelee::Uninit()
{
	//親クラスの終了
	CAttack_Manager::Uninit();
}

//=============================================
//更新
//=============================================
void CMelee::Update()
{
	//親クラスの更新
	CAttack_Manager::Update();

	//体力取得
	int nLife = GetLife();

	if (nLife > 0)
	{//ライフがあれば処理実行

		for (int nCnt = 0; nCnt < CObject::MAX_OBJECT; nCnt++)
		{
			//オブジェクト取得
			CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, nCnt);

			if (pObj != nullptr)
			{//ヌルポインタじゃなければ
				//タイプ取得
				CObject::OBJECT_TYPE type = pObj->GetType();
				if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
				{
					CPlayer* pPlayer = (CPlayer*)pObj;

					//自分自身のpos取得
					D3DXVECTOR3 pos = GetPos();

					//プレイヤーのposを自分に代入
					pos.y = pPlayer->GetPos().y + pPlayer->GetMaxPos().y * 0.5f;
					pos.z = pPlayer->GetPos().z;

					if (pPlayer->GetWay() == true)
					{//右向いてるなら
						pos.x = pPlayer->GetPos().x + pPlayer->GetMaxPos().x;
					}
					else if (pPlayer->GetWay() == false)
					{//左向いてるなら
						pos.x = pPlayer->GetPos().x + pPlayer->GetMinPos().x;
					}
					//posを代入
					SetPos(pos);
				}
			}

		}

		//当たり判定チェック変数
		bool bHitCheck = false; 

		//敵との当たり判定
		bHitCheck = HitEnemy();

		if (bHitCheck == true)
		{
			Uninit();
			return;
		}

		//ブロックとの当たり判定
		bHitCheck = HitBlock();

		if (bHitCheck == true)
		{
			Uninit();
			return;
		}
	}
	else
	{
		//終了
		Uninit();
		return;
	}
}

//=============================================  
//描画
//=============================================
void CMelee::Draw()
{
	//親クラスの描画
	CAttack_Manager::Draw();
}

//=============================================
//近接攻撃作成
//=============================================
CMelee* CMelee::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nLife,int nDamage)
{
	CMelee* pMelee = new CMelee;
	//nullならnullを返す
   if(pMelee ==nullptr) {return nullptr;}

   CTexture* pTexture = CManager::GetTexture();

   pMelee->SetPos(pos); //pos設定
   pMelee->SetSize(size); //サイズ設定
   pMelee->SetRot(rot); //方向設定
   pMelee->SetLife(nLife); //寿命代入
   pMelee->SetDamage(nDamage); //ダメージ代入
   pMelee->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME))); //テクスチャの設定
   pMelee->SetType(OBJECT_TYPE_MELEE); //タイプ設定

   pMelee->Init(); //初期化

   return pMelee;
 }
