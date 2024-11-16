//=============================================
//
//キャラクターのステートパターン[character_state.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _CHARACTER_STATE_H_
#define _CHARACTER_STATE_H_

#include "character.h"

//=============================================
//前方宣言
//=============================================
class CCharacter;

//=============================================
//キャラクターのステートクラス
//=============================================
class CCharacterState
{
public:
	virtual void Shot(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character); 
	virtual void Move(CCharacter* character);
};

//=============================================
//キャラクターの撃ってる状態
//=============================================
class CShotState : public CCharacterState
{
public:
	virtual void Shot(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character)override;
};

//=============================================
//キャラクターの動いてる状態
//=============================================
class CMoveState : public CCharacterState
{
public:
	virtual void Move(CCharacter* character)override;
};

#endif // !_CHARACTER_STATE_H
