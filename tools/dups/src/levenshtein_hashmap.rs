use crate::types::Function;
use std::collections::HashMap;

pub struct LevenshteinHashMap {
    pub map: HashMap<Vec<u8>, Vec<Function>>,
    threshold: f64,
    cache: HashMap<(Vec<u8>, Vec<u8>), f64>,
}

fn levenshtein_similarity(
    s1: &[u8],
    s2: &[u8],
    cache: &mut HashMap<(Vec<u8>, Vec<u8>), f64>,
) -> f64 {
    if let Some(result) = cache.get(&(s1.to_vec(), s2.to_vec())) {
        // Return cached result if it exists
        return *result;
    }

    let len1 = s1.len();
    let len2 = s2.len();
    let mut dp = vec![vec![0; len2 + 1]; len1 + 1];

    for i in 0..=len1 {
        dp[i][0] = i;
    }

    for j in 0..=len2 {
        dp[0][j] = j;
    }

    for (i, x) in s1.iter().enumerate() {
        for (j, y) in s2.iter().enumerate() {
            dp[i + 1][j + 1] = if x == y {
                dp[i][j]
            } else {
                dp[i][j].min(dp[i][j + 1]).min(dp[i + 1][j]) + 1
            };
        }
    }

    let max_len = len1.max(len2) as f64;
    let result = (max_len - dp[len1][len2] as f64) / max_len;
    cache
        .entry((s1.to_vec(), s2.to_vec()))
        .and_modify(|v| *v = result)
        .or_insert(result);
    result
}

impl LevenshteinHashMap {
    pub fn new(threshold: f64) -> Self {
        Self {
            map: HashMap::new(),
            threshold,
            cache: HashMap::new(),
        }
    }
    pub fn _len(&self) -> usize {
        self.map.len()
    }
    pub fn _iter(&self) -> impl Iterator<Item = (&Vec<u8>, &Vec<Function>)> {
        self.map.iter()
    }

    pub fn _get(&mut self, key: &[u8]) -> Option<&mut Vec<Function>> {
        let mut closest_key = None;
        let mut closest_similarity = f64::MIN;


        for (k, _) in self.map.iter() {
            let size_diff = key.len().min(k.len()) as f64 / key.len().max(k.len()) as f64;
            if size_diff < self.threshold || size_diff <= closest_similarity {
                continue;
            }

            let similarity = levenshtein_similarity(key, k, &mut self.cache);

            if  similarity >= self.threshold && similarity > closest_similarity {
                closest_key = Some(k.clone());
                closest_similarity = similarity;
            }
        }

        closest_key.and_then(|k| self.map.get_mut(&k))
    }

    pub fn insert(&mut self, key: Vec<u8>, mut value: Function) {
        let mut closest_key = None;
        let mut closest_similarity = f64::MIN;

        for k in self.map.keys() {
            let size_diff = key.len().min(k.len()) as f64 / key.len().max(k.len()) as f64;
            if size_diff < self.threshold || size_diff <= closest_similarity {
                continue;
            }

            let similarity = levenshtein_similarity(&key, k, &mut self.cache);

            if  similarity >= self.threshold && similarity > closest_similarity {
                closest_key = Some(k.clone());
                closest_similarity = similarity;
            }
        }

        if let Some(k) = closest_key {
            let val = self.map.get_mut(&k);
            value.similarity = closest_similarity;
            val.unwrap().push(value);
        } else {
            value.similarity = 1.0;
            self.map.insert(key, vec![value]);
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_insert_and_get_same_cluster() {
        let mut map = LevenshteinHashMap::new(0.95);
        let func1 = Function {
            name: String::from("func1"),
            ops: vec![],
            key: vec![1, 2, 3],
            decompiled: false,
            dir: String::from("testdir1"),
            file: String::from("testfile1"),
            similarity: 0.0,
        };
        let func2 = Function {
            name: String::from("func2"),
            ops: vec![],
            key: vec![1, 2, 3],
            decompiled: false,
            dir: String::from("testdir2"),
            file: String::from("testfile2"),
            similarity: 0.0,
        };

        map.insert(func1.key.clone(), func1.clone());
        map.insert(func2.key.clone(), func2.clone());

        // both functions should be in the same cluster
        let result1 = map._get(&vec![1, 2, 3]);
        assert_eq!(result1.expect("has items").len(), 2);
    }

    #[test]
    fn test_insert_and_get_different_cluster() {
        let mut map = LevenshteinHashMap::new(0.95);
        let func1 = Function {
            name: String::from("func1"),
            ops: vec![],
            key: vec![1, 2, 3],
            decompiled: false,
            dir: String::from("testdir1"),
            file: String::from("testfile1"),
            similarity: 0.0,
        };
        let func2 = Function {
            name: String::from("func2"),
            ops: vec![],
            key: vec![4, 5, 6],
            decompiled: false,
            dir: String::from("testdir2"),
            file: String::from("testfile2"),
            similarity: 0.0,
        };

        map.insert(func1.key.clone(), func1.clone());
        map.insert(func2.key.clone(), func2.clone());

        // functions should be in different clusters
        let result1 = map._get(&vec![1, 2, 3]);
        assert_eq!(result1.expect("has items").len(), 1);

        let result2 = map._get(&vec![4, 5, 6]);
        assert_eq!(result2.expect("has items").len(), 1);
    }
}
