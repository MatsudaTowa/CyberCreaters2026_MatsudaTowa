//=============================================
//
//ゲージフレーム管理[gauge_fream.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "gauge_fream.h"
#include "manager.h"
#include "gauge.h"

//texパス
const std::string CGauge_Fream::TEXTURE_NAME = "data\\TEXTURE\\slashgauge_frame.png";

//=============================================
//コンストラクタ
//=============================================
CGauge_Fream::CGauge_Fream(int nPriority):CObject2D(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CGauge_Fream::~CGauge_Fream()
{
}

//=============================================
//初期化
//=============================================
HRESULT CGauge_Fream::Init()
{
    //親クラスの初期化を呼ぶ
    CObject2D::Init();

    //テクスチャ座標設定
    SetTexPos(D3DXVECTOR2(1.0f,1.0f));

    //頂点設定
    SetVtx(1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

    //ゲージ生成
    CGauge::Create(D3DXVECTOR3(GetPos().x - GetSize().x * 0.5f,GetPos().y - 10.0f,GetPos().z),D3DXVECTOR2(0.0f, 30.0f),CGauge::GAUGE_TYPE_SLASH,D3DXCOLOR(1.0f,0.5f,0.0f,1.0f));

    return S_OK;
}

//=============================================
//終了
//=============================================
void CGauge_Fream::Uninit()
{
    //親クラスの終了呼ぶ
    CObject2D::Uninit();
}

//=============================================
//更新
//=============================================
void CGauge_Fream::Update()
{
    //親クラスの更新呼ぶ
    CObject2D::Update();
}

//=============================================
//描画
//=============================================
void CGauge_Fream::Draw()
{
    //親クラスの描画呼ぶ
    CObject2D::Draw();
}

//=============================================
//生成
//=============================================
CGauge_Fream* CGauge_Fream::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
    CTexture* pTexture = CManager::GetTexture();
    CGauge_Fream* pGauge_Fream = new CGauge_Fream;

    // nullならnullを返す
    if(pGauge_Fream == nullptr) {return nullptr;}

    pGauge_Fream->SetPos(pos); //pos設定

    pGauge_Fream->SetSize(size); //size設定

    pGauge_Fream->SetType(OBJECT_TYPE_GAUGE_FREAM); //タイプ設定

    pGauge_Fream->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME))); //テクスチャ設定

    pGauge_Fream->Init(); //初期化処理

    return pGauge_Fream;
}
