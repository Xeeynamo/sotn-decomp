use std::env;
use std::io::{self, Read, Write};
use std::process::{Command, Stdio};
use std::os::unix::process::ExitStatusExt;

const END_OF_COMMENT: &str = " */  ";
const MIN_LENGTH: usize = "    /* 99 0891A698 100006D0 */  ".len();
const DATA_POS: usize = "    /* 1BD8C 0891A698 ".len();

fn should_patch(op: &str) -> bool {
    const OPS: &[&str] = &[
        "vrot","vmov","vone","vzero","vs2i","vi2f","vadd","lv","sv","vcst","vmul","vsin","vcos",
        "vf2id","vf2iz","vf2in","vf2iu","vsub","vdiv","vscl","vtfm4","vmax","vmin","vdot","vcrsp",
        "vfad","vavg","vcmp","vsgn","vrsq","vcmovt","vsqrt","vcmovf","vfim","vocp","vuc2ifs",
        "vi2uc","mtv","mfv","vpfxs","vpfxt","bvtl","vpfxd",
    ];
    OPS.contains(&op)
}

fn patch_line(line: &str) -> String {
    if line.len() < MIN_LENGTH {
        return line.to_owned();
    }
    match line.find(END_OF_COMMENT) {
        None => line.to_owned(),
        Some(end_of_comment_index) => {
            let opcode_index = end_of_comment_index+END_OF_COMMENT.len();
            let remaining = &line[opcode_index..];
            let opcode_raw = remaining.split_whitespace().next().unwrap_or_default();
            if opcode_raw.len() < 2 {
                return line.to_owned();
            }

            // strip suffix like ".s", ".p" from the opcode
            let opcode = opcode_raw.split('.').next().unwrap_or(opcode_raw);
            if !should_patch(opcode) {
                return line.to_owned();
            }

            let mut out = String::with_capacity(line.len() + 16);
            out.push_str(&line[..opcode_index]);
            out.push_str(".word 0x");
            let data_str = &line[end_of_comment_index-8..end_of_comment_index];
            let b = data_str.as_bytes();
            for ch in &[ // convert 0x12345678 to 0x78563412
                b[6] as char, b[7] as char, b[4] as char, b[5] as char,
                b[2] as char, b[3] as char, b[0] as char, b[1] as char,
            ] {
                out.push(*ch);
            }
            out
        }
    }

}

fn main() {
    let mut input = String::new();
    if io::stdin().read_to_string(&mut input).is_err() {
        std::process::exit(1);
    }

    let patched_lines = input
        .lines()
        .map(patch_line)
        .collect::<Vec<_>>()
        .join("\n") + "\n";

    let mut proc = match Command::new("bin/allegrex-as")
        .args(env::args().skip(1))
        .envs(env::vars())
        .stdin(Stdio::piped())
        .stdout(Stdio::inherit())
        .stderr(Stdio::inherit())
        .spawn()
    {
        Ok(c) => c,
        Err(e) => {
            println!("failed to run bin/allegrex-as: {}", e);
            std::process::exit(1)
        },
    };

    if let Some(mut stdin) = proc.stdin.take() {
        let _ = stdin.write_all(patched_lines.as_bytes());
        let _ = stdin.flush();
    }

    let status = proc.wait().unwrap_or_else(|_| std::process::ExitStatus::from_raw(1));
    std::process::exit(status.code().unwrap_or(1));
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_patch() {
        assert_eq!(patch_line("    /* 1BD30 0891A63C 000091C8 */  lv.s S410, 0x0($a0)"),
                   "    /* 1BD30 0891A63C 000091C8 */  .word 0xC8910000");
        assert_eq!(patch_line("    /* 7F0 09237E70 04208300 */  sllv       $a0, $v1, $a0"),
                   "    /* 7F0 09237E70 04208300 */  sllv       $a0, $v1, $a0");
    }
}
