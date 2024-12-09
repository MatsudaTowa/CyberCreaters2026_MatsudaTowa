//=============================================
//
//プレイヤー処理[player.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "player.h"
#include "input.h"
#include "block.h"
#include "field.h"
#include "camera.h"
#include "game.h"
#include"renderer.h"
#include "scene.h"

//モデルパス
const char* CPlayer::MODEL_NAME = "data\\MODEL\\face.x";

//通常の移動速度
const float CPlayer::DEFAULT_MOVE = 0.7;

//移動抵抗
const float CPlayer::DAMPING_COEFFICIENT = 0.3f;

//通常のジャンプ力
const float CPlayer::DEFAULT_JUMP = 30.0f;

//ジャンプ回数
const int CPlayer::MAX_JUMPCNT = 2;

//ステート切り替えフレーム
const int CPlayer::STATE_FRAME = 60;

//プレイヤーをリスポーンされる座標
const float CPlayer::DEADZONE_Y = -100.0f;

//テクスチャ初期化
LPDIRECT3DTEXTURE9 CPlayer::m_pTextureTemp = nullptr;

LPD3DXBUFFER CPlayer::m_pBuffMat = nullptr;

LPD3DXMESH CPlayer::m_pMesh = nullptr;

DWORD CPlayer::m_dwNumMat = 0;

bool CPlayer::m_PlayerDeath = false;

//=============================================
//コンストラクタ
//=============================================
CPlayer::CPlayer(int nPriority):CCharacter(nPriority)
{//イニシャライザーで各メンバ変数初期化

	//ステートを通常に
	SetState(CCharacter::CHARACTER_STATE::CHARACTER_NORMAL);

	//死んでない状態に
	m_PlayerDeath = false;

}

//=============================================
//デストラクタ
//=============================================
CPlayer::~CPlayer()
{
}

//=============================================
//初期化
//=============================================
HRESULT CPlayer::Init()
{
	CRenderer* pRender = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();


	//移動量初期化
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f,0.0f,0.0f);
	//ムーブ値代入
	SetMove(move);

	return S_OK;
}

//=============================================
//初期化(セット用)
//=============================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife)
{
	CModel* pModel = CManager::GetInstance()->GetModel();

	SetPos(pos); //pos設定
	SetRot(rot); //rot設定
	SetLife(nLife); //体力代入

	//xファイル読み込み
	BindXFile(pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).pBuffMat,
		pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).dwNumMat,
		pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).pMesh);

	SetType(OBJECT_TYPE_PLAYER); //タイプ設定

	CRenderer* pRender = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();

	//移動量初期化
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//シーンのポインタ取得
	CScene* pScene = CManager::GetInstance()->GetScene();

	//CScene::MODE mode = pScene->GetSceneMode();

	//ムーブ値代入
	SetMove(move);

	return S_OK;
}


//=============================================
//終了
//=============================================
void CPlayer::Uninit()
{
	//親クラスの終了処理を呼ぶ
	CObjectX::Uninit();

}

//=============================================
//更新
//=============================================
void CPlayer::Update()
{
	//SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	//現在のシーンを取得
	CScene::MODE pScene = CScene::GetSceneMode();

	if (pScene != CScene::MODE::MODE_TITLE)
	{
		//状態を取得
		CCharacter::CHARACTER_STATE state = GetState();

		if (state == CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE)
		{
			//状態のカウント数取得
			int nStateCnt = GetStateCnt();

			//ステート変更カウント進める
			nStateCnt++;

			if (nStateCnt >= STATE_FRAME)
			{
				//通常に戻す
				state = CCharacter::CHARACTER_STATE::CHARACTER_NORMAL;
				//ステートカウントリセット
				nStateCnt = 0;

				//状態代入
				SetState(state);
			}

			//ステートカウント代入
			SetStateCnt(nStateCnt);
		}

		//重力処理
		Gravity();

		//移動処理
		PlayerMove();
		
		//位置取得
		D3DXVECTOR3 pos = GetPos();

		//過去の位置
		D3DXVECTOR3 oldpos = GetOldPos();

		//移動量取得
		D3DXVECTOR3 move = GetMove();

		//移動量を更新(減速）
		move *= 1.0f - DAMPING_COEFFICIENT;

		//移動量代入
		SetMove(move);

		//過去の位置に今の位置を代入
		oldpos = pos;

		//過去の位置代入
		SetOldPos(oldpos);

		//移動量追加
		pos += move;

		//座標を更新
		SetPos(pos);

		//最大最小値取得
		D3DXVECTOR3 minpos = GetMinPos();
		D3DXVECTOR3 maxpos = GetMaxPos();

		//ブロックとの接触処理
		HitBlock();

		//床との接触処理
		HitField();

		//ゲームの状態取得
		CGame::GAME_STATE Game_state = CGame::GetState();

		if (GetLaunding())
		{//着地してるなら
			//ジャンプ数リセット
			m_nJumpCnt = 0;
		}

		if (pos.y < DEADZONE_Y)
		{//リスポーン処理
			ReSpawn();
		}

		//マウスの情報取得
		CInputMouse* pMouse = CManager::GetInstance()->GetMouse();
		CInputPad* pPad = CManager::GetInstance()->GetPad();

		//どっち向いてるか取得
		bool bWay = GetWay();
	}
}

//=============================================
//描画
//=============================================
void CPlayer::Draw()
{
	//親クラスの描画を呼ぶ
	CCharacter::Draw();

	DebugPos();
}

//=============================================
//生成
//=============================================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot, int nLife)
{
	CModel* pModel = CManager::GetInstance()->GetModel();

	CPlayer* pPlayer = new CPlayer;

	// nullならnullを返す
	if (pPlayer == nullptr) {return nullptr;}

	pPlayer->SetPos(pos); //pos設定
	pPlayer->SetRot(rot); //rot設定
	pPlayer->SetLife(nLife); //体力代入

	//xファイル読み込み
	pPlayer->BindXFile(pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).pBuffMat,
					pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).dwNumMat,
					pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).pMesh);

	pPlayer->SetType(OBJECT_TYPE_PLAYER); //タイプ設定

	pPlayer->Init(); //初期化処理
	
	return pPlayer;
}

//=============================================
//ダメージを受けたとき
//=============================================
void CPlayer::Damage(int nDamage)
{
	//体力取得
	int nLife = GetLife();

	//状態を取得
	CCharacter::CHARACTER_STATE state = GetState();

	if (nLife > 0)
	{//HPが残ってたら

		nLife -= nDamage;

		//ダメージ状態に変更
		state = CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE;

		//現在の状態を代入
		SetState(state);

		//体力代入
		SetLife(nLife);
	}
	if (nLife <= 0)
	{//HPが0以下だったら
		//終了
		Uninit();
		//死んだ状態に
		m_PlayerDeath = true;
	}
}

//=============================================
//リスポーン
//=============================================
void CPlayer::ReSpawn()
{
	//自分自身のpos取得
	D3DXVECTOR3 PlayerPos = GetPos();

	PlayerPos = D3DXVECTOR3(-900.0f, 0.5f, 0.0f);

	//pos代入
	SetPos(PlayerPos);
}

//=============================================
//移動処理
//=============================================
void CPlayer::PlayerMove()
{
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();
	CInputPad* pPad = CManager::GetInstance()->GetPad();
	D3DXVECTOR3 vecDirection(0.0f, 0.0f, 0.0f);

	//カメラタイプ取得
	CCamera::CANERA_TYPE pCameraType = CCamera::GetType();

	//どっち向いてるか取得
	bool bWay = GetWay();

	switch (pCameraType)
	{//サイドビューの時は横にしか動かないように設定
	case CCamera::CANERA_TYPE::TYPE_SIDEVIEW:
		if (pKeyboard->GetPress(DIK_A) || pPad->GetPress(CInputPad::JOYKEY::JOYKEY_LEFT))
		{
			vecDirection.x -= 1.0f;
			bWay = false;
		}
		else if (pKeyboard->GetPress(DIK_D) || pPad->GetPress(CInputPad::JOYKEY::JOYKEY_RIGHT))
		{
			vecDirection.x += 1.0f;
			bWay = true;
		}
		break;
	case CCamera::CANERA_TYPE::TYPE_PARALLEL_SIDEVIEW:
		if (pKeyboard->GetPress(DIK_A) || pPad->GetPress(CInputPad::JOYKEY::JOYKEY_LEFT))
		{
			vecDirection.x -= 1.0f;
			bWay = false;
		}
		else if (pKeyboard->GetPress(DIK_D) || pPad->GetPress(CInputPad::JOYKEY::JOYKEY_RIGHT))
		{
			vecDirection.x += 1.0f;
			bWay = true;
		}
		break;
	default:
		if (pKeyboard->GetPress(DIK_W))
		{
			vecDirection.z += 1.0f;
		}
		if (pKeyboard->GetPress(DIK_S))
		{
			vecDirection.z -= 1.0f;
		}
		if (pKeyboard->GetPress(DIK_A))
		{
			vecDirection.x -= 1.0f;
			bWay = false;
		}
		else if (pKeyboard->GetPress(DIK_D))
		{
			vecDirection.x += 1.0f;
			bWay = true;
		}
		break;
	}

	//どっち向いてるか代入
	SetWay(bWay);

	//移動量取得
	D3DXVECTOR3 move = GetMove();

	//着地してるか取得
	bool bLanding = GetLaunding();

	if (vecDirection.x == 0.0f && vecDirection.z == 0.0f)
	{ // 動いてない。
		move.x = 0.0f;
		move.z = 0.0f;
	}
	else
	{
		float rotMoveY = atan2f(vecDirection.x, vecDirection.z);

		//オブジェクト2Dからrotを取得
		D3DXVECTOR3 rot = GetRot();

		//状態を取得
		CCharacter::CHARACTER_STATE state = GetState();

		if (state == CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE)
		{
			move.x += sinf(rotMoveY) * DEFAULT_MOVE * 0.5f;
			move.z += cosf(rotMoveY) * DEFAULT_MOVE * 0.5f;
		}
		else
		{
			move.x += sinf(rotMoveY) * DEFAULT_MOVE;
			move.z += cosf(rotMoveY) * DEFAULT_MOVE;
		}

		rot.y = rotMoveY + D3DX_PI;
		//rotを代入
		SetRot(rot);
	}
	if (m_nJumpCnt < MAX_JUMPCNT)
	{//ジャンプ数以下だったら
		if (pKeyboard->GetTrigger(DIK_SPACE) || pPad->GetTrigger(CInputPad::JOYKEY::JOYKEY_A))
		{
			move.y = DEFAULT_JUMP;
			bLanding = false; //空中
			m_nJumpCnt++; //ジャンプ数加算
		}
	}

	//移動量代入
	SetMove(move);

	//着地してるか代入
	SetLanding(bLanding);

}

//=============================================
//プレイヤーのデバッグ表示
//=============================================
void CPlayer::DebugPos()
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n\n[player]\npos:%.1f,%.1f,%.1f\nrot:%.1f,%.1f,%.1f"
		, GetPos().x, GetPos().y, GetPos().z, GetRot().x, GetRot().y, GetRot().z);
	//テキストの描画
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
#endif // _DEBUG


}


