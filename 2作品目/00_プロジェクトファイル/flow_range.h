//=============================================
//
//プレイヤーの集中攻撃の範囲[flow_range.h]
//Auther Matsuda Towa
//
//=============================================

#ifndef _FLOW_RANGE_H_ //これが定義されてないとき

#define _FLOW_RANGE_H_

#include"main.h"
#include "object3D.h"
class CFlow_Range : public CObject3D
{
public:
	static const int FLOW_RANGE_PRIORITY = 4; //描画順
	CFlow_Range(int nPriority = FLOW_RANGE_PRIORITY);
	~CFlow_Range()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	//近接攻撃作成
	static CFlow_Range* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 Minpos, D3DXVECTOR3 Maxpos);

	//最小値取得
	D3DXVECTOR3& GetMinPos();

	//最大値取得
	D3DXVECTOR3& GetMaxPos();

	void SizeUp(bool bWay);
private:
	D3DXVECTOR3 m_Minpos;
	D3DXVECTOR3 m_Maxpos;
	void SetVtxFlow_Range(D3DXVECTOR3 nor, D3DCOLOR col);

};
#endif