//=============================================
//
//3DTemplate[game.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _GAME_H_ //これが定義されてないとき

#define _GAME_H_
#include "main.h"
#include "scene.h"
#include "edit.h"
#include "timer.h"
#include "score.h"
#include "enemy.h"
#include "player.h"

class CGame:public CScene
{
public:

	typedef enum
	{
		GAME_STATE_NORMAL = 0,
		GAME_STATE_BOSS,
		GAME_STATE_MAX,
	}GAME_STATE;

	//読み込むときに必要なエネミーの構造体
	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		CEnemy::ENEMY_TYPE type;
	}LOAD_ENEMY;

	//読み込むときに必要なブロックの構造体
	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		CBlock::BLOCKTYPE type;
	}LOAD_BLOCK;

	static const std::string ENEMY_FILE;	//エネミーのファイル
	static const std::string BLOCK_FILE;	//エネミーのファイル
	static const int DELAY_CNT = 30; //リザルトに飛ぶまでのディレイ
	static const int ENEMY_TXT_MAX = 2048; //敵を読み込む際の読み込める最大文字数
	static const int BLOCK_TXT_MAX = 2048; //敵を読み込む際の読み込める最大文字数
	CGame();
	~CGame() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static void SetState(GAME_STATE state)
	{
		m_GameState = state;
	}

	static GAME_STATE&GetState();

	static CScore*GetScore();
	static CPlayer*GetPlayer();
private:
	int m_nResultDelay; //リザルトへのディレイ
	bool m_bEdit; //エディットしてるかどうか
	static GAME_STATE m_GameState; //ゲームステート
	LOAD_ENEMY m_LoadEnemy; //読み込むときに必要なエネミーの情報
	LOAD_BLOCK m_LoadBlock; //読み込むときに必要なブロックの情報
	static CEdit*m_pEdit;
	static CTimer*m_pTimer;
	static CScore*m_pScore;
	static CPlayer*m_pPlayer;

	void LoadEnemy(const std::string* pFileName);
	void LoadBlock(const std::string* pFileName);
};
#endif