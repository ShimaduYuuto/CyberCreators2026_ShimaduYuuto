//======================================
//
//	テクスチャの管理[texture.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "texture.h"
#include "manager.h"

//静的メンバ変数の初期化
int CTexture::m_nTextureNumAll = 0;	//テクスチャの数
std::vector<LPDIRECT3DTEXTURE9> CTexture::m_pTexture = {};	//テクスチャのポインタ
std::map<std::string, int> CTexture::m_pTexturemap = {};	//テクスチャの情報

//============================
//テクスチャのコンストラクタ
//============================
CTexture::CTexture()
{
	//テクスチャの数の初期化
	m_nTextureNumAll = 0;
}

//============================
//テクスチャのデストラクタ
//============================
CTexture::~CTexture()
{

}

//============================
//テクスチャの破棄
//============================
void CTexture::Unload()
{
	//全てのテクスチャの番号とパスを破棄
	m_pTexturemap.erase(m_pTexturemap.begin(), m_pTexturemap.end());

	//全てのテクスチャの情報を破棄
	m_pTexture.erase(m_pTexture.begin(), m_pTexture.end());

	//カウントを0にする
	m_nTextureNumAll = 0;
}

//============================
//テクスチャの登録
//============================
int CTexture::Regist(const char* pTextureName)
{
	//テクスチャが存在していなかったら
	if (m_pTexturemap.count(pTextureName) == NULL)	//1つも無かったら０
	{
		//テクスチャ情報を読み込む用の変数
		LPDIRECT3DTEXTURE9 pTex;

		//テクスチャの読み込む
		D3DXCreateTextureFromFile(CManager::GetInstance()->GetRenderer()->GetDevice(),
			pTextureName,
			&pTex);

		//テクスチャ情報のメモリを動的確保
		m_pTexture.push_back(pTex);

		//値を挿入
		m_pTexturemap[pTextureName] = m_nTextureNumAll;

		//カウントの加算
		m_nTextureNumAll++;
	}

	//テクスチャの値を返す
	return m_pTexturemap[pTextureName];
}

//============================
//テクスチャの取得
//============================
LPDIRECT3DTEXTURE9 CTexture::GetAddress(int nIdx)
{
	//テクスチャの数だけ周回
	for (auto iter : m_pTexturemap)
	{
		//引数と値が一致したなら
		if (iter.second == nIdx)
		{
			//テクスチャのパスを返す
			return m_pTexture[nIdx];
		}
	}
	
	//テクスチャが存在しない
	return NULL;
}