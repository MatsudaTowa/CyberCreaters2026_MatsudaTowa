//=============================================
//
//3DTemplate[effect.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _EFFECT_H_ //これが定義されてないとき

#define _EFFECT_H_
#include "main.h"
#include "billboard.h"

class CEffect : public CBillboard
{
public:
	static const std::string TEXTURE_NAME;	//テクスチャの名前
	static const int EFFECT_PRIORITY = 3; //描画順
	static const int TEX_SPLIT_X; //テクスチャの分割数
	static const int TEX_SPLIT_Y; //テクスチャの分割数
	static const int ANIMATION_FRAME; //アニメーションフレーム数
	CEffect(int nPriority = EFFECT_PRIORITY);
	~CEffect()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	//エフェクト作成
	static CEffect* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,D3DXCOLOR col,int nLife);
private:
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;
	D3DXCOLOR m_col;
	float m_fLength; //対角線
	float m_fAngle; //角度
	int m_nLife; //寿命
};
#endif