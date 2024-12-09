//=============================================
//
//スコア処理「scorer.h」
// Author松田永久
//
//=============================================
#ifndef _SCORE_H_ //これが定義されてないとき
#define _SCORE_H_
#include "main.h"
#include "object2D.h"
#include "number.h"

//=============================================
//スコアクラス
//=============================================
class CScore
{
public:
	static const int NUM_DIGIT = 6;  //桁数

	CScore();
	virtual ~CScore();
	virtual HRESULT Init();
	virtual void Uninit();
	virtual void Update();
	void AddScore(int nValue);
	void ExportScore(const std::string* pFileName); //スコア書き出し
	void Reset();

	int m_nScore; //スコアの値
	void SetScore(int nScore);

	void SetPos(D3DXVECTOR3 pos)
	{
		m_pos = pos;
	}

	void SetDigitShift(float shift)
	{
		m_DigitShift = shift;
	}

	D3DXVECTOR3& GetPos();
	float& GetDigitShift();
	CNumber_2D* m_pNumber[NUM_DIGIT];
private:
	D3DXVECTOR3 m_pos;
	float m_DigitShift;
};

#endif // DEBUG