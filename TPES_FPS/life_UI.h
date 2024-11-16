//=============================================
//
//体力表示「life_UI.h」
// Author松田永久
//
//=============================================
#ifndef _LIFE_UI_H_ //これが定義されてないとき
#define _LIFE_UI_H_
#include "main.h"
#include "object2D.h"
#include "number.h"

//=============================================
//体力表示クラス
//=============================================
class CLife_UI
{
public:
	static const int NUM_DIGIT = 3;  //桁数
	static const float DIGIT_SHIFT;  //桁ごとに座標をずらす

	CLife_UI();
	~CLife_UI();
	HRESULT Init();
	void Uninit();
	void Update();
	int m_nLife; //体力の値
	void SetLife_UI(int nLife);

private:
	D3DXVECTOR3 m_pos;
	CNumber* m_pNumber[NUM_DIGIT];
};

#endif // DEBUG