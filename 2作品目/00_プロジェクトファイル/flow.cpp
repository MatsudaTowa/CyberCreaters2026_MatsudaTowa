//=============================================
//
//集中斬撃[flow.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "flow.h"
#include "renderer.h"
#include"manager.h"

//テクスチャ初期化
LPDIRECT3DTEXTURE9 CFlow::m_pTextureTemp = nullptr;
const std::string CFlow::TEXTURE_NAME = "data\\TEXTURE\\flow_anim.png";

//=============================================
//コンストラクタ
//=============================================
CFlow::CFlow(int nPriority):CAttack_Manager(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CFlow::~CFlow()
{
}

//=============================================
//初期化
//=============================================
HRESULT CFlow::Init()
{
	//親クラスの初期化
	CAttack_Manager::Init();

	m_nDamageCnt = PLAYER_DAMAGE_FRAME; //最初にヒットさせるためにダメージのフレーム数を代入

		//テクスチャ移動量取得
	D3DXVECTOR2 tex_move = GetTexMove();
	tex_move.x = 1.0f / (float)TEX_SPLIT_X;
	tex_move.y = 1.0f / (float)TEX_SPLIT_Y;
	//テクスチャ移動量代入
	SetTexMove(tex_move);

	//テクスチャ座標取得
	D3DXVECTOR2 tex_pos = GetTexPos();
	tex_pos.x = 0.0f;
	tex_pos.y = 0.0f;
	//テクスチャ座標代入
	SetTexPos(tex_pos);

	//アニメーションフレーム代入
	SetAnimFrame(ANIMATION_FRAME);

	//頂点座標
	SetVtxAnim(D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), tex_pos, tex_move);

	return S_OK;
}

//=============================================
//終了
//=============================================
void CFlow::Uninit()
{
	//親クラスの終了
	CAttack_Manager::Uninit();
}

//=============================================
//更新
//=============================================
void CFlow::Update()
{
	//親クラスの更新
	CAttack_Manager::Update();

	//体力取得
	int nLife = GetLife();

	if (nLife > 0)
	{//ライフがあれば処理実行

		//テクスチャ情報取得
		D3DXVECTOR2 tex_pos = GetTexPos();
		D3DXVECTOR2 tex_move = GetTexMove();

		//頂点座標
		SetVtxAnim(D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(0.2f, 0.8f, 0.9f, 1.0f), tex_pos, tex_move);
		//アニメーション後のテクスチャ座標取得
		tex_pos = GetTexPos();
		//アニメーションを繰り返す
		if (tex_pos.x >= 1.0f)
		{
			tex_pos.x = 0.0f;
		}
		SetTexPos(tex_pos);

		//当たり判定チェック変数
		bool bHitCheck = false;
		switch (m_type)
		{
		case FLOW_TYPE_PLAYER:
			m_nDamageCnt++;//ヒットカウント計測

			if (m_nDamageCnt >= ENEMY_DAMAGE_FRAME)
			{//フレーム数に到達したら
				bHitCheck = HitEnemy();
				m_nDamageCnt = 0;
			}
			break;

		case FLOW_TYPE_ENEMY:
			
			m_nDamageCnt++;//ヒットカウント計測

			if(m_nDamageCnt >= PLAYER_DAMAGE_FRAME)
			{//フレーム数に到達したら
				bHitCheck = HitPlayer();
				m_nDamageCnt = 0;
			}

			break;

		default:
			assert(false);
			break;
		}
	}
	else
	{
		//終了
		Uninit();
	}
}

//=============================================
//描画
//=============================================
void CFlow::Draw()
{
	//親クラスの描画
	CAttack_Manager::Draw();
}

//=============================================
//生成
//=============================================
CFlow* CFlow::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nLife, int nDamage , FLOW_TYPE type)
{
	CFlow* pFlow = new CFlow;

	if (pFlow == nullptr) { return nullptr; }
	CTexture* pTexture = CManager::GetTexture();

	pFlow->SetPos(pos); //pos設定
	pFlow->SetSize(size); //サイズ設定
	pFlow->SetLife(nLife); //寿命代入
	pFlow->SetDamage(nDamage); //ダメージ代入
	pFlow->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));
	pFlow->m_type = type; //弾の設定
	pFlow->SetType(OBJECT_TYPE_FLOW); //タイプ設定
	pFlow->Init();

	return pFlow;
}
