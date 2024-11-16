//=============================================
//
//3DTemplate[object2D.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _OBJECT2D_H_ //これが定義されてないとき

#define _OBJECT2D_H_
#include "main.h"
#include "object.h"

//2Dオブジェクトクラス
class CObject2D : public CObject
{
public:
	CObject2D(int nPriority = 3);
	~CObject2D()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void BindTexture(LPDIRECT3DTEXTURE9 pTex);

	//posの代入
	void SetPos(D3DXVECTOR3 pos)
	{
		m_pos = pos;
	}

	//rotの代入
	void SetRot(D3DXVECTOR3 rot)
	{
		m_rot = rot;
	}

	//サイズの代入
	void SetSize(D3DXVECTOR2 size)
	{
		m_size = size;
	}

	//テクスチャ座標の代入
	void SetTexPos(D3DXVECTOR2 tex)
	{
		m_tex_pos = tex;
	}

	//テクスチャ座標の代入
	void SetVtxBuff(LPDIRECT3DVERTEXBUFFER9 Buff)
	{
		m_pVtxBuff = Buff;
	}


	//頂点座標の代入
	void SetVtx(float rhw, D3DCOLOR col);

	//頂点座標(拡縮、回転)の代入
	void SetVtx(float rhw, D3DCOLOR col,float fAngle,float fLength);

	void SetVtx_FootPos(float rhw, D3DCOLOR col,float fAngle,float fLength);

	//posの取得
	D3DXVECTOR3& GetPos();

	//rotの取得
	D3DXVECTOR3& GetRot();

	//サイズの取得
	D3DXVECTOR2& GetSize();

	//テクスチャ座標の取得
	D3DXVECTOR2& GetTexPos();

	LPDIRECT3DVERTEXBUFFER9& GetVtxBuff();

private:

	LPDIRECT3DTEXTURE9 m_pTexture; //テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //頂点バッファへのポインタ


	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR2 m_size;
	D3DXVECTOR2 m_tex_pos; //tex座標

};
#endif