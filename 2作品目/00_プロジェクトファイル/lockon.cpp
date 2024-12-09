//=============================================
//
//照準[lockon.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "lockon.h"
#include "manager.h"

//texパス
const std::string CLockOn::TEXTURE_NAME = "data\\TEXTURE\\lockon.png";

//最大ダメージを与えるロックオンサイズ
const float CLockOn::MAX_DAMAGE_LOCKON_SIZE = 10.0f;
//威力が一番低いロックオンするサイズ
const float CLockOn::MIN_DAMAGE_LOCKON_SIZE = 70.0f;
//中くらいのダメージロックオンするサイズ
const float CLockOn::MEDIUM_DAMAGE_LOCKON_SIZE = 40.0f;

//=============================================
//コンストラクタ
//=============================================
CLockOn::CLockOn(int nPriority):CBillboard(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CLockOn::~CLockOn()
{
}

//=============================================
//初期化
//=============================================
HRESULT CLockOn::Init()
{
	//親クラスの初期化
	CObject3D::Init();
	//頂点設定
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f), m_col);
	return S_OK;
}

//=============================================
//終了
//=============================================
void CLockOn::Uninit()
{
	//親クラスの終了
	CObject3D::Uninit();
}

//=============================================
//更新
//=============================================
void CLockOn::Update()
{
	//親クラスの更新
	CObject3D::Update();

	ChangeSize();

	//頂点設定
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f), m_col);
}

//=============================================
//描画
//=============================================
void CLockOn::Draw()
{
	//親クラスの描画
	CObject3D::Draw();
}

//=============================================
//サイズ変更
//=============================================
void CLockOn::ChangeSize()
{
	//サイズ取得
	D3DXVECTOR3 size = GetSize();

	if (size.x > CLockOn::MAX_DAMAGE_LOCKON_SIZE && size.y > CLockOn::MAX_DAMAGE_LOCKON_SIZE)
	{
		size.x-=1.2f;
		size.y-=1.2f;
	}

	SetSize(size);

}

//=============================================
//サイズリセット
//=============================================
void CLockOn::SizeReset()
{
	SetSize(m_DefaultSize);
}

//=============================================
//生成
//=============================================
CLockOn* CLockOn::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col)
{
	CLockOn* pLockOn = new CLockOn;

	// nullならnullを返す
	if (pLockOn == nullptr) { return nullptr; }

	//テクスチャ取得
	CTexture* pTexture = CManager::GetTexture();

	pLockOn->SetPos(pos); //pos設定

	pLockOn->SetSize(size); //サイズ設定

	pLockOn->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME))); //テクスチャの設定

	pLockOn->m_DefaultSize = size;

	pLockOn->m_col = col; //カラーの設定

	pLockOn->SetType(OBJECT_TYPE_LOCKON); //オブジェクトのタイプ設定

	pLockOn->Init(); //エフェクトの初期化処理

	return pLockOn;
}

//=============================================
//サイズチェンジ
//=============================================
void CLockOn::ChangeSize(float fRatioFrame)
{
	float fAddSize = m_DefaultSize.x * fRatioFrame;
	D3DXVECTOR3 size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//if (size.x < m_DefaultSize.x)
	{
		size.x = fAddSize;
		size.y = fAddSize;
	}

	SetSize(size);
}
