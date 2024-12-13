//================================
//
//enemy002_alterego.cppに必要な宣言[enemy002_alterego.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _ENEMY002_ALTEREGO_H_ //このマクロ定義がされていなかったら
#define _ENEMY002_ALTEREGO_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "enemy002.h"
#include "state_enemy002.h"

//偽物のエネミークラス
class CEnemy002_AlterEgo : public CEnemy002
{
public:

	//定数
	static const std::string FILEPATH;		//読み込むファイル
	static constexpr int LIFE{ 1 };			//体力

	//メンバ関数
	CEnemy002_AlterEgo();				//コンストラクタ
	~CEnemy002_AlterEgo() override;		//デストラクタ
	HRESULT Init() override;			//初期化
	void Uninit() override;				//終了
	void Update() override;				//更新
	void Draw() override;				//描画

	//生成
	static CEnemy002_AlterEgo* Create(D3DXVECTOR3 pos);

	//状態のリセット
	void StateReset() override;


private:

};

#endif