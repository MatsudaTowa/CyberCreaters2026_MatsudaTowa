//=============================================
//
//3DTemplate[result.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "result.h"
#include "result_screen.h"
#include "manager.h"
#include "evaluation.h"

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
    CResult_Screen::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f, 0.0f));
    CSound* pSound = CManager::GetSound();

    pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_BGM_RESULT);

    //スコア初期化
    if (m_pScore == nullptr)
    {
        m_pScore = new CScore;

        m_pScore->Init();
    }
    int nScore = m_pScore->GetScore();
    m_pScore->AddScore(nScore);

    //スコアによって変える
    if(nScore >= 5000)
    {
        CEvaluation::Create(D3DXVECTOR3(200.0f,480.0f,0.0f),D3DXVECTOR2(200.0f,200.0f),CEvaluation::EVALUATION::EVALUATION_S);
    }
    else if (nScore >= 3000 && nScore < 5000)
    {
        CEvaluation::Create(D3DXVECTOR3(200.0f, 480.0f, 0.0f), D3DXVECTOR2(200.0f, 200.0f), CEvaluation::EVALUATION::EVALUATION_A);
    }
    else if (nScore >= 1000 && nScore < 3000)
    {
        CEvaluation::Create(D3DXVECTOR3(200.0f, 480.0f, 0.0f), D3DXVECTOR2(200.0f, 200.0f), CEvaluation::EVALUATION::EVALUATION_B);
    }
    else if (nScore >= 0 && nScore < 1000)
    {
        CEvaluation::Create(D3DXVECTOR3(200.0f, 480.0f, 0.0f), D3DXVECTOR2(200.0f, 200.0f), CEvaluation::EVALUATION::EVALUATION_C);
    }
    return S_OK;
}

//=============================================
//終了
//=============================================
void CResult::Uninit()
{
    CSound* pSound = CManager::GetSound();
    //サウンドの停止
    pSound->StopSound();
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
    CObject::UpdateAll();
    if (m_pScore != nullptr)
    {
        m_pScore->Update();
    }
    CInputKeyboard* pKeyboard = CManager::GetKeyboard();
    CInputPad* pPad = CManager::GetPad();
    if (pKeyboard->GetTrigger(DIK_RETURN) || pPad->GetTrigger(CInputPad::JOYKEY::JOYKEY_A))
    {
        CManager::SetMode(CScene::MODE::MODE_TITLE);
    }
}

//=============================================
//描画
//=============================================
void CResult::Draw()
{
}
