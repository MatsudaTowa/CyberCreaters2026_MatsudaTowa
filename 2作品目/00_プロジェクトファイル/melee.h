//=============================================
//
//近接攻撃[melee.h]
//Auther Matsuda Towa
//
//=============================================

#ifndef _MELEE_H_ //これが定義されてないとき

#define _MELEE_H_

#include"main.h"
#include "attack_manager.h"
class CMelee : public CAttack_Manager
{
public:
	static const std::string TEXTURE_NAME;	//テクスチャの名前
	static const int MELEE_PRIORITY = 30; //描画順
	CMelee(int nPriority = MELEE_PRIORITY);
	~CMelee()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	//近接攻撃作成
	static CMelee* Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot, D3DXVECTOR3 size, int nLife,int nDamage);

private:
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;
};
#endif