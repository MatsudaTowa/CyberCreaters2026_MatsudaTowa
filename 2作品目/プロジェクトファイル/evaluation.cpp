//=============================================
//
//評価[evaluation.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "evaluation.h"
#include "manager.h"

const std::string CEvaluation::TEX_EVALUATION_S = "data\\TEXTURE\\evaluation_S.png";
const std::string CEvaluation::TEX_EVALUATION_A = "data\\TEXTURE\\evaluation_A.png";
const std::string CEvaluation::TEX_EVALUATION_B = "data\\TEXTURE\\evaluation_B.png";
const std::string CEvaluation::TEX_EVALUATION_C = "data\\TEXTURE\\evaluation_C.png";

//=============================================
//コンストラクタ
//=============================================
CEvaluation::CEvaluation(int nPriority):CObject2D(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CEvaluation::~CEvaluation()
{
}

//=============================================
//初期化
//=============================================
HRESULT CEvaluation::Init()
{
	//親クラスの初期化を呼ぶ
	CObject2D::Init();

	//テクスチャ座標設定
	SetTexPos(D3DXVECTOR2(1.0f, 1.0f));

	//頂点設定
	SetVtx(1.0f, D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
	return S_OK;
}

//=============================================
//終了
//=============================================
void CEvaluation::Uninit()
{
	//親クラスの終了呼ぶ
	CObject2D::Uninit();
}

//=============================================
//更新
//=============================================
void CEvaluation::Update()
{
	//親クラスの更新呼ぶ
	CObject2D::Update();
}

//=============================================
//描画
//=============================================
void CEvaluation::Draw()
{
	//親クラスの描画呼ぶ
	CObject2D::Draw();
}

//=============================================
//生成
//=============================================
CEvaluation* CEvaluation::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, EVALUATION evaluation)
{
	CEvaluation* pEvaluation = new CEvaluation;

	// nullならnullを返す
	if (pEvaluation == nullptr) { return nullptr; }

	pEvaluation->SetPos(pos); //pos設定

	pEvaluation->SetSize(size); //サイズ設定

	//テクスチャ取得
	CTexture* pTexture = CManager::GetTexture();

	switch (evaluation)
	{
	case CEvaluation::EVALUATION::EVALUATION_S:
		pEvaluation->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEX_EVALUATION_S))); //テクスチャの設定
		break;
	case CEvaluation::EVALUATION::EVALUATION_A:
		pEvaluation->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEX_EVALUATION_A))); //テクスチャの設定
		break;
	case CEvaluation::EVALUATION::EVALUATION_B:
		pEvaluation->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEX_EVALUATION_B))); //テクスチャの設定
		break;
	case CEvaluation::EVALUATION::EVALUATION_C:
		pEvaluation->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEX_EVALUATION_C))); //テクスチャの設定
		break;
	default:
		break;
	}

	pEvaluation->SetType(OBJECT_TYPE_EVALUATION); //オブジェクトのタイプ設定

	pEvaluation->Init();

	return pEvaluation;
}
