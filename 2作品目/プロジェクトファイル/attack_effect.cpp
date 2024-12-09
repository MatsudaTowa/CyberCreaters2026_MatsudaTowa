//=============================================
//
//攻撃エフェクト[attack_effect.h]
//Auther Matsuda Towa
//
//=============================================
#include "attack_effect.h"
#include "manager.h"
//画像分割数
const int CAttack_Effect::TEX_SPLIT_X = 1;
//画像分割数
const int CAttack_Effect::TEX_SPLIT_Y = 1;
//画像切り替わりカウント
const int CAttack_Effect::ANIMATION_FRAME = 5;

//texパス
const std::string CAttack_Effect::TEXTURE_NAME = "data\\TEXTURE\\effect000.jpg";

//テクスチャ初期化
LPDIRECT3DTEXTURE9 CAttack_Effect::m_pTextureTemp = nullptr;

//=============================================
//コンストラクタ
//=============================================
CAttack_Effect::CAttack_Effect(int nPriority):CBillboard(nPriority)
{
	SetSize(D3DXVECTOR3(0.0f,0.0f,0.0f));
}

//=============================================
//デストラクタ
//=============================================
CAttack_Effect::~CAttack_Effect()
{
}

//=============================================
//初期化
//=============================================
HRESULT CAttack_Effect::Init()
{
	//頂点設定
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f), m_col);
	return S_OK;
}

//=============================================
//終了
//=============================================
void CAttack_Effect::Uninit()
{
 	CObject3D::Uninit();
}

//=============================================
//更新
//=============================================
void CAttack_Effect::Update()
{
	CObject3D::Update();
	//頂点設定
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f), m_col);
}

//=============================================
//描画
//=============================================
void CAttack_Effect::Draw()
{
	CRenderer* pRender = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
	//zの比較方法変更
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	//zバッファに書き込まない
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	//αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//
	CBillboard::Draw();

	//zの比較方法変更
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	//zバッファに書き込まない
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================
//拡大
//=============================================
void CAttack_Effect::SizeChange(float fRatioFrame)
{
	float fAddSize = m_DefaultSize.x * fRatioFrame;
	D3DXVECTOR3 size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//if (size.x < m_DefaultSize.x)
	{
		size.x = fAddSize;
		size.y = fAddSize;
	}

	SetSize(size);

}

//=============================================
//サイズリセット
//=============================================
void CAttack_Effect::SizeReset()
{
	SetSize(m_DefaultSize);
}

//=============================================
//生成
//=============================================
CAttack_Effect* CAttack_Effect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col)
{
	CAttack_Effect* pAttack_Effect = new CAttack_Effect;

	// nullならnullを返す
	if (pAttack_Effect == nullptr) { return nullptr; }

	//テクスチャ取得
	CTexture* pTexture = CManager::GetTexture();

	pAttack_Effect->SetPos(pos); //pos設定

	pAttack_Effect->m_DefaultSize = size; //サイズ設定

	pAttack_Effect->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME))); //テクスチャの設定

	pAttack_Effect->m_col = col; //カラーの設定

	pAttack_Effect->SetType(OBJECT_TYPE_ATTACK_EFFECT); //オブジェクトのタイプ設定

	pAttack_Effect->Init(); //エフェクトの初期化処理

	return pAttack_Effect;
}
