//=============================================
//
//評価[evaluation.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _EVALUATION_H_ //これが定義されてないとき

#define _EVALUATION_H_
#include "main.h"
#include "object2D.h"

class CEvaluation : public CObject2D
{
public:
	static const std::string TEX_EVALUATION_S;	//テクスチャの名前
	static const std::string TEX_EVALUATION_A;	//テクスチャの名前
	static const std::string TEX_EVALUATION_B;	//テクスチャの名前
	static const std::string TEX_EVALUATION_C;	//テクスチャの名前
	static const int EVALUATION_PRIORITY = 80;  //描画順

	typedef enum
	{
		EVALUATION_NONE = 0,
		EVALUATION_S,
		EVALUATION_A,
		EVALUATION_B,
		EVALUATION_C,
		EVALUATION_MAX,
	}EVALUATION;

	CEvaluation(int nPriority = EVALUATION_PRIORITY);
	~CEvaluation()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CEvaluation* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,EVALUATION evaluation);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;

};
#endif