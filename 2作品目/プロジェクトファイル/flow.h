//=============================================
//
//集中斬撃[flow.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "attack_manager.h"

#ifndef _FLOW_H_ //これが定義されてないとき

#define _FLOW_H_

class CFlow : public CAttack_Manager
{
public:
	static const std::string TEXTURE_NAME;	//テクスチャの名前
	static const int FLOW_PRIORITY = 10; //描画順
	static const int PLAYER_DAMAGE_FRAME = 60; //ダメージを与えるフレーム間隔
	static const int ENEMY_DAMAGE_FRAME = 10; //ダメージを与えるフレーム間隔
	static const int TEX_SPLIT_X = 4; //テクスチャの分割数
	static const int TEX_SPLIT_Y = 1; //テクスチャの分割数
	static const int ANIMATION_FRAME = 7; //アニメーションフレーム数

	typedef enum
	{
		FLOW_TYPE_PLAYER = 0,
		FLOW_TYPE_ENEMY,
		FLOW_TYPE_MAX,
	}FLOW_TYPE;

	CFlow(int nPriority = FLOW_PRIORITY);
	~CFlow()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	//弾作成
	static CFlow* Create(D3DXVECTOR3 pos,D3DXVECTOR3 size, int nLife,int nDamage,  FLOW_TYPE type);
private:
	int m_nDamageCnt; //ダメージを与えるまでを計測するカウント
	FLOW_TYPE m_type;
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;
};
#endif