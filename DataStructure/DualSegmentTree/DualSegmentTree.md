# DualSegmentTree（双対セグメント木）
長さ $N$ の配列に対して区間作用・１点取得を $O(\log N)$ で行う.   
区間作用・区間取得ができる遅延評価セグメント木と比べ機能を落とした代わりに，定数倍と実装が軽い.   

遅延を伝播させる機能も削除しているため，非可換な作用（区間更新など）はそのまま用いることができない.   
（区間更新の場合は｛時間，値｝のペアをもってchmaxするとできる）

## 使い方
$S$ は型， $op$ は二項演算， $e$ は単位元（ACLのsegtreeと同じ）. 
- `DualSegTree<S, op, e> seg(int N)` : コンストラクタ. 長さ $N$ の配列 $A$ を作る. 初期値は $e$ .  $O(N)$
- `DualSegTree<S, op, e> seg(vector<S> v)` : コンストラクタ.  $v$ の内容で初期化された配列 $A$ を作る.  $O(N)$
- `void set(int i, S x)` : $A_i$ に $x$ を代入する.  $O(\log N)$
- `S get(int i)` : $A_i$ の値を取得する.  $O(\log N)$
- `void apply(int l, int r, S x)` : $\ i=l~,\cdots,~r-1$ に対して $A_i=op(A_i,~x)$ .  $O(\log N)$
