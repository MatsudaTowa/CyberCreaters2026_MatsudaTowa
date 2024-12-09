//=============================================
//
//レティクル[reticle.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "reticle.h"
#include "manager.h"

//テクスチャ初期化
LPDIRECT3DTEXTURE9 CReticle::m_pTextureTemp = nullptr;
const std::string CReticle::RETICLE_TEXTURE_NAME = "data\\TEXTURE\\lockon.png";

//=============================================
//コンストラクタ
//=============================================
CReticle::CReticle(int nPriority):CBillboard(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CReticle::~CReticle()
{
}

//=============================================
//初期化
//=============================================
HRESULT CReticle::Init()
{
	//親クラスの初期化
	CObject3D::Init();
	//頂点座標
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	return S_OK;
}

//=============================================
//終了
//=============================================
void CReticle::Uninit()
{
	//親クラスの終了
	CObject3D::Uninit();
}

//=============================================
//更新
//=============================================
void CReticle::Update()
{
	//親クラスの更新
	CObject3D::Update();
	//頂点座標
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

//=============================================
//描画
//=============================================
void CReticle::Draw()
{
	//親クラスの描画
	CBillboard::Draw();
}

//=============================================
//生成
//=============================================
CReticle* CReticle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CReticle* pRaticle = new CReticle;

	if (pRaticle == nullptr) 
	{
		return nullptr; 
	}

	CTexture* pTexture = CManager::GetInstance()->GetTexture();

	pRaticle->SetPos(pos); //pos設定
	pRaticle->SetSize(size); //サイズ設定
	pRaticle->SetRot(rot);
	pRaticle->BindTexture(pTexture->GetAddress(pTexture->Regist(&RETICLE_TEXTURE_NAME)));

	pRaticle->SetType(OBJECT_TYPE_RETICLE); //タイプ設定
	pRaticle->Init();

	return pRaticle;
}

//=============================================
//移動処理
//=============================================
void CReticle::Move()
{

}
