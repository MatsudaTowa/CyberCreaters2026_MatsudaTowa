//=============================================
//
//アイテムのUI[item_UI.h]
//Auther Matsuda Towa
//
//=============================================
#include "item_UI.h"
#include "manager.h"

//テクスチャ初期化
LPDIRECT3DTEXTURE9 CItem_UI::m_pTexture = nullptr;
const std::string CItem_UI::SLASH_TEXTURE_NAME = "data\\TEXTURE\\item_book000.png";
const std::string CItem_UI::FLOW_TEXTURE_NAME = "data\\TEXTURE\\item_book001.png";
//=============================================
//コンストラクタ
//=============================================
CItem_UI::CItem_UI(int nPriority):CObject2D(nPriority),m_type(CItem_UI::ITEM_UI_TYPE::ITEM_UI_TYPE_NONE)
{//イニシャライザーでプライオリティ設定、タイプ初期化
}

//=============================================
//デストラクタ
//=============================================
CItem_UI::~CItem_UI()
{
}

//=============================================
//初期化
//=============================================
HRESULT CItem_UI::Init()
{
	//親クラスの初期化
	CObject2D::Init();

	//頂点設定
	SetVtx(1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	return S_OK;
}

//=============================================
//終了
//=============================================
void CItem_UI::Uninit()
{
	//親クラスの終了
	CObject2D::Uninit();
}

//=============================================
//更新
//=============================================
void CItem_UI::Update()
{
	//親クラスの更新
	CObject2D::Update();

	//頂点設定
	SetVtx(1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

//=============================================
//描画
//=============================================
void CItem_UI::Draw()
{
	//親クラスの描画
	CObject2D::Draw();
}

void CItem_UI::SetTex(ITEM_UI_TYPE type)
{
	m_type = type;
	CTexture* pTexture = CManager::GetTexture();
	switch (m_type)
	{
	case CItem_UI::ITEM_UI_TYPE::ITEM_UI_TYPE_NONE:
		SetSize(D3DXVECTOR2(0.0f,0.0f));
		break;
	case CItem_UI::ITEM_UI_TYPE::ITEM_UI_TYPE_PANETRARING_SLASH:
		SetSize(D3DXVECTOR2(80.0f, 80.0f));
		CItem_UI::BindTexture(pTexture->GetAddress(pTexture->Regist(&SLASH_TEXTURE_NAME))); //テクスチャの設定
		break;
	case CItem_UI::ITEM_UI_TYPE::ITEM_UI_TYPE_FLOW:
		SetSize(D3DXVECTOR2(80.0f, 80.0f));
		CItem_UI::BindTexture(pTexture->GetAddress(pTexture->Regist(&FLOW_TEXTURE_NAME)));	//テクスチャの設定
		break;
	default:
		break;
	}
}

//=============================================
//生成
//=============================================
CItem_UI* CItem_UI::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
    CTexture* pTexture = CManager::GetTexture();
    CItem_UI* pItem_UI = new CItem_UI;

    // nullならnullを返す
    if (pItem_UI == nullptr) { return nullptr; }

    pItem_UI->SetPos(pos); //pos設定

    pItem_UI->SetSize(size); //size設定

    pItem_UI->SetType(OBJECT_TYPE_ITEM_UI); //オブジェクトタイプ設定

    pItem_UI->Init(); //初期化処理

    return pItem_UI;
}
