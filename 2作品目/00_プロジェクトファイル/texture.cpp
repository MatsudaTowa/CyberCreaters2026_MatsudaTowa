//=============================================
//
//3DTemplate[texture.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "texture.h"
#include "manager.h"

//texパス
const std::string CTexture::TEXTURE_NAME[CTexture::TEXTURE::TEXTURE_MAX] =
{
	"data\\TEXTURE\\slash_test.png",
	"data\\TEXTURE\\acquisition_y.png",
	"data\\TEXTURE\\acquisition_F.png",
	"data\\TEXTURE\\effect000.jpg",
	"data\\TEXTURE\\bg_test.jpg",
	"data\\TEXTURE\\flow_anim.png",
	"data\\TEXTURE\\item_book000.png",
	"data\\TEXTURE\\item_book001.png",
	"data\\TEXTURE\\lockon.png",
	"data\\TEXTURE\\number_test.png",
	"data\\TEXTURE\\result_test.png",
	"data\\TEXTURE\\title_test.png",
};

//=============================================
//コンストラクタ
//=============================================
CTexture::CTexture()
{
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		m_apTexture[nCnt] = nullptr;
	}

	m_nNumAll = 0;
}

//=============================================
//デストラクタ
//=============================================
CTexture::~CTexture()
{
}

//=============================================
//テクスチャ破棄
//=============================================
void CTexture::Unload()
{
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		if (m_apTexture[nCnt] != nullptr)
		{

			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = nullptr;
			m_texName[nCnt] = nullptr;

		}
	}
	m_nNumAll = 0;

}

//=============================================
//テクスチャ登録
//=============================================
int CTexture::Regist(const std::string* pTex)
{
	int nIdx = 0;
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		if (m_apTexture[nCnt] == nullptr)
		{
			LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

			//テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,
				pTex->c_str(),
				&m_apTexture[nCnt]);
			
			//引数のファイルパスを保存
			m_texName[nCnt] = (std::string*)pTex;
			nIdx = nCnt;	//番号の保存
			m_nNumAll++;	//総数のカウントアップ
			break;
		}
		else if (m_texName[nCnt] ==pTex)
		{//引数のテクスチャが存在するなら

			//番号を代入してbreak
			nIdx = nCnt;
			break;
		}
	}
 	return nIdx;
}

//=============================================
//テクスチャアドレス取得
//=============================================
LPDIRECT3DTEXTURE9 CTexture::GetAddress(int nIdx)
{
	return m_apTexture[nIdx];
}
