//=============================================
//
//3DTemplate[result.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "result.h"
#include "result_screen.h"
#include "manager.h"

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
  
    return S_OK;
}

//=============================================
//終了
//=============================================
void CResult::Uninit()
{
    CObject::ReleaseAll();
}

//=============================================
//更新
//=============================================
void CResult::Update()
{
    CInputKeyboard* pKeyboard = CManager::GetKeyboard();
    CInputPad* pPad = CManager::GetPad();
    if (pKeyboard->GetTrigger(DIK_RETURN) || pPad->GetTrigger(CInputPad::JOYKEY::JOYKEY_A))
    {
        CManager::m_pFade->SetFade(CScene::MODE::MODE_TITLE);
    }
}

//=============================================
//描画
//=============================================
void CResult::Draw()
{
}
