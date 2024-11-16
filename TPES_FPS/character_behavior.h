//=============================================
//
//キャラクターのストラテジーパターン[character_behavior.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _CHARACTER_BEHAVIOR_H_ //これが定義されてないとき

#define _CHARACTER_BEHAVIOR_H_
#include "main.h"
#include "manager.h"
#include "character.h"

class CCharacter;

//=============================================
//移動ストラテジー
//=============================================
class CMove
{
public:
	CMove();
	virtual ~CMove();
	virtual void Move(CCharacter*character) = 0;
protected:
};

//=============================================
//攻撃ストラテジー
//=============================================
class CAttack
{
public:
	CAttack();
	virtual ~CAttack();
	virtual void Attack(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type,CCharacter* character) = 0;
};
#endif
