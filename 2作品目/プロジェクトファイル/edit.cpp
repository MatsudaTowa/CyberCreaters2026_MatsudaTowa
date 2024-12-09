//=============================================
//
//エディター[edit.h]
//Auther Matsuda Towa
//
//=============================================
#include "edit.h"
#include "camera.h"
#include "manager.h"
#include "input.h"

//=============================================
//コンストラクタ
//=============================================
CEdit::CEdit()
{
}

//=============================================
//デストラクタ
//=============================================
CEdit::~CEdit()
{
}

//=============================================
//初期化
//=============================================
void CEdit::Init()
{
}

//=============================================
//更新
//=============================================
void CEdit::Update()
{
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();

	if (pKeyboard->GetTrigger(DIK_RETURN))
	{
		SetBlock();
	}
}

//=============================================
//ブロック設置
//=============================================
void CEdit::SetBlock()
{
	if (m_nNumBlock < CEdit::BLOCK_MAX)
	{
		CBlock*pBlock = CBlock::Create(CBlock::BLOCKTYPE::BLOCKTYPE_DEFAULT,D3DXVECTOR3(0.0f,20.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),1,false);

		CInputKeyboard * pKeyboard = CManager::GetKeyboard();

		//ブロックの座標取得
		D3DXVECTOR3 pos = pBlock->GetPos();

		if (pKeyboard->GetPress(DIK_D))
		{
			pos.x += 1.0f;
		}

		pBlock->SetPos(pos);
	}
}

//=============================================
//ブロック保存
//=============================================
void CEdit::SaveBlock()
{
}
