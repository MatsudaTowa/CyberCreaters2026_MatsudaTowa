//=============================================
//
//3DTemplate[result.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "result.h"
#include "result_screen.h"
#include "manager.h"
#include "wave.h"
#include "game.h"

//スコア設定
CScore* CResult::m_pScore = nullptr;

//=============================================
//コンストラクタ
//=============================================
CResult::CResult()
{
}

//=============================================
//デストラクタ
//=============================================
CResult::~CResult()
{
}

//=============================================
//初期化
//=============================================
HRESULT CResult::Init()
{
    //スコア初期化
    if (m_pScore == nullptr)
    {
        m_pScore = new CScore;

        m_pScore->Init();
    }

    CResult_Screen::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f, 0.0f));
  
    return S_OK;
}

//=============================================
//終了
//=============================================
void CResult::Uninit()
{
    for (int nCnt = 0; nCnt < CManager::NUM_RESULT_FILE; nCnt++)
    {
        CManager::ExportScoreReset(&CManager::RESULT_SCORE_FILE[nCnt]);
    }
    if (m_pScore != nullptr)
    {
        m_pScore->Uninit();
        m_pScore = nullptr;
    }

    CObject::ReleaseAll();
}

//=============================================
//更新
//=============================================
void CResult::Update()
{
    CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();
    CInputPad* pPad = CManager::GetInstance()->GetPad();

    if (m_pScore != nullptr)
    {
        m_pScore->Update();
    }

    if (pKeyboard->GetTrigger(DIK_RETURN) || pPad->GetTrigger(CInputPad::JOYKEY::JOYKEY_A))
    {
        CManager::GetInstance()->GetFade()->SetFade(CScene::MODE::MODE_TITLE);
    }
}

//=============================================
//描画
//=============================================
void CResult::Draw()
{
}
