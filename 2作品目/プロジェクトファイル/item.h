//=============================================
//
//3DTemplate[item.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _ITEM_H_ //これが定義されてないとき

#define _ITEM_H_
#include "main.h"
#include "billboard.h"
#include "button_UI.h"
#include "item_UI.h"

class CItem : public CBillboard
{
public:
	static const std::string SLASH_TEXTURE_NAME;	//テクスチャの名前
	static const std::string FLOW_TEXTURE_NAME;	//テクスチャの名前

	static const int ITEM_PRIORITY = 3; //描画順
	typedef enum
	{
		ITEMTYPE_NONE = 0,
		ITEMTYPE_PANETRARING_SLASH, //斬撃の剣
		ITEMTYPE_FLOW, //集中斬撃の剣
		ITEMTYPE_MAX,
	}ITEMTYPE;

	CItem(int nPriority = ITEM_PRIORITY);
	~CItem()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	//ブロック作成
	static CItem* Create(ITEMTYPE type, D3DXVECTOR3 pos,D3DXVECTOR3 size, D3DXVECTOR3 rot);
private:

	ITEMTYPE m_ItemType; //アイテムのタイプ
	void HitItem(); //アイテムとの当たり判定
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;

	static LPD3DXMESH m_pMesh; //メッシュ情報
	static 	LPD3DXBUFFER m_pBuffMat; //マテリアル情報
	static	DWORD m_dwNumMat; //マテリアル数;

	CButton_UI*m_pButton_UI; //「Fで拾う」3DUI
};
#endif