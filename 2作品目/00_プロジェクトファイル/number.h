//=============================================
//
//数字管理「number.h」
// Author松田永久
//
//=============================================
#ifndef _NUMBER_H_ //これが定義されてないとき
#define _NUMBER_H_
#include "main.h"
#include "object2D.h"

//=============================================
//ナンバークラス
//=============================================
class CNumber:public CObject2D
{
public:
	static const std::string TEXTURE_NAME;	//テクスチャの名前
	static const int NUMBER_PRIORITY = 85;  //描画順
	CNumber(int nPriority = NUMBER_PRIORITY);
	~CNumber()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	//数字のポリゴン生成処理
	static CNumber* Create(D3DXVECTOR3 pos ,D3DXVECTOR2 size);

	void SetNumber(float fNumPos1,float fNumPos2,D3DXCOLOR col);

	void NumberVtx();

private:
	D3DXVECTOR2 m_mintex; //テクスチャの最小座標
	D3DXVECTOR2 m_maxtex; //テクスチャの最大座標
	D3DXCOLOR m_col; //カラー
};

#endif // DEBUG