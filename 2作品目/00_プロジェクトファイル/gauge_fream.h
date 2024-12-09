//=============================================
//
//ゲージフレーム管理[gauge_fream.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _GAUGE_FREAM_H_ //これが定義されてないとき

#define _GAUGE_FREAM_H_
#include "main.h"
#include "object2D.h"

//レンダラークラス
class CGauge_Fream : public CObject2D
{
public:
	static const std::string TEXTURE_NAME;	//テクスチャの名前
	static const int GAUGE_FREAM_PRIORITY = 80;  //描画順
	CGauge_Fream(int nPriority = GAUGE_FREAM_PRIORITY);
	~CGauge_Fream()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CGauge_Fream* Create(D3DXVECTOR3 pos,D3DXVECTOR2 size);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
};
#endif