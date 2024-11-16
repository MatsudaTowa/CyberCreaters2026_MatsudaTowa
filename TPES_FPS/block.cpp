//=============================================
//
//3DTemplate[block.h]
//Auther Matsuda Towa
//
//=============================================
#include "block.h"
#include "manager.h"
#include "player.h"

//モデルパス
const std::string CBlock::MODEL_NAME = "data\\MODEL\\Container.x";
const std::string CBlock::WOOD_MODEL_NAME = "data\\MODEL\\wood.x";
const std::string CBlock::AZUMAYA_MODEL_NAME = "data\\MODEL\\azumaya.x";
const std::string CBlock::DANGOYA_MODEL_NAME = "data\\MODEL\\dangoya.x";
const std::string CBlock::MESH_MODEL_NAME = "data\\MODEL\\mesh.x";

//テクスチャ初期化
LPDIRECT3DTEXTURE9 CBlock::m_pTextureTemp = nullptr;

LPD3DXBUFFER CBlock::m_pBuffMat = nullptr;

LPD3DXMESH CBlock::m_pMesh = nullptr;

DWORD CBlock::m_dwNumMat = 0;

//=============================================
//コンストラクタ
//=============================================
CBlock::CBlock(int nPriority):CObjectX(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CBlock::~CBlock()
{
}

//=============================================
//初期化
//=============================================
HRESULT CBlock::Init()
{
	//親クラスの初期化処理
	CObjectX::Init();
	return S_OK;
}

//=============================================
//終了
//=============================================
void CBlock::Uninit()
{
	//親クラスの終了処理
	CObjectX::Uninit();
}

//=============================================
//更新
//=============================================
void CBlock::Update()
{
	//親クラスの更新処理
	CObjectX::Update();
}

//=============================================
//描画
//=============================================
void CBlock::Draw()
{
	//親クラスの描画処理
	CObjectX::Draw();
}

//=============================================
//ブロック生成
//=============================================
CBlock* CBlock::Create(BLOCKTYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife, bool bBreak)
{
	CBlock* pBlock = new CBlock;

	//nullならnullを返す
	if (pBlock == nullptr) {return nullptr;}
	
	CModel* pModel = CManager::GetModel();
	CTexture* pTex = CManager::GetTexture();

	pBlock->m_type = type;
	pBlock->SetPos(pos); //pos設定
	pBlock->SetRot(rot); //pos設定
	pBlock->m_nLife = nLife; //寿命代入
	pBlock->m_bBreak = bBreak; //壊せるかどうか
	//pBlock->BindTexture(m_pTextureTemp);

	switch (pBlock->m_type)
	{
	case CBlock::BLOCKTYPE::BLOCKTYPE_DEFAULT:
		//Xファイル読み込み
		pBlock->BindXFile(pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).pBuffMat,
			pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).dwNumMat,
			pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).pMesh);
			break;
	case CBlock::BLOCKTYPE::BLOCKTYPE_WOOD:
		//Xファイル読み込み
		pBlock->BindXFile(pModel->GetModelInfo(pModel->Regist(&WOOD_MODEL_NAME)).pBuffMat,
			pModel->GetModelInfo(pModel->Regist(&WOOD_MODEL_NAME)).dwNumMat,
			pModel->GetModelInfo(pModel->Regist(&WOOD_MODEL_NAME)).pMesh);
		break;
	case CBlock::BLOCKTYPE::BLOCKTYPE_AZUMAYA:
		//Xファイル読み込み
		pBlock->BindXFile(pModel->GetModelInfo(pModel->Regist(&AZUMAYA_MODEL_NAME)).pBuffMat,
			pModel->GetModelInfo(pModel->Regist(&AZUMAYA_MODEL_NAME)).dwNumMat,
			pModel->GetModelInfo(pModel->Regist(&AZUMAYA_MODEL_NAME)).pMesh);
		break;
	case CBlock::BLOCKTYPE::BLOCKTYPE_DANGOYA:
		//Xファイル読み込み
		pBlock->BindXFile(pModel->GetModelInfo(pModel->Regist(&DANGOYA_MODEL_NAME)).pBuffMat,
			pModel->GetModelInfo(pModel->Regist(&DANGOYA_MODEL_NAME)).dwNumMat,
			pModel->GetModelInfo(pModel->Regist(&DANGOYA_MODEL_NAME)).pMesh);
		break;
	case CBlock::BLOCKTYPE::BLOCKTYPE_MESH:
		//Xファイル読み込み
		pBlock->BindXFile(pModel->GetModelInfo(pModel->Regist(&MESH_MODEL_NAME)).pBuffMat,
			pModel->GetModelInfo(pModel->Regist(&MESH_MODEL_NAME)).dwNumMat,
			pModel->GetModelInfo(pModel->Regist(&MESH_MODEL_NAME)).pMesh);
		D3DXMATERIAL* pMat; //マテリアル
		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
		//pBlock->BindTexture((pTex->GetAddress(pTex->Regist(&pMat->pTextureFilename()))); //テクスチャ設定
		break;
	default:
		break;
	}

	pBlock->SetType(OBJECT_TYPE_BLOCK); //タイプ設定
	pBlock->Init();
	
	return pBlock;
}