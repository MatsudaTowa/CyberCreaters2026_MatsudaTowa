//=============================================
//
//3DTemplate[title.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "title.h"
#include "title_screen.h"
#include "object.h"
#include "object2D.h"
#include "object3D.h"
#include "objectX.h"
#include "player.h"
#include "colision.h"
#include "block.h"
#include"player_test.h"
#include "field.h"
#include "manager.h"
#include "sound.h"

const std::string CTitle::BLOCK_FILE = "data\\FILE\\block.txt";


//=============================================
//コンストラクタ
//=============================================
CTitle::CTitle()
{
}

//=============================================
//デストラクタ
//=============================================
CTitle::~CTitle()
{
}

//=============================================
//初期化
//=============================================
HRESULT CTitle::Init()
{
    //地面生成
    CField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 0.0f, 1000.0f));

	//ブロック生成
	LoadBlock(&CTitle::BLOCK_FILE);

	//プレイヤー生成
	CPlayer_test* pPlayer_test = CPlayer_test::Create(D3DXVECTOR3(0.0f, 0.5f, -300.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f), 100);

    m_pTitleScreen[0] = CTitle_Screen::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f,150.0f,0.0f),D3DXVECTOR2(400.0f,200.0f),CTitle_Screen::TITLE_UI::UI_TITLE_ROGO);

    m_pTitleScreen[1]=CTitle_Screen::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 600.0f, 0.0f), D3DXVECTOR2(200.0f, 100.0f), CTitle_Screen::TITLE_UI::UI_TITLE_PRESS_BUTTON);

    return S_OK;
}

//=============================================
//終了
//=============================================
void CTitle::Uninit()
{
    CObject::ReleaseAll();
}

//=============================================
//更新
//=============================================
void CTitle::Update()
{
    CObject::UpdateAll();
    CInputKeyboard* pKeyboard = CManager::GetKeyboard();
    CInputPad* pPad = CManager::GetPad();

    //CFade*pFade= CFade::GetFade();
    if (pKeyboard->GetTrigger(DIK_RETURN) || pPad->GetTrigger(CInputPad::JOYKEY::JOYKEY_A))
    {
        CManager::m_pFade->SetFade(CScene::MODE::MODE_GAME);
    }
}

//=============================================
//描画
//=============================================
void CTitle::Draw()
{
}

//=============================================
//ブロック読み込み
//=============================================
void CTitle::LoadBlock(const std::string* pFileName)
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