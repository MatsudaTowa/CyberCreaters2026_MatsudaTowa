//=============================================
//
//スキップUI[skip_UI.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "skip_UI.h"
#include "manager.h"
#include "object.h"

//texパス
const std::string CSkip_UI::BUTTON_START_TEXTURE_NAME = "data\\TEXTURE\\skip_start.png";
const std::string CSkip_UI::BUTTON_ENTER_TEXTURE_NAME = "data\\TEXTURE\\skip_enter.png";

//=============================================
//コンストラクタ
//=============================================
CSkip_UI::CSkip_UI(int nPriority) :CObject2D(nPriority), m_nChangeCnt(0),m_col(D3DXCOLOR(0.0f,0.0f,0.0f,0.0f)),m_bPress(false)
{
	//初期値代入
	m_col = D3DXCOLOR(0.2f,0.2f,0.2f,1.0f);
}

//=============================================
//デストラクタ
//=============================================
CSkip_UI::~CSkip_UI()
{
}

//=============================================
//初期化
//=============================================
HRESULT CSkip_UI::Init()
{

	//親クラスの初期化を呼ぶ
	CObject2D::Init();

	//テクスチャ座標設定
	SetTexPos(D3DXVECTOR2(1.0f, 1.0f));

	//頂点設定
	SetVtx(1.0f, D3DXCOLOR(m_col));
	return S_OK;
}

//=============================================
//終了
//=============================================
void CSkip_UI::Uninit()
{
	//親クラスの終了呼ぶ
	CObject2D::Uninit();
}

//=============================================
//更新
//=============================================
void CSkip_UI::Update()
{
	//親クラスの更新呼ぶ
	CObject2D::Update();

	CTexture* pTexture = CManager::GetTexture();

	CInputPad* pPad = CManager::GetPad();

	if (pPad->GetConnet())
	{
		BindTexture(pTexture->GetAddress(pTexture->Regist(&BUTTON_START_TEXTURE_NAME)));
	}
	else if (!pPad->GetConnet())
	{
		BindTexture(pTexture->GetAddress(pTexture->Regist(&BUTTON_ENTER_TEXTURE_NAME)));
	}

	//頂点設定
	SetVtx(1.0f, D3DXCOLOR(m_col));
}

//=============================================
//描画
//=============================================
void CSkip_UI::Draw()
{
	//親クラスの描画呼ぶ
	CObject2D::Draw();
}

//=============================================
//生成
//=============================================
CSkip_UI* CSkip_UI::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	CTexture* pTexture = CManager::GetTexture();
	CSkip_UI* pSkip_UI = new CSkip_UI;
	CInputPad* pPad = CManager::GetPad();

	//nullならnullを返す
	if (pSkip_UI == nullptr) { return nullptr; }

	pSkip_UI->SetPos(pos); //pos設定

	pSkip_UI->SetSize(size); //size設定

	if (pPad->GetConnet())
	{
		pSkip_UI->BindTexture(pTexture->GetAddress(pTexture->Regist(&BUTTON_START_TEXTURE_NAME)));
	}
	else if (!pPad->GetConnet())
	{
		pSkip_UI->BindTexture(pTexture->GetAddress(pTexture->Regist(&BUTTON_ENTER_TEXTURE_NAME)));
	}

	pSkip_UI->SetType(OBJECT_TYPE_TUTORIAL); //タイプ設定

	pSkip_UI->Init();

	return pSkip_UI;
}

void CSkip_UI::ColorChange()
{
	m_nChangeCnt++;
	if (m_nChangeCnt >= CHANGE_FRAME)
	{
		if (m_bPress && m_col.r < 1.0f && m_col.g < 1.0f&& m_col.b < 1.0f)
		{
			m_col.r += 0.1f;
			m_col.g += 0.1f;
			m_col.b += 0.1f;
		}
		else if (!m_bPress && m_col.r > 0.2f && m_col.g > 0.2f && m_col.b > 0.2f)
		{
			m_col.r -= 0.1f;
			m_col.g -= 0.1f;
			m_col.b -= 0.1f;
		}
		m_nChangeCnt = 0;

	}
}
