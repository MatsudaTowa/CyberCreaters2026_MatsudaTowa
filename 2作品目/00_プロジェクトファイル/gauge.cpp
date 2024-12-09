//=============================================
//
//ゲージ管理[gauge.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "gauge_fream.h"
#include "gauge.h"
#include "manager.h"
#include "player.h"

//ゲージの最大値
const float CGauge::MAX_GAUGE_WIDE = 350.0f;

//=============================================
//コンストラクタ
//=============================================
CGauge::CGauge(int nPriority):CObject2D(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CGauge::~CGauge()
{
}

//=============================================
//初期化
//=============================================
HRESULT CGauge::Init()
{
    //親クラスの初期化を呼ぶ
    CObject2D::Init();

	//テクスチャ座標設定
	SetTexPos(D3DXVECTOR2(1.0f, 1.0f));

    //頂点設定
	SetGaugeVtx(1.0f, m_col);

    return S_OK;
}

//=============================================
//終了
//=============================================
void CGauge::Uninit()
{
    //親クラスの終了呼ぶ
    CObject2D::Uninit();
}

//=============================================
//更新
//=============================================
void CGauge::Update()
{
    //親クラスの更新呼ぶ
    CObject2D::Update();

	//頂点設定
	SetGaugeVtx(1.0f, m_col);
}

//=============================================
//描画
//=============================================
void CGauge::Draw()
{
    //親クラスの描画呼ぶ
    CObject2D::Draw();
}

//=============================================
//ゲージ増加処理
//=============================================
void CGauge::AddGauge()
{
	//自分自身のサイズ取得
   D3DXVECTOR2 size = GetSize();

   size.x += 1.5f;

   //サイズ代入
   SetSize(size);
}

//=============================================
//ゲージ減少処理
//=============================================
void CGauge::SubGauge(float fCost)
{
	//自分自身のサイズ取得
	D3DXVECTOR2 size = GetSize();

	size.x -= fCost;

	//サイズ代入
	SetSize(size);
}

//=============================================
//ゲージの頂点生成
//=============================================
void CGauge::SetGaugeVtx(float rhw, D3DCOLOR col)
{
    CRenderer* pRender = CManager::GetRenderer();

    LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();

    if (GetVtxBuff() == nullptr)
    {
        pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &GetVtxBuff(), NULL);
    }
    VERTEX_2D* pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得
	GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(GetPos().x
		, GetPos().y - GetSize().y
		, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(GetPos().x + GetSize().x
		, GetPos().y - GetSize().y
		, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(GetPos().x
		, GetPos().y + GetSize().y
		, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(GetPos().x + GetSize().x
		, GetPos().y + GetSize().y
		, 0.0f);

	//rhwの設定
	pVtx[0].rhw = rhw;
	pVtx[1].rhw = rhw;
	pVtx[2].rhw = rhw;
	pVtx[3].rhw = rhw;

	//頂点カラーの設定
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//アンロック
	GetVtxBuff()->Unlock();
}

//=============================================
//生成
//=============================================
CGauge* CGauge::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, GAUGE_TYPE type, D3DXCOLOR col)
{
    CGauge* pGauge = nullptr;

	switch (type)
	{
	case GAUGE_TYPE_SLASH:
		pGauge = new CGauge_Slash;
		pGauge->SetType(OBJECT_TYPE_GAUGE_SLASH); //タイプ設定
		break;
	case GAUGE_TYPE_LIFE:
		pGauge = new CGauge_Life;
		pGauge->SetType(OBJECT_TYPE_GAUGE_LIFE); //タイプ設定
		break;
	default:
		assert(false);
		break;
	}

    // nullならnullを返す
    if (pGauge == nullptr) { return nullptr; }

    pGauge->SetPos(pos); //pos設定

    pGauge->SetSize(size); //size設定

	pGauge->m_type = type; //ゲージのタイプ設定

	pGauge->m_col = col; //カラー設定

    //pGauge->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));

    pGauge->Init();

	return pGauge;
}

//=============================================
//コンストラクタ
//=============================================
CGauge_Slash::CGauge_Slash(int nPriority):CGauge(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CGauge_Slash::~CGauge_Slash()
{
}

//=============================================
//初期化
//=============================================
HRESULT CGauge_Slash::Init()
{
	//親クラスの初期化
	CGauge::Init();

	return S_OK;
}

//=============================================
//終了
//=============================================
void CGauge_Slash::Uninit()
{
	//親クラスの終了
	CGauge::Uninit();
}

//=============================================
//更新
//=============================================
void CGauge_Slash::Update()
{
	//親クラスの更新
	CGauge::Update();

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//ヌルポインタじゃなければ
			//タイプ取得
			CObject::OBJECT_TYPE type = pObj->GetType();

			//敵との当たり判定
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
			{
				CPlayer* pPlayer = (CPlayer*)pObj;

				if (GetSize().x <= MAX_GAUGE_WIDE && pPlayer->m_OldPress != true &&pPlayer->m_Attack != CPlayer::PLAYER_ATTACK_MELEE)
				{//最大値以下で左クリック押されてなかったら加算
					AddGauge();
				}
			}
		}
	}
}

//=============================================
//描画
//=============================================
void CGauge_Slash::Draw()
{
	//親クラスの描画
	CGauge::Draw();
}

//=============================================
//コンストラクタ
//=============================================
CGauge_Life::CGauge_Life(int nPriority):CGauge(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CGauge_Life::~CGauge_Life()
{
}

//=============================================
//初期化
//=============================================
HRESULT CGauge_Life::Init()
{
	//親クラスの初期化
	CGauge::Init();

	return S_OK;
}

//=============================================
//終了
//=============================================
void CGauge_Life::Uninit()
{
	//親クラスの終了
	CGauge::Uninit();
}

//=============================================
//更新
//=============================================
void CGauge_Life::Update()
{
	//親クラスの更新
	CGauge::Update();
}

//=============================================
//描画
//=============================================
void CGauge_Life::Draw()
{
	//親クラスの描画
	CGauge::Draw();
}

