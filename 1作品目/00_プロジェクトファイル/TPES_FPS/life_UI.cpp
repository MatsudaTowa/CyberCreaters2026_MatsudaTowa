//=============================================
//
//体力表示「life_UI.cpp」
// Author松田永久
//
//=============================================
#include "life_UI.h"
#include "manager.h"
//桁ごとにずらす
const float CLife_UI::DIGIT_SHIFT = 50.0f;

//=============================================
//コンストラクタ
//=============================================
CLife_UI::CLife_UI() :m_nLife(0), m_pos(), m_pNumber()
{
}

//=============================================
//デストラクタ
//=============================================
CLife_UI::~CLife_UI()
{
}

//=============================================
//初期化
//=============================================
HRESULT CLife_UI::Init()
{
	//初期位置代入
	m_pos = D3DXVECTOR3(300.0f, 650.0f, 0.0f);

	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		if (m_pNumber[nCnt] == nullptr)
		{
			m_pNumber[nCnt] = CNumber_2D::Create(m_pos, D3DXVECTOR2(30.0f, 50.0f));
			//座標をずらす
			m_pos.x -= DIGIT_SHIFT;
		}
	}
	return S_OK;
}

//=============================================
//終了
//=============================================
void CLife_UI::Uninit()
{
	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		if (m_pNumber[nCnt] != nullptr)
		{
			m_pNumber[nCnt]->Uninit();
			m_pNumber[nCnt] = nullptr;
		}
	}
}

//=============================================
//更新
//=============================================
void CLife_UI::Update()
{
}

//=============================================
//UIに設定
//=============================================
void CLife_UI::SetLife_UI(int nLife)
{
	//テクスチャ座標設定
	int a_PosTexU[NUM_DIGIT];

	//現在計算してる桁
	int nDigit = 1;
	int nCnt;
	for (nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		//今の時間から計算
		a_PosTexU[nCnt] = nLife / nDigit % 10;

		//桁を進める
		nDigit *= 10;
	}

	for (nCnt = NUM_DIGIT - 1; nCnt >= 0; nCnt--)
	{
		//テクスチャの座標計算用変数
		float fMinTexU, fMaxTexU;

		fMinTexU = a_PosTexU[nCnt] * 0.1f;
		fMaxTexU = fMinTexU + 0.1f;

		m_pNumber[nCnt]->SetNumber(fMinTexU, fMaxTexU, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}
