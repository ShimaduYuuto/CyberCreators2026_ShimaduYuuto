//================================
//
//enemybulletmanager.cppに必要な宣言[enemybulletmanager.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _ENEMYBULLETMANAGER_H_ //このマクロ定義がされていなかったら
#define _ENEMYBULLETMANAGER_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "main.h"
#include "enemybullet.h"

//エネミーバレットマネージャーのクラス
class CEnemyBulletManager
{
public:

	//メンバ関数
	CEnemyBulletManager();			//コンストラクタ
	~CEnemyBulletManager();			//デストラクタ
	HRESULT Init();					//初期化
	void Uninit();					//終了
	void Regist(CEnemyBullet* enemybullet);	//登録
	void Erase(CEnemyBullet* enemybullet);	//削除

	//リストの取得
	std::list<CEnemyBullet*> GetList() { return m_apManager; }

private:

	//メンバ変数
	std::list<CEnemyBullet*> m_apManager;	//敵を管理
};

#endif