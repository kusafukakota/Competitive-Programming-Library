# Binary Trie
非負整数の多重集合を管理できる。
## 使い方
挿入される値の最大値のビット長を $`w`$ とする。  
引数`xor_val`を指定すると，全要素を`xor_val`でxorした場合の動作をする。（変更はしない）
- `bool empty()` : 空かどうかを返す。$`O(1)`$
- `int size()` : 要素の個数（種類数ではない）を返す。$`O(1)`$
- `void insert(T val)` : 要素`val`を追加する。$`O(w)`$
- `void erase(T val)` : 要素`val`があれば１つ消去する。無ければ何もしない。 $`O(w)`$
- `void xor_all(T val)` : 全要素を`val`でxorした値に変更する。$`O(1)`$
- `T max_element(T xor_val = 0)` : 最大値を返す。$`O(w)`$
- `T min_element(T xor_val = 0)` : 最小値を返す。$`O(w)`$
- `T kth_smallest(int k, T xor_val = 0)` : `k`番目に小さい値を返す。`k`は0-indexed。$`O(w)`$
- `int lower_bound(T val, T xor_val = 0)` : `val`未満の要素数（種類数ではない）を返す。$`O(w)`$
- `int upper_bound(T val, T xor_val = 0)` : `val`以下の要素数（種類数ではない）を返す。$`O(w)`$
- `int count(T val)` : `val`の個数を返す。$`O(w)`$

