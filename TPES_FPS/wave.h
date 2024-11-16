//=============================================
//
//ウェーブ処理[wave.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _WAVE_H_ //これが定義されてないとき

#define _WAVE_H_
#include "main.h"
#include "block.h"
#include "enemy.h"
#include "score.h"

//=============================================
//  ウェーブクラス定義
//=============================================
class CWave
{
public:
	static const int TXT_MAX = 1024; //敵を読み込む際の読み込める最大文字数
	//ウェーブ列挙
	enum class WAVE
	{
		NONE = 0,
		ONE,
		TWO,
		THREE,
		BOSS,
		RESULT,
		MAX,
	};

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

	//読み込むときに必要な壁の構造体
	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 size;
		D3DXVECTOR3 rot;
	}LOAD_WALL;

	// メンバ関数
	CWave();
	virtual ~CWave();

	virtual HRESULT Init();
	virtual void Uninit();
	virtual void Update();

	static CWave* Create(WAVE wave);
	static CWave* Create(WAVE wave,WAVE next_wave,const char* ResultFile);
	static WAVE GetCurrentWave();
	static CScore* GetScore();

	void LoadBlock(const std::string* pFileName);
	void LoadWall(const std::string* pFileName);
	void LoadEnemy(const std::string* pFileName);

	void SetWaveScore(int nScore);

	int GetWaveScore();

	//ウェーブのリザルトテンプレートメソッド
	void WaveResult(std::string* pFileName)
	{
		m_pScore->ExportScore(pFileName);
		m_pScore->Reset();
	}
protected:
	// メンバ変数
	LOAD_ENEMY m_LoadEnemy; //読み込むときに必要なエネミーの情報
	LOAD_BLOCK m_LoadBlock; //読み込むときに必要なブロックの情報
	LOAD_WALL m_LoadWall; //読み込むときに必要な壁の情報

	int m_nScore; //スコア格納変数
	static CScore* m_pScore;
	static WAVE m_next; //次のウェーブ
	static const char* m_ResultFile; //リザルトファイル
	static WAVE m_CurrentWave; //現在のウェーブ
};

#endif