# ErasablePriorityQueue（消せるpriority_queue）
消せる priority_queue. multiset でも同じことができるが，こちらの方が定数倍が良い.

## 使い方
$T$ は型， $N$ は要素数．
- `ErasablePriorityQueue<T, greater<T>>` : コンストラクタ．数を昇順で管理する．
- `ErasablePriorityQueue<T, less<T>>` : コンストラクタ．数を降順で管理する．
- `void push(T x)` : $x$ を追加する． $O(\log N)$
- `void erase(T x)` : $x$ を削除する．入っている数より多く消すと壊れる． $O(\log N)$
- `T top()` : 最大値/最小値を返す． $O(1)$
- `int size()` : 要素数を返す． $O(1)$
- `bool empty()` : キューが空かどうか返す． $O(1)$
