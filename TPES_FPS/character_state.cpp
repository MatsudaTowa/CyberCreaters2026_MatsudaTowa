//=============================================
//
//キャラクターのステートパターン[character_state.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "character_state.h"

//=============================================
//キャラクターのショット
//=============================================
void CCharacterState::Shot(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character)
{
}

//=============================================
//キャラクターの動き
//=============================================
void CCharacterState::Move(CCharacter* character)
{
}

//=============================================
//キャラクターのショット
//=============================================
void CShotState::Shot(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character)
{
	character->m_pAttack->Attack(Allegiance,type,character);
}

//=============================================
//キャラクターの動き
//=============================================
void CMoveState::Move(CCharacter* character)
{
	character->m_pMove->Move(character);
}
