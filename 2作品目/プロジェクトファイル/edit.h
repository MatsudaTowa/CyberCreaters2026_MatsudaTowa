//=============================================
//
//エディター[edit.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _EDIT_H_ //これが定義されてないとき

#define _EDIT_H_

#include "main.h"
#include "block.h"
//=============================================
//エディタークラス
//=============================================
class CEdit
{
public:
	static const int BLOCK_MAX = 128; //描画順
	CEdit();
	~CEdit();

	void Init();

	void Update();

	void SetBlock(); //ブロックの設置
	void SaveBlock(); //ブロックの保存
private:
	int m_nNumBlock; //ブロックの設置数

	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		CBlock::BLOCKTYPE type;
	}EDIT_BLOCK_INFO;

	EDIT_BLOCK_INFO m_Edit_Block_Info;

	CBlock* m_EditBlockInfo;
};
#endif