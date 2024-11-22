//================================
//
//object.cppに必要な宣言[object.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _OBJECT_H_ //このマクロ定義がされていなかったら
#define _OBJECT_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "main.h"

//オブジェクトクラス
class CObject
{
public:
	//定数
	static const int MAX_OBJECT = 256;	//オブジェクトの最大
	static const int NUM_PRIORITY = 16;	//プライオリティの数

	//オブジェクトのタグ
	typedef enum
	{
		TAG_NONE = 0,	//特に無し
		TAG_PAUSE,		//ポーズ中に更新するオブジェクト
		TAG_GAME,		//ゲーム中に更新するオブジェクト
		TAG_MAX,		//列挙の最大
	}TAG;

	//オブジェクトの種類
	typedef enum
	{
		TYPE_NONE = 0,	//タイプなし
		TYPE_ENEMY,		//敵
		TYPE_PLAYER,	//プレイヤー
		TYPE_MAX,		//最大
	}TYPE;

	//関数
	CObject(int nPriority = 3);			//コンストラクタ
	virtual ~CObject();					//デストラクタ
	virtual HRESULT Init() = 0;			//初期化
	virtual void Uninit() = 0;			//終了
	virtual void Update() = 0;			//更新
	virtual void Draw() = 0;			//描画
	static void ReleaseAll();			//全オブジェクトの開放
	static void UpdateAll();			//全オブジェクトの更新
	static void DrawAll();				//全オブジェクトの描画
	void SetDeath() { m_bDeath = true; }//オブジェクトの死亡フラグを立てる
	bool GetDeath() { return m_bDeath; }//オブジェクトの死亡判定の取得
	static CObject* GetTopObject(int priority);//オブジェクトの先頭を取得

	//パラメーターの設定と取得
	virtual void SetPos(D3DXVECTOR3 Pos) { m_Pos = Pos; }	//位置の設定
	D3DXVECTOR3& GetPos() { return m_Pos; }					//位置の取得
	void SetType(TYPE type) {m_Type = type;}				//種類の設定
	TYPE GetType() { return m_Type; }						//種類の取得
	CObject* GetNext() { return m_pNext; }					//次のポインタの取得

protected:
	void Release();							//自分自身の開放

private:
	static int m_nNumAll;					//オブジェクトの総数
	static CObject* m_pTop[NUM_PRIORITY];	//先頭のオブジェクトポインタ
	static CObject* m_pCur[NUM_PRIORITY];	//現在（最後尾）のポインタ
	CObject* m_pPrev;						//前のオブジェクトのポインタ
	CObject* m_pNext;						//次のオブジェクトのポインタ
	bool m_bDeath;							//死亡フラグ
	int m_nPriority;						//描画優先度
	D3DXVECTOR3 m_Pos;						//オブジェクトの位置
	TYPE m_Type;							//オブジェクトの種類
};

#endif