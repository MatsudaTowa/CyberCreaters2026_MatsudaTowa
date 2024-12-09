//=============================================
//
//3DTemplate[bullet.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "bullet.h"
#include "manager.h"
#include "effect.h"
#include "enemy.h"
#include "game.h"

//テクスチャ初期化
LPDIRECT3DTEXTURE9 CBullet::m_pTextureTemp = nullptr;
const std::string CBullet::PANETRARING_TEXTURE_NAME ="data\\TEXTURE\\slash_test.png";
const std::string CBullet::ELEC_TEXTURE_NAME ="data\\TEXTURE\\elekball.png";

//=============================================
//コンストラクタ
//=============================================
CBullet::CBullet(int nPriority):CAttack_Manager(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CBullet::~CBullet()
{
}

//=============================================
//初期化
//=============================================
HRESULT CBullet::Init()
{
	//親クラスの初期化
	CAttack_Manager::Init();

	return S_OK;
}

//=============================================
//終了
//=============================================
void CBullet::Uninit()
{
	//親クラスの終了
	CAttack_Manager::Uninit();
}

//=============================================
//更新
//=============================================
void CBullet::Update()
{
	//親クラスの更新
	CAttack_Manager::Update();
	
	//使用しているとき
	OnActive();

}

//=============================================  
//描画
//=============================================
void CBullet::Draw()
{
	//親クラスの描画
	CAttack_Manager::Draw();
}

//=============================================
//使用されてる時の処理
//=============================================
void CBullet::OnActive()
{
	//体力取得
	int nLife = GetLife();

	if (nLife > 0)
	{//ライフがあれば処理実行
		D3DXVECTOR3 pos = GetPos();
		pos += m_move;
		//座標を更新
		SetPos(pos);
		//頂点座標
		SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		//当たり判定チェック変数
		bool bHitCheck = false;

		//埋まってるかのチェック変数
		bool bHitUnder = false;

		bHitUnder = HitGround();

		if (m_type != CBullet::BULLET_TYPE_PANETRARING_SLASH)
		{
			if (bHitUnder == true)
			{//当たってたら
				Uninit();
				return;
			}
		}

		switch (m_Allegiance)
		{
		case BULLET_ALLEGIANCE_PLAYER:
			bHitCheck = HitEnemy();
			if (bHitCheck == true)
			{
				//Uninit();
			}
			break;

		case BULLET_ALLEGIANCE_ENEMY:
			bHitCheck = HitPlayer();
			if (bHitCheck == true)
			{
				Uninit();
			}
			break;

		default:
			assert(false);
			break;
		}

		//当たり判定チェック
		bHitCheck = HitBlock();

		if (bHitCheck == true)
		{//当たってたら
			Uninit();
		}
	}
	else
	{
		//終了
		Uninit();
	}
}

//=============================================
//弾作成
//=============================================
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR3 size
,int nLife, int nDamage, BULLET_ALLEGIANCE Allegiance,BULLET_TYPE type)
{
	CBullet* pBullet = nullptr;

	switch (type)
	{
	case CBullet::BULLET_TYPE::BULLET_TYPE_PANETRARING_SLASH:
		pBullet = new CPanetRaring_Slash;
		break;

	case CBullet::BULLET_TYPE::BULLET_TYPE_ELECBULLET:
		pBullet = new CElecBullet;
		break;

	default:
		break;
	}

	if (pBullet == nullptr) {return nullptr;}

	CTexture* pTexture = CManager::GetTexture();

	pBullet->SetPos(pos); //pos設定
	pBullet->SetSize(size); //サイズ設定
	pBullet->SetRot(rot);
	pBullet->m_move = move; //移動量代入
	pBullet->SetLife(nLife); //寿命代入
	pBullet->SetDamage(nDamage); //威力代入

	switch (type)
	{
	case CBullet::BULLET_TYPE::BULLET_TYPE_PANETRARING_SLASH:
		pBullet->BindTexture(pTexture->GetAddress(pTexture->Regist(&PANETRARING_TEXTURE_NAME)));
		break;

	case CBullet::BULLET_TYPE::BULLET_TYPE_ELECBULLET:
		pBullet->BindTexture(pTexture->GetAddress(pTexture->Regist(&ELEC_TEXTURE_NAME)));
		break;

	default:
		break;
	}
	pBullet->m_type = type;
	pBullet->m_Allegiance = Allegiance; //弾の設定
	pBullet->SetType(OBJECT_TYPE_BULLET); //タイプ設定
	pBullet->Init();

	return pBullet;
}

//=============================================
//移動量取得
//=============================================
D3DXVECTOR3 CBullet::GetMove()
{
	return m_move;
}

//=============================================
//敵か自分か取得
//=============================================
CBullet::BULLET_ALLEGIANCE CBullet::GetBulletAllegiance()
{
	return m_Allegiance;
}

//=============================================
//コンストラクタ
//=============================================
CPanetRaring_Slash::CPanetRaring_Slash(int nPriority):CBullet(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CPanetRaring_Slash::~CPanetRaring_Slash()
{
}

//=============================================
//初期化
//=============================================
HRESULT CPanetRaring_Slash::Init()
{
	//親クラスの初期化
	CBullet::Init();

	return S_OK;
}

//=============================================
//終了
//=============================================
void CPanetRaring_Slash::Uninit()
{
	//親クラスの終了
	CBullet::Uninit();
}

//=============================================
//更新
//=============================================
void CPanetRaring_Slash::Update()
{
	//親クラスの更新
	CBullet::Update();

	//体力取得
	int nLife = GetLife();

	if (nLife > 0)
	{//ライフがあれば処理実行

		//埋まってるかのチェック変数
		bool bHitUnder = false;

		bHitUnder = HitGround();
	}
}

//=============================================
//描画
//=============================================
void CPanetRaring_Slash::Draw()
{
	//親クラスの描画
	CBullet::Draw();
}


//=============================================
//コンストラクタ
//=============================================
CElecBullet::CElecBullet(int nPriority) :CBullet(nPriority),m_Electype(CElecBullet::ELECTYPE::TYPE_NONE),
m_nStandbyCnt(0),m_TargetPos(D3DXVECTOR3(0.0f,0.0f,0.0f))
{//イニシャライザーでプライオリティ設定、各メンバ変数初期化
}

//=============================================
//デストラクタ
//=============================================
CElecBullet::~CElecBullet()
{
}

//=============================================
//初期化
//=============================================
HRESULT CElecBullet::Init()
{
	//親クラスの初期化
	CBullet::Init();

	//スタンバイ状態に
	m_Electype = CElecBullet::ELECTYPE::TYPE_STAND_BY;

	//スタンバイ状態の時間を設定
	m_nStandbyCnt = CBossEnemy::BOSS_SHOT_FRAME * CBossEnemy::CREATE_BULLET;

	return S_OK;
}

//=============================================
//終了
//=============================================
void CElecBullet::Uninit()
{
	//親クラスの終了
	CBullet::Uninit();
}

//=============================================
//更新
//=============================================
void CElecBullet::Update()
{
	if (m_Electype == CElecBullet::ELECTYPE::TYPE_MOVE)
	{
		//親クラスの更新
		CBullet::Update();
	}
	else if (m_Electype == CElecBullet::ELECTYPE::TYPE_STAND_BY)
	{
		D3DXVECTOR3 PlayerPos = CGame::GetPlayer()->GetPos();
		D3DXVECTOR3 PlayerMaxPos = CGame::GetPlayer()->GetMaxPos();
		m_TargetPos = PlayerPos - PlayerMaxPos * 0.5f;
		//カウントダウン
		m_nStandbyCnt--;

		if (m_nStandbyCnt <= 0)
		{//0以下になったら
			CSound* pSound = CManager::GetSound();

			pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_BOSS_SHOT);
			m_Electype = CElecBullet::ELECTYPE::TYPE_MOVE;
			float x = m_TargetPos.x - GetPos().x; //敵との距離の差分計算（横）
			float y = m_TargetPos.y - GetPos().y; //敵との距離の差分計算（縦）

			float fAngle = atan2f(x, y);

			D3DXVECTOR3 rot = GetRot();

			rot.y = fAngle + D3DX_PI;

			D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			move.x += sinf(fAngle) * 5.0f;
			move.y += cosf(fAngle) * 5.0f;

			SetMove(D3DXVECTOR3(move.x, move.y, 0.0f));
		}

		//使用しているとき
		OnActive();

		for (int nCnt = 0; nCnt < CObject::MAX_OBJECT; nCnt++)
		{
			//オブジェクト取得
			CObject* pObj = CObject::Getobject(CEnemy::ENEMY_PRIORITY, nCnt);

			if (pObj != nullptr)
			{//ヌルポインタじゃなければ
				//タイプ取得
				CObject::OBJECT_TYPE type = pObj->GetType();
				if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_ENEMY)
				{
					CEnemy* pEnemy = (CEnemy*)pObj;

					if (pEnemy->m_Type == CEnemy::ENEMY_TYPE::ENEMY_TYPE_BOSS)
					{
						//自分自身のpos取得
						D3DXVECTOR3 pos = GetPos();

						/*SetMove(D3DXVECTOR3(x, y, 0));*/

						pos += pEnemy->GetMove();

						SetPos(pos);

						//m_fAngle+= 0.2f;
					}
				}
			}
		}
	}
}

//=============================================
//描画
//=============================================
void CElecBullet::Draw()
{
	//親クラスの描画
	CBullet::Draw();
}

//=============================================
//生成
//=============================================
CElecBullet* CElecBullet::ElecCreate(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nLife, int nDamage, BULLET_ALLEGIANCE Allegiance, BULLET_TYPE type)
{
	CElecBullet* pBullet = new CElecBullet;

	if (pBullet == nullptr) { return nullptr; }

	CTexture* pTexture = CManager::GetTexture();

	pBullet->SetPos(pos); //pos設定
	pBullet->SetSize(size); //サイズ設定
	pBullet->SetRot(rot);
	pBullet->SetLife(nLife); //寿命代入
	pBullet->SetDamage(nDamage); //威力代入

	pBullet->BindTexture(pTexture->GetAddress(pTexture->Regist(&ELEC_TEXTURE_NAME)));

	pBullet->SetBulletType(type);
	pBullet->SetBulletAllegiance(Allegiance); //弾の設定
	pBullet->SetType(OBJECT_TYPE_BULLET); //タイプ設定
	pBullet->Init();

	return pBullet;
}
