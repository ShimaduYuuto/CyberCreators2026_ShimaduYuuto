//======================================
//
//	オブジェクトの描画[object.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "object.h"
#include "manager.h"

//staticの初期化
int CObject::m_nNumAll = 0;
CObject* CObject::m_pCur[NUM_PRIORITY] = { nullptr };			//最後尾のポインタの初期化
CObject* CObject::m_pTop[NUM_PRIORITY] = { nullptr };			//最初のポインタの初期化

//============================
//オブジェクトのコンストラクタ
//============================
CObject::CObject(int nPriority) :
	m_bDeath(false),
	m_bUpdateJudge(true),
	m_Pos(),
	m_Type(),
	m_pNext(nullptr),
	m_pPrev(nullptr),
	m_TagType(TAG_NONE)
{
	//描画優先度設定
	m_nPriority = nPriority;

	CObject* pObj = this;				//自身のポインタを取得
	m_nNumAll++;						//総数をカウント

	pObj->m_pPrev = m_pCur[nPriority];	//自分の前のオブジェクトポインタを取得

	//初めてのオブジェクトなら静的メンバに代入
	if (m_pTop[nPriority] == nullptr)
	{
		m_pTop[nPriority] = pObj;	//最初のオブジェクトのポインタ
		m_pCur[nPriority] = pObj;	//最後尾のオブジェクトのポインタ
		m_pCur[nPriority]->m_pNext = nullptr;	//次のポインタを初期化
	}
	else
	{
		m_pCur[nPriority]->m_pNext = pObj;	//現在の最後尾に次のポインタを設定
	}
	
	pObj->m_pNext = nullptr;			//次のポインタを初期化
	m_pCur[nPriority] = pObj;			//最後尾を更新
	m_bDeath = false;					//死亡フラグの初期化
	m_Pos = { NULL, NULL, NULL };		//位置の初期化
	m_Type = TYPE_NONE;					//種類の初期化
}

//============================
//オブジェクトのデストラクタ
//============================
CObject::~CObject()
{

}

//============================
//オブジェクトの初期化
//============================
HRESULT CObject::Init()
{
	return S_OK;
}

//============================
//オブジェクトの終了処理
//============================
void CObject::Uninit()
{
	//死亡判定
	m_bDeath = true;
}

//============================
//オブジェクトの更新処理
//============================
void CObject::Update()
{

}

//============================
//オブジェクトの描画処理
//============================
void CObject::Draw()
{

}

//============================
//オブジェクトの開放処理
//============================
void CObject::Release()
{
	//変数に代入
	int nPriority = m_nPriority;

	//nullチェック
	if (this != nullptr)
	{
		CObject* pObj = this;					//自身のポインタを取得

		if (pObj->m_pPrev != nullptr)
		{
			pObj->m_pPrev->m_pNext = pObj->m_pNext;	//自身の前後を繋ぐ
		}
		
		if (pObj->m_pNext != nullptr)
		{
			pObj->m_pNext->m_pPrev = pObj->m_pPrev;	//自身の前後を繋ぐ
		}

		//最後尾が現在のポインタなら前のポインタに更新
		if (pObj == m_pCur[nPriority])
		{
			m_pCur[nPriority] = pObj->m_pPrev;	//ポインタの変更
		}

		//最初が現在のポインタなら次のポインタに更新
		if (pObj == m_pTop[nPriority])
		{
			m_pTop[nPriority] = pObj->m_pNext;	//ポインタの変更
		}

		//リストから削除
		delete pObj;
		pObj = nullptr;
		m_nNumAll--;
	}
}

//============================
//オブジェクトの全開放処理
//============================
void CObject::ReleaseAll()
{
	//保険として先に終了処理を実行
	for (int i = 0; i < NUM_PRIORITY; i++)
	{
		CObject* pObj = m_pTop[i];	//先頭取得

		//最大数が不明なのでwhileを使用
		while (pObj != nullptr)
		{
			CObject* pNext = pObj->m_pNext;	//次のポインタを取得
			pObj->Uninit();					//終了処理
			pObj = pNext;					//ポインタを進める
		}
	}

	//プライオリティの数だけ周回
	for (int i = 0; i < NUM_PRIORITY; i++)
	{
		CObject* pObj = m_pTop[i];	//先頭取得

		//最大数が不明なのでwhileを使用
		while (pObj != nullptr)
		{
			CObject* pNext = pObj->m_pNext;	//次のポインタを取得
			pObj->Release();				//開放処理
			pObj = pNext;					//ポインタを進める
		}

		//静的ポインタ変数の初期化
		m_pTop[i] = nullptr;
		m_pCur[i] = nullptr;
	}
}

//============================
//オブジェクトの全更新処理
//============================
void CObject::UpdateAll()
{
	//現在のシーンを取得
	CScene* pScene = CManager::GetInstance()->GetScene();

	//変数の宣言
	CObject* pObj = nullptr;

	//プライオリティの数だけ周回
	for (int i = 0; i < NUM_PRIORITY; i++)
	{
		pObj = m_pTop[i];	//先頭取得

		//最大数が不明なのでwhileを使用
		while (pObj != nullptr)
		{
			CObject* pNext = pObj->m_pNext;	//次のポインタを取得

			if (pObj->m_bUpdateJudge)
			{
				pObj->Update();				//更新処理
			}
			
			pObj = pNext;					//ポインタを進める
		}
	}
	
	//プライオリティの数だけ周回
	for (int i = 0; i < NUM_PRIORITY; i++)
	{
		pObj = m_pTop[i];	//先頭取得

	//最大数が不明なのでwhileを使用
		while (pObj != nullptr)
		{
			CObject* pNext = pObj->m_pNext;	//次のポインタを取得

			//死亡フラグが立っていたらRelease
			if (pObj->m_bDeath)
			{
				pObj->Release();
			}

			pObj = pNext;	//ポインタを進める
		}
	}
}

//============================
//オブジェクトの全描写処理
//============================
void CObject::DrawAll()
{
	//プライオリティの数だけ周回
	for (int i = 0; i < NUM_PRIORITY; i++)
	{
		CObject* pObj = m_pTop[i];	//先頭取得

		//最大数が不明なのでwhileを使用
		while (pObj != nullptr)
		{
			CObject* pNext = pObj->m_pNext;	//次のポインタを取得
			pObj->Draw();					//更新処理
			pObj = pNext;					//ポインタを進める
		}
	}
}

//============================
//オブジェクトの先頭を取得
//============================
CObject* CObject::GetTopObject(int priority)
{
	//プライオリティの範囲内なら返す
	if (priority >= 0 && priority < NUM_PRIORITY)
	{
		return m_pTop[priority];
	}
	
	//範囲外ならnullptr
	return nullptr;
}

//============================
//更新するオブジェクトを変更
//============================
void CObject::ChangeUpdateObject(TAG tag)
{
	//プライオリティの数だけ周回
	for (int i = 0; i < NUM_PRIORITY; i++)
	{
		CObject* pObj = m_pTop[i];	//先頭取得

		//最大数が不明なのでwhileを使用
		while (pObj != nullptr)
		{
			CObject* pNext = pObj->m_pNext;	//次のポインタを取得

			//引数のタグと一致したら更新判定にする
			if (pObj->m_TagType == tag || pObj->m_TagType == TAG_NONE)
			{
				pObj->m_bUpdateJudge = true;
			}
			else
			{
				pObj->m_bUpdateJudge = false;
			}

			pObj = pNext;					//ポインタを進める
		}
	}
}