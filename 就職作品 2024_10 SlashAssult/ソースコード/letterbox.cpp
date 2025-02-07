//======================================
//
//	レターボックスの処理[letterbox.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "letterbox.h"
#include "manager.h"

//============================
//レターボックスのコンストラクタ
//============================
CLetterBox::CLetterBox() :
	m_pLetterBox(),
	m_nTime(0),
	m_nCurrentTime(0)
{
	//レターボックスの初期化
	for (int i = 0; i < NUM_LETTERBOX; i++)
	{
		m_pLetterBox[i] = nullptr;
	}
}

//============================
//レターボックスのデストラクタ
//============================
CLetterBox::~CLetterBox()
{
	//レターボックスの終了処理
	for (int i = 0; i < NUM_LETTERBOX; i++)
	{
		//nullptrチェック
		if (m_pLetterBox[i] == nullptr)
		{
			continue;
		}

		m_pLetterBox[i]->Uninit();
		m_pLetterBox[i] = nullptr;
	}
}

//============================
//レターボックスの初期化
//============================
HRESULT CLetterBox::Init()
{
	//レターボックスの初期化
	for (int i = 0; i < NUM_LETTERBOX; i++)
	{
		//レターボックス
		if (m_pLetterBox[i] != nullptr)
		{
			continue;
		}

		m_pLetterBox[i] = CObject2D::Create();													//生成
		m_pLetterBox[i]->SetPos({(float)SCREEN_WIDTH * 0.5f, i * (float)SCREEN_HEIGHT, 0.0f});	//位置
		m_pLetterBox[i]->SetSize({ (float)SCREEN_WIDTH, 0.0f, 0.0f });							//サイズ
		m_pLetterBox[i]->SetColor({ 0.0f, 0.0f, 0.0f, 1.0f });									//色
	}

	return S_OK;
}

//============================
//レターボックスの終了処理
//============================
void CLetterBox::Uninit()
{
	//レターボックスの終了処理
	for (int i = 0; i < NUM_LETTERBOX; i++)
	{
		//nullptrチェック
		if (m_pLetterBox[i] == nullptr)
		{
			continue;
		}

		m_pLetterBox[i]->Uninit();
	}

	//レターボックスクラス(自身)の破棄
	CObject::Uninit();
}

//============================
//レターボックスの更新処理
//============================
void CLetterBox::Update()
{
	//時間のカウント
	m_nCurrentTime++;

	//最初の一定時間だけサイズを加算
	if (m_nCurrentTime <= TIME_INTERPOLATION)
	{
		//レターの数だけ周回
		for (int i = 0; i < NUM_LETTERBOX; i++)
		{
			//高さを加算して設定
			D3DXVECTOR3 Size = m_pLetterBox[i]->GetSize();
			Size.y += HEIGHT_LETTERBOX / TIME_INTERPOLATION;

			//サイズの補正
			if (Size.y > HEIGHT_LETTERBOX)
			{
				Size.y = HEIGHT_LETTERBOX;
			}

			//サイズの設定
			m_pLetterBox[i]->SetSize(Size);
		}
	}

	//終了前の一定時間だけサイズを減算
	else if (m_nCurrentTime >= m_nTime - TIME_INTERPOLATION)
	{
		//レターの数だけ周回
		for (int i = 0; i < NUM_LETTERBOX; i++)
		{
			//高さを加算して設定
			D3DXVECTOR3 Size = m_pLetterBox[i]->GetSize();
			Size.y -= HEIGHT_LETTERBOX / TIME_INTERPOLATION;

			//サイズの補正
			if (Size.y < 0.0f)
			{
				Size.y = 0.0f;
			}

			//サイズの設定
			m_pLetterBox[i]->SetSize(Size);
		}
	}

	//寿命を迎えたら消去
	if (m_nCurrentTime > m_nTime)
	{
		Uninit();
	}
}

//============================
//レターボックスの描画処理
//============================
void CLetterBox::Draw()
{

}

//============================
//レターボックスの生成処理
//============================
CLetterBox* CLetterBox::Create(int time)
{
	//レターボックスの生成
	CLetterBox* pLetterBox = nullptr;
	pLetterBox = new CLetterBox;

	//初期化
	pLetterBox->Init();

	//時間
	pLetterBox->m_nTime = time + static_cast<float>((TIME_INTERPOLATION * 2.0f));	//補間の時間を追加

	return nullptr;
}