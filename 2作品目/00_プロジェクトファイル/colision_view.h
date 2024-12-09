//=============================================
//
//当たり判定可視化[colision_view.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _COLISION_VIEW_H_ //これが定義されてないとき

#define _COLISION_VIEW_H_

#include "main.h"
#include "object3D.h"

//=============================================
//当たり判定可視化クラス
//=============================================
class CColision_View :public CObject3D
{
public:
	static const int COLIVISON_VIEW_PRIORITY = 20;  //描画順

	CColision_View(int nPriority = COLIVISON_VIEW_PRIORITY);
	~CColision_View()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CColision_View* Create(D3DXVECTOR3 pos, D3DXVECTOR3 Minpos,D3DXVECTOR3 Maxpos, D3DCOLOR col);

private:
	void SetVtxColision_View(D3DXVECTOR3 nor, D3DCOLOR col); //頂点生成
	D3DCOLOR m_Col; //カラー
	D3DXVECTOR3 m_Minpos; //最小値
	D3DXVECTOR3 m_Maxpos; //最大値
};
#endif