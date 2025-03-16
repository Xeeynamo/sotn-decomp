// use std::env;
use std::fs::File;
use std::io::{self, Read, BufReader};
use std::collections::HashMap;
use regex::Regex;
use std::io::BufRead;
// use std::io::Seek;

#[allow(dead_code)]
fn dakuten(chr: char, prev: char) -> Option<char> {
    match (chr, prev) {
        ('゙', 'シ') => Some('ジ'),
        ('゙', 'ク') => Some('グ'),
        ('゙', 'て') => Some('で'),
        ('゙', 'ト') => Some('ド'),
        ('゙', 'サ') => Some('ザ'),
        ('゙', 'タ') => Some('ダ'),
        ('゙', 'か') => Some('が'),
        ('゙', 'テ') => Some('デ'),
        ('゙', 'ハ') => Some('バ'),
        ('゙', 'セ') => Some('ゼ'),
        ('゙', 'ホ') => Some('ボ'),
        ('゙', 'ヒ') => Some('ビ'),
        ('゙', 'こ') => Some('ご'),
        ('゙', 'ふ') => Some('ぶ'),
        ('゙', 'と') => Some('ど'),
        ('゙', 'へ') => Some('べ'),
        ('゙', 'ヘ') => Some('ベ'),
        ('゙', 'ス') => Some('ズ'),
        ('゙', 'カ') => Some('ガ'),
        ('゙', 'ケ') => Some('ゲ'),
        ('゙', 'し') => Some('じ'),
        ('゙', 'き') => Some('ぎ'),
        ('゙', 'は') => Some('ば'),
        ('゙', 'フ') => Some('ブ'),
        ('゙', 'ウ') => Some('ヴ'),
        ('゙', 'さ') => Some('ざ'),
        ('゙', 'ひ') => Some('び'),
        ('゙', 'せ') => Some('ぜ'),
        ('゙', 'コ') => Some('ゴ'),
        ('゙', 'ほ') => Some('ぼ'),
        ('゙', 'キ') => Some('ギ'),
        ('゙', 'そ') => Some('ぞ'),
        ('゙', 'た') => Some('だ'),
        ('゙', 'ソ') => Some('ゾ'),
        ('゙', 'く') => Some('ぐ'),
        ('゚', 'フ') => Some('プ'),
        ('゚', 'ヒ') => Some('ピ'),
        ('゚', 'ハ') => Some('パ'),
        ('゚', 'ヘ') => Some('ペ'),
        ('゚', 'ホ') => Some('ポ'),
        _ => None,
    }
}

const TABLE: [char; 256] = [
    //0      1      2      3      4      5      6      7      8      9      A      B      C      D      E      F
    ' ',    '!',   '\'',  '#',   '$',   '%',   '&',   '\'',   '(',   ')',   '男',  '+',   ',',   '-',   '.',   '/',
    '0',    '1',   '2',   '3',   '4',   '5',   '6',   '7',   '8',   '9',   ':',   '人',  '手',  '=',   '玉',  '?',
    '石',   'A',   'B',   'C',   'D',   'E',   'F',   'G',   'H',   'I',   'J',   'K',   'L',   'M',   'N',   'O',
    'P',    'Q',   'R',   'S',   'T',   'U',   'V',   'W',   'X',   'Y',   'Z',   '[',   '剣',  ']',   '盾',  '_',
    '書',   'a',   'b',   'c',   'd',   'e',   'f',   'g',   'h',   'i',   'j',   'k',   'l',   'm',   'n',   'o',
    'p',    'q',   'r',   's',   't',   'u',   'v',   'w',   'x',   'y',   'z',   '炎',  '氷',  '雷',  '~',   '女',
    '力',   '。',   '「',  '」',  '、',  '・',  'ヲ',  'ァ',  'ィ',   'ゥ',  'ェ',  'ォ',  'ャ',  'ュ',  'ョ',  'ッ',
    'ー',   'ア',   'イ',  'ウ',  'エ',  'オ',  'カ',  'キ',  'ク',   'ケ',  'コ',  'サ',  'シ',  'ス',  'セ',  'ソ',
    'タ',   'チ',   'ツ',  'テ',  'ト',  'ナ',  'ニ',  'ヌ',  'ネ',   'ノ',  'ハ',  'ヒ',  'フ',  'ヘ',  'ホ',  'マ',
    'ミ',   'ム',   'メ',  'モ',  'ヤ',  'ユ',  'ヨ',  'ラ',  'リ',   'ル',  'レ',  'ロ',  'ワ',  'ン',  'ﾞ',   'ﾟ', // dakuten and handakuten are lower in the graphic than seen here and get shifted by the code upwards when printing
    '子',   '悪',   '魔',  '人',  '妖',  '精',  'を',  'ぁ',  'ぃ',   'ぅ',  'ぇ',  'ぉ',  'ゃ',  'ゅ',  'ょ',  'っ',
    '金',   'あ',   'い',  'う',  'え',  'お',  'か',  'き',  'く',   'け',  'こ',  'さ',  'し',  'す',  'せ',  'そ',
    'た',   'ち',   'つ',  'て',  'と',  'な',  'に',  'ぬ',  'ね',   'の',  'は',  'ひ',  'ふ',  'へ',  'ほ',  'ま',
    'み',   'む',   'め',  'も',  'や',  'ゆ',  'よ',  'ら',  'り',   'る',  'れ',  'ろ',  'わ',  'ん',  '指',  '輪',
    '←',    '↖',   '↑',   '↗',  '→',   '↘',  '↓',  '↙',  '○',    '×',   '□',   '△',  '名',  '刀',  '聖',  '血',
    '✈',   '★',   '☀',   '☁',  '☃',   '♂',   '♀',  '©',   '®',   '§',    '¶', '∑', '大',  '光',  '邪',  '月'
];

#[allow(dead_code)]
#[allow(unused_assignments)]
fn convert_j(f: &[u8]) -> String {
    let mut pos = 0;
    let mut result = String::new();
    let mut prev: Option<char> = None;
    let mut prev_prev: Option<char> = None;

    while pos < f.len() {
        let ch = f[pos];
        prev_prev = prev;
        prev = Some(TABLE[ch as usize]);
        pos += 1;

        if ch == 0xFF {
            if pos >= f.len() {
                break;
            }
            let next_ch = f[pos];
            pos += 1;

            if next_ch == 0 {
                break;
            }
            if next_ch != 0xFF {
                if let Some(prev_prev_char) = prev_prev {
                    result.pop();
                    if let Some(dakuten_char) = dakuten(TABLE[next_ch as usize], prev_prev_char) {
                        result.push(dakuten_char);
                    }
                }
                continue;
            }
        }
        if ch != 158 && ch != 159 {
            result.push(TABLE[ch as usize]);
        }
    }
    result
}

#[allow(dead_code)]
fn utf8_to_byte_literals_escaped(input: &str) -> String {
    let out = utf8_to_byte_literals(input);
    out.iter()
        .map(|&val| format!("\\x{:02X}", val))
        .collect::<String>()
}

fn utf8_to_byte_literals(input_str: &str) -> Vec<u8> {
    let mut bytes = Vec::new();
    for char in input_str.chars() {
        if has_dakuten(&char) || has_handakuten(&char) {
            bytes.extend(dakuten_to_bytes(&char));
        } else if char == '月' {
            bytes.push(0xFF);
            bytes.push(0xFF);
        } else {
            if let Some(index) = table_index(&char){
                bytes.push(index as u8);
            }
        }
    }
    bytes.push(0xFF);
    bytes
}

fn has_dakuten(utf8_char: &char) -> bool {
    let dakuten_chars = [
        'が', 'ぎ', 'ぐ', 'げ', 'ご', 'ざ', 'じ', 'ず', 'ぜ', 'ぞ',
        'だ', 'ぢ', 'づ', 'で', 'ど', 'ば', 'び', 'ぶ', 'べ', 'ぼ', 
        'ガ', 'ギ', 'グ', 'ゲ', 'ゴ', 'ザ', 'ジ', 'ズ', 'ゼ', 'ゾ', 
        'ダ', 'ヂ', 'ヅ', 'デ', 'ド', 'バ', 'ビ', 'ブ', 'ベ', 'ボ', 
        'ヴ',
    ];
    dakuten_chars.contains(&utf8_char)
}

fn has_handakuten(utf8_char: &char) -> bool {
    let handakuten_chars = [
        'ぱ', 'ぴ', 'ぷ', 'ぺ', 'ぽ', 'パ', 'ピ', 'プ', 'ペ', 'ポ',
    ];
    handakuten_chars.contains(&utf8_char)
}

fn dakuten_to_bytes(input_chr: &char) -> Vec<u8> {
    let no_dakuten = remove_dakuten_handakuten(input_chr);
    let no_dakuten_bytes = table_index(&no_dakuten).unwrap() as u8;
    let mut byte = 158;
    if has_handakuten(input_chr) {
        byte = 159;
    }
    vec![no_dakuten_bytes, 0xFF, byte]
}

fn remove_dakuten_handakuten(utf8_char: &char) -> char {
    let table: HashMap<char, char> = [
        ('が', 'か'), ('ぎ', 'き'), ('ぐ', 'く'), ('げ', 'け'), ('ご', 'こ'),
        ('ざ', 'さ'), ('じ', 'し'), ('ず', 'す'), ('ぜ', 'せ'), ('ぞ', 'そ'),
        ('だ', 'た'), ('ぢ', 'ち'), ('づ', 'つ'), ('で', 'て'), ('ど', 'と'),
        ('ば', 'は'), ('び', 'ひ'), ('ぶ', 'ふ'), ('べ', 'へ'), ('ぼ', 'ほ'),
        ('ぱ', 'は'), ('ぴ', 'ひ'), ('ぷ', 'ふ'), ('ぺ', 'へ'), ('ぽ', 'ほ'),
        ('ガ', 'カ'), ('ギ', 'キ'), ('グ', 'ク'), ('ゲ', 'ケ'), ('ゴ', 'コ'),
        ('ザ', 'サ'), ('ジ', 'シ'), ('ズ', 'ス'), ('ゼ', 'セ'), ('ゾ', 'ソ'),
        ('ダ', 'タ'), ('ヂ', 'チ'), ('ヅ', 'ツ'), ('デ', 'テ'), ('ド', 'ト'),
        ('バ', 'ハ'), ('ビ', 'ヒ'), ('ブ', 'フ'), ('ベ', 'ヘ'), ('ボ', 'ホ'),
        ('パ', 'ハ'), ('ピ', 'ヒ'), ('プ', 'フ'), ('ペ', 'ヘ'), ('ポ', 'ホ'),
        ('ヴ', 'ウ')
    ].iter().cloned().collect();
    
    *table.get(utf8_char).unwrap_or(utf8_char)
}

// fn parse(filename: &str, str_offset: &str) -> io::Result<()> {
//     let offset = usize::from_str_radix(str_offset, 16).unwrap();
//     let file = File::open(filename)?;
//     let mut reader = BufReader::new(file);

//     reader.seek(io::SeekFrom::Start(offset as u64))?;

//     let mut r = String::new();
//     loop {
//         let mut buffer = [0];
//         match reader.read_exact(&mut buffer) {
//             Ok(_) => {
//                 let ch = buffer[0];
//                 if ch == 0xFF {
//                     break;
//                 }
//                 r.push((ch + 0x20) as char);
//             }
//             Err(_) => break,
//         }
//     }

//     println!(r#"_S("{}")"#, r);
//     Ok(())
// }

fn process_macro_with_transform(line: &str, regex: &str, transform: impl Fn(&str) -> Vec<u8>) -> String {
    let re = Regex::new(regex).unwrap();
    re.replace_all(line, |match_: &regex::Captures| {
        let s = match_.get(1).map_or("", |m| m.as_str());
        // println!("{}", s);
        let s = s.replace(r#"\\"#, "\"");
        let out = transform(&s);
        let escaped = out.iter()
            .map(|&c| format!("\\x{:02X}", c))
            .collect::<String>();
        format!("\"{}\"", escaped)
    }).to_string()
}

fn process_s_macro(line: &str) -> String {
    process_macro_with_transform(line, r"_S\(([^()]*|(?:[^()]*\([^()]*\)[^()]*)*)\)", utf8_to_byte_literals)
}

fn process_s2_macro(line: &str) -> String {
    process_macro_with_transform(line, r"_S2\((.*?)\)", alt_utf8_to_byte_literals)
}

fn process_s2_hd_macro(line: &str) -> String {
    process_macro_with_transform(line, r"_S2_HD\((.*?)\)", alt_hd_utf8_to_byte_literals)
}

fn do_sub(line: &str) -> String {
    let mut processed = process_s_macro(line);
    processed = process_s2_macro(&processed);
    processed = process_s2_hd_macro(&processed);
    processed
}

fn process(filename: Option<String>) -> io::Result<()> {
    let reader: Box<dyn Read> = match filename {
        Some(file) => Box::new(BufReader::new(File::open(file)?)),
        None => Box::new(io::stdin()),
    };

    let mut reader = BufReader::new(reader);
    let mut line = String::new();
    while reader.read_line(&mut line)? > 0 {
        print!("{}", do_sub(&line));
        line.clear();
    }

    Ok(())
}

use lazy_static::lazy_static;

lazy_static! {
    static ref ALT_UTF8_TO_INDEX: HashMap<char, usize> = {
        let values = "ＡＴＤＥＦ".chars().collect::<Vec<char>>();
        values.into_iter().enumerate().map(|(index, value)| (value, index)).collect::<HashMap<char, usize>>()
    };

    // static ref ALT_HD_UTF8_TO_INDEX: HashMap<char, usize> = {
    //     let values = [
    //         "装備技システム短剣必殺使攻撃力防",
    //         "御魔導器拳こ一覧棒両手食物爆弾盾",
    //         "投射薬ん右左武兜鎧マントその他い",
    //     ]
    //     .concat();
    //     values.chars().enumerate().map(|(index, value)| (value, index)).collect::<HashMap<char, usize>>()
    // };
    static ref UTF8_TO_INDEX: HashMap<char, usize> = {
        let mut map = HashMap::new();
        for (index, value) in TABLE.iter().enumerate() {
            map.insert(*value, index);
        }
        map
    };
}
fn table_index(c: &char) -> Option<usize> {
    return UTF8_TO_INDEX.get(c).copied();
}

fn alt_hd_utf8_to_index(c: &char) -> Option<usize> {
    match c {
        '装' => Some(0),
        '備' => Some(1),
        '技' => Some(2),
        'シ' => Some(3),
        'ス' => Some(4),
        'テ' => Some(5),
        'ム' => Some(6),
        '短' => Some(7),
        '剣' => Some(8),
        '必' => Some(9),
        '殺' => Some(10),
        '使' => Some(11),
        '攻' => Some(12),
        '撃' => Some(13),
        '力' => Some(14),
        '防' => Some(15),
        '御' => Some(16),
        '魔' => Some(17),
        '導' => Some(18),
        '器' => Some(19),
        '拳' => Some(20),
        'こ' => Some(21),
        '一' => Some(22),
        '覧' => Some(23),
        '棒' => Some(24),
        '両' => Some(25),
        '手' => Some(26),
        '食' => Some(27),
        '物' => Some(28),
        '爆' => Some(29),
        '弾' => Some(30),
        '盾' => Some(31),
        '投' => Some(32),
        '射' => Some(33),
        '薬' => Some(34),
        'ん' => Some(35),
        '右' => Some(36),
        '左' => Some(37),
        '武' => Some(38),
        '兜' => Some(39),
        '鎧' => Some(40),
        'マ' => Some(41),
        'ン' => Some(42),
        'ト' => Some(43),
        '其' => Some(44),
        '他' => Some(45),
        'い' => Some(46),
        _ => None,
    }
}

fn alt_utf8_to_index(c: &char) -> Option<usize> {
    match c {
        'Ａ' => Some(0),
        'Ｔ' => Some(1),
        'Ｄ' => Some(2),
        'Ｅ' => Some(3),
        'Ｆ' => Some(4),
        _ => None,
    }
}

fn alt_utf8_to_byte_literals(input_str: &str) -> Vec<u8> {
    let mut bytes = Vec::new();
    for char in input_str.chars() {
        if let Some(index) =alt_utf8_to_index(&char) {
            bytes.push(index as u8);
        }
    }
    bytes.push(0xFF);
    bytes
}

fn alt_hd_utf8_to_byte_literals(input_str: &str) -> Vec<u8> {
    let mut bytes = Vec::new();
    for char in input_str.chars() {
        if let Some(index) = alt_hd_utf8_to_index(&char) {
            bytes.push(index as u8);
        }
    }
    bytes.push(0xFF);
    bytes
}

use clap::{Arg};

// fn main() {
//     let args: Vec<String> = env::args().collect();
//     let command = if args.len() > 1 { &args[1] } else { "" };

//     match command {
//         "parse" => {
//             if args.len() < 4 {
//                 eprintln!("Usage: parse <filename> <offset>");
//                 return;
//             }
//             let filename = &args[2];
//             let offset = &args[3];
//             if let Err(e) = parse(filename, offset) {
//                 eprintln!("Error: {}", e);
//             }
//         }
//         "process" => {
//             let filename = if args.len() > 2 { Some(args[2].clone()) } else { None };
//             if let Err(e) = process(filename) {
//                 eprintln!("Error: {}", e);
//             }
//         }
//         _ => {
//             eprintln!("Usage: <parse|process>");
//         }
//     }
// }
use clap::{ArgAction, Command};

fn main() {
    let matches = Command::new("string processor")
        .version("1.0")
        .author("Your Name <your.email@example.com>")
        .about("String processor to interpret sequence of characters from SOTN")
        .subcommand(
            Command::new("process")
                .about("process a file")
                .arg(
                    Arg::new("filename")
                        .short('f')
                        .long("filename")
                        .help("Filename")
                        .action(ArgAction::Set)
                        .num_args(1),
                )
        )
        .get_matches();

    match matches.subcommand() {
        // Some(("parse", sub_m)) => {
        //     // let filename = sub_m.value_of("filename").unwrap();
        //     // let offset = sub_m.value_of("offset").unwrap();
        // }
        Some(("process", sub_m)) => {
            if sub_m.contains_id("filename") {
                let filename = sub_m
                .get_one::<String>("filename")
                .expect("is present");
                let _ = process(Some(filename.to_string()));
            } else {
                let _ = process(None);
            }
        }
        _ => {}
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_dakuten() {
        assert_eq!(dakuten('゙', 'シ'), Some('ジ'));
        assert_eq!(dakuten('゙', 'ク'), Some('グ'));
        assert_eq!(dakuten('゙', 'て'), Some('で'));
        assert_eq!(dakuten('゚', 'フ'), Some('プ'));
        assert_eq!(dakuten('゚', 'ヒ'), Some('ピ'));
        assert_eq!(dakuten('゙', 'X'), None);
    }

    #[test]
    fn test_utf8_to_byte_literals_escaped()
    {
        assert_eq!(utf8_to_byte_literals_escaped("すで"), "\\xBD\\xC3\\xFF\\x9E\\xFF");
        assert_eq!(utf8_to_byte_literals_escaped("あかつきの剣"), "\\xB1\\xB6\\xC2\\xB7\\xC9\\x3C\\xFF");
        assert_eq!(utf8_to_byte_literals_escaped("聖なるめがね"), "\\xEE\\xC5\\xD9\\xD2\\xB6\\xFF\\x9E\\xC8\\xFF");
        assert_eq!(utf8_to_byte_literals_escaped("バルザイのえん月刀"), "\\x8A\\xFF\\x9E\\x99\\x7B\\xFF\\x9E\\x72\\xC9\\xB4\\xDD\\xFF\\xFF\\xED\\xFF");
        assert_eq!(utf8_to_byte_literals_escaped("Str. potion"), "\\x33\\x54\\x52\\x0E\\x00\\x50\\x4F\\x54\\x49\\x4F\\x4E\\xFF");
    }

    #[test]
    fn test_do_sub() {
        // Test case 1: Test _S("すで")
        let line = r#"{_S("すで"), "装備なし（素手）", 0, 0, 0, 3, 255, 0, 0, 36, 42, 0, 5, 128, 0, 0, false, 8, 0, 0, 0, 0, 4, 2, 1, 1, 1, 1, 0},"#;
        let out = do_sub(line);
        let expected = r#"{"\xBD\xC3\xFF\x9E\xFF", "装備なし（素手）", 0, 0, 0, 3, 255, 0, 0, 36, 42, 0, 5, 128, 0, 0, false, 8, 0, 0, 0, 0, 4, 2, 1, 1, 1, 1, 0},"#;
        assert_eq!(out, expected);

        // Test case 2: Test _S("")
        let line = r#"_S("")"#;
        let out = do_sub(line);
        let expected = r#""\xFF""#;
        assert_eq!(out, expected);

        // // Test case 3: Test _S with symbols and quotes
        // let line = r#"_S("\"(\")")"#;
        // let out = do_sub(line);
        // let expected = r#""\x02\x08\x02\x09\xFF""#;
        // assert_eq!(out, expected);

        // Test case 4: Test _S2("ＡＴＴ")
        let line = r#"_S2("ＡＴＴ")"#;
        let out = do_sub(line);
        let expected = r#""\x00\x01\x01\xFF""#;
        assert_eq!(out, expected);

        // Test case 5: Test _S2("")
        let line = r#"_S2("")"#;
        let out = do_sub(line);
        let expected = r#""\xFF""#;
        assert_eq!(out, expected);

        // Test case 6: Test _S2_HD("攻撃力")
        let line = r#"_S2_HD("攻撃力")"#;
        let out = do_sub(line);
        let expected = r#""\x0C\x0D\x0E\xFF""#;
        assert_eq!(out, expected);

        // Test case 7: Test _S2_HD("")
        let line = r#"_S2_HD("")"#;
        let out = do_sub(line);
        let expected = r#""\xFF""#;
        assert_eq!(out, expected);
    }

    #[test]
    fn more_do_sub()
    {
        let line = r#"{_S("たび人ぼう"), "旅人の基本装備である帽子", 0, 3, 0, 0, 1, 0, 0, 0x0000, 0x0000, 0x0000, 168, 168, 0, 0},"#;
        let out = do_sub(line);
        let expected = r#"{"\xC0\xCB\xFF\x9E\xA3\xCE\xFF\x9E\xB3\xFF", "旅人の基本装備である帽子", 0, 3, 0, 0, 1, 0, 0, 0x0000, 0x0000, 0x0000, 168, 168, 0, 0},"#;
        assert_eq!(out, expected);

        let line = r#"/* 0x18C */ {_S("Guardian"), 500, 50, 33, 34, 35, 0x0000, 0x0040, 0xE000, 0x0800, 60, 1500, 321, 255, 2, 1, 6, 24, 0x08403410},"#;
        let out = do_sub(line);
        let expected = r#"/* 0x18C */ {"\x27\x55\x41\x52\x44\x49\x41\x4E\xFF", 500, 50, 33, 34, 35, 0x0000, 0x0040, 0xE000, 0x0800, 60, 1500, 321, 255, 2, 1, 6, 24, 0x08403410},"#;
        assert_eq!(out, expected);

let line = r#"const char* g_goldCollectTexts[] = {
    _S("$1"),   _S("$25"),  _S("$50"),   _S("$100"),  _S("$250"),
    _S("$400"), _S("$700"), _S("$1000"), _S("$2000"), _S("$5000"),
};"#;

let expected = r#"const char* g_goldCollectTexts[] = {
    "\x04\x11\xFF",   "\x04\x12\x15\xFF",  "\x04\x15\x10\xFF",   "\x04\x11\x10\x10\xFF",  "\x04\x12\x15\x10\xFF",
    "\x04\x14\x10\x10\xFF", "\x04\x17\x10\x10\xFF", "\x04\x11\x10\x10\x10\xFF", "\x04\x12\x10\x10\x10\xFF", "\x04\x15\x10\x10\x10\xFF",
};"#;

        let out = do_sub(line);
        assert_eq!(out, expected);

        let line = r#"_S("ナイフ(サブ)"),"#;
        let out = do_sub(line);
        let expected = r#""\x85\x72\x8C\x08\x7B\x8C\xFF\x9E\x09\xFF","#;
        assert_eq!(out, expected);
    }
}
