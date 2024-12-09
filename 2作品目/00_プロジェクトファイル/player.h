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
#include "gauge.h"
#include "item_UI.h"
#include "lockon.h"
//プレイヤークラス
class CPlayer : public CCharacter
{
public:
	static const int PLAYER_PRIORITY = 8; //描画順

	typedef enum
	{
		PLAYER_ATTACK_MELEE = 0, //近距離攻撃のみ
		PLAYER_ATTACK_PANETRARING_SLASH, //貫通斬撃
		PLAYER_ATTACK_FLOW, //集中斬撃
		PLAYER_ATTACK_MAX,
	}PLAYER_ATTACK;

	CPlayer(int nPriority = PLAYER_PRIORITY);
	~CPlayer()override;
	HRESULT Init()override;
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife);
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void LockOn();

	void LockOn_ChangeSize(float fRatioFrame);

	void LockOn_Flow();	//集中斬撃を照準に合わせて出す

	void Delete_LockOn();	//照準削除

	//プレイヤー作成
	static CPlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife);

	void Damage(int nDamage); //当たり判定

	bool m_OldPress; //左クリック押されてるかどうか

	bool m_OldRelease; //左クリック離されたどうか

	PLAYER_ATTACK m_Attack; //プレイヤーの攻撃方法

	static bool m_PlayerDeath;

	bool m_bLockOn; //ロックオン状態かどうか

	CLockOn* m_pLockOn; //ロックオンの情報

private:
	static const std::string MODEL_NAME;	//モデルの名前

	//プレイヤーの移動関連
	static const float DEFAULT_MOVE; //通常時の移動
	static const float DAMPING_COEFFICIENT; //移動抵抗
	static const float DEFAULT_JUMP; //通常時のジャンプ力
	static const int MAX_JUMPCNT; //ジャンプ回数
	static const int STATE_FRAME; //ステート変更フレーム数
	static const float DEADZONE_Y; //これを過ぎたらプレイヤー破棄

	//斬撃関連
	static const int SLASH_COOLTIME = 30; //クールタイム
	static const int SLASH_COST = 5; //斬撃コスト
	static const int CHARGE_INTERVAL = 10; //段階が上がる間隔
	static const int MAX_CHARGE; //最終段階

	static const int MELEE_DAMAGE = 1; //近接ダメージ

	void Gauge(CGauge*pGauge);

	void ReSpawn(); //リスポーン
	void PlayerMove(); //プレイヤー移動処理
	void PerformMelee(D3DXVECTOR3 pos, bool bWay); //近接攻撃処理

	D3DXVECTOR3 m_SlashSize; //斬撃のサイズ
	bool m_bSize; //サイズ変更するかどうか
	bool m_bFlow; //集中状態かどうか
	int m_PressCnt; //何秒間押されたか
	int m_ReleaseCnt; //離してからのカウント
	int m_nJumpCnt; //ジャンプカウント
	int m_nChargeCnt; //何段階目かカウント
	int m_nSlashDamage; //斬撃のダメージ(引き渡し用)

	CItem_UI* m_pItemUI; //何を持ってるのかの2DUI

	static LPDIRECT3DTEXTURE9 m_pTextureTemp;

	static LPD3DXMESH m_pMesh;
	static 	LPD3DXBUFFER m_pBuffMat; //マテリアル情報
	static	DWORD m_dwNumMat; //マテリアル数
};
#endif