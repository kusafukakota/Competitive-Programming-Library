# Binary Trie
## 使い方
挿入される値の最大値のビット長を$`w`$とする。
- `bool empty()` : 空かどうかを返す。$`O(1)`$
- `int size()` : 格納されている整数の個数（種類数ではない）を返す。$`O(1)`$
- `void insert(T val)` : `val`を挿入する。$`O(w)`$
- `void erase(T val)` : `val`があれば１つ消去する。無ければ何もしない。 $`O(w)`$
- `void xor_all(T val)` : 全要素を`val`でxorした値に変更する。$`O(1)`$
- 
