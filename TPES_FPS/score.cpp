//=============================================
//
//スコア処理「scorer.cpp」
// Author松田永久
//
//=============================================
#include "score.h"
#include "manager.h"

//=============================================
//コンストラクタ
//=============================================
CScore::CScore():m_nScore(0),m_pos(D3DXVECTOR3(0.0f,0.0f,0.0f))
{//イニシャライザーでメンバ変数初期化

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
			m_pNumber[nCnt] = CNumber::Create(m_pos, D3DXVECTOR2(30.0f, 50.0f));
			//座標をずらす
			m_pos.x -= m_DigitShift;
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

//=============================================
//スコア書き出し
//=============================================
void CScore::ExportScore(std::string* pFileName)
{
	//ファイルの読み込み
	FILE* pFile = fopen(pFileName->c_str(), "wb");

	if (pFile != NULL)
	{
		fwrite(&m_nScore, sizeof(int), 1, pFile);
		fclose(pFile);
	}
}

//=============================================
//スコアリセット
//=============================================
void CScore::Reset()
{
	m_nScore = 0;
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

//=============================================
//表示座標取得
//=============================================
D3DXVECTOR3& CScore::GetPos()
{
	return m_pos;
}

//=============================================
//桁の座標ずらす変数取得
//=============================================
float& CScore::GetDigitShift()
{
	return m_DigitShift; 
}
