
pub const WINDOW_SIZE: usize = 0x400;
pub const MAX_MATCH: usize = 34;
pub const MATCH_THRESHOLD: usize = 2;
pub const INITIAL_CURSOR: usize = WINDOW_SIZE - MAX_MATCH;
const NIL: usize = WINDOW_SIZE;

pub fn decompress(data: &[u8]) -> Vec<u8> {
    let mut dictionary = [0u8; WINDOW_SIZE];
    let mut cursor = INITIAL_CURSOR;
    let mut output = Vec::new();
    let mut source = 0usize;
    let mut flags: u32 = 0;

    while source < data.len() {
        flags >>= 1;
        if flags & 0x100 == 0 {
            flags = data[source] as u32 | 0xFF00;
            source += 1;
        }

        if flags & 1 != 0 {
            if source >= data.len() {
                break;
            }
            let value = data[source];
            source += 1;
            output.push(value);
            dictionary[cursor] = value;
            cursor = (cursor + 1) & (WINDOW_SIZE - 1);
        } else {
            if source + 1 >= data.len() {
                break;
            }
            let (first, second) = (data[source], data[source + 1]);
            source += 2;
            let index = first as usize | ((second as usize & 0xE0) << 3);
            let length = (second as usize & 0x1F) + MATCH_THRESHOLD + 1;
            for step in 0..length {
                let value = dictionary[(index + step) & (WINDOW_SIZE - 1)];
                output.push(value);
                dictionary[cursor] = value;
                cursor = (cursor + 1) & (WINDOW_SIZE - 1);
            }
        }
    }
    output
}

struct MatchTree {
    text: [u8; WINDOW_SIZE + MAX_MATCH - 1],
    left: [usize; WINDOW_SIZE + 257],
    right: [usize; WINDOW_SIZE + 257],
    parent: [usize; WINDOW_SIZE + 257],
    match_position: usize,
    match_length: usize,
}

impl MatchTree {
    fn new() -> Box<MatchTree> {
        Box::new(MatchTree {
            text: [0; WINDOW_SIZE + MAX_MATCH - 1],
            left: [NIL; WINDOW_SIZE + 257],
            right: [NIL; WINDOW_SIZE + 257],
            parent: [NIL; WINDOW_SIZE + 257],
            match_position: 0,
            match_length: 0,
        })
    }

    fn insert(&mut self, position: usize) {
        let mut compare: i32 = 1;
        let mut node = WINDOW_SIZE + 1 + self.text[position] as usize;
        self.left[position] = NIL;
        self.right[position] = NIL;
        self.match_length = 0;

        loop {
            if compare >= 0 {
                if self.right[node] != NIL {
                    node = self.right[node];
                } else {
                    self.right[node] = position;
                    self.parent[position] = node;
                    return;
                }
            } else if self.left[node] != NIL {
                node = self.left[node];
            } else {
                self.left[node] = position;
                self.parent[position] = node;
                return;
            }

            let mut length = 1;
            while length < MAX_MATCH {
                compare = self.text[position + length] as i32 - self.text[node + length] as i32;
                if compare != 0 {
                    break;
                }
                length += 1;
            }
            if length > self.match_length {
                self.match_position = node;
                self.match_length = length;
                if length == MAX_MATCH {
                    break;
                }
            }
        }

        self.parent[position] = self.parent[node];
        self.left[position] = self.left[node];
        self.right[position] = self.right[node];
        let (l, r) = (self.left[node], self.right[node]);
        self.parent[l] = position;
        self.parent[r] = position;
        let up = self.parent[node];
        if self.right[up] == node {
            self.right[up] = position;
        } else {
            self.left[up] = position;
        }
        self.parent[node] = NIL;
    }

    fn delete(&mut self, position: usize) {
        if self.parent[position] == NIL {
            return;
        }
        let replacement;
        if self.right[position] == NIL {
            replacement = self.left[position];
        } else if self.left[position] == NIL {
            replacement = self.right[position];
        } else {
            let mut candidate = self.left[position];
            if self.right[candidate] != NIL {
                while self.right[candidate] != NIL {
                    candidate = self.right[candidate];
                }
                let up = self.parent[candidate];
                self.right[up] = self.left[candidate];
                let l = self.left[candidate];
                self.parent[l] = up;
                self.left[candidate] = self.left[position];
                let l = self.left[position];
                self.parent[l] = candidate;
            }
            self.right[candidate] = self.right[position];
            let r = self.right[position];
            self.parent[r] = candidate;
            replacement = candidate;
        }

        self.parent[replacement] = self.parent[position];
        let up = self.parent[position];
        if self.right[up] == position {
            self.right[up] = replacement;
        } else {
            self.left[up] = replacement;
        }
        self.parent[position] = NIL;
    }
}

pub fn compress(data: &[u8]) -> Vec<u8> {
    if data.is_empty() {
        return Vec::new();
    }

    let mut tree = MatchTree::new();
    let mut source = MAX_MATCH.min(data.len());
    let mut pending = source;
    let mut read_position = 0usize;
    let mut cursor = INITIAL_CURSOR;
    tree.text[cursor..cursor + pending].copy_from_slice(&data[..pending]);

    tree.insert(cursor);

    let mut output = Vec::new();
    let mut group: Vec<u8> = vec![0];
    let mut mask: u32 = 1;

    while pending > 0 {
        let match_length = tree.match_length.min(pending);
        let consumed;
        if match_length <= MATCH_THRESHOLD {
            consumed = 1;
            group[0] |= mask as u8;
            group.push(tree.text[cursor]);
        } else {
            consumed = match_length;
            group.push((tree.match_position & 0xFF) as u8);
            group.push(
                (((tree.match_position >> 3) & 0xE0) | (match_length - MATCH_THRESHOLD - 1)) as u8,
            );
        }

        mask <<= 1;
        if mask == 0x100 {
            output.extend_from_slice(&group);
            group = vec![0];
            mask = 1;
        }

        let mut advanced = 0;
        while advanced < consumed && source < data.len() {
            let value = data[source];
            source += 1;
            tree.delete(read_position);
            tree.text[read_position] = value;
            if read_position < MAX_MATCH - 1 {
                tree.text[read_position + WINDOW_SIZE] = value;
            }
            read_position = (read_position + 1) & (WINDOW_SIZE - 1);
            cursor = (cursor + 1) & (WINDOW_SIZE - 1);
            tree.insert(cursor);
            advanced += 1;
        }
        while advanced < consumed {
            tree.delete(read_position);
            read_position = (read_position + 1) & (WINDOW_SIZE - 1);
            cursor = (cursor + 1) & (WINDOW_SIZE - 1);
            pending -= 1;
            if pending > 0 {
                tree.insert(cursor);
            }
            advanced += 1;
        }
    }

    if group.len() > 1 {
        output.extend_from_slice(&group);
    }
    output
}

#[cfg(test)]
mod tests {
    use super::*;

    fn round_trips(data: &[u8]) -> bool {
        let packed = compress(data);
        let unpacked = decompress(&packed);
        unpacked.len() >= data.len() && &unpacked[..data.len()] == data
    }

    #[test]
    fn empty_input_makes_an_empty_stream() {
        assert!(compress(&[]).is_empty());
        assert!(decompress(&[]).is_empty());
    }

    #[test]
    fn literals_round_trip() {
        assert!(round_trips(b"A"));
        assert!(round_trips(b"the quick brown fox"));
        assert!(round_trips(&(0..=255u8).collect::<Vec<u8>>()));
    }

    #[test]
    fn runs_and_repeats_round_trip() {
        assert!(round_trips(&[0u8; 4096]));
        assert!(round_trips(&[0xABu8; 33]));
        assert!(round_trips(&b"abcabcabcabc".repeat(500)));
        let mut long = Vec::new();
        for i in 0..8192u32 {
            long.push((i % 7) as u8);
        }
        assert!(round_trips(&long));
    }

    #[test]
    fn pseudorandom_input_round_trips() {
        let mut state = 0x1234_5678u32;
        let data: Vec<u8> = (0..20000)
            .map(|_| {
                state = state.wrapping_mul(1103515245).wrapping_add(12345);
                (state >> 16) as u8
            })
            .collect();
        assert!(round_trips(&data));
    }

    #[test]
    fn a_run_actually_compresses() {
        let data = [0x5Au8; 2048];
        assert!(compress(&data).len() < data.len() / 8);
    }

    #[test]
    fn overshoot_never_exceeds_a_whole_match() {
        let data: Vec<u8> = (0..1000).map(|i| (i % 13) as u8).collect();
        let unpacked = decompress(&compress(&data));
        assert!(unpacked.len() >= data.len());
        assert!(
            unpacked.len() - data.len() < MAX_MATCH,
            "overshot by {}",
            unpacked.len() - data.len()
        );
    }
}
