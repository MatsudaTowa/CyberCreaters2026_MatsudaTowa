//=============================================
//
//レティクル[reticle.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "billboard.h"

#ifndef _RETICLE_H_ //これが定義されてないとき

#define _RETICLE_H_

//=============================================
//レティクルクラス
//=============================================
class CReticle : public CBillboard
{
public:
	static const std::string RETICLE_TEXTURE_NAME;	//テクスチャの名前

	static const int RETICLE_PRIORITY = 30; //描画順

	CReticle(int nPriority = RETICLE_PRIORITY);
	~CReticle()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	//弾作成
	static CReticle* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);

	void Move();
private:
	D3DXVECTOR3 m_move; //移動量
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;
};

#endif