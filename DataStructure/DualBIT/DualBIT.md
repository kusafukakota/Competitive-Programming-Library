# DualBIT
BITを２本持つことで区間加算クエリにも対応できる．
## 使い方
$T$ は型， $N$ は要素数．
- `DualBIT<T>(int N)` : コンストラクタ．長さ $N$ の配列 $A$ を作る．初期値は全て０． $O(N)$
- `void add(int i, T x)` : $A_i$ に $x$ を加算する． $O(\log N)$
- `void add(int l, int r, T x)` : $\ i=l~,\cdots,~r-1$ に対して $A_i$ に $x$ を加算する． $O(\log N)$
- `T sum(int i)` : $A_0+A_1+\cdots+A_{i-1}$ を返す． $O(\log N)$
- `T sum(int l,int r)` : $A_l+A_{l+1}+\cdots+A_{i-1}$ を返す． $O(\log N)$
- `T operator[](int i)` : $A_i$ を返す． $O(\log N)$
