//=============================================
//
//3DTemplate[character.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "character.h"
#include "block.h"
#include "player.h"
#include "field.h"
#include "colision.h"

//ボス戦のX座標
const float CCharacter::BOSS_FIELD_X = 600.0f;
//重力値
const float CCharacter::GRAVITY_MOVE = 1.5f;
//重力最大値
const float CCharacter::GRAVITY_MAX = 20.0f;

//=============================================
//コンストラクタ
//=============================================
CCharacter::CCharacter(int nPriority):CObjectX(nPriority),m_bLanding(false),m_bWay(false),m_move(D3DXVECTOR3(0.0f,0.0f,0.0f)),m_nLife(0)
,m_nStateCnt(0),m_oldpos(D3DXVECTOR3(0.0f,0.0f,0.0f)),m_State(CCharacter::CHARACTER_STATE::CHARACTER_NORMAL), 
m_PartsCnt(0), m_nMotionFrameCnt(0), m_nKeySetCnt(0), m_Motion(0), m_bLoopFinish(),m_Speed(), 
m_Jump(), m_pGun(),m_MotionSet(), m_pMove(),m_pAttack(), m_pCharacterState(), m_nJumpCnt(0)
{//イニシャライザーでプライオリティ設定、各メンバ変数初期化
	m_pMove = nullptr;
	m_pAttack = nullptr;
	m_pCharacterState = nullptr;
}

//=============================================
//デストラクタ
//=============================================
CCharacter::~CCharacter()
{
	if (m_pMove != nullptr)
	{
		delete m_pMove;
	}
	if (m_pAttack != nullptr)
	{
		delete m_pAttack;
	}
	if (m_pCharacterState != nullptr)
	{
		delete m_pCharacterState;
	}
}

//=============================================
//初期化
//=============================================
HRESULT CCharacter::Init()
{
	if (m_pCharacterState == nullptr)
	{
		m_pCharacterState = new CMoveState;
	}
	//最初どのモーションでもない値を代入
	m_Motion = -1;
	//ループモーション終わってる判定に
	m_bLoopFinish = true;
	//銃クラス作成
	//m_pGun = new CGun;
	//親クラスの初期化
	CObjectX::Init();
    return S_OK;
}

//=============================================
//終了
//=============================================
void CCharacter::Uninit()
{
	if (m_pGun != nullptr)
	{
		delete m_pGun;
		m_pGun = nullptr;
	}
    CObjectX::Uninit();
}

//=============================================
//更新
//=============================================
void CCharacter::Update()
{
	//重力処理
	Gravity();

	//位置取得
	D3DXVECTOR3 pos = GetPos();

	//移動量を更新(減速）
	m_move *= 1.0f - 0.3f;

	//過去の位置に今の位置を代入
	m_oldpos = pos;

	//移動量追加
	pos += m_move;

	//座標を更新
	SetPos(pos);

	//最大最小値取得
	D3DXVECTOR3 minpos = GetMinPos();
	D3DXVECTOR3 maxpos = GetMaxPos();

	if (m_bLanding)
	{//着地してるなら
		//ジャンプ数リセット
		m_nJumpCnt = 0;
	}

	//ブロックとの接触処理
	HitBlock();

	//床との接触処理
	HitField();

	//壁との接触処理
	HitWall();
}

//=============================================
//描画
//=============================================
void CCharacter::Draw()
{
	switch (m_State)
	{
	case CCharacter::CHARACTER_STATE::CHARACTER_NORMAL:
		CObjectX::Draw();
		break;
	case CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE:
		//ダメージ状態の色に変更
		CObjectX::Draw(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		break;
	default:
		break;
	}
}

//=============================================
//モーション用の描画
//=============================================
void CCharacter::MotionDraw(int NumParts)
{
	//デバイスの取得
	CRenderer* pRender = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
	D3DMATERIAL9 matDef; //現在のマテリアルの保存
	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス
	D3DXMATRIX MtxWorld = GetMtxWorld();

	//マトリックスの初期化
	D3DXMatrixIdentity(&MtxWorld);

	//αテストを有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);

	D3DXMatrixMultiply(&MtxWorld, &MtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);

	D3DXMatrixMultiply(&MtxWorld, &MtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &MtxWorld);

	for (int nCnt = 0; nCnt < NumParts; nCnt++)
	{
		switch (m_State)
		{
		case CCharacter::CHARACTER_STATE::CHARACTER_NORMAL:
			m_apModel[nCnt]->Draw();
			break;
		case CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE:
			//ダメージ状態の色に変更
			m_apModel[nCnt]->Draw(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			break;
		default:
			break;
		}
	}
}

//=============================================
//モーション用の描画(色付き)
//=============================================
void CCharacter::MotionDraw(int NumParts, D3DXCOLOR col)
{
	//デバイスの取得
	CRenderer* pRender = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
	D3DMATERIAL9 matDef; //現在のマテリアルの保存
	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス
	D3DXMATRIX MtxWorld = GetMtxWorld();

	//マトリックスの初期化
	D3DXMatrixIdentity(&MtxWorld);

	//αテストを有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);

	D3DXMatrixMultiply(&MtxWorld, &MtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);

	D3DXMatrixMultiply(&MtxWorld, &MtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &MtxWorld);

	for (int nCnt = 0; nCnt < NumParts; nCnt++)
	{
		switch (m_State)
		{
		case CCharacter::CHARACTER_STATE::CHARACTER_NORMAL:
			m_apModel[nCnt]->Draw(col);
			break;
		case CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE:
			//ダメージ状態の色に変更
			m_apModel[nCnt]->Draw(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			break;
		default:
			break;
		}
	}
}

//=============================================
//パーツのロード
//=============================================
void CCharacter::Load_Parts(const char* FileName)
{
	int nCnt = 0;
	int nCntName = 0;
	int nCntKey = 0; //キーを入れるパーツのカウント数
	int nCntMotion = 0; //キー数のカウント
	int nCntMotionSet = 0; //モーションの種類のカウント
	char aDataSearch[256];
	char aEqual[256]; //[＝]読み込み用
	char aGets[256]; //モーションのいらないもの読み込み用
	float speed = 0.0f;//移動量
	float jump = 0.0f;//ジャンプ力
	float radius = 0.0f;//半径
	float height = 0.0f;//高さ

	char Path[256][MAX_PARTS]; //パーツのパス

	//ファイルの読み込み
	FILE* pFile;

	//ファイルの読み込み
	pFile = fopen(FileName, "r");

	if (pFile == NULL)
	{//種類の情報のデータファイルが開けなかった場合
		//処理を終了する
		return;
	}

	//ENDが見つかるまで読み込みを繰り返す
	while (1)
	{
		fscanf(pFile, "%s", aDataSearch); //検索

		if (!strcmp(aDataSearch, "END"))
		{//読み込みを終了
			fclose(pFile);
			break;
		}
		if (aDataSearch[0] == '#')
		{
			continue;
		}

		if (!strcmp(aDataSearch, "NUM_MODEL"))
		{//モデル数読み込み
			fscanf(pFile, "%s", &aEqual[0]);
			fscanf(pFile, "%d", &m_PartsCnt);
		}
		if (!strcmp(aDataSearch, "MODEL_FILENAME"))
		{//モデルファイル読み込み
			fscanf(pFile, "%s", &aEqual[0]);
			fscanf(pFile, "%s", &Path[0][nCntName]);
			//モデルパーツのクリエイト
			m_apModel[nCntName] = CModel_Parts::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), &Path[0][nCntName]);

			nCntName++;
		}

		if (!strcmp(aDataSearch, "CHARACTERSET"))
		{
			//項目ごとのデータを代入
			while (1)
			{
				fscanf(pFile, "%s", aDataSearch); //検索

				if (!strcmp(aDataSearch, "END_CHARACTERSET"))
				{
					break;
				}
				else if (!strcmp(aDataSearch, "MOVE"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f", &m_Speed);
				}
				else if (!strcmp(aDataSearch, "JUMP"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f", &m_Jump);
				}
				else if (!strcmp(aDataSearch, "RADIUS"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f", &radius);
				}
				else if (!strcmp(aDataSearch, "HEIGHT"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f", &height);
				}
				else if (!strcmp(aDataSearch, "PARTSSET"))
				{
					//項目ごとのデータを代入
					while (1)
					{
						fscanf(pFile, "%s", aDataSearch); //検索

						if (!strcmp(aDataSearch, "END_PARTSSET"))
						{
							break;
						}
						else if (!strcmp(aDataSearch, "INDEX"))
						{
							fscanf(pFile, "%s", &aEqual[0]);
							fscanf(pFile, "%d", &m_apModel[nCnt]->m_nIdx);
						}
						else if (!strcmp(aDataSearch, "PARENT"))
						{
							fscanf(pFile, "%s", &aEqual[0]);
							fscanf(pFile, "%d", &m_apModel[nCnt]->m_nIdxModelParent);

							//親を設定
							if (m_apModel[nCnt]->m_nIdxModelParent == -1)
							{
								m_apModel[nCnt]->SetParent(nullptr);
							}
							else
							{
								m_apModel[nCnt]->SetParent(m_apModel[m_apModel[nCnt]->m_nIdxModelParent]);
							}

						}
						else if (!strcmp(aDataSearch, "POS"))
						{
							fscanf(pFile, "%s", &aEqual[0]);
							fscanf(pFile, "%f %f %f",
								&m_apModel[nCnt]->m_pos.x,
								&m_apModel[nCnt]->m_pos.y,
								&m_apModel[nCnt]->m_pos.z);

							m_apModel[nCnt]->SetPos(m_apModel[nCnt]->m_pos);

							m_apModel[nCnt]->m_Tpos = m_apModel[nCnt]->m_pos;
						}
						else if (!strcmp(aDataSearch, "ROT"))
						{
							fscanf(pFile, "%s", &aEqual[0]);
							fscanf(pFile, "%f %f %f",
								&m_apModel[nCnt]->m_rot.x,
								&m_apModel[nCnt]->m_rot.y,
								&m_apModel[nCnt]->m_rot.z);

							m_apModel[nCnt]->SetRot(m_apModel[nCnt]->m_rot);

							m_apModel[nCnt]->m_Trot = m_apModel[nCnt]->m_rot;

						}
					}
					nCnt++; //データ数加算
				}
			}
		}
		if (!strcmp(aDataSearch, "MOTIONSET"))
		{
			//項目ごとのデータを代入
			while (1)
			{
				fscanf(pFile, "%s", aDataSearch); //検索

				if (!strcmp(aDataSearch, "END_MOTIONSET"))
				{
					nCntMotion = 0;
					break;
				}
				else if (!strcmp(aDataSearch, "LOOP"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%d", &m_MotionSet[nCntMotionSet].nLoop);
				}
				else if (!strcmp(aDataSearch, "NUM_KEY"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%d", &m_MotionSet[nCntMotionSet].nNumKey);

				}
				else if (!strcmp(aDataSearch, "KEYSET"))
				{
					fgets(&aGets[0], 39, pFile);

					//項目ごとのデータを代入
					while (1)
					{
						fscanf(pFile, "%s", aDataSearch); //検索

						if (!strcmp(aDataSearch, "END_KEYSET"))
						{
							nCntKey = 0;
							break;
						}

						else if (!strcmp(aDataSearch, "FRAME"))
						{
							fscanf(pFile, "%s", &aEqual[0]);
							fscanf(pFile, "%d", &m_MotionSet[nCntMotionSet].keySet[nCntMotion].nFrame);
						}
						else if (!strcmp(aDataSearch, "KEY"))
						{
							//項目ごとのデータを代入
							while (1)
							{
								fscanf(pFile, "%s", aDataSearch);

								if (!strcmp(aDataSearch, "END_KEY"))
								{
									break;
								}
								else if (!strcmp(aDataSearch, "POS"))
								{
									fscanf(pFile, "%s", &aEqual[0]);
									fscanf(pFile, "%f %f %f", &m_MotionSet[nCntMotionSet].keySet[nCntMotion].key[nCntKey].pos.x,
										&m_MotionSet[nCntMotionSet].keySet[nCntMotion].key[nCntKey].pos.y,
										&m_MotionSet[nCntMotionSet].keySet[nCntMotion].key[nCntKey].pos.z);
								}
								else if (!strcmp(aDataSearch, "ROT"))
								{
									fscanf(pFile, "%s", &aEqual[0]);
									fscanf(pFile, "%f %f %f", &m_MotionSet[nCntMotionSet].keySet[nCntMotion].key[nCntKey].rot.x,
										&m_MotionSet[nCntMotionSet].keySet[nCntMotion].key[nCntKey].rot.y,
										&m_MotionSet[nCntMotionSet].keySet[nCntMotion].key[nCntKey].rot.z);
								}
							}
							nCntKey++; //パーツ数加算
						}
					}
					nCntMotion++; //キー数加算
				}
			}
			nCntMotionSet++; //キータイプ数加算
		}
	}
}

//=============================================
//モーション処理
//=============================================
void CCharacter::Motion(int NumParts)
{
	D3DXVECTOR3 MovePos[MAX_PARTS];
	D3DXVECTOR3 MoveRot[MAX_PARTS];

	int nNextKey = (m_nKeySetCnt + 1) % m_MotionSet[m_Motion].nNumKey;

	for (int nMotionCnt = 0; nMotionCnt < NumParts; nMotionCnt++)
	{
		MovePos[nMotionCnt] = (m_MotionSet[m_Motion].keySet[nNextKey].key[nMotionCnt].pos - m_MotionSet[m_Motion].keySet[m_nKeySetCnt].key[nMotionCnt].pos) / (float)m_MotionSet[m_Motion].keySet[m_nKeySetCnt].nFrame;
		MoveRot[nMotionCnt] = (m_MotionSet[m_Motion].keySet[nNextKey].key[nMotionCnt].rot - m_MotionSet[m_Motion].keySet[m_nKeySetCnt].key[nMotionCnt].rot) / (float)m_MotionSet[m_Motion].keySet[m_nKeySetCnt].nFrame;

		m_apModel[nMotionCnt]->m_pos += MovePos[nMotionCnt];
		m_apModel[nMotionCnt]->m_rot += MoveRot[nMotionCnt];
		//Pos.x += MovePos[nMotionCnt].x;
		//SetPos(Pos);
	}

	m_nMotionFrameCnt++;

	if (m_nMotionFrameCnt > m_MotionSet[m_Motion].keySet[m_nKeySetCnt].nFrame)
	{

		m_nMotionFrameCnt = 0;
		m_nKeySetCnt = (m_nKeySetCnt + 1) % m_MotionSet[m_Motion].nNumKey;
		if (m_nKeySetCnt == 0 && m_MotionSet[m_Motion].nLoop == 0)
		{//キーが終わりループモーションじゃなければ
			//モーションをニュートラルに
			SetMotion(0);
			//終わった判定
			m_bLoopFinish = true;
		}
		
	}
}

//=====================================
//引数で指定したモーションに切り替える
//=====================================
void CCharacter::SetMotion(int Motion)
{
	if (m_Motion != Motion)
	{
		m_Motion = Motion;

		//フレームリセット
		m_nMotionFrameCnt = 0;

		//キーカウントリセット
		m_nKeySetCnt = 0;

		if (m_MotionSet[m_Motion].nLoop == 0)
		{
			//終わった判定
			m_bLoopFinish = false;
		}

		for (int nCntParts = 0; nCntParts < m_PartsCnt; nCntParts++)
		{
			m_apModel[nCntParts]->m_pos = m_apModel[nCntParts]->m_Tpos;
			m_apModel[nCntParts]->m_rot = m_apModel[nCntParts]->m_Trot;
			m_apModel[nCntParts]->m_rot = m_MotionSet[Motion].keySet[0].key[nCntParts].rot;
		}
	}
}


//=============================================
//重力処理
//=============================================
void CCharacter::Gravity()
{
    if (m_move.y < GRAVITY_MAX)
    {
        m_move.y -= GRAVITY_MOVE;
    }
}

//=============================================
//ジャンプ処理
//=============================================
void CCharacter::Jump()
{
	m_move.y = m_Jump; //ジャンプ力代入
	m_bLanding = false; //空中状態
}

//=============================================
//ブロックとの接触判定
//=============================================
void CCharacter::HitBlock()
{
	D3DXVECTOR3 CharacterPos = GetPos();

	//サイズ取得
	D3DXVECTOR3 CharacterMin = GetMinPos();
	D3DXVECTOR3 CharacterMax = GetMaxPos();
	BOOL hit;
	FLOAT distance;

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(CBlock::BLOCK_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//ヌルポインタじゃなければ
			//タイプ取得
			CObject::OBJECT_TYPE type = pObj->GetType();

			//ブロックとの当たり判定
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_BLOCK)
			{
				//安全にダウンキャスト
				CBlock* pBlock = dynamic_cast<CBlock*>(pObj);

				//D3DXVECTOR3 dir = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

				//D3DXIntersect(pBlock->GetpMesh(), &CharacterPos, &dir, &hit, NULL, NULL, NULL, &distance, NULL, NULL);

				//当たり判定チェック
				CColision::COLISION Checkcolision_X = CColision::CheckColision_X(m_oldpos, CharacterPos,CharacterMin,CharacterMax,pBlock->GetPos(),pBlock->GetMinPos(),pBlock->GetMaxPos());
				
				CColision::COLISION Checkcolision_Y = CColision::CheckColision_Y(m_oldpos, CharacterPos, CharacterMin, CharacterMax, pBlock->GetPos(), pBlock->GetMinPos(), pBlock->GetMaxPos());

				CColision::COLISION Checkcolision_Z = CColision::CheckColision_Z(m_oldpos, CharacterPos, CharacterMin, CharacterMax, pBlock->GetPos(), pBlock->GetMinPos(), pBlock->GetMaxPos());

				if (Checkcolision_X == CColision::COLISION::COLISON_X)
				{//x方向に当たってたら
					CharacterPos.x = m_oldpos.x;
					m_move.x = 0.0f;
				}
				if (Checkcolision_Z == CColision::COLISION::COLISON_Z)
				{//z方向に当たってたら
					CharacterPos.z = m_oldpos.z;
					m_move.z = 0.0f;
				}
				if (Checkcolision_Y == CColision::COLISION::COLISON_UNDER_Y)
				{//y(下)方向に当たってたら
					CharacterPos.y = m_oldpos.y;
				}

				if (Checkcolision_Y == CColision::COLISION::COLISON_TOP_Y)
				{//y(上)方向に当たってたら
					CharacterPos.y = m_oldpos.y;
					m_move.y = 0.0f;
					m_bLanding = true; //着地
				}
			}
		}
	}
	//SetPos(D3DXVECTOR3(CharacterPos.x, CharacterPos.y - distance, CharacterPos.z));

	SetPos(CharacterPos);
}


//=============================================
//床との接触判定
//=============================================
void CCharacter::HitField()
{
	D3DXVECTOR3 CharacterPos = GetPos();

	//サイズ取得
	D3DXVECTOR3 CharacterMin = GetMinPos();
	D3DXVECTOR3 CharacterMax = GetMaxPos();

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(CField::FIELD_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//ヌルポインタじゃなければ
			//タイプ取得
			CObject::OBJECT_TYPE type = pObj->GetType();

			//ブロックとの当たり判定
			//床との当たり判定
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_FIELD)
			{
				CField* pField = dynamic_cast<CField*>(pObj);

				//当たり判定チェック
				CColision::COLISION Checkcolision_Y = CColision::CheckColision_Y(m_oldpos, CharacterPos, CharacterMin, CharacterMax, pField->GetPos(), pField->GetSize());

				if (Checkcolision_Y == CColision::COLISION::COLISON_TOP_Y)
				{//y(上)方向に当たってたら
					CharacterPos.y = m_oldpos.y;
					m_move.y = 0.0f;
					m_bLanding = true; //着地
				}

				//TODO:壁の当たり判定やったらこれを使う必要なくなる
				{
					if (m_oldpos.x > pField->GetPos().x - pField->GetSize().x
						&& CharacterPos.x < pField->GetPos().x - pField->GetSize().x)
					{
						CharacterPos.x = m_oldpos.x;
						m_move.x = 0.0f;
					}

					if (m_oldpos.x < pField->GetPos().x + pField->GetSize().x
						&& CharacterPos.x > pField->GetPos().x + pField->GetSize().x)
					{
						CharacterPos.x = m_oldpos.x;
						m_move.x = 0.0f;
					}


					if (m_oldpos.z > pField->GetPos().z - pField->GetSize().z
						&& CharacterPos.z < pField->GetPos().z - pField->GetSize().z)
					{
						CharacterPos.z = m_oldpos.z;
						m_move.x = 0.0f;
					}

					if (m_oldpos.z < pField->GetPos().z + pField->GetSize().z
						&& CharacterPos.z > pField->GetPos().z + pField->GetSize().z)
					{
						CharacterPos.z = m_oldpos.z;
						m_move.x = 0.0f;
					}
				}
				
			}
		}
	}
	SetPos(CharacterPos);
}

//=============================================
//壁との接触判定
//=============================================
void CCharacter::HitWall()
{
	D3DXVECTOR3 CharacterPos = GetPos();

	//サイズ取得
	D3DXVECTOR3 CharacterMin = GetMinPos();
	D3DXVECTOR3 CharacterMax = GetMaxPos();

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(CWall::WALL_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//ヌルポインタじゃなければ
			//タイプ取得
			CObject::OBJECT_TYPE type = pObj->GetType();

			//ブロックとの当たり判定
			//床との当たり判定
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_WALL)
			{
				CWall* pWall = dynamic_cast<CWall*>(pObj);

				ColisionWall_X(CharacterPos, CharacterMin, CharacterMax, pWall);
				ColisionWall_Z(CharacterPos, CharacterMin, CharacterMax, pWall);
			}
		}
	}
	SetPos(CharacterPos);
}

//=============================================
//壁との接触判定_X
//=============================================
void CCharacter::ColisionWall_X(D3DXVECTOR3& CharacterPos, const D3DXVECTOR3& CharacterMin, const D3DXVECTOR3& CharacterMax, CWall* pWall)
{
	//当たり判定チェック
	CColision::COLISION Checkcolision_X = CColision::CheckColision_X(m_oldpos, CharacterPos, CharacterMin, CharacterMax, pWall->GetPos(), pWall->GetSize());
	if (Checkcolision_X == CColision::COLISION::COLISON_X)
	{//x方向に当たってたら
		CharacterPos.x = m_oldpos.x;
		m_move.x = 0.0f;
	}
}

//=============================================
//壁との接触判定_Z
//=============================================
void CCharacter::ColisionWall_Z(D3DXVECTOR3& CharacterPos, const D3DXVECTOR3& CharacterMin, const D3DXVECTOR3& CharacterMax, CWall* pWall)
{
	//当たり判定チェック
	CColision::COLISION Checkcolision_Z = CColision::CheckColision_Z(m_oldpos, CharacterPos, CharacterMin, CharacterMax, pWall->GetPos(), pWall->GetSize());
	if (Checkcolision_Z == CColision::COLISION::COLISON_Z)
	{//z方向に当たってたら
		CharacterPos.z = m_oldpos.z;
		m_move.z = 0.0f;
	}
}

//=============================================
//移動量取得
//=============================================
D3DXVECTOR3& CCharacter::GetMove()
{
    return m_move;
}

//=============================================
//過去の位置取得
//=============================================
D3DXVECTOR3& CCharacter::GetOldPos()
{
    return m_oldpos;
}

//=============================================
//着地してるかどうか取得
//=============================================
bool& CCharacter::GetLaunding()
{
    return m_bLanding;
}

//=============================================
//どっち向いてるかどうかを取得(true:右false:左)
//=============================================
bool& CCharacter::GetWay()
{
    return m_bWay;
}

//=============================================
//終わってるか取得
//=============================================
bool& CCharacter::GetFinish()
{
	return m_bLoopFinish;
}

//=============================================
//体力取得
//=============================================
int& CCharacter::GetLife()
{
	return m_nLife;
}

float& CCharacter::GetSpeed()
{
	return m_Speed;	
}


//=============================================
//状態取得
//=============================================
CCharacter::CHARACTER_STATE& CCharacter::GetState()
{
	return m_State;
}

//=============================================
//ステートカウント取得
//=============================================
int& CCharacter::GetStateCnt()
{
	return m_nStateCnt;
}

//=============================================
//ジャンプ数取得
//=============================================
int& CCharacter::GetJumpCnt()
{
	return m_nJumpCnt;
}

//=============================================
//キャラクターのステート変更
//=============================================
void CCharacter::ChangeState(CCharacterState* state)
{
	//今のステートを消し引数のステートに切り替える
	if (m_pCharacterState != nullptr)
	{
		delete m_pCharacterState;
		m_pCharacterState = state;
	}
}
