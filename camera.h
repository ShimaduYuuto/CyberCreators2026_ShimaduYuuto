//================================
//
//camera.cppに必要な宣言[camera.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _CAMERA_H_ //このマクロ定義がされていなかったら
#define _CAMERA_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "main.h"
#include "collision.h"

//カメラクラス
class CCamera
{
public:

	//定数
	static const float LENGTH_NORMAL;	//通常のカメラの距離
	static const float LENGTH_SLOW;		//スロー時のカメラの距離
	static constexpr float LENGTH_POSR{100.0f};	//注視点とプレイヤーの位置

	//メンバ関数
	CCamera();				//コンストラクタ
	~CCamera();				//デストラクタ
	HRESULT Init();			//初期化
	void Uninit();			//終了
	void Update();			//更新
	void SetCamera();		//カメラの設定
	D3DXVECTOR3& GetPos() { return m_posV; }	//カメラの位置
	D3DXVECTOR3& GetRot() { return m_rot; }		//カメラの向き
	bool GetViewObject(D3DXMATRIX mtx);			//カメラに映っているか
	bool GetViewObject(D3DXVECTOR3 pos);		//カメラに映っているか
	void SetShake(float frame, float magnitude);//カメラの揺れの設定
	void SetPosR(D3DXVECTOR3 pos) { m_posR = pos; }	//注視点の設定
	
private:

	//メンバ変数
	D3DXVECTOR3 m_posV;				//視点
	D3DXVECTOR3 m_posR;				//注視点
	D3DXVECTOR3 m_vecU;				//上方向のベクトル
	D3DXVECTOR3 m_rot;				//向き
	D3DXMATRIX m_mtxProjection;		//プロジェクションマトリックス
	D3DXMATRIX m_mtxView;			//ビューマトリックス
	D3DVIEWPORT9 m_Viewport;		//ビューポート
	float m_fShakeFrameCount;		//カメラを揺らすフレーム
	float m_fShakeMagnitude;		//カメラの揺れる大きさ
	float m_fLength;				//視点と注視点の距離
};

#endif