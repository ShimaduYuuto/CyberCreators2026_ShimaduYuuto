//================================
//
//title.cppに必要な宣言[title.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _TITLE_H_ //このマクロ定義がされていなかったら
#define _TITLE_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "scene.h"
#include "field.h"
#include "title_player.h"

//タイトルクラス
class CTitle : public CScene
{
public:

	//メンバ関数
	CTitle();						//コンストラクタ
	~CTitle() override;				//デストラクタ
	HRESULT Init() override;		//初期化
	void Uninit() override;			//終了
	void Update() override;			//更新
	void Draw() override;			//描画

	//ポインタの取得
	CTitle_Player* GetPlayer() { if (m_pPlayer == nullptr) { return nullptr; } return m_pPlayer; }				//プレイヤーの取得
	CField* GetField() { if (m_pField == nullptr) { return nullptr; } return m_pField; }						//フィールドの取得

private:
	CTitle_Player* m_pPlayer;			//タイトル用プレイヤー
	CField* m_pField;					//フィールド
};

#endif