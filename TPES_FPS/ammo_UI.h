//=============================================
//
//残弾数表示「ammo_UI.h」
// Author松田永久
//
//=============================================
#ifndef _AMMO_UI_H_ //これが定義されてないとき
#define _AMMO_UI_H_
#include "main.h"
#include "object2D.h"
#include "number.h"

//=============================================
//残弾数表示クラス
//=============================================
class CAmmo_UI
{
public:
	static const int NUM_DIGIT = 2;  //桁数
	static const float DIGIT_SHIFT;  //桁ごとに座標をずらす

	CAmmo_UI();
	~CAmmo_UI();
	HRESULT Init();
	void Uninit();
	void Update();
	int m_nAmmo; //スコアの値
	void SetAmmo_UI(int nAmmo);

private:
	D3DXVECTOR3 m_pos;
	CNumber* m_pNumber[NUM_DIGIT];
};

#endif // DEBUG