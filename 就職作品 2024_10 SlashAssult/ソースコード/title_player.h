//================================
//
//title_player.cppに必要な宣言[title_player.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _TITLE_PLAYER_H_ //このマクロ定義がされていなかったら
#define _TITLE_PLAYER_H_ //２重インクルード防止のマクロ定義

#include "character.h"

//タイトルプレイヤークラス
class CTitle_Player : public CCharacter
{
public:

	static const std::string FILEPATH;		//読み込むファイル

	//キーの種類
	typedef enum
	{
		TITLE_PLAYERMOTION_NORMAL = 0,
		TITLE_PLAYERMOTION_STANDUP,
		TITLE_PLAYERMOTION_MAX
	}TITLE_PLAYERMOTION;

	//メンバ関数
	CTitle_Player(int nPriority = 2);		//コンストラクタ
	~CTitle_Player() override;				//デストラクタ
	HRESULT Init() override;				//初期化
	void Uninit() override;					//終了
	void Update() override;					//更新
	void Draw() override;					//描画

	//静的関数
	static CTitle_Player* Create();	//Playerの生成

};

#endif