# PrioritySum
数の多重集合において，昇順/降順 $`k`$ 個の総和を求める。同じディレクトリにある PriorirySum_Multi より機能が制限されるが，定数倍が軽い。
## 使い方
$`N`$を要素数とする。
- `MinSum/MaxSum<T> s(k)` : コンストラクタ。`T`は要素の型，昇順/降順 $`k`$ 個に指定。
- `void insert(T x)` : 要素 $`x`$ を追加する。ならし $`O(\log N)`$
- `void erase(T x)` : 要素 $`x`$ を削除する。ならし $`O(\log N)`$
- `void query()` : 昇順/降順 $`k`$ 個の総和を返す。$`O(1)`$
- `void set(T K)` : $`k`$ の値を $`K`$ に指定し直す。$`O(|k-K|\log N)`$
- `ll get()` : $`k`$ の値を返す。$`O(1)`$
- `ll size()` : 要素数を返す。$`O(1)`$
