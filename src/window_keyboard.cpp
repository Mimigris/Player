/*
 * This file is part of EasyRPG Player.
 *
 * EasyRPG Player is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EasyRPG Player is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EasyRPG Player. If not, see <http://www.gnu.org/licenses/>.
 */

#include <string>
#include <algorithm>

#include "window_keyboard.h"
#include "game_system.h"
#include "input.h"
#include "bitmap.h"
#include "font.h"

const char* const Window_Keyboard::DONE = "<Done>";
const char* const Window_Keyboard::SPACE = "SPACE";
const char* const Window_Keyboard::NEXT_PAGE = "<Page>";
const char* const Window_Keyboard::DONE_2KE = "<OK!>";
const char* const Window_Keyboard::DONE_2K3 = "< OK >";
const char* const Window_Keyboard::DONE_JP = "<決定>";
const char* const Window_Keyboard::DONE_RU = "<OK>";
const char* const Window_Keyboard::DONE_KO = "<결정>";
const char* const Window_Keyboard::DONE_ZH_CN = "<确定>";
const char* const Window_Keyboard::DONE_ZH_TW = "<確定>";
const char* const Window_Keyboard::DONE_ZH_KANA = "<确认>";

/*
 * Hiragana <-> Katakana; Hangul 1 <-> Hangul 2; Simp. Chinese 1 <-> Simp. Chinese 2;
 * Trad. Chinese 1 <-> Trad. Chinese 2; Rus.Cyrillic <-> Rus.Latin; letter <-> symbol;
 *  letter 2ke <-> symbol 2ke; letter 2k3e <-> symbol 2ke
 */

Keyboard_Layout Window_Keyboard::layouts[Window_Keyboard::MODE_END] = {
	{
		"<かな>",
		{ // Hiragana
			{"あ", "い", "う", "え", "お", "が", "ぎ", "ぐ", "げ", "ご"},
			{"か", "き", "く", "け", "こ", "ざ", "じ", "ず", "ぜ", "ぞ"},
			{"さ", "し", "す", "せ", "そ", "だ", "ぢ", "づ", "で", "ど"},
			{"た", "ち", "つ", "て", "と", "ば", "び", "ぶ", "べ", "ぼ"},
			{"な", "に", "ぬ", "ね", "の", "ぱ", "ぴ", "ぷ", "ぺ", "ぽ"},
			{"は", "ひ", "ふ", "へ", "ほ", "ぁ", "ぃ", "ぅ", "ぇ", "ぉ"},
			{"ま", "み", "む", "め", "も", "っ", "ゃ", "ゅ", "ょ", "ゎ"},
			{"や", "ゆ", "よ", "わ", "ん", "ー", "～", "・", "＝", "☆"},
			{"ら", "り", "る", "れ", "ろ", "ヴ", NEXT_PAGE, "", DONE}
		}
	},
	{
		"<カナ>",
		{ // Katakana
			{"ア", "イ", "ウ", "エ", "オ", "ガ", "ギ", "グ", "ゲ", "ゴ"},
			{"カ", "キ", "ク", "ケ", "コ", "ザ", "ジ", "ズ", "ゼ", "ゾ"},
			{"サ", "シ", "ス", "セ", "ソ", "ダ", "ヂ", "ヅ", "デ", "ド"},
			{"タ", "チ", "ツ", "テ", "ト", "バ", "ビ", "ブ", "ベ", "ボ"},
			{"ナ", "ニ", "ヌ", "ネ", "ノ", "パ", "ピ", "プ", "ペ", "ポ"},
			{"ハ", "ヒ", "フ", "ヘ", "ホ", "ァ", "ィ", "ゥ", "ェ", "ォ"},
			{"マ", "ミ", "ム", "メ", "モ", "ッ", "ャ", "ュ", "ョ", "ヮ"},
			{"ヤ", "ユ", "ヨ", "ワ", "ン", "ー", "～", "・", "＝", "☆"},
			{"ラ", "リ", "ル", "レ", "ロ", "ヴ", NEXT_PAGE, "", DONE}
		}
	},
	{
		"<平假>",
		{ // Hiragana zh RPG_RT Secret Memory/RPG Maker 2003 (next page and done text changed, ー, ～, ・, ＝ replaced by  -, ~, ■, =; note that the original engine could allow you to type broken characters after trying these characters previously mentioned outside of ■, no plan to replicate this behaviour) 
			{"あ", "い", "う", "え", "お", "が", "ぎ", "ぐ", "げ", "ご"},
			{"か", "き", "く", "け", "こ", "ざ", "じ", "ず", "ぜ", "ぞ"},
			{"さ", "し", "す", "せ", "そ", "だ", "ぢ", "づ", "で", "ど"},
			{"た", "ち", "つ", "て", "と", "ば", "び", "ぶ", "べ", "ぼ"},
			{"な", "に", "ぬ", "ね", "の", "ぱ", "ぴ", "ぷ", "ぺ", "ぽ"},
			{"は", "ひ", "ふ", "へ", "ほ", "ぁ", "ぃ", "ぅ", "ぇ", "ぉ"},
			{"ま", "み", "む", "め", "も", "っ", "ゃ", "ゅ", "ょ", "ゎ"},
			{"や", "ゆ", "よ", "わ", "ん", "-", "~", "■", "=", "☆"},
			{"ら", "り", "る", "れ", "ろ", "ヴ", NEXT_PAGE, "", DONE}
		}
	},
	{
		"<片假>",
		{ // Katakana zh RPG_RT Secret Memory/RPG Maker 2003 (next page and done text changed, ー, ～, ・, ＝ replaced by  -, ~, ■, =; note that the original engine could allow you to type broken characters after trying these characters previously mentioned outside of ■, no plan to replicate this behaviour)
			{"ア", "イ", "ウ", "エ", "オ", "ガ", "ギ", "グ", "ゲ", "ゴ"},
			{"カ", "キ", "ク", "ケ", "コ", "ザ", "ジ", "ズ", "ゼ", "ゾ"},
			{"サ", "シ", "ス", "セ", "ソ", "ダ", "ヂ", "ヅ", "デ", "ド"},
			{"タ", "チ", "ツ", "テ", "ト", "バ", "ビ", "ブ", "ベ", "ボ"},
			{"ナ", "ニ", "ヌ", "ネ", "ノ", "パ", "ピ", "プ", "ペ", "ポ"},
			{"ハ", "ヒ", "フ", "ヘ", "ホ", "ァ", "ィ", "ゥ", "ェ", "ォ"},
			{"マ", "ミ", "ム", "メ", "モ", "ッ", "ャ", "ュ", "ョ", "ヮ"},
			{"ヤ", "ユ", "ヨ", "ワ", "ン", "-", "~", "■", "=", "☆"},
			{"ラ", "リ", "ル", "レ", "ロ", "ヴ", NEXT_PAGE, "", DONE}
		}
	},
	{
		"<앞P>",
		{ // Hangul 1
			{"가", "갸", "거", "겨", "고", "교", "구", "계", "그", "기"},
			{"나", "냐", "너", "녀", "노", "뇨", "누", "뉴", "느", "녹"},
			{"다", "댜", "더", "뎌", "도", "됴", "두", "듀", "드", "디"},
			{"라", "랴", "러", "려", "로", "료", "루", "류", "르", "리"},
			{"마", "먀", "머", "며", "모", "묘", "무", "물", "므", "미"},
			{"바", "뱌", "버", "벼", "보", "뵤", "부", "뷰", "비", "밤"},
			{"사", "색", "서", "세", "소", "쇼", "수", "슈", "신", "심"},
			{"아", "야", "어", "여", "오", "요", "우", "유", "으", "이"},
			{"〜", "·", ".", "☆", SPACE, "", NEXT_PAGE, "", DONE}
		}

	},
	{
		"<뒤P>",
		{ // Hangul 2
			{"자", "쟈", "저", "져", "조", "죠", "주", "쥬", "즈", "지"},
			{"차", "챠", "처", "쳐", "초", "쵸", "추", "츄", "츠", "치"},
			{"카", "캬", "커", "켜", "코", "쿄", "쿠", "큐", "크", "키"},
			{"타", "탸", "터", "텨", "토", "툐", "투", "튜", "트", "티"},
			{"파", "퍄", "퍼", "펴", "포", "표", "푸", "퓨", "프", "피"},
			{"하", "햐", "허", "혀", "호", "효", "후", "휴", "흐", "해"},
			{"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"},
			{"진", "녘", "의", "민", "예", "건", "현", "운", "걔", "임"},
			{"영", "은", "성", "준", SPACE, "", NEXT_PAGE, "", DONE}
		},
	},
	{
		"<翻页>",
		{ // Simp. Chinese 1
			{"阿", "艾", "安", "奥", "巴", "拜", "班", "邦", "贝", "本"},
			{"比", "宾", "波", "伯", "布", "查", "达", "丹", "当", "道"},
			{"德", "登", "迪", "蒂", "丁", "度", "杜", "顿", "多", "厄"},
			{"尔", "恩", "法", "凡", "菲", "费", "芬", "佛", "弗", "夫"},
			{"盖", "格", "戈", "冈", "古", "哈", "海", "汉", "豪", "赫"},
			{"华", "霍", "基", "吉", "加", "杰", "捷", "金", "卡", "凯"},
			{"科", "克", "肯", "拉", "莱", "兰", "朗", "劳", "勒", "雷"},
			{"里", "利", "立", "丽", "莉", "林", "琳", "留", "隆", "鲁"},
			{"路", "伦", "罗", "洛", "律", "", NEXT_PAGE, "", DONE}
		}
	},
	{
		"<前页>",
		{ // Simp. Chinese 2
			{"玛", "迈", "曼", "梅", "美", "门", "米", "密", "明", "缪"},
			{"摩", "莫", "姆", "穆", "那", "娜", "纳", "奈", "南", "尼"},
			{"宁", "纽", "奴", "诺", "欧", "帕", "派", "佩", "皮", "普"},
			{"奇", "琪", "琼", "丘", "萨", "撒", "赛", "桑", "瑟", "森"},
			{"沙", "山", "珊", "史", "世", "斯", "丝", "司", "苏", "所"},
			{"索", "塔", "泰", "坦", "汤", "特", "提", "汀", "统", "瓦"},
			{"威", "维", "韦", "卫", "温", "沃", "乌", "西", "希", "夏"},
			{"辛", "修", "休", "雅", "亚", "林", "琳", "留", "隆", "鲁"},
			{"伊", "英", "尤", "则", "扎", "", NEXT_PAGE, "", DONE}
		}
	},
	{
		"<翻页>",
		{ // Simp. Chinese Alt A 1 (used in Ib)
			{"泉", "声", "咽", "危", "石", "日", "色", "冷", "青", "松"},
			{"薄", "暮", "空", "潭", "曲", "安", "禅", "制", "毒", "龙"},
			{"海", "内", "存", "知", "己", "天", "涯", "若", "比", "邻"},
			{"燕", "草", "如", "碧", "丝", "秦", "桑", "低", "绿", "枝"},
			{"当", "君", "怀", "归", "日", "是", "妾", "断", "肠", "时"},
			{"当", "路", "谁", "相", "假", "知", "音", "世", "所", "稀"},
			{"只", "应", "守", "寂", "寞", "还", "掩", "故", "园", "扉"},
			{"坐", "观", "垂", "钓", "者", "－", "～", "·", "＝", "☆"},
			{"徒", "有", "羡", "鱼", "情", "的", NEXT_PAGE, "", DONE}
		}
	},
	{
		"<翻页>",
		{ // Simp. Chinese Alt A 2 (used in Ib)
			{"几", "行", "归", "塞", "尽", "念", "尔", "独", "何", "之"},
			{"暮", "雨", "相", "呼", "失", "寒", "塘", "欲", "下", "迟"},
			{"霞", "光", "连", "碧", "彩", "湖", "岸", "水", "连", "滩"},
			{"天", "地", "丹", "青", "绘", "人", "间", "锦", "绣", "看"},
			{"返", "景", "入", "深", "林", "复", "照", "青", "苔", "上"},
			{"中", "岁", "颇", "好", "道", "晚", "家", "南", "山", "陲"},
			{"兴", "来", "每", "独", "往", "胜", "事", "空", "自", "知"},
			{"遥", "夜", "泛", "清", "瑟", "－", "～", "·", "＝", "☆"},
			{"瑟", "风", "生", "翠", "萝", "的", NEXT_PAGE, "", DONE}
		}
	},
	{
		"<翻页>",
		{ // Simp. Chinese Alt B 1 (used in 2kki)
			{"阿", "伊", "乌", "俄", "欧", "安", "英", "奥", "恩", "翁"},
			{"卡", "奇", "库", "克", "寇", "加", "吉", "古", "格", "果"},
			{"萨", "斯", "苏", "瑟", "索", "扎", "兹", "祖", "泽", "佐"},
			{"塔", "提", "图", "特", "托", "达", "迪", "杜", "德", "多"},
			{"纳", "尼", "努", "奈", "诺", "哈", "希", "胡", "赫", "霍"},
			{"法", "菲", "福", "芬", "佛", "巴", "比", "布", "贝", "波"},
			{"马", "米", "穆", "梅", "莫", "帕", "皮", "普", "培", "坡"},
			{"亚", "约", "云", "耶", "尤", "瓦", "维", "温", "尔", "沃"},
			{"拉", "利", "鲁", "勒", "罗", "·", NEXT_PAGE, "", DONE}
		}
	},
	{
		"<翻页>",
		{ // Simp. Chinese Alt B 2 (used in 2kki)
			{"Ａ", "Ｂ", "Ｃ", "Ｄ", "Ｅ", "Ｆ", "Ｇ", "Ｈ", "Ｉ", "Ｊ"},
			{"Ｋ", "Ｌ", "Ｍ", "Ｎ", "Ｏ", "Ｐ", "Ｑ", "Ｒ", "Ｓ", "Ｔ"},
			{"Ｕ", "Ｖ", "Ｗ", "Ｘ", "Ｙ", "Ｚ", "ａ", "ｂ", "ｃ", "ｄ"},
			{"ｅ", "ｆ", "ｇ", "ｈ", "ｉ", "ｊ", "ｋ", "ｌ", "ｍ", "ｎ"},
			{"ｏ", "ｐ", "ｑ", "ｒ", "ｓ", "ｔ", "ｕ", "ｖ", "ｗ", "ｘ"},
			{"ｙ", "ｚ", "艾", "莉", "酱", "芭", "蒂", "蕾", "莲", "萝"},
			{"芙", "莎", "琴", "妮", "娅", "娃", "娜", "黛", "丝", "御"},
			{"美", "兰", "玛", "琳", "珊", "瓦", "维", "温", "尔", "沃"},
			{"珍", "坂", "朵", "露", "琪", "·", NEXT_PAGE, "", DONE}
		}
	},
	{
		"<翻页>",
		{ // Simp. Chinese Alt C 1 (used in the Simplified Chinese translation of Buried Barry)
			{"越", "鸟", "从", "南", "来", "胡", "鹰", "亦", "北", "度"},
			{"旧", "户", "闲", "花", "草", "驯", "鸽", "傍", "檐", "隙"},
			{"狗", "吠", "深", "巷", "中", "鸡", "鸣", "桑", "树", "颠"},
			{"烽", "火", "连", "三", "月", "家", "书", "抵", "万", "金"},
			{"石", "角", "恣", "幽", "步", "长", "乌", "遂", "遐", "征"},
			{"自", "倚", "能", "歌", "日", "先", "皇", "掌", "上", "怜"},
			{"控", "弦", "破", "左", "的", "右", "发", "摧", "月", "支"},
			{"嗟", "余", "有", "两", "耳", "未", "省", "听", "丝", "篁"},
			{"小", "桥", "流", "水", "人", "家", NEXT_PAGE, "", DONE}
		}
	},
	{
		"<翻页>",
		{ // Simp. Chinese Alt C 2 (used in the Simplified Chinese translation of Buried Barry)
			{"知", "音", "者", "诚", "希", "念", "子", "不", "能", "别"},
			{"义", "公", "习", "禅", "寂", "结", "宇", "依", "空", "林"},
			{"山", "阴", "遇", "羽", "客", "爱", "此", "好", "鹅", "宾"},
			{"潜", "身", "猫", "相", "雀", "引", "喙", "禽", "呼", "偶"},
			{"绕", "堤", "龙", "骨", "冷", "拂", "岸", "鸭", "头", "香"},
			{"昨", "日", "登", "高", "罢", "今", "朝", "更", "举", "觞"},
			{"吴", "江", "赋", "鹦", "鹉", "落", "笔", "超", "群", "英"},
			{"清", "水", "出", "芙", "蓉", "天", "然", "去", "雕", "饰"},
			{"枯", "藤", "老", "树", "昏", "鸦", NEXT_PAGE, "", DONE}
		}
	},
	{
		"<翻頁>",
		{ // Trad. Chinese 1
			{"泉", "聲", "咽", "危", "石", "日", "色", "冷", "青", "松"},
			{"薄", "暮", "空", "潭", "曲", "安", "禪", "制", "毒", "龍"},
			{"海", "內", "存", "知", "己", "天", "涯", "若", "比", "鄰"},
			{"滿", "階", "芳", "草", "綠", "一", "片", "杏", "花", "香"},
			{"恨", "無", "千", "日", "酒", "空", "斷", "九", "迴", "腸"},
			{"當", "路", "誰", "相", "假", "知", "音", "世", "所", "稀"},
			{"只", "應", "守", "寂", "寞", "還", "掩", "故", "園", "扉"},
			{"坐", "觀", "垂", "釣", "者", "－", "～", "’", "＝", "☆"},
			{"徒", "有", "羨", "魚", "情", "的", NEXT_PAGE, "", DONE}
		}
	},
	{
		"<前頁>",
		{ // Trad. Chinese 2
			{"幾", "行", "歸", "塞", "盡", "念", "爾", "獨", "何", "之"},
			{"暮", "雨", "相", "呼", "失", "寒", "塘", "欲", "下", "遲"},
			{"霞", "光", "連", "碧", "彩", "湖", "岸", "水", "連", "灘"},
			{"天", "地", "丹", "青", "繪", "人", "間", "錦", "秀", "看"},
			{"返", "景", "入", "深", "林", "復", "照", "青", "苔", "上"},
			{"中", "歲", "頗", "好", "道", "晚", "家", "南", "山", "睡"},
			{"興", "來", "每", "獨", "往", "勝", "事", "空", "自", "知"},
			{"遙", "夜", "泛", "清", "瑟", "－", "～", "’", "＝", "☆"},
			{"西", "風", "生", "翠", "蘿", "的", NEXT_PAGE, "", DONE}
		}
	},
	{
		"<頁１>",
		{ // Trad. Chinese Alt 1 (used in the Traditional Chinese translation of Buried Barry)
			{"Ａ", "Ｂ", "Ｃ", "Ｄ", "Ｅ", "Ｆ", "Ｇ", "Ｈ", "Ｉ", "Ｊ"},
			{"Ｋ", "Ｌ", "Ｍ", "Ｎ", "Ｏ", "Ｐ", "Ｑ", "Ｒ", "Ｓ", "Ｔ"},
			{"Ｕ", "Ｖ", "Ｗ", "Ｘ", "Ｙ", "Ｚ", "ａ", "ｂ", "ｃ", "ｄ"},
			{"ｅ", "ｆ", "ｇ", "ｈ", "ｉ", "ｊ", "ｋ", "ｌ", "ｍ", "ｎ"},
			{"ｏ", "ｐ", "ｑ", "ｒ", "ｓ", "ｔ", "ｕ", "ｖ", "ｗ", "ｘ"},
			{"ｙ", "ｚ", "子", "力", "小", "大", "天", "中", "太", "夫"},
			{"月", "幻", "日", "毛", "文", "古", "艾", "白", "玉", "世"},
			{"冬", "加", "卡", "平", "多", "巧", "弗", "米", "西", "安"},
			{"伊", "亨", "克", "里", "坎", "阿", NEXT_PAGE, "", DONE}
		}
	},
	{
		"<頁２>",
		{ // Trad. Chinese Alt 2 (used in the Traditional Chinese translation of Buried Barry)
			{"貝", "利", "芙", "芬", "拉", "欣", "東", "雨", "依", "武"},
			{"秀", "金", "耶", "肯", "青", "法", "奇", "皇", "宜", "兒"},
			{"昂", "哈", "思", "紅", "香", "茱", "美", "南", "威", "珍"},
			{"迪", "風", "哥", "席", "真", "修", "恩", "倫", "格", "亞"},
			{"海", "特", "夏", "娜", "莉", "球", "彩", "菲", "雪", "飛"},
			{"萊", "梅", "琴", "凱", "斯", "晴", "黑", "絲", "塔", "葛"},
			{"葉", "斐", "雅", "瑟", "瑞", "雷", "豪", "維", "赫", "爾"},
			{"德", "蓮", "瑪", "嘉", "歐", "蕾", "龍", "瓊", "黛", "藍"},
			{"薩", "蘇", "寶", "羅", "麗", "蘭", NEXT_PAGE, "", DONE}
		}
	},
	{
		"<Абвг>",
		{ // Cp1251 Russian Cyrillic (+ Bel. and Ukr. letters in the last row)
			{"А", "Б", "В", "Г", "Д", "а", "б", "в", "г", "д"},
			{"Е", "Ё", "Ж", "З", "И", "е", "ё", "ж", "з", "и"},
			{"Й", "К", "Л", "М", "Н", "й", "к", "л", "м", "н"},
			{"О", "П", "Р", "С", "Т", "о", "п", "р", "с", "т"},
			{"У", "Ф", "Х", "Ц", "Ч", "у", "ф", "х", "ц", "ч"},
			{"Ш", "Щ", "Ъ", "Ы", "Ь", "ш", "щ", "ъ", "ы", "ь"},
			{"Э", "Ю", "Я",  "",  "", "э", "ю", "я",  "",  ""},
			{"Ґ", "Є", "І", "Ї", "Ў", "ґ", "є", "і", "ї", "ў"},
			{"ʼ",  "",  "",  "",  "",  "", NEXT_PAGE, "", DONE}
		}
	},
	{
		"<Abcd>",
		{ // Letter
			{"A", "B", "C", "D", "E", "a", "b", "c", "d", "e"},
			{"F", "G", "H", "I", "J", "f", "g", "h", "i", "j"},
			{"K", "L", "M", "N", "O", "k", "l", "m", "n", "o"},
			{"P", "Q", "R", "S", "T", "p", "q", "r", "s", "t"},
			{"U", "V", "W", "X", "Y", "u", "v", "w", "x", "y"},
			{"Z", "" , "" , "" , "" , "z"},
			{"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"},
			{SPACE},
			{"" , "" , "" , "" , "" , "" , NEXT_PAGE, "", DONE}
		}
	},
	{
		"<$A$B>",
		{ // ExFont Symbol
			{"$A", "$B", "$C", "$D", "$E", "$a", "$b", "$c", "$d", "$e"},
			{"$F", "$G", "$H", "$I", "$J", "$f", "$g", "$h", "$i", "$j"},
			{"$K", "$L", "$M", "$N", "$O", "$k", "$l", "$m", "$n", "$o"},
			{"$P", "$Q", "$R", "$S", "$T", "$p", "$q", "$r", "$s", "$t"},
			{"$U", "$V", "$W", "$X", "$Y", "$u", "$v", "$w", "$x", "$y"},
			{"$Z",  "" ,  "" ,  "" ,  "" , "$z"},
			{},
			{},
			{ "" ,  "" ,  "" ,  "" ,  "" ,  "" , NEXT_PAGE, "", DONE}
		}
	},
	{
		"<Letter>",
		{ // Letter 2k-3 - uses <Done> as a confirmation (used in the English translation of Ib, or Answered Prayers)
			{"A", "B", "C", "D", "E", "a", "b", "c", "d", "e"},
			{"F", "G", "H", "I", "J", "f", "g", "h", "i", "j"},
			{"K", "L", "M", "N", "O", "k", "l", "m", "n", "o"},
			{"P", "Q", "R", "S", "T", "p", "q", "r", "s", "t"},
			{"U", "V", "W", "X", "Y", "u", "v", "w", "x", "y"},
			{"Z", " ", " ", " ", " ", "z", " ", " ", " ", " "},
			{"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"},
			{"", "", "", " ", " ", " ", " ", " ", " ", " "},
			{" " , " " , " " , " " , " " , " " , NEXT_PAGE, "", DONE}
		}
	},
	{
		"<Symbol>",
		{ // Symbol 2k-3 - uses <Done> as a confirmation (used in the English translation of Ib, or Answered Prayers)
			{"!", "?", ",", ".", "/", "$F", "$G", "$H", "$I", "$J"},
			{":", ";", "(", ")", "@", "$K", "$L", "$M", "$N", " "},
			{"[", "]", "{", "}", "*", "$O", "$P", "$Q", "$R", "$S"},
			{"+", "-", "^", "%", "#", "$T", "$U", "$V", "$W", "$X"},
			{"`", "~", "\"", "'", "=", "$Y", "$Z", " ", " ", " "},
			{"&", "|", "_", "\\", " ", "$C", "$o", "$a", "$b", "$c"},
			{"$s", "$t", "$u", "$v", " ", "$D", "$E", "$p", "$q", "$r"},
			{"$w", "$x", "$y", "$z", " ", " ", " ", " ", " ", " "},
			{" " , " " , " " , " " , " " , " " , NEXT_PAGE, "", DONE}
		}
	},
	{
		"<Norm>",
		{ // Letter 2k3 OFF - uses < OK > as a confirmation
			{"A", "B", "C", "D", "E", "a", "b", "c", "d", "e"},
			{"F", "G", "H", "I", "J", "f", "g", "h", "i", "j"},
			{"K", "L", "M", "N", "O", "k", "l", "m", "n", "o"},
			{"P", "Q", "R", "S", "T", "p", "q", "r", "s", "t"},
			{"U", "V", "W", "X", "Y", "u", "v", "w", "x", "y"},
			{"Z", " ", " ", " ", " ", "z", " ", " ", " ", " "},
			{"0", "1", "2", "3", "4", "é", "è", "ê", "ë", "à"},
			{"5", "6", "7", "8", "9", "â", "ä", "ç", "ï", "î"},
			{" " , " " , " " , " " , " " , " " , NEXT_PAGE, "", DONE}
		}
	},
	{
		"<Spec>",
		{ // Symbol 2k3 OFF - uses < OK > as a confirmation
			{"!", "?", ",", ".", "/", "$F", "$G", "$H", "$I", "$J"},
			{":", ";", "(", ")", "@", "$K", "$L", "$M", "$N", " "},
			{"[", "]", "{", "}", "*", "$O", "$P", "$Q", "$R", "$S"},
			{"+", "-", "^", "%", "#", "$T", "$U", "$V", "$W", "$X"},
			{"`", "~", "\"", "'", "=", "$Y", "$Z", " ", " ", " "},
			{"&", "|", "_", "\\", " ", "$C", "$o", "$a", "$b", "$c"},
			{"$s", "$t", "$u", "$v", " ", "$D", "$E", "$p", "$q", "$r"},
			{"$w", "$x", "$y", "$z", " ", "â", "ä", "ç", "ï", "î"},
			{" " , " " , " " , " " , " " , " " , NEXT_PAGE, "", DONE}
		}
	},
	{
		"<Norm>",
		{ // Letter Spanish (used in the Spanish version of Toilet in Wonderland - uses < OK > as a confirmation)
			{"A", "B", "C", "D", "E", "a", "b", "c", "d", "e"},
			{"F", "G", "H", "I", "J", "f", "g", "h", "i", "j"},
			{"K", "L", "M", "N", "O", "k", "l", "m", "n", "o"},
			{"P", "Q", "R", "S", "T", "p", "q", "r", "s", "t"},
			{"U", "V", "W", "X", "Y", "u", "v", "w", "x", "y"},
			{"Z", " ", "Ñ", " ", "Ü", "z", " ", "ñ", " ", "ü"},
			{"Á", "É", "Í", "Ó", "Ú", "á", "é", "í", "ó", "ú"},
			{"1", "2", "3", "4", "5", " ", " ", " ", " ", " "},
			{"6" , "7" , "8" , "9" , "0" , " " , NEXT_PAGE, "", DONE}
		}
	},
	{
		"<Símb>",
		{ // Symbol Spanish (used in the Spanish version of Toilet in Wonderland - uses < OK > as a confirmation)
			{"$A", "$B", "$C", "$D", "$E", "$a", "$b", "$c", "$d", "$e"},
			{"$F", "$G", "$H", "$I", " ", "$f", "$g", "$h", "$i", "$n"},
			{"$J", "$K", "$L", "$M", "$N", "$j", "$k", "$l", "$m", "$o"},
			{"$O", "$P", "$Q", "$R", " ", " ", "$z", "$s", "$w", "$p"},
			{"$S", "$T", "$U", "$V", " ", " ", "$v", " ", "$t", "$q"},
			{"$W", "$X", "$Y", "$Z", " ", " ", "$y", "$u", "$x", "$r"},
			{"\\", "|", "'", "`", "^", "-", "[", "]", "{", "}"},
			{"_", "¬", "$", "#", "@", " ", " ", " ", " ", " "},
			{ "!" ,  "&" ,  "?" ,  "*" ,  "/" ,  " " , NEXT_PAGE, "", DONE}
		}
	},
	{
		"<ABC>",
		{ // Letter RPG2ke
			{"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"},
			{"K", "L", "M", "N", "O", "P", "Q", "R", "S", "T"},
			{"U", "V", "W", "X", "Y", "Z", "(", ")", "~", "="},
			{"a", "b", "c", "d", "e", "f", "g", "h", "i", "j"},
			{"k", "l", "m", "n", "o", "p", "q", "r", "s", "t"},
			{"u", "v", "w", "x", "y", "z", ":", ";", "!", "?"},
			{"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"},
			{"\"", "@", "+", "&", "/", ".", ",", "-", "'", "_"},
			{"|" , "[", "]", "?", "°", " ", NEXT_PAGE, "", DONE}
		}
	},
	{
		"<ABC>",
		{ // Letter RPG2k3e (~ and = are reversed compared to 2ke, the second ? is replaced by * and reversed with @)
			{"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"},
			{"K", "L", "M", "N", "O", "P", "Q", "R", "S", "T"},
			{"U", "V", "W", "X", "Y", "Z", "(", ")", "=", "~"},
			{"a", "b", "c", "d", "e", "f", "g", "h", "i", "j"},
			{"k", "l", "m", "n", "o", "p", "q", "r", "s", "t"},
			{"u", "v", "w", "x", "y", "z", ":", ";", "!", "?"},
			{"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"},
			{"\"", "*", "+", "&", "/", ".", ",", "-", "'", "_"},
			{"|" , "[", "]", "@", "°", " ", NEXT_PAGE, "", DONE}
		}
	},
	{
		"<Sym>",
		{ // Symbol RPG2ke (while the comma and cedilla use the exact same visual in the original engine, those two are different characters)
			{"À", "Á", "Â", "Ã", "Ä", "Å", "ƒ", "Æ", "Ç", "È"},
			{"É", "Ê", "Ë", "Ì", "Í", "Î", "Ï", "Ð", "Ñ", "Ò"},
			{"Ó", "Ô", "Õ", "Ö", "©", "Ø", "Ù", "Ú", "Û", "Ü"},
			{"Ý", "Þ", "ß", "{", "}", "•", "§", "€", "£", "¥"},
			{"à", "á", "â", "ã", "ä", "å", "¸", "æ", "ç", "è"},
			{"é", "ê", "ë", "ì", "í", "î", "ï", "ð", "ñ", "ò"},
			{"ó", "ô", "õ", "ö", "®", "ø", "ù", "ú", "û", "ü"},
			{"ý", "þ", "ÿ", "¿", "¡", ".", ",", "-", "'", "_"},
			{"†" , "‡", "%", "…", "μ", " ", NEXT_PAGE, "", DONE}
		}
	}
};

Window_Keyboard::Window_Keyboard(int ix, int iy, int iwidth, int iheight, const char* ndone_text)
		: Window_Base(ix, iy, iwidth, iheight)
		, done_text(ndone_text)
		, play_cursor(false)
{
	row = 0;
	col = 0;

	SetContents(Bitmap::Create(width - 16, height - 16));

	row_spacing = 16;
	col_spacing = (contents->GetWidth() - 2 * border_x) / col_max;

	mode = Letter;
	next_mode = Symbol;

	Refresh();
	UpdateCursorRect();
}

void Window_Keyboard::SetMode(Window_Keyboard::Mode nmode, Window_Keyboard::Mode nnext_mode) {
	mode = nmode;
	next_mode = nnext_mode;
	Refresh();
	UpdateCursorRect();
}

std::string const& Window_Keyboard::GetKey(int row, int col) const {
	std::string const& str = layouts[mode].items[row][col];
	if (str == NEXT_PAGE) {
		return layouts[next_mode].key_text;
	}
	else if (str == DONE) {
		return done_text;
	}
	else {
		return str;
	}
}

std::string const& Window_Keyboard::GetSelected() const {
	return layouts[mode].items[row][col];
}

Rect Window_Keyboard::GetItemRect(int row, int col) const {
	return Rect(col * col_spacing + border_x,
				row * row_spacing + border_y,
				Text::GetSize(*Font::Default(), GetKey(row, col)).width + 8,
				row_spacing);
}

void Window_Keyboard::UpdateCursorRect() {
	Rect r = GetItemRect(row, col);
	r.y -= 2;
	SetCursorRect(r);
}

void Window_Keyboard::Refresh() {
	contents->Clear();

	for (int j = 0; j < row_max; j++) {
		for (int i = 0; i < col_max; i++) {
			Rect r = GetItemRect(j, i);
			contents->TextDraw(r.x + 4, r.y, Font::ColorDefault, GetKey(j, i));
		}
	}
}

void Window_Keyboard::Update() {
	Window_Base::Update();

	// move left on wide fields
	int skip_dir = -1;

	if (active) {
		if (Input::IsRepeated(Input::DOWN)) {
			play_cursor = true;
			row = (row + 1) % row_max;
		}
		if (Input::IsRepeated(Input::UP)) {
			play_cursor = true;
			row = (row + row_max - 1) % row_max;
		}
		if (Input::IsRepeated(Input::RIGHT)) {
			play_cursor = true;
			col = (col + 1) % col_max;
			skip_dir = 1;
		}
		if (Input::IsRepeated(Input::LEFT)) {
			play_cursor = true;
			col = (col + col_max - 1) % col_max;
		}
	}

	// Special handling for wide fields
	if (col > 0) {
		// page switch and done are always in the bottom right corner
		if ((row == row_max - 1 && (col == col_max - 3 || col == col_max - 1))
			|| GetKey(row, col - 1) == SPACE)
			col = std::min(col + skip_dir, col_max - 1);
	}

	// Skip empty cells
	if (GetSelected().empty()) {
		Update();
		return;
	}

	if (play_cursor) {
		Main_Data::game_system->SePlay(Main_Data::game_system->GetSystemSE(Main_Data::game_system->SFX_Cursor));
		play_cursor = false;
	}
	UpdateCursorRect();
}
