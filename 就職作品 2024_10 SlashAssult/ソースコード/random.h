//================================
//
//random.cppに必要な宣言[random.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _RANDOM_H_ //このマクロ定義がされていなかったら
#define _RANDOM_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "main.h"

//ランダムクラス
class CRandom
{
private:

	//関数
	CRandom() : m_Engine(m_Seed_gen()) {}	//コンストラクタで初期化

public:

	//インスタンスの生成
	static CRandom* GetInstance()
	{
		static CRandom instance;	//静的インスタンス
		return &instance;
	}

	//範囲内で乱数値を返す
	template<typename T>
	static T GetRandom(T min, T max)
	{
		//数値型でない場合はコンパイルエラーにする
		static_assert(std::is_arithmetic<T>::value, "数値型以外の型は扱えません");

		// シングルトンからエンジンを取得
		std::mt19937& engine = GetInstance()->m_Engine;

		//渡された型に応じて乱数を生成の仕方を判断
		using Distribution = typename std::conditional<
			std::is_integral<T>::value,						//整数型かを判断
			std::uniform_int_distribution<T>,				//整数の乱数
			std::uniform_real_distribution<T>				//浮動小数点の乱数
		>::type;

		//取得した型で乱数を生成
		Distribution Random(min, max);	//最小と最大の範囲で乱数を決める
		T Value = (Random(engine));

		return Value;
	}

	//乱数値を返す
	template<typename T>
	static T GetRandom()
	{
		//数値型でない場合はコンパイルエラーにする
		static_assert(std::is_arithmetic<T>::value, "数値型以外の型は扱えません");

		//マクロを解除しておく
		#undef max  

		// 最小値と最大値を浮動小数点型の最小最大値に設定
		T min = std::numeric_limits<T>::lowest();  // 最小値
		T max = std::numeric_limits<T>::max();     // 最大値

		return CRandom::GetRandom(min, max);
	}

private:

	//変数
	std::mt19937 m_Engine;
	std::random_device m_Seed_gen;

};

#endif