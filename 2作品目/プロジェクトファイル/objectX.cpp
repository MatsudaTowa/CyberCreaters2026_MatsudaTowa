//=============================================
//
//3DTemplate[objectX.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "objectX.h"
#include "renderer.h"
#include "manager.h"
#include "colision_view.h"
//=============================================
//コンストラクタ
//=============================================
CObjectX::CObjectX(int nPriority):CObject(nPriority),m_col(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))
{
	m_pBuffMat = nullptr;
	m_pMesh = nullptr;

	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		m_pTexture[nCnt] = nullptr;
	}
}

//=============================================
//デストラクタ
//=============================================
CObjectX::~CObjectX()
{
}

//=============================================
//初期化
//=============================================
HRESULT CObjectX::Init()
{

	return S_OK;
}

//=============================================
//終了
//=============================================
void CObjectX::Uninit()
{
	//メッシュの破棄
	if (m_pMesh != nullptr)
	{
		m_pMesh->Release();
		m_pMesh = nullptr;
	}

	//マテリアルの破棄
	if (m_pBuffMat != nullptr)
	{
		m_pBuffMat->Release();
		m_pBuffMat = nullptr;
	}

	Release();

}

//=============================================
//更新
//=============================================
void CObjectX::Update()
{
}

//=============================================
//描画
//=============================================
void CObjectX::Draw()
{
	if (m_pMesh != nullptr && m_pBuffMat != nullptr)
	{
		//デバイスの取得
		CRenderer* pRender = CManager::GetRenderer();
		LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
		D3DMATERIAL9 matDef; //現在のマテリアルの保存
		D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス

		//マトリックスの初期化
		D3DXMatrixIdentity(&m_mtxWorld);

		//αテストを有効
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		D3DXMATERIAL* pMat; //マテリアル

		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
		{
			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//テクスチャの設定
			pDevice->SetTexture(0, m_pTexture[nCntMat]);

			//パーツの設定
			m_pMesh->DrawSubset(nCntMat);
		}

		//// ディフューズカラーを変更
		//pMat->MatD3D.Diffuse = D3DXCOLOR(pMat->MatD3D.Diffuse.r, pMat->MatD3D.Diffuse.g, pMat->MatD3D.Diffuse.b, pMat->MatD3D.Diffuse.a);

		//αテストを無効に
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

		//現在を取得
		pDevice->GetMaterial(&matDef);

		//保存してたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
	
}

//=============================================
//描画(カラー変更)
//=============================================
void CObjectX::Draw(D3DXCOLOR col)
{
	if (m_pMesh != nullptr && m_pBuffMat != nullptr)
	{
		//デバイスの取得
		CRenderer* pRender = CManager::GetRenderer();
		LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
		D3DMATERIAL9 matDef; //現在のマテリアルの保存
		D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス

		//マトリックスの初期化
		D3DXMatrixIdentity(&m_mtxWorld);

		//αテストを有効
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		D3DXMATERIAL* pMat; //マテリアル

		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
		{
			//今描画するマテリアル情報格納
			D3DMATERIAL9 DrawMat = pMat[nCntMat].MatD3D;

			DrawMat.Diffuse = col;

			//マテリアルの設定
			pDevice->SetMaterial(&DrawMat);

			//テクスチャの設定
			pDevice->SetTexture(0, m_pTexture[nCntMat]);

			//パーツの設定
			m_pMesh->DrawSubset(nCntMat);

		}

		//αテストを無効に
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

		//現在を取得
		pDevice->GetMaterial(&matDef);

		//保存してたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}

}

//=============================================
//テクスチャ設定
//=============================================
void CObjectX::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		m_pTexture[nCnt] = pTex;
	}
}

//=============================================
//モデル設定
//=============================================
void CObjectX::BindXFile(LPD3DXBUFFER pBuffMat, DWORD dwNumMat, LPD3DXMESH pMesh)
{
	pBuffMat->AddRef();
	pMesh->AddRef();

	m_pBuffMat = pBuffMat;
	m_dwNumMat = dwNumMat;
	m_pMesh = pMesh;

	int nNumVtx; //頂点数
	DWORD sizeFVF; //頂点フォーマットのサイズ
	BYTE* pVtxBuff; //頂点バッファのポインタ

		//頂点数の取得
	nNumVtx = m_pMesh->GetNumVertices();
	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	m_minpos = D3DXVECTOR3(100000.0f, 1000000.0f, 1000000.0f); //モデルの最小位置
	m_maxpos = D3DXVECTOR3(-100000.0f, -1000000.0f, -100000.0f); //モデルの最大位置

	//頂点バッファのロック
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		//頂点座標の代入
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		//x座標の最大値最小値チェック
		if (vtx.x > m_maxpos.x)
		{
			m_maxpos.x = vtx.x;
		}
		if (vtx.x < m_minpos.x)
		{
			m_minpos.x = vtx.x;
		}

		//y座標の最大値最小値チェック
		if (vtx.y > m_maxpos.y)
		{
			m_maxpos.y = vtx.y;
		}
		if (vtx.y < m_minpos.y)
		{
			m_minpos.y = vtx.y;
		}

		//z座標の最大値最小値チェック
		if (vtx.z > m_maxpos.z)
		{
			m_maxpos.z = vtx.z;
		}
		if (vtx.z < m_minpos.z)
		{
			m_minpos.z = vtx.z;
		}

		// 次の頂点に進む
		pVtxBuff += sizeFVF;
	}

	m_pMesh->UnlockVertexBuffer();
}

//=============================================
//座標取得
//=============================================
D3DXVECTOR3& CObjectX::GetPos()
{
	return m_pos;
}

//=============================================
//方向取得
//=============================================
D3DXVECTOR3& CObjectX::GetRot()
{
	return m_rot;
}

//=============================================
//最小値取得
//=============================================
D3DXVECTOR3& CObjectX::GetMinPos()
{
	if (m_pMesh != nullptr && m_pBuffMat != nullptr)
	{
		int nNumVtx; //頂点数
		DWORD sizeFVF; //頂点フォーマットのサイズ
		BYTE* pVtxBuff; //頂点バッファのポインタ

			//頂点数の取得
		nNumVtx = m_pMesh->GetNumVertices();
		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

		m_minpos = D3DXVECTOR3(100000.0f, 1000000.0f, 1000000.0f); //モデルの最小位置
		m_maxpos = D3DXVECTOR3(-100000.0f, -1000000.0f, -100000.0f); //モデルの最大位置

		//頂点バッファのロック
		m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//頂点座標の代入
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//x座標の最小値チェック
			if (vtx.x < m_minpos.x)
			{
				m_minpos.x = vtx.x;
			}

			//y座標の最小値チェック
			if (vtx.y < m_minpos.y)
			{
				m_minpos.y = vtx.y;
			}

			//z座標の最小値チェック
			if (vtx.z < m_minpos.z)
			{
				m_minpos.z = vtx.z;
			}

			// 次の頂点に進む
			pVtxBuff += sizeFVF;
		}

		m_pMesh->UnlockVertexBuffer();
	}
	
	return m_minpos;
}

//=============================================
//最大値取得
//=============================================
D3DXVECTOR3& CObjectX::GetMaxPos()
{
	if (m_pMesh != nullptr && m_pBuffMat != nullptr)
	{
		int nNumVtx; //頂点数
		DWORD sizeFVF; //頂点フォーマットのサイズ
		BYTE* pVtxBuff; //頂点バッファのポインタ

			//頂点数の取得
		nNumVtx = m_pMesh->GetNumVertices();
		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

		m_minpos = D3DXVECTOR3(100000.0f, 1000000.0f, 1000000.0f); //モデルの最小位置
		m_maxpos = D3DXVECTOR3(-100000.0f, -1000000.0f, -100000.0f); //モデルの最大位置

	//頂点バッファのロック
		m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//頂点座標の代入
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//x座標の最大値チェック
			if (vtx.x > m_maxpos.x)
			{
				m_maxpos.x = vtx.x;
			}

			//y座標の最大値チェック
			if (vtx.y > m_maxpos.y)
			{
				m_maxpos.y = vtx.y;
			}

			//z座標の最大値チェック
			if (vtx.z > m_maxpos.z)
			{
				m_maxpos.z = vtx.z;
			}
			// 次の頂点に進む
			pVtxBuff += sizeFVF;
		}

		m_pMesh->UnlockVertexBuffer();
	}
	
	return m_maxpos;
}

//=============================================
//メッシュ情報取得
//=============================================
LPD3DXMESH& CObjectX::GetpMesh()
{
	return m_pMesh;
}

//=============================================
//マテリアル情報取得
//=============================================
LPD3DXBUFFER& CObjectX::GetpBuffMat()
{
	return m_pBuffMat;
}

//=============================================
//マテリアル数取得
//=============================================
DWORD& CObjectX::GetNumMat()
{
	return m_dwNumMat;
}

//=============================================
//ワールドマトリックス取得
//=============================================
D3DXMATRIX& CObjectX::GetMtxWorld()
{
	return m_mtxWorld;
}

//=============================================
//カラー取得
//=============================================
D3DXCOLOR& CObjectX::GetCol()
{
	return m_col;
}
