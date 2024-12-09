//=============================================
//
//3DTemplate[block.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _BLOCK_H_ //これが定義されてないとき

#define _BLOCK_H_
#include "main.h"
#include "objectX.h"

class CBlock : public CObjectX
{
public:
	static const std::string MODEL_NAME;	//モデルの名前
	static const std::string WOOD_MODEL_NAME;	//モデルの名前
	static const std::string AZUMAYA_MODEL_NAME;	//モデルの名前
	static const std::string DANGOYA_MODEL_NAME;	//モデルの名前

	static const int BLOCK_PRIORITY = 3; //描画順
	typedef enum
	{
		BLOCKTYPE_NONE = 0,
		BLOCKTYPE_DEFAULT,
		BLOCKTYPE_WOOD,
		BLOCKTYPE_AZUMAYA,
		BLOCKTYPE_DANGOYA,
		BLOCKTYPE_MAX,
	}BLOCKTYPE;

	CBlock(int nPriority = BLOCK_PRIORITY);
	~CBlock()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	//ブロック作成
	static CBlock* Create(BLOCKTYPE type,D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife,bool bBreak);
private:

	BLOCKTYPE m_type;
	bool m_bBreak; //壊せるかどうか
	int m_nLife;
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;

	static LPD3DXMESH m_pMesh; //メッシュ情報
	static 	LPD3DXBUFFER m_pBuffMat; //マテリアル情報
	static	DWORD m_dwNumMat; //マテリアル数;
};
#endif