#pragma once
#include <array>
#include <string>
#include <iterator>
#include <algorithm>

namespace Gui {
	void 自定义菜单();
	void 左边选择菜单();

	void 主页菜单(); void 主题初始化(); void 主页菜单_公告();
	void 透视菜单(); void 透视菜单_分组(); void 透视菜单_串流(); void 透视菜单_玩家(); void 透视菜单_颜色(); void 透视菜单_雷达(); void 透视菜单_载具(); void 透视菜单_物品();
	void 自瞄菜单(); void 自瞄菜单_瞄准(); void 自瞄菜单_武器(); void 自瞄菜单_武器_步枪(); void 自瞄菜单_武器_参数();
	void 杂项菜单();
	void 设置菜单(); void 设置菜单_配置文件(); void 设置菜单_管理();

}

namespace Obf {

	inline std::string xor_(std::string s) {
		std::string out{};
		for (char& c : s) {
			out += c ^ (s.length() + 1) ^ 'f';
		}
		return out;
	}

	template<std::size_t S>
	struct Xor_String {
		std::array<char, S> charArr;

		inline auto operator()() {
			std::string str{};

			std::transform(charArr.begin(), charArr.end() - 1, std::back_inserter(str), [](auto const& c) {
				return c ^ S ^ 'f';
				});
			return str;
		}

		constexpr Xor_String(const char(&string)[S]) : charArr{} {
			auto it = charArr.begin();
			for (auto const& c : string) {
				*it = c ^ S ^ 'f';
				it++;
			}
		}
	};
}
#define obf(string) []() { static auto result = Obf::Xor_String<sizeof(string)/sizeof(char)>(string); return result(); }()