//=============================================
//
//ウェーブスコア処理「wave_scorer.h」
// Author松田永久
//
//=============================================
#ifndef _WAVE_SCORE_H_ //これが定義されてないとき
#define _WAVE_SCORE_H_
#include "main.h"
#include "object2D.h"
#include "score.h"

//=============================================
//スコアクラス
//=============================================
class CWaveScore : public CScore
{
public:
	static const float DIGIT_SHIFT;
	CWaveScore();
	~CWaveScore() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
private:
};

#endif // DEBUG
