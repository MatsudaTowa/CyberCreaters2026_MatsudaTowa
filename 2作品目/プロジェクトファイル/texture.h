//=============================================
//
//3DTemplate[texture.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _TEXTURE_H_ //これが定義されてないとき

#define _TEXTURE_H_
#include "main.h"

class CTexture
{
public:
	typedef enum
	{
		BULLET = 0,
		UI_PAD_Y,
		UI_KEYBOARD_F,
		EFFECT,
		FIELD,
		FLOW,
		ITEM_00,
		ITEM_01,
		LOCKON,
		NUMBER,
		RESULT,
		TITLE,
		TEXTURE_MAX,
	}TEXTURE;
	static const std::string TEXTURE_NAME[TEXTURE_MAX];
	static const int MAX_TEX = 256; //テクスチャの数
	CTexture();
	~CTexture();
	void Unload(); //テクスチャ破棄
	int Regist(const std::string*pTex);
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx);
private:
	LPDIRECT3DTEXTURE9 m_apTexture[MAX_TEX]; //テクスチャへのポインタ
	std::string* m_texName[MAX_TEX]; //テクスチャネーム保存用
	int m_nNumAll; //テクスチャ総数
};
#endif