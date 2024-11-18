//=============================================
//
//3DTemplate[bullet.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "bullet.h"
#include "manager.h"
#include "game.h"

//テクスチャ初期化
LPDIRECT3DTEXTURE9 CBullet::m_pTextureTemp = nullptr;
const std::string CBullet::BULLET_TEXTURE_NAME ="data\\TEXTURE\\effect000.jpg";

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

		switch (m_Allegiance)
		{
		case BULLET_ALLEGIANCE_PLAYER:
			bHitCheck = HitEnemy();

		case BULLET_ALLEGIANCE_ENEMY:
			bHitCheck = HitPlayer();
			break;

		default:
			assert(false);
			break;
		}

		//当たり判定チェックTODO:レイでやれ
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
	case CBullet::BULLET_TYPE::BULLET_TYPE_NORMAL:
		pBullet = new CBullet;
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
	case CBullet::BULLET_TYPE::BULLET_TYPE_NORMAL:
		pBullet->BindTexture(pTexture->GetAddress(pTexture->Regist(&BULLET_TEXTURE_NAME)));
		break;
	default:
		assert(false);
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
