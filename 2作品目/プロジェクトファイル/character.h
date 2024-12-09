//=============================================
//
//3DTemplate[character.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _CHARACTER_H_ //これが定義されてないとき

#define _CHARACTER_H_
#include "main.h"
#include "objectX.h"
#include "bullet.h"
//プレイヤークラス
class CCharacter : public CObjectX
{
public:
	static const int CHARACTER_PRIORITY = 8; //描画順
	static const float  BOSS_FIELD_X; //ボス戦のX座標

	typedef enum
	{
		CHARACTER_NORMAL = 0, //通常状態
		CHARACTER_DAMAGE, //ダメージ状態
		CHARACTER_STATE_MAX,
	}CHARACTER_STATE;

	CCharacter(int nPriority = CHARACTER_PRIORITY);
	~CCharacter()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void Gravity(); //重力処理
	void HitBlock(); //ブロック当たり判定
	void HitField(); //床当たり判定
	void HitPlayer(); //プレイヤーとの当たり判定
	void HitEnemy(); //敵との当たり判定
	void ShotBullet(D3DXVECTOR3 pos,float move, D3DXVECTOR3 size, bool bWay, int nDamage,CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type); //弾発射処理

	//移動量代入
	void SetMove(D3DXVECTOR3 move)
	{
		m_move = move;
	}

	//oldpos代入
	void SetOldPos(D3DXVECTOR3 oldpos)
	{
		m_oldpos = oldpos;
	}

	//着地してるかどうかを代入
	void SetLanding(bool bLanding)
	{
		m_bLanding = bLanding;
	}

	//どっち向いてるかどうかを代入(true:右false:左)
	void SetWay(bool bWay)
	{
		m_bWay = bWay;
	}

	//体力代入
	void SetLife(int nLife)
	{
		m_nLife = nLife;
	}

	//状態代入
	void SetState(CHARACTER_STATE state)
	{
		m_State = state;
	}

	//ステートカウント代入
	void SetStateCnt(int nStateCnt)
	{
		m_nStateCnt = nStateCnt;
	}

	//移動量取得
	D3DXVECTOR3& GetMove();

	//過去の位置取得
	D3DXVECTOR3& GetOldPos();

	//着地してるかどうか取得
	bool& GetLaunding();

	//どっち向いてるかどうかを取得(true:右false:左)
	bool& GetWay();

	//体力取得
	int& GetLife();

	//状態取得
	CHARACTER_STATE& GetState();

	//ステートカウント取得
	int& GetStateCnt();

private:
	static const float GRAVITY_MOVE; //重力値
	static const float GRAVITY_MAX; //重力最大値

	D3DXVECTOR3 m_move; //速度
	D3DXVECTOR3 m_oldpos; //過去の位置
	bool m_bLanding; //着地してるかどうか
	bool m_bWay; //どっち向いてるか(true:右false:左)
	int m_nLife; //体力
	int m_nStateCnt; //ステート切り替え計測カウント
	CHARACTER_STATE m_State; //プレイヤー状態
	D3DXCOLOR m_col; //カラー
};
#endif