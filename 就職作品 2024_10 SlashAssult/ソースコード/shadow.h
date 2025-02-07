//================================
//
//shadow.cppに必要な宣言[shadow.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _SHADOW_H_ //このマクロ定義がされていなかったら
#define _SHADOW_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "object3D.h"

//影クラス
class CShadow : public CObject3D
{
public:

	//定数
	static const std::string FILEPATH;	//テクスチャパス
	static const D3DXCOLOR COLOR;		//色

	//メンバ関数
	CShadow(int nPriority = 1);								//コンストラクタ
	~CShadow() override;									//デストラクタ
	HRESULT Init() override;								//初期化
	void Uninit() override;									//終了
	void Update() override;									//更新
	void Draw() override;									//描画
	static CShadow* Create(D3DXVECTOR3* pos, float radius);	//影の生成

	//描画するか
	void SetDrawJudge(bool judge) { m_bDrawJudge = judge; }	//設定
	bool GetDrawJudge() { return m_bDrawJudge; }			//取得

private:

	D3DXVECTOR3* m_TargetPos;	//影の対象の位置
	bool m_bDrawJudge;				//描画するか
};

#endif