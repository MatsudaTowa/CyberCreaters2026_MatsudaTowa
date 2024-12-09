//=============================================
//
//スコア処理「scorer.cpp」
// Author松田永久
//
//=============================================
#include "score.h"
#include "manager.h"

//桁ごとにずらす
const float CScore::DIGIT_SHIFT = 50.0f;
const float CScore::DEBUG_DIGIT_SHIFT = 120.0f;

int CScore::m_nSaveScore = 0; 

//=============================================
//コンストラクタ
//=============================================
CScore::CScore():m_nScore(0),m_pos(D3DXVECTOR3(0.0f,0.0f,0.0f))
{//イニシャライザーでメンバ変数初期化

	//現在のシーンを取得
	CScene::MODE pScene = CScene::GetSceneMode();
	if (pScene == CScene::MODE::MODE_GAME)
	{
		//初期位置代入
		m_pos = D3DXVECTOR3(300.0f, 650.0f, 0.0f);
	}
	else if (pScene == CScene::MODE::MODE_RESULT)
	{
		//初期位置代入
		m_pos = D3DXVECTOR3(1140.0f, 460.0f, 0.0f);
	}

	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		m_pNumber[nCnt] = nullptr;
	}

}

//=============================================
//デストラクタ
//=============================================
CScore::~CScore()
{
}

//=============================================
//初期化
//=============================================
HRESULT CScore::Init()
{
	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{

		if (m_pNumber[nCnt] == nullptr)
		{
			//現在のシーンを取得
			CScene::MODE pScene = CScene::GetSceneMode();
			if (pScene == CScene::MODE::MODE_GAME)
			{
				m_pNumber[nCnt] = CNumber::Create(m_pos, D3DXVECTOR2(30.0f, 50.0f));
				//座標をずらす
				m_pos.x -= DIGIT_SHIFT;
			}
			else if (pScene == CScene::MODE::MODE_RESULT)
			{
				m_pNumber[nCnt] = CNumber::Create(m_pos, D3DXVECTOR2(70.0f, 90.0f));
				//座標をずらす
				m_pos.x -= DEBUG_DIGIT_SHIFT;
			}
		}
	}

	return S_OK;
}

//=============================================
//終了
//=============================================
void CScore::Uninit()
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
void CScore::Update()
{
	SetScore(m_nScore);
}

//=============================================
//描画
//=============================================
void CScore::AddScore(int nValue)
{
	m_nScore += nValue;
}

int CScore::GetScore()
{
	return m_nSaveScore;
}

//=============================================
//スコア設定
//=============================================
void CScore::SetScore(int nScore)
{
	//テクスチャ座標設定
	int a_PosTexU[NUM_DIGIT];

	//現在計算してる桁
	int nDigit = 1;
	int nCnt;
	for (nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		//今の時間から計算
		a_PosTexU[nCnt] = m_nScore / nDigit % 10;

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
