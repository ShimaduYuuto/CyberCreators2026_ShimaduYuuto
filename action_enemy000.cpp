////======================================
////
////	アクション処理[action_enemy000.cpp]
////	Author : Yuuto Shimadu
////
////======================================
//
////ヘッダーのインクルード
//#include "action_enemy000.h"
//#include "normalattack_enemy000.h"
//
////============================
////コンストラクタ
////============================
//CAction_Enemy000::CAction_Enemy000() :
//	m_NextAction(ACTION_ENEMY000_NONE),
//	m_pCharacter(nullptr)
//{
//
//}
//
////============================
////デストラクタ
////============================
//CAction_Enemy000::~CAction_Enemy000()
//{
//
//}
//
////============================
////初期化
////============================
//HRESULT CAction_Enemy000::Init()
//{
//	CAction::Init();
//
//	return S_OK;
//}
//
////============================
////更新
////============================
//void CAction_Enemy000::Update()
//{
//	CAction::Update();
//}
//
////============================
////次のアクションの設定
////============================
//void CAction_Enemy000::SetNextAction()
//{
//
//}
//
////============================
////クリエイト
////============================
//CAction_Enemy000* CAction_Enemy000::Create(ACTION_ENEMY000 action_enemy000, CCharacter* character)
//{
//	//ポインタ用の変数
//	CAction_Enemy000* pAction = nullptr;
//
//	//アクションの種類に応じてクラスを変更
//	switch (action_enemy000)
//	{
//	case ACTION_ENEMY000_NONE:	//何もなし
//		break;
//
//	case ACTION_ENEMY000_NORMALATTACK:	//通常攻撃
//		pAction = new CNormalAttack_Enemy000;
//		break;
//	}
//
//	//ヌルポインタならアサートを通す
//	if (pAction == nullptr)
//	{
//		assert(true);
//	}
//
//	//ポインタを取得
//	pAction->m_pCharacter = character;
//
//	//初期化
//	pAction->Init();
//
//	return pAction;
//}