use crate::image::Rgba;
use crate::sprite::PALETTE_BANK_SIZE;

pub struct Record {
    pub index: usize,
    pub width: u32,
    pub height: u32,
    pub pixels: Vec<u8>,
}

pub struct Group {
    pub label: Option<usize>,
    pub palette: Option<Vec<u8>>,
    pub records: Vec<Record>,
}

pub const SHEET_WIDTH: u32 = 640;
const MARGIN: u32 = 8;
const GUTTER: u32 = 6;
const HEADER_HEIGHT: u32 = 18;
const LABEL_HEIGHT: u32 = GLYPH_HEIGHT + 3;

const BACKGROUND: [u8; 4] = [22, 22, 27, 255];
const HEADER_BAND: [u8; 4] = [50, 50, 62, 255];
const HEADER_TEXT: [u8; 4] = [236, 236, 246, 255];
const LABEL_TEXT: [u8; 4] = [140, 140, 158, 255];
const RECORD_BACKING: [u8; 4] = [38, 38, 46, 255];

const DIGITS: [[u8; 5]; 10] = [
    [0b111, 0b101, 0b101, 0b101, 0b111],
    [0b010, 0b110, 0b010, 0b010, 0b111],
    [0b111, 0b001, 0b111, 0b100, 0b111],
    [0b111, 0b001, 0b111, 0b001, 0b111],
    [0b101, 0b101, 0b111, 0b001, 0b001],
    [0b111, 0b100, 0b111, 0b001, 0b111],
    [0b111, 0b100, 0b111, 0b101, 0b111],
    [0b111, 0b001, 0b001, 0b001, 0b001],
    [0b111, 0b101, 0b111, 0b101, 0b111],
    [0b111, 0b101, 0b111, 0b001, 0b111],
];
const GLYPH_WIDTH: u32 = 3;
const GLYPH_HEIGHT: u32 = 5;
const GLYPH_SPACING: u32 = 1;

fn digits_of(value: usize, min_width: usize) -> Vec<usize> {
    let mut out = Vec::new();
    let mut value = value;
    while value > 0 {
        out.push(value % 10);
        value /= 10;
    }
    while out.len() < min_width.max(1) {
        out.push(0);
    }
    out.reverse();
    out
}

fn number_width(count: usize, scale: u32) -> u32 {
    if count == 0 {
        return 0;
    }
    (count as u32) * (GLYPH_WIDTH + GLYPH_SPACING) * scale - GLYPH_SPACING * scale
}

fn draw_number(
    sheet: &mut Rgba,
    x: u32,
    y: u32,
    value: usize,
    min_width: usize,
    scale: u32,
    colour: [u8; 4],
) {
    let mut cursor = x;
    for digit in digits_of(value, min_width) {
        let glyph = DIGITS[digit];
        for (row, bits) in glyph.iter().enumerate() {
            for column in 0..GLYPH_WIDTH {
                if bits & (1 << (GLYPH_WIDTH - 1 - column)) == 0 {
                    continue;
                }
                sheet.fill_rect(
                    cursor + column * scale,
                    y + (row as u32) * scale,
                    scale,
                    scale,
                    colour,
                );
            }
        }
        cursor += (GLYPH_WIDTH + GLYPH_SPACING) * scale;
    }
}

struct Placement {
    x: u32,
    y: u32,
}

fn place(records: &[Record], top: u32) -> (Vec<Placement>, u32) {
    let mut placements = Vec::with_capacity(records.len());
    let mut x = MARGIN;
    let mut y = top;
    let mut shelf = 0u32;
    for record in records {
        let height = record.height + LABEL_HEIGHT;
        if x > MARGIN && x + record.width > SHEET_WIDTH - MARGIN {
            x = MARGIN;
            y += shelf + GUTTER;
            shelf = 0;
        }
        placements.push(Placement { x, y });
        x += record.width + GUTTER;
        shelf = shelf.max(height);
    }
    (placements, y + shelf - top)
}

fn colour_of(palette: Option<&Vec<u8>>, index: u8) -> [u8; 4] {
    if index == 0 {
        return RECORD_BACKING;
    }
    match palette {
        Some(rgb) if rgb.len() == PALETTE_BANK_SIZE * 3 => {
            let at = index as usize * 3;
            [rgb[at], rgb[at + 1], rgb[at + 2], 255]
        }
        _ => {
            let level = index * 17;
            [level, level, level, 255]
        }
    }
}

fn draw_record(sheet: &mut Rgba, at: &Placement, record: &Record, palette: Option<&Vec<u8>>) {
    sheet.fill_rect(at.x, at.y, record.width, record.height, RECORD_BACKING);
    for y in 0..record.height {
        for x in 0..record.width {
            let index = record.pixels[(y * record.width + x) as usize];
            sheet.set(at.x + x, at.y + y, colour_of(palette, index));
        }
    }
    draw_number(
        sheet,
        at.x,
        at.y + record.height + 2,
        record.index,
        1,
        1,
        LABEL_TEXT,
    );
}

pub fn build(groups: &[Group]) -> Rgba {
    let mut height = MARGIN;
    let mut layout = Vec::with_capacity(groups.len());
    for group in groups {
        height += HEADER_HEIGHT;
        let (placements, used) = place(&group.records, height);
        layout.push(placements);
        height += used + GUTTER * 2;
    }
    height = height.max(MARGIN * 2);

    let mut sheet = Rgba::new(SHEET_WIDTH, height, BACKGROUND);
    let mut cursor = MARGIN;
    for (group, placements) in groups.iter().zip(&layout) {
        sheet.fill_rect(0, cursor, SHEET_WIDTH, HEADER_HEIGHT, HEADER_BAND);
        let mut after = MARGIN;
        if let Some(label) = group.label {
            draw_number(&mut sheet, MARGIN, cursor + 4, label, 2, 2, HEADER_TEXT);
            after += number_width(2, 2) + 8;
        }
        draw_number(
            &mut sheet,
            after,
            cursor + 7,
            group.records.len(),
            1,
            1,
            LABEL_TEXT,
        );
        cursor += HEADER_HEIGHT;

        let mut used = 0;
        for (record, at) in group.records.iter().zip(placements) {
            draw_record(&mut sheet, at, record, group.palette.as_ref());
            used = used.max(at.y + record.height + LABEL_HEIGHT - cursor);
        }
        cursor += used + GUTTER * 2;
    }
    sheet
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn digits_pad_and_order_most_significant_first() {
        assert_eq!(digits_of(0, 2), vec![0, 0]);
        assert_eq!(digits_of(7, 2), vec![0, 7]);
        assert_eq!(digits_of(123, 2), vec![1, 2, 3]);
    }

    #[test]
    fn a_number_is_drawn_inside_its_measured_width() {
        let mut sheet = Rgba::new(64, 16, BACKGROUND);
        draw_number(&mut sheet, 0, 0, 90, 2, 1, HEADER_TEXT);
        let width = number_width(2, 1);
        assert!((0..width).any(|x| (0..GLYPH_HEIGHT).any(|y| lit(&sheet, x, y))));
        assert!(!(width..64).any(|x| (0..16).any(|y| lit(&sheet, x, y))));
    }

    fn lit(sheet: &Rgba, x: u32, y: u32) -> bool {
        let at = ((y * sheet.width + x) * 4) as usize;
        sheet.pixels[at..at + 4] != BACKGROUND
    }

    #[test]
    fn records_wrap_onto_a_new_shelf_instead_of_running_off_the_sheet() {
        let record = |index: usize, width: u32| Record {
            index,
            width,
            height: 16,
            pixels: vec![0; (width * 16) as usize],
        };
        let records = vec![record(0, 300), record(1, 300), record(2, 300)];
        let (placements, height) = place(&records, 0);
        assert_eq!(placements[0].y, placements[1].y, "two fit on one shelf");
        assert!(placements[2].y > placements[1].y, "the third must wrap");
        assert!(
            placements[2].x == MARGIN,
            "a wrapped record starts at the margin"
        );
        assert!(height >= (16 + LABEL_HEIGHT) * 2);
    }
}
