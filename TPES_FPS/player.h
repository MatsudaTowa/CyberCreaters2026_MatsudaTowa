//=============================================
//
//プレイヤー処理[player.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _PLAYER_H_ //これが定義されてないとき

#define _PLAYER_H_
#include "main.h"
#include "character.h"
#include "manager.h"
//プレイヤークラス
class CPlayer : public CCharacter
{
public:
	static const int PLAYER_PRIORITY = 8; //描画順

	CPlayer(int nPriority = PLAYER_PRIORITY);
	~CPlayer()override;
	HRESULT Init()override;
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife);
	void Uninit()override;
	void Update()override;
	void Draw()override;

	//プレイヤー作成
	static CPlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife);

	void Damage(int nDamage); //当たり判定

	static bool m_PlayerDeath;

private:
	static const std::string MODEL_NAME;	//モデルの名前

	//プレイヤーの移動関連
	static const float DEFAULT_MOVE; //通常時の移動
	static const float DAMPING_COEFFICIENT; //移動抵抗
	static const float DEFAULT_JUMP; //通常時のジャンプ力
	static const int MAX_JUMPCNT; //ジャンプ回数
	static const int STATE_FRAME; //ステート変更フレーム数
	static const float DEADZONE_Y; //これを過ぎたらプレイヤー破棄

	void ReSpawn(); //リスポーン
	void PlayerMove(); //プレイヤー移動処理

	int m_nJumpCnt; //ジャンプカウント

	static LPDIRECT3DTEXTURE9 m_pTextureTemp;

	static LPD3DXMESH m_pMesh;
	static 	LPD3DXBUFFER m_pBuffMat; //マテリアル情報
	static	DWORD m_dwNumMat; //マテリアル数

	void DebugPos();

	float fSpeed;
	float fJump;
	float fRadius;
	float fHeight;
};
#endif