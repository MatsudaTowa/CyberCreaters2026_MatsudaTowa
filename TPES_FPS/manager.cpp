//=============================================
//
//3DTemplate[manager.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "manager.h"
#include "renderer.h"
//#include "fade.h"

//シーン設定
CScene* CManager::m_pScene = nullptr;

////シーン設定
//CFade* CManager::m_pFade = nullptr;

//レンダラー設定
CRenderer*CManager::m_pRenderer = nullptr;

//キーボード設定
CInputKeyboard*CManager::m_pKeyboard = nullptr;

//マウス設定
CInputMouse* CManager::m_pMouse = nullptr;

//Pad設定
CInputPad* CManager::m_pPad = nullptr;

//カメラ設定
CCamera*CManager::m_pCamera = nullptr;

//ライト設定
CLight*CManager::m_pLight = nullptr;

//テクスチャ設定
CTexture* CManager::m_pTexture = nullptr;

//モデル設定
CModel* CManager::m_pModel = nullptr;

//サウンド設定
CSound* CManager::m_pSound = nullptr;

//フェード設定
CFade* CManager::m_pFade = nullptr;

//=============================================
//コンストラクタ
//=============================================
CManager::CManager()
{
}

//=============================================
//デストラクタ
//=============================================
CManager::~CManager()
{
}

//=============================================
//初期化
//=============================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{

	//生成＆初期化
	if (m_pRenderer == nullptr)
	{
		m_pRenderer = new CRenderer();
		m_pRenderer->Init(hWnd,bWindow);
	}
	if (m_pKeyboard == nullptr)
	{
		m_pKeyboard = new CInputKeyboard();

		//キーボードの初期化処理
		if (FAILED(m_pKeyboard->Init(hInstance, hWnd)))
		{
			return E_FAIL;
		}
	}
	if (m_pMouse == nullptr)
	{
		m_pMouse = new CInputMouse();

		//マウスの初期化処理
		if (FAILED(m_pMouse->Init(hInstance, hWnd)))
		{
			return E_FAIL;
		}
	}
	if (m_pPad == nullptr)
	{
		m_pPad = new CInputPad();

		//マウスの初期化処理
		if (FAILED(m_pPad->Init(hInstance, hWnd)))
		{
			return E_FAIL;
		}
	}

	//カメラ生成
	if (m_pCamera == nullptr)
	{
		m_pCamera = new CCamera();
		m_pCamera->Init();
	}

	if (m_pScene == nullptr)
	{
		m_pScene =new CScene();
		m_pScene->Init();

	}

	//ライト生成
	if (m_pLight == nullptr)
	{
		m_pLight = new CLight();
		m_pLight->Init();
	}

	//テクスチャ生成
	if (m_pTexture == nullptr)
	{
		m_pTexture = new CTexture();
	}

	//モデル生成
	if (m_pModel == nullptr)
	{
		m_pModel = new CModel();
	}

	//サウンド生成
	if (m_pSound == nullptr)
	{
		m_pSound = new CSound();
		m_pSound->InitSound(hWnd);

	}

	//最初のシーン設定
	if (m_pFade == nullptr)
	{
		m_pFade = CFade::Create(D3DXVECTOR3(0.0f,0.0f,0.0f));
	}

	//m_pFade->SetFade(CScene::MODE::MODE_TITLE);

	SetMode(CScene::MODE::MODE_TITLE);

	return S_OK;
}

//=============================================
//終了処理
//=============================================
void CManager::Uninit()
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->Unload();
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	if (m_pModel != nullptr)
	{
		m_pModel->Unload();
		delete m_pModel;
		m_pModel = nullptr;
	}

	if (m_pSound != nullptr)
	{
		m_pSound->UninitSound();
		delete m_pSound;
		m_pSound = nullptr;
	}

	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}

	//キーボードの終了処理
	m_pKeyboard->Uninit();
	//マウスの終了処理
	m_pMouse->Uninit();
	//Padの終了処理
	m_pPad->Uninit();

	if (m_pFade != nullptr)
	{
		m_pFade->Uninit();
		m_pFade = nullptr;
	}

	CObject::ReleaseAll();

}

//=============================================
//更新処理
//=============================================
void CManager::Update()
{
	//更新処理
	m_pRenderer->Update();
	m_pCamera->Update();
	m_pKeyboard->Update();
	m_pMouse->Update();
	m_pPad->Update();

	if (m_pFade != nullptr)
	{
		m_pFade->Update();
	}

	//シーンの更新
	if (m_pScene != nullptr)
	{
		m_pScene->Update();
	}
	CObject::UpdateAll();

}

//=============================================
//描画処理
//=============================================
void CManager::Draw()
{
	//描画処理
	m_pRenderer->Draw();

	//シーンの描画
	if (m_pScene != nullptr)
	{
		m_pScene->Draw();
	}

}

//=============================================
//シーン設定
//=============================================
void CManager::SetMode(CScene::MODE mode)
{
	//シーン終了
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}

	//シーン切り替え
	if (m_pScene == nullptr)
	{
		m_pScene = CScene::Create(mode);
	}
}

//=============================================
//シーン
//=============================================
CScene* CManager::GetScene()
{
	return m_pScene;
}

//=============================================
//レンダラー取得
//=============================================
CRenderer* CManager::GetRenderer()
{
	return m_pRenderer;
}

//=============================================
//キーボード情報取得
//=============================================
CInputKeyboard* CManager::GetKeyboard()
{
	return m_pKeyboard;
}

//=============================================
//pad情報取得
//=============================================
CInputMouse* CManager::GetMouse()
{
	return m_pMouse;
}

//=============================================
//マウス情報取得
//=============================================
CInputPad* CManager::GetPad()
{
	return m_pPad;
}

//=============================================
//カメラ取得
//=============================================
CCamera* CManager::GetCamera()
{
	return m_pCamera;
}

//=============================================
//ライト取得
//=============================================
CLight* CManager::GetLight()
{
	return m_pLight;
}

//=============================================
//テクスチャ取得
//=============================================
CTexture* CManager::GetTexture()
{
	return m_pTexture;
}

//=============================================
//モデル取得
//=============================================
CModel* CManager::GetModel()
{
	return m_pModel;
}

//=============================================
//サウンド取得
//=============================================
CSound* CManager::GetSound()
{
	return m_pSound;
}

CFade* CManager::GetFade()
{
	return m_pFade;
}

