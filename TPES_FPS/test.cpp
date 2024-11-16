//=============================================
//
//テストシーン[test.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "test.h"
#include "object.h"
#include "object2D.h"
#include "object3D.h"
#include "objectX.h"
#include "player.h"
#include "colision.h"
#include "block.h"
#include "field.h"
#include "manager.h"

//読み込むブロック情報のファイル
const std::string CTest::BLOCK_FILE = "data\\FILE\\block_test.txt";

//=============================================
// コンストラクタ
//=============================================
CTest::CTest()
{
}

//=============================================
// デストラクタ
//=============================================
CTest::~CTest()
{
}

//=============================================
// 初期化
//=============================================
HRESULT CTest::Init()
{
	//ブロック生成
	LoadBlock(&CTest::BLOCK_FILE);

	//プレイヤー生成
	CPlayer_test* pPlayer_test = CPlayer_test::Create(D3DXVECTOR3(0.0f, 0.5f, 0.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f), 100);
	return S_OK;
}

//=============================================
// 終了
//=============================================
void CTest::Uninit()
{
	CObject::ReleaseAll();
}

//=============================================
// 更新
//=============================================
void CTest::Update()
{
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();

	//if (m_bEdit == false)
	//{
	CObject::UpdateAll();

	if (pKeyboard->GetTrigger(DIK_RETURN))
	{
		CManager::m_pFade->SetFade(CScene::MODE::MODE_RESULT);
	}
}

//=============================================
// 描画
//=============================================
void CTest::Draw()
{
}

//=============================================
// ブロック読み込み
//=============================================
void CTest::LoadBlock(const std::string* pFileName)
{
	char aDataSearch[BLOCK_TXT_MAX];
	char aEqual[BLOCK_TXT_MAX]; //[＝]読み込み用
	int nNumBlock; //ブロックの数

	//ファイルの読み込み
	FILE* pFile = fopen(pFileName->c_str(), "r");

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

		if (!strcmp(aDataSearch, "NUM_BLOCK"))
		{//モデル数読み込み
			fscanf(pFile, "%s", &aEqual[0]);
			fscanf(pFile, "%d", &nNumBlock);
		}
		if (!strcmp(aDataSearch, "BLOCKSET"))
		{
			//項目ごとのデータを代入
			while (1)
			{
				fscanf(pFile, "%s", aDataSearch); //検索

				if (!strcmp(aDataSearch, "END_BLOCKSET"))
				{
					//エネミー生成
					CBlock::Create(m_LoadBlock.type, m_LoadBlock.pos, m_LoadBlock.rot, 1, false);
					break;
				}
				else if (!strcmp(aDataSearch, "POS"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f %f %f",
						&m_LoadBlock.pos.x,
						&m_LoadBlock.pos.y,
						&m_LoadBlock.pos.z);
				}
				else if (!strcmp(aDataSearch, "ROT"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f %f %f",
						&m_LoadBlock.rot.x,
						&m_LoadBlock.rot.y,
						&m_LoadBlock.rot.z);
				}
				else if (!strcmp(aDataSearch, "TYPE"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%d", &m_LoadBlock.type);
				}
			}
		}
	}
}
