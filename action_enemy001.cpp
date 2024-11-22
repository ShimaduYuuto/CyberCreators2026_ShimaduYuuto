////======================================
////
////	アクション処理[action_enemy001.cpp]
////	Author : Yuuto Shimadu
////
////======================================
//
////ヘッダーのインクルード
//#include "action_enemy001.h"
//#include "spawn_shield.h"
//#include "normalattack_enemy001.h"
//
////============================
////コンストラクタ
////============================
//CAction_Enemy001::CAction_Enemy001() :
//	m_NextAction(ACTION_ENEMY001_NONE),
//	m_pCharacter(nullptr),
//	m_NowAction(ACTION_ENEMY001_NONE)
//{
//
//}
//
////============================
////デストラクタ
////============================
//CAction_Enemy001::~CAction_Enemy001()
//{
//
//}
//
////============================
////初期化
////============================
//HRESULT CAction_Enemy001::Init()
//{
//	CAction::Init();
//
//	return S_OK;
//}
//
////============================
////更新
////============================
//void CAction_Enemy001::Update()
//{
//	CAction::Update();
//}
//
////============================
////次のアクションの設定
////============================
//void CAction_Enemy001::SetNextAction()
//{
//
//}
//
////============================
////クリエイト
////============================
//CAction_Enemy001* CAction_Enemy001::Create(ACTION_ENEMY001 action_enemy001, CCharacter* character)
//{
//	//ポインタ用の変数
//	CAction_Enemy001* pAction = nullptr;
//
//	//アクションの種類に応じてクラスを変更
//	switch (action_enemy001)
//	{
//	case ACTION_ENEMY001_NONE:	//何もなし
//		break;
//
//	case ACTION_ENEMY001_SPAWN_SHIELD:	//盾の生成
//		pAction = new CSpawn_Shield;
//		break;
//
//	case ACTION_ENEMY001_ATTACK:		//通常攻撃
//		pAction = new CNormalAttack_Enemy001;
//		break;
//
//		//現在のアクションを設定
//		pAction->m_NowAction = action_enemy001;
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