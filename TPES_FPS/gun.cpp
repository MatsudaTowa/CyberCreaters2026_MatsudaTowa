//=============================================
//
//銃[gun.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "gun.h"
#include "assault_behavior.h"
//=============================================
//コンストラクタ
//=============================================
CGun::CGun():m_Ammo(),m_Lv(),m_ReloadFrame(),m_FireRate(), m_nRateCnt(0),m_nDamage(0),m_Size()
{
	m_pShot = nullptr;
	m_pReload = nullptr;
}

//=============================================
//デストラクタ
//=============================================
CGun::~CGun()
{
	if (m_pShot != nullptr)
	{
		delete m_pShot;
		m_pShot = nullptr;
	}
	if (m_pReload != nullptr)
	{
		delete m_pReload;
		m_pReload = nullptr;
	}
}

//=============================================
//弾数取得
//=============================================
int& CGun::GetAmmo()
{
	return m_Ammo;
}

//=============================================
//レベル取得
//=============================================
int& CGun::GetLv()
{
	return m_Lv;
}

//=============================================
//リロードフレーム取得
//=============================================
int& CGun::GetReloadFrame()
{
	return m_ReloadFrame;
}

//=============================================
//発射レート取得
//=============================================
int& CGun::GetFireRate()
{
	return m_FireRate;
}

//弾のスピード
const float CAssultRifle::DEFAULT_AR_BULLET_SPEED = 50.0f;
const D3DXVECTOR3 CAssultRifle::DEFAULT_AR_SIZE = {1.5f,1.5f,1.5f};

//=============================================
//コンストラクタ
//=============================================
CAssultRifle::CAssultRifle()
{
	if (m_pShot == nullptr)
	{
		m_pShot = new CAssaultShot;
	}
	if (m_pReload == nullptr)
	{
		m_pReload = new CAssaultReload;
	}
}

//=============================================
//デストラクタ
//=============================================
CAssultRifle::~CAssultRifle()
{

}

//=============================================
//初期化
//=============================================
HRESULT CAssultRifle::Init()
{
	//現在の弾数取得
	int nAmmo = GetAmmo();
	//現在のレベル取得
	int nLv = GetLv();
	//現在のリロードフレーム取得
	int nReloadFrame = GetReloadFrame();
	//現在の発射レート取得
	int nFireRate = GetFireRate();

	//デフォルトのマガジン弾数代入
	nAmmo = CAssultRifle::DEFAULT_AR_MAG_SIZE;
	//初期レベル代入
	nLv = 1;
	//デフォルトのリロードフレーム代入
	nReloadFrame = CAssultRifle::DEFAULT_AR_RELOAD_FRAME;
	//デフォルトの発射レート代入
	nFireRate = CAssultRifle::DEFAULT_AR_FIRE_RATE;

	//押したらすぐ発射するため
	m_nRateCnt = CAssultRifle::DEFAULT_AR_FIRE_RATE;

	//ダメージの代入
	m_nDamage = CAssultRifle::DEFAULT_AR_DAMAGE;

	//サイズの代入
	m_Size = CAssultRifle::DEFAULT_AR_SIZE;

	//各メンバー変数に代入
	SetAmmo(nAmmo);
	SetLv(nLv);
	SetReloadFrame(nReloadFrame);
	SetFireRate(nFireRate);

	return S_OK;
}

//=============================================
//更新
//=============================================
void CAssultRifle::Uninit()
{
}

//=============================================
//リロード処理
//=============================================
bool CAssultRifle::Reload()
{
	bool bReload = true; //リロード中かどうか
	if (m_pReload != nullptr)
	{
		bReload = m_pReload->Reload(this);
	}
	return bReload;
}
