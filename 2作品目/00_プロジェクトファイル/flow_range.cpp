//=============================================
//
//プレイヤーの集中攻撃の範囲[flow_range.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "flow_range.h"
#include "manager.h"
#include "colision.h"
#include "enemy.h"
#include "flow.h"
#include "lockon.h"

//=============================================
//コンストラクタ
//=============================================
CFlow_Range::CFlow_Range(int nPriority):CObject3D(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CFlow_Range::~CFlow_Range()
{
}

//=============================================
//初期化
//=============================================
HRESULT CFlow_Range::Init()
{
	//親クラスの初期化
	CObject3D::Init();

	//頂点設定
	SetVtxFlow_Range(D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(0.5f, 0.0f, 0.0f, 0.7f));
	return S_OK;
}

//=============================================
//終了
//=============================================
void CFlow_Range::Uninit()
{
	//親クラスの終了
	CObject3D::Uninit();
}

//=============================================
//更新
//=============================================
void CFlow_Range::Update()
{
	//親クラスの更新
	CObject3D::Update();

	//マウスの情報取得
	CInputMouse* pMouse = CManager::GetMouse();

	CInputPad* pPad = CManager::GetPad();

	//頂点設定
	SetVtxFlow_Range(D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(0.5f, 0.0f, 0.0f, 0.7f));

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(CEnemy::ENEMY_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//ヌルポインタじゃなければ
			//タイプ取得
			CObject::OBJECT_TYPE type = pObj->GetType();

			//敵との当たり判定
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_ENEMY)
			{
				CEnemy* pEnemy = (CEnemy*)pObj;

				CColision::COLISION colision = CColision::CheckFlow_RangeColision(GetPos(),m_Minpos,m_Maxpos,pEnemy->GetPos(),pEnemy->GetMinPos(),pEnemy->GetMaxPos());

				if (colision != CColision::COLISION::COLISON_NONE)
				{
					pEnemy->LockOn();

					if (pMouse->GetRelease(0) || pPad->GetRelease(CInputPad::JOYKEY::JOYKEY_X))
					{
						pEnemy->LockOn_Flow();
					}
				}
			}
		}
	}
	if (pMouse->GetRelease(0) || pPad->GetRelease(CInputPad::JOYKEY::JOYKEY_X))
	{
		//CFlow* pFlow = CFlow::Create(D3DXVECTOR3(pEnemy->GetPos().x, pEnemy->GetPos().y + 5.0f, -10.0f),
		//	D3DXVECTOR3(20.0f, 20.0f, 0.0f), 90, 1, CFlow::FLOW_TYPE::FLOW_TYPE_PLAYER);
		Uninit();
	}
}

//=============================================
//描画
//=============================================
void CFlow_Range::Draw()
{
	//親クラスの描画
	CObject3D::Draw();
}

//=============================================
//生成
//=============================================
CFlow_Range* CFlow_Range::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,D3DXVECTOR3 Minpos, D3DXVECTOR3 Maxpos)
{
	CFlow_Range* pFlow_Range = new CFlow_Range;
	//nullならnullを返す
	if (pFlow_Range == nullptr) { return nullptr; }

	pFlow_Range->SetPos(pos); //pos設定
	pFlow_Range->m_Minpos = Minpos; //最小値代入
	pFlow_Range->m_Maxpos = Maxpos; //最大値代入
	pFlow_Range->SetRot(rot); //方向設定

	pFlow_Range->SetType(OBJECT_TYPE_FLOW_RANGE); //タイプ設定

	pFlow_Range->Init(); //初期化

	return pFlow_Range;
}

//========================================
//最小値取得
//========================================
D3DXVECTOR3& CFlow_Range::GetMinPos()
{
	return m_Minpos;
}

//========================================
//最大値取得
//========================================
D3DXVECTOR3& CFlow_Range::GetMaxPos()
{
	return m_Maxpos;
}

//========================================
//専用の頂点生成
//========================================
void CFlow_Range::SetVtxFlow_Range(D3DXVECTOR3 nor, D3DCOLOR col)
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

//========================================
//サイズ変更
//========================================
void CFlow_Range::SizeUp(bool bWay)
{
	if (bWay == true)
	{//右向きだったら
		m_Maxpos.x += 1.5f;
	}
	else if (bWay == false)
	{//左向きだったら
		m_Minpos.x -= 1.5f;
	}
}
