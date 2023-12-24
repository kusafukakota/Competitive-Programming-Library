# PrioritySum_Multi
整数の多重集合において，昇順/降順 $`k`$ 個の総和を求める。同じディレクトリにある PrioritySum より機能が多いが，定数倍が重い。
# 使い方
$`N`$ を要素の種類数とする。  
`use` $`\longrightarrow`$ `build` $`\longrightarrow`$ その他 の順番で使う。
- `void use(ll x)` : `insert`クエリで追加される整数を入力する。$`O(\log N)`$
- `void build()` : データ構造を構築する。`use`で追加される整数を入力し終えてから呼び出す。$`O(N\log N)`$
- `void insert(ll x,ll c = 1)` : 要素 $`x`$ を $`c`$ 個追加する。$`O(\log N)`$
- `void erase(ll x,ll c = 1)` : 要素 $`x`$ を $`c`$ 個削除する。存在する数より多く消すと壊れる。$`O(\log N)`$
- `ll min(ll k)` : 昇順 $`k`$ 個の総和を返す。$`O(\log N)`$
- `ll max(ll k)` : 降順 $`k`$ 個の総和を返す。$`O(\log N)`$
