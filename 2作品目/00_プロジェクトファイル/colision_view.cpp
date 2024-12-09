//=============================================
//
//当たり判定可視化[colision_view.h]
//Auther Matsuda Towa
//
//=============================================
#include "colision_view.h"
#include "manager.h"

//=============================================
//コンストラクタ
//=============================================
CColision_View::CColision_View(int nPriority):CObject3D(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CColision_View::~CColision_View()
{
}

//=============================================
//初期化
//=============================================
HRESULT CColision_View::Init()
{
	//親クラスの初期化
	CObject3D::Init();
	return S_OK;
}

//=============================================
//終了
//=============================================
void CColision_View::Uninit()
{
	//親クラスの終了
	CObject3D::Uninit();
}

//=============================================
//更新
//=============================================
void CColision_View::Update()
{
	//親クラスの更新
	CObject3D::Update();

	//頂点座標
	SetVtxColision_View(D3DXVECTOR3(0.0f, 0.0f, -1.0f), m_Col);
}

//=============================================
//描画
//=============================================
void CColision_View::Draw()
{
	//親クラスの描画
	CObject3D::Draw();
}

//=============================================
//生成
//=============================================
CColision_View* CColision_View::Create(D3DXVECTOR3 pos, D3DXVECTOR3 MinPos, D3DXVECTOR3 MaxPos, D3DCOLOR col)
{
	CColision_View* pColision_View = new CColision_View();

	//nullならnullを返す
	if (pColision_View == nullptr) { return nullptr; }

	pColision_View->SetPos(pos); //pos代入
	pColision_View->m_Minpos = MinPos; //size代入
	pColision_View->m_Maxpos = MaxPos; //size代入
	pColision_View->m_Col = col; //カラー代入
	pColision_View->SetType(OBJECT_TYPE_COLISION_VIEW); //タイプ設定
	pColision_View->Init();

	return pColision_View;
}

//=============================================
//頂点生成
//=============================================
void CColision_View::SetVtxColision_View(D3DXVECTOR3 nor, D3DCOLOR col)
{
	CRenderer* pRender = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();

	LPDIRECT3DVERTEXBUFFER9 pBuff = GetVtxBuff();
	if (pBuff == nullptr)
	{
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &pBuff, NULL);
	}
	VERTEX_3D* pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	pBuff->Lock(0, 0, reinterpret_cast<void**>(&pVtx), 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_Minpos.x
		, m_Maxpos.y
		, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_Maxpos.x
		, m_Maxpos.y
		, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Minpos.x
		, m_Minpos.y
		, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_Maxpos.x
		, m_Minpos.y
		, 0.0f);

	//rhwの設定
	pVtx[0].nor =
		pVtx[1].nor =
		pVtx[2].nor =
		pVtx[3].nor = nor;

	//頂点カラーの設定
	pVtx[0].col =
		pVtx[1].col =
		pVtx[2].col =
		pVtx[3].col = col;

	//アンロック
	pBuff->Unlock();

	SetVtxBuff(pBuff);
}
