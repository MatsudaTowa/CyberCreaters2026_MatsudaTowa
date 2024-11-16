//=============================================
//
//アサルト銃のストラテジーパターン[assault_behavior.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "assault_behavior.h"

//=============================================
//コンストラクタ
//=============================================
CAssaultShot::CAssaultShot()
{
}

//=============================================
//デストラクタ
//=============================================
CAssaultShot::~CAssaultShot()
{
}

//=============================================
//アサルト弾発射処理
//=============================================
void CAssaultShot::Shot(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nDamage, 
CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type,CGun* gun)
{
	//現在の弾数取得
	int nAmmo = gun->GetAmmo();
	if (nAmmo > 0)
	{
		CBullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), move,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(size.x, size.y, 0.0f), 60, nDamage, Allegiance, type);
		nAmmo--;
	}
	gun->SetAmmo(nAmmo);
}

//=============================================
//コンストラクタ
//=============================================
CAssaultReload::CAssaultReload()
{
}

//=============================================
//デストラクタ
//=============================================
CAssaultReload::~CAssaultReload()
{
}

//=============================================
//アサルトリロード処理
//=============================================
bool CAssaultReload::Reload(CGun* gun)
{
	bool bReload = true; //リロード中かどうか
	int nCnt = GetReloadCnt();
	
	nCnt++;

	if (nCnt >= CAssultRifle::DEFAULT_AR_RELOAD_FRAME)
	{
		nCnt = 0;
		//現在の弾数取得
		int nAmmo = gun->GetAmmo();
		//デフォルトのマガジン弾数代入
		nAmmo = CAssultRifle::DEFAULT_AR_MAG_SIZE;
		gun->SetAmmo(nAmmo);
		bReload = false;
	}

	SetReloadCnt(nCnt);
	return bReload;
}
