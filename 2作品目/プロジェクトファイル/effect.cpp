//=============================================
//
//3DTemplate[effect.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "effect.h"
#include "manager.h"

//画像分割数
const int CEffect::TEX_SPLIT_X = 1;
//画像分割数
const int CEffect::TEX_SPLIT_Y = 1;
//画像切り替わりカウント
const int CEffect::ANIMATION_FRAME = 5;

//texパス
const std::string CEffect::TEXTURE_NAME = "data\\TEXTURE\\120.png";

//テクスチャ初期化
LPDIRECT3DTEXTURE9 CEffect::m_pTextureTemp = nullptr;

//=============================================
//コンストラクタ
//=============================================
CEffect::CEffect(int nPriority):CBillboard(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CEffect::~CEffect()
{
}

//=============================================
//初期化
//=============================================
HRESULT CEffect::Init()
{
	//サイズ取得
	D3DXVECTOR3 size = GetSize();

	//対角線
	m_fLength = sqrtf(size.x * size.x + size.y * size.y);

	//角度
	m_fAngle = atan2f(size.x, size.y);

	////テクスチャ移動量取得
	//D3DXVECTOR2 tex_move = GetTexMove();
	//tex_move.x = 1.0f / (float)TEX_SPLIT_X;
	//tex_move.y = 1.0f / (float)TEX_SPLIT_Y;
	//テクスチャ移動量代入
	//SetTexMove(tex_move);

	//テクスチャ座標取得
	D3DXVECTOR2 tex_pos = GetTexPos();
	tex_pos.x = 1.0f;
	tex_pos.y = 1.0f;
	//テクスチャ座標代入
	SetTexPos(tex_pos);
	
	////アニメーションフレーム代入
	//SetAnimFrame(ANIMATION_FRAME);

	//頂点設定
	SetVtx(D3DXVECTOR3(0.0f,0.0f,-1.0f), m_col);
	return S_OK;
}

//=============================================
//終了
//=============================================
void CEffect::Uninit()
{
	CObject3D::Uninit();
}

//=============================================
//更新
//=============================================
void CEffect::Update()
{
	//テクスチャ情報取得
	D3DXVECTOR2 tex_pos = GetTexPos();
	//D3DXVECTOR2 tex_move = GetTexMove();
	//AnimationTex(tex_pos, tex_move);

	D3DXVECTOR3 size = GetSize();
	if (m_nLife > 0)
	{
		m_nLife--;
		size.x -= 0.2f;
		size.y -= 0.2f;
	}
	else
	{
		Release();
		return;
	}
	SetSize(size);
	//対角線
	m_fLength = sqrtf(size.x * size.x + size.y * size.y);

	//角度
	m_fAngle = atan2f(size.x, size.y);
	//頂点設定
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f), m_col);
}

//=============================================  
//描画
//=============================================
void CEffect::Draw()
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
//エフェクト生成
//=============================================
CEffect* CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, int nLife)
{
	CEffect* pEffect = new CEffect;

	// nullならnullを返す
	if (pEffect == nullptr) { return nullptr; }

	//テクスチャ取得
	CTexture* pTexture = CManager::GetTexture();

	pEffect->SetPos(pos); //pos設定

	pEffect->SetSize(size); //サイズ設定

	pEffect->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME))); //テクスチャの設定

	pEffect->m_col = col; //カラーの設定

	pEffect->m_nLife = nLife; //引数の寿命を代入

	pEffect->SetType(OBJECT_TYPE_EFFECT); //オブジェクトのタイプ設定

	pEffect->Init(); //エフェクトの初期化処理

	return pEffect;
}
