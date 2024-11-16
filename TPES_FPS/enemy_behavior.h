//=============================================
//
//エネミーのストラテジーパターン[enemy_behavior.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _ENEMY_BEHAVIOR_
#define _ENEMY_BEHAVIOR_
#include "character_behavior.h"
#include "enemy.h"

//=============================================
//敵の移動のストラテジー
//=============================================
class CEnemyMove : public CMove
{
public:
	static const int MAX_JUMPCNT = 2; //ジャンプ回数

	CEnemyMove();
	~CEnemyMove() override;
	void Move(CCharacter* character)override;
private:
	static const int MOVE_FRAME = 60; //移動フレーム
	static const int RIGHT_PARCENT = 50; //右の確立
	static const int LEFT_PARCENT = 100; //左の確立

	int m_nRight;//左に行く確率
	int m_nLeft; //右に行く確率
	bool m_bRandom; //どっちに行くか決める
	int m_nStateChangeCnt; //ステート変更カウント
};

//=============================================
//敵の攻撃のストラテジー
//=============================================
class CEnemyAttack : public CAttack
{
public:
	CEnemyAttack();
	~CEnemyAttack() override;
	void Attack(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character) override;
	void LookAtPlayer(CCharacter* character); //プレイヤーのほうを向かせる処理

private:
	static const int SHOT_FRAME = 180; //射撃フレーム

	int m_nStateChangeCnt;//ステート変更カウント
};
#endif // !_ENEMY_BEHAVIOR_
