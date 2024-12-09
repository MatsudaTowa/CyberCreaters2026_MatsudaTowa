//=============================================
//
//攻撃エフェクト[attack_effect.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _ATTACK_EFFECT_H_ //これが定義されてないとき

#define _ATTACK_EFFECT_H_
#include "main.h"
#include "billboard.h"

class CAttack_Effect : public CBillboard
{
public:
	static const std::string TEXTURE_NAME;	//テクスチャの名前
	static const int ATTACK_EFFECT_PRIORITY = 3; //描画順
	static const int TEX_SPLIT_X; //テクスチャの分割数
	static const int TEX_SPLIT_Y; //テクスチャの分割数
	static const int ANIMATION_FRAME; //アニメーションフレーム数
	CAttack_Effect(int nPriority = ATTACK_EFFECT_PRIORITY);
	~CAttack_Effect()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void SizeChange(float fRatioFrame);
	void SizeReset();

	//エフェクト作成
	static CAttack_Effect* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col);
private:
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;
	D3DXCOLOR m_col;
	D3DXVECTOR3 m_DefaultSize;
};
#endif