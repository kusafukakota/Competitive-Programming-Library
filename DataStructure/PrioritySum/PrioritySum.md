# PrioritySum
数の多重集合において，昇順/降順 $`k`$ 個の総和を求める。同じディレクトリにある PriorirySum_Multi より機能が制限されるが，定数倍が軽い。
## 使い方
$`N`$を要素数とする。
- `MinSum/MaxSum<T> s(k)` : コンストラクタ。`T`は要素の型，昇順/降順 $`k`$ 個に指定。
- `void insert(T x)` : 
