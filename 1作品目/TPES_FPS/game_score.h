//=============================================
//
//ゲームスコア処理「game_scorer.h」
// Author松田永久
//
//=============================================
#ifndef _GAME_SCORE_H_ //これが定義されてないとき
#define _GAME_SCORE_H_
#include "main.h"
#include "object2D.h"
#include "score.h"

//=============================================
//スコアクラス
//=============================================
class CGameScore : public CScore
{
public:
	static const float DIGIT_SHIFT;
	CGameScore();
	~CGameScore() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
private:
};

#endif // DEBUG
