//================================
//
//sound.cppに必要な宣言[sound.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _SOUND_H_ //このマクロ定義がされていなかったら
#define _SOUND_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "main.h"

//サウンドクラス
class CSound
{
public:
	//サウンドの列挙型
	typedef enum
	{
		SOUND_LABEL_BGM = 0,		//BGM
		SOUND_LABEL_BATTLE,			//バトル
		SOUND_LABEL_ATTACK,			//攻撃
		SOUND_LABEL_STICK,			//張り付き
		SOUND_LABEL_DAMAGE,			//ダメージ
		SOUND_LABEL_REPEL,			//弾く
		SOUND_LABEL_EXPLOSION,		//爆発
		SOUND_LABEL_CHARGEATTACK,	//チャージ攻撃
		SOUND_LABEL_CHARGE000,		//チャージ
		SOUND_LABEL_SWING,			//素振り
		SOUND_LABEL_CHARGE001,		//弾のチャージ音
		SOUND_LABEL_SHOT,			//発射音
		SOUND_LABEL_BULLETHIT,		//弾のヒット音
		SOUND_LABEL_RUMBLING,		//地響き音
		SOUND_LABEL_DESTROY,		//撃破音
		SOUND_LABEL_EXPLOSION001,	//爆発音
		SOUND_LABEL_TITLE,			//タイトルBGM
		SOUND_LABEL_RESULT,			//リザルトBGM
		SOUND_LABEL_WIND,			//風のBGM
		SOUND_LABEL_MAX,			//最大値
	}SOUND_LABEL;

	//*****************************************************************************
	// サウンド情報の構造体定義
	//*****************************************************************************
	typedef struct
	{
		const char* pFilename;	// ファイル名
		int nCntLoop;			// ループカウント
		float Volume;			// 音量
	} SOUNDINFO;

	//定数
	static const SOUNDINFO SOUND_INFO[SOUND_LABEL_MAX];

	//メンバ関数
	CSound();								//コンストラクタ
	~CSound();								//デストラクタ
	HRESULT Init(HWND hWnd);				//初期化
	void Uninit(void);						//終了処理
	HRESULT PlaySound(SOUND_LABEL label);	//サウンドを流す
	void Stop(SOUND_LABEL label);			//サウンドを一つを止める
	void Stop(void);						//全てのサウンドを止める
private:
	IXAudio2* m_pXAudio2 = NULL;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice* m_pMasteringVoice = NULL;			// マスターボイス
	IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL_MAX] = {};	// ソースボイス
	BYTE* m_apDataAudio[SOUND_LABEL_MAX] = {};					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// オーディオデータサイズ
};

#endif