//=============================================
//
//数字管理「number.cpp」
// Author松田永久
//
//=============================================
#include "number.h"
#include "manager.h"

//texパス
const std::string CNumber::TEXTURE_NAME = "data\\TEXTURE\\number_000.png";

//=============================================
//コンストラクタ
//=============================================
CNumber::CNumber(int nPriority) : CObject2D(nPriority), m_mintex(D3DXVECTOR2(0.0f,0.0f)),m_maxtex(D3DXVECTOR2(0.0f, 0.0f)), m_col(D3DXCOLOR(0.0f,0.0f,0.0f,0.0f))
{
}

//=============================================
//デストラクタ
//=============================================
CNumber::~CNumber()
{
}

//=============================================
//初期化
//=============================================
HRESULT CNumber::Init()
{
	//親クラスの初期化
	CObject2D::Init();

	//頂点生成
	NumberVtx();

	return S_OK;
}

//=============================================
//終了
//=============================================
void CNumber::Uninit()
{
	//親クラスの終了
	CObject2D::Uninit();
}

//=============================================
//更新
//=============================================
void CNumber::Update()
{
	//親クラスの更新
	CObject2D::Update();

	//頂点生成
	NumberVtx();
}

//=============================================
//描画
//=============================================
void CNumber::Draw()
{
	//親クラスの描画
	CObject2D::Draw();
}

//=============================================
//生成
//=============================================
CNumber* CNumber::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	CTexture* pTexture = CManager::GetTexture();
	CNumber* pNumber = new CNumber;

	// nullならnullを返す
	if (pNumber == nullptr) { return nullptr; }

	pNumber->SetPos(pos); //pos設定

	pNumber->SetSize(size); //size設定

	pNumber->SetType(OBJECT_TYPE_NUMBER); //タイプ設定

	pNumber->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME))); //テクスチャ設定

	pNumber->Init(); //初期化処理

	return pNumber;
}

//=============================================
//数字の設定
//=============================================
void CNumber::SetNumber(float fNumPos1, float fNumPos2, D3DXCOLOR col)
{
	m_mintex.x = fNumPos1;
	m_maxtex.x = fNumPos2;
	m_col =col;
}

//=============================================
//数字専用の頂点生成
//=============================================
void CNumber::NumberVtx()
{
	CRenderer* pRender = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();

	LPDIRECT3DVERTEXBUFFER9 pBuff = GetVtxBuff();

	if (pBuff == nullptr)
	{
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &pBuff, NULL);
	}
	VERTEX_2D* pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得
	pBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(GetPos().x-GetSize().x
		, GetPos().y -GetSize().y
		, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(GetPos().x + GetSize().x
		, GetPos().y -GetSize().y
		, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(GetPos().x -GetSize().x
		, GetPos().y + GetSize().y
		, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(GetPos().x+GetSize().x
		, GetPos().y + GetSize().y
		, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	pVtx[0].tex = D3DXVECTOR2(m_mintex.x, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_maxtex.x, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(m_mintex.x, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_maxtex.x, 1.0f);

	//アンロック
	pBuff->Unlock();

	SetVtxBuff(pBuff);
}
