//=============================================
//
//プレイヤーのストラテジーパターン[player_behavior.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _PLAYER_BEHAVIOR_
#define _PLAYER_BEHAVIOR_
#include "character_behavior.h"
#include "player_test.h"

class CPlayer_test;
//=============================================
//プレイヤーの移動のストラテジー
//=============================================
class CPlayerMove : public CMove
{
public:
	static const int MAX_JUMPCNT = 2; //ジャンプ回数

	CPlayerMove();
	~CPlayerMove() override;
	void Move(CCharacter* character)override;
};

//=============================================
//プレイヤーの移動のストラテジー
//=============================================
class CPlayerSliding
{
public:
	CPlayerSliding();
	~CPlayerSliding();
	void Sliding(CPlayer_test* player);
};


//=============================================
//プレイヤーの攻撃のストラテジー
//=============================================
class CPlayerAttack : public CGunAttack
{
public:
	CPlayerAttack();
	~CPlayerAttack() override;
	void GunAttack(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character) override;
};
#endif // !_ENEMY_BEHAVIOR_
