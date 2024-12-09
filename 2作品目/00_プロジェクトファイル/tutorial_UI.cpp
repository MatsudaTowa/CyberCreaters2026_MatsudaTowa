//=============================================
//
//チュートリアルUI[tutorial_UI.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "tutorial_UI.h"
#include "manager.h"

const std::string CTutorial_UI::TEXTURE_NAME_MOVE_PAD = "data\\TEXTURE\\tutorial_move_pad.png";
const std::string CTutorial_UI::TEXTURE_NAME_MOVE_KEYBOARD = "data\\TEXTURE\\tutorial_move_keyboard.png";
const std::string CTutorial_UI::TEXTURE_NAME_MELEE_PAD = "data\\TEXTURE\\tutorial_melee_pad_B.png";
const std::string CTutorial_UI::TEXTURE_NAME_MELEE_MOUSE = "data\\TEXTURE\\tutorial_melee_mouse_R.png";
const std::string CTutorial_UI::TEXTURE_NAME_SLASH_PAD = "data\\TEXTURE\\tutorial_slash_pad_X.png";
const std::string CTutorial_UI::TEXTURE_NAME_SLASH_MOUSE = "data\\TEXTURE\\tutorial_slash_mouse_L.png";
const std::string CTutorial_UI::TEXTURE_NAME_GAUGE = "data\\TEXTURE\\tutorial_gauge.png";

//=============================================
//コンストラクタ
//=============================================
CTutorial_UI::CTutorial_UI(int nPriority):CBillboard(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CTutorial_UI::~CTutorial_UI()
{
}

//=============================================
//初期化
//=============================================
HRESULT CTutorial_UI::Init()
{
	//親クラスの初期化
	CObject3D::Init();
	//頂点設定
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.9f));
	return S_OK;
}

//=============================================
//終了
//=============================================
void CTutorial_UI::Uninit()
{
	//親クラスの終了
	CObject3D::Uninit();
}

//=============================================
//更新
//=============================================
void CTutorial_UI::Update()
{
	//親クラスの更新
	CObject3D::Update();

	//テクスチャ取得
	CTexture* pTexture = CManager::GetTexture();

	CInputPad* pPad = CManager::GetPad();

	switch (m_type)
	{
	case CTutorial_UI::TUTORIAL_TYPE::TUTORIAL_TYPE_MOVE:
		if (pPad->GetConnet())
		{
			BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME_MOVE_PAD))); //テクスチャの設定
		}
		else if (!pPad->GetConnet())
		{
			BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME_MOVE_KEYBOARD))); //テクスチャの設定
		}
		break;
	case CTutorial_UI::TUTORIAL_TYPE::TUTORIAL_TYPE_MELEE:
		if (pPad->GetConnet())
		{
			BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME_MELEE_PAD))); //テクスチャの設定
		}
		else if (!pPad->GetConnet())
		{
			BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME_MELEE_MOUSE))); //テクスチャの設定
		}
		break;
	case CTutorial_UI::TUTORIAL_TYPE::TUTORIAL_TYPE_SLASH:
		if (pPad->GetConnet())
		{
			BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME_SLASH_PAD))); //テクスチャの設定
		}
		else if (!pPad->GetConnet())
		{
			BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME_SLASH_MOUSE))); //テクスチャの設定
		}
		break;
	case CTutorial_UI::TUTORIAL_TYPE::TUTORIAL_TYPE_GAUGE:
		BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME_GAUGE))); //テクスチャの設定
		break;
	default:
		break;
	}
}

//=============================================
//描画
//=============================================
void CTutorial_UI::Draw()
{
	//親クラスの描画
	CObject3D::Draw();
}

//=============================================
//生成
//=============================================
CTutorial_UI* CTutorial_UI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TUTORIAL_TYPE type)
{
	CTutorial_UI* pTutorialUI = new CTutorial_UI;

	// nullならnullを返す
	if (pTutorialUI == nullptr) { return nullptr; }

	pTutorialUI->SetPos(pos); //pos設定

	pTutorialUI->SetSize(size); //サイズ設定

	//テクスチャ取得
	CTexture* pTexture = CManager::GetTexture();

	CInputPad* pPad = CManager::GetPad();

	pTutorialUI->m_type = type;

	switch (pTutorialUI->m_type)
	{
	case CTutorial_UI::TUTORIAL_TYPE::TUTORIAL_TYPE_MOVE:
		if (pPad->GetConnet())
		{
			pTutorialUI->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME_MOVE_PAD))); //テクスチャの設定
		}
		else if (!pPad->GetConnet())
		{
			pTutorialUI->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME_MOVE_KEYBOARD))); //テクスチャの設定
		}
		break;
	case CTutorial_UI::TUTORIAL_TYPE::TUTORIAL_TYPE_MELEE:
		if (pPad->GetConnet())
		{
			pTutorialUI->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME_MELEE_PAD))); //テクスチャの設定
		}
		else if (!pPad->GetConnet())
		{
			pTutorialUI->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME_MELEE_MOUSE))); //テクスチャの設定
		}
		break;
	case CTutorial_UI::TUTORIAL_TYPE::TUTORIAL_TYPE_SLASH:
		if (pPad->GetConnet())
		{
			pTutorialUI->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME_SLASH_PAD))); //テクスチャの設定
		}
		else if (!pPad->GetConnet())
		{
			pTutorialUI->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME_SLASH_MOUSE))); //テクスチャの設定
		}
		break;	
	case CTutorial_UI::TUTORIAL_TYPE::TUTORIAL_TYPE_GAUGE:
		pTutorialUI->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME_GAUGE))); //テクスチャの設定
		break;
	default:
		break;
	}

	pTutorialUI->SetType(OBJECT_TYPE_TUTORIAL_UI); //オブジェクトのタイプ設定

	pTutorialUI->Init();

	return pTutorialUI;
}
