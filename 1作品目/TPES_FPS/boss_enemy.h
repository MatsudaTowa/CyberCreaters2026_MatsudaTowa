//=============================================
//
//ボスの敵の処理[boss_enemy.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _BOSS_ENEMY_H_ //これが定義されてないとき

#define _BOSS_ENEMY_H_
#include "main.h"
#include "model_parts.h"
#include "enemy.h"
#include "enemy_behavior.h"
#include "boss_behavior.h"
#include "boss_state.h"
#include"player_test.h"

class CBossChase;
class CBossWandering;
class CBossConfusion;
class CBossTackle;
class CBossState;

//ボスのエネミークラス
class CBossEnemy :public CEnemy
{
public:
	static const int NUM_PARTS = 15; //パーツ数
	static const int MAX_KEY = 20; //キー最大数
	static const int NUM_MOTION = 3;
	static const int ENEMY_PRIORITY = 8; //描画順
	static const int PARTS_PARENT[NUM_PARTS]; //パーツ数
	static const int DEFAULT_LIFE = 100; //ライフ
	static const float FIND_PLAYER_DISTANCE; //この値までだったら追いかける
	static const float LOST_PLAYER_DISTANCE; //この値以上だったら見失う

	//モーションの種類の列挙
	enum Motion_Type
	{
		MOTION_NEUTRAL = 0,
		MOTION_MOVE,
		MOTION_ATTACK,
		MOTION_MAX,
	};

	CBossEnemy(int nPriority = ENEMY_PRIORITY);
	~CBossEnemy() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void ChangeState(CBossState* state);

	void ColisionPlayer(); //プレイヤーとの当たり判定

	void CheckColisionPlayer(CPlayer_test* pPlayer, int nPartsCnt, const D3DXVECTOR3& pos, const D3DXVECTOR3& Minpos, const D3DXVECTOR3& Maxpos);

	CBossChase* m_pChase; //追跡処理

	CBossWandering* m_pWandering; //徘徊処理

	CBossConfusion* m_pConfusion; //混乱

	CBossTackle* m_pTackle; //タックル処理
private:
	//エネミーの移動関連
	static const float DEFAULT_MOVE; //通常時の移動

	void DrawDebug();

	Motion_Type m_Motion; //モーションの種類

	//ボスのステートパターン
	CBossState* m_pBossState;
};

#endif