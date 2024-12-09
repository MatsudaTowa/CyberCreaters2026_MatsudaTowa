//=============================================
//
//スキップUI[skip_UI.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _SKIP_UI_H_ //これが定義されてないとき

#define _SKIP_UI_H_
#include "main.h"
#include "object2D.h"

class CSkip_UI : public CObject2D
{
public:

	static const std::string BUTTON_START_TEXTURE_NAME;	//テクスチャの名前
	static const std::string BUTTON_ENTER_TEXTURE_NAME;	//テクスチャの名前
	static const int TITLE_SCREEN_PRIORITY = 10;  //描画順
	static const int CHANGE_FRAME = 8;  //色のチェンジ
	CSkip_UI(int nPriority = TITLE_SCREEN_PRIORITY);
	~CSkip_UI()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CSkip_UI* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);
	void ColorChange();
	int m_nChangeCnt;
	bool  m_bPress;
	D3DXCOLOR m_col;
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;

};
#endif