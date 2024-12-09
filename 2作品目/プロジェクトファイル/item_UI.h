//=============================================
//
//アイテムのUI[item_UI.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _ITEM_UI_H_ //これが定義されてないとき

#define _ITEM_UI_H_
#include "main.h"
#include "object2D.h"

//アイテムUIクラス
class CItem_UI : public CObject2D
{
public:
	static const std::string SLASH_TEXTURE_NAME;	//テクスチャの名前
	static const std::string FLOW_TEXTURE_NAME;	//テクスチャの名前
	static const int ITEM_UI_PRIORITY = 80;  //描画順

	typedef enum
	{
		ITEM_UI_TYPE_NONE = 0,
		ITEM_UI_TYPE_PANETRARING_SLASH,
		ITEM_UI_TYPE_FLOW,
		ITEM_UI_TYPE_MAX,
	}ITEM_UI_TYPE;

	CItem_UI(int nPriority = ITEM_UI_PRIORITY);
	~CItem_UI()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void SetTex(ITEM_UI_TYPE type);
	static CItem_UI* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	ITEM_UI_TYPE m_type;
};
#endif