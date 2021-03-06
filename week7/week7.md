# 第十一章 摊还分析

### 11.2 二项队列

- 声明：

​       N个元素的二项队列可以通过N次相继插入而以O(N)时间建成。

- 令Ci是第i次插入的代价。令Ti为第i次插入后的树的棵数。T0=0为树的初始棵 数。此时我们得到不变式

​        Ci +(Ti — Ti-1)= 2

- 数据结构在任意时刻的状态由一个称为位 势的函数给出。这个位势函数不由程序保存，而是一个计数装置，该装置将帮助进行分析。 当一些操作花费少于我们允许它们使用的时间时，则没有用到的时间就以一个更高位势的 形式“存储”起来。数据结构的位势就是树的棵数。
- 当我们有一些插入只用到一个单位而不是规定的两个单位的时候，则这个额外的单位通过增加位势而被存储起来以备其后使用。当操作出现超出规定的时间时，则超出的时间通过 位势的减少来计算。可以把位势看作一个储蓄账户。如果一次操作使用了少于指定的时间， 那么这个差额就被存储起来以备后面更昂贵的操作使用。
- 一旦位势函数被选定，我们就可写出主要的方程：

​        Tactual+△Potential=Tamortized

​        Tactual是一次操作的实际时间，代表需要执行一次特定操作需要的精确(遵守的)时间量。

##### 定理11.1 Insert 、 DeleteMin以及Merge对于二项队列的摊还运行时间分别是O(1)、O(log N)和 O(log N)。

## 11.3 斜堆

定义：一个节点少如果其右子树的后裔数至少是该P的后裔总数的一半，则称节点少 是重的，否则称之为轻的。注意，一个节点的后裔个数包括该节点本身。

##### 定理11.2 合并两个斜堆的摊还时间为O( log N)。

注意，初始的位势为0而且位势总是非负的。验证这一点很 重要，否则摊还时间就不能成为实际时间的界而且也就没有意义了。

## 11.4 斐波那契堆

斐波那契堆通过添加两个新的观念推广了二叉堆：

- DecreaseKey的一种不同的实现方法：我们以前看到的那种方法是把元素朝向根节 点上滤c对于这种方法似乎没有理由期望O(1)的摊还时间界，因此需要一种新的 方法。
- 懒惰合并:只有当两个堆需要合并时才进行合并。这类似于懒惰删 除。对于懒惰合并，Merge是低廉的，但是因为懒惰合并并不实际把树结合在一起， 所以DeleteMin操作可能会遇到许多的树，从而使这种操作的代价高昂。任何一次 DeleteMin都可能花费线性时间，但是总能够把时间归咎到前面的一些Merge操 作中去。特别地，一次昂贵的DeleteMin必须在其前面要有大量的非常低廉的 Merge操作，它们能够储存额外的位势。

### 11.4.1 切除左式堆中的节点

- 在二叉堆中，DecreaseKey操作是通过降低节点的值然后将其朝着根上滤直到建成堆 序来实现的。在最坏的情形下，它花费O(log N)时间，这是平衡树中通向根的最长路径 的长。
- 解决的办法是把堆沿着虚线切开，如此得到两棵树，然后再把这两棵树合并成一棵。令X为 要执行DecreaseKey操作的节点，令P为它的父节点。在切断以后我们得到两棵树，即根为 X的H1和T2，T2是原来的树除去H1后得到的树。如果这两棵树都是左式堆，那么它们可以以时间O(log N)合并，整个操作也就完成了。

恢复左式堆的性质，这要用到下列两个观察到的结论：

- 只有从P到T2的根的路径上的节点可能破坏左式堆的性质，它们可以通过交换子节点来调整。
- 由于最大右路径长最多有Llog(N+l)」个节点，因此我们只需检查从P到T2的根的路径上的前Llog(N+l)J个节点。

### 11.4.2 二项队列的懒惰合并

为了合并两个二项队列，只要把两个二项树的表连在一起，结果得到 一个新的二项队列。这个新的二项队列可能含有相同大小的多棵树，因此破坏二项队列的 性质。为了保持一致性，我们将把它叫作懒惰二项队列。这是一种快速操作，该操作总是花费常数(最坏情形)时间。和前面一样，一次插入通过创建一个单节点二项队列并将其合并而完成，区别在于合并是懒惰的。

###### 懒惰二项队列的摊还分析

为了进行懒惰二项队列的摊还分析，我们将用到对标准二项队列所使用的相同的位势 函数。因此，懒惰二项队列的位势是树的棵数。

##### 定理11.3 Merge和Insert的摊还运行时间对于懒惰二项队列均为0(1)。Delete- Min的摊还运行时间为O(log N) 。

### 11.4.3 斐波那契堆操作

为了保证R = O(log N),我们对所有的非根节点应用下述法则：

- 将第一次（因为切除而）失去一个子节点的（非根）节点做上标记。
- 如果被标记的节点又失去另外一个儿子节点，那么将其从它的父节点切除。这个节点现在变成了一棵分离的树的根并且不再被标记。这叫作一次级联切除,因为在一次DecreaseKey操作中可能出现多次这种切除。

### 11.4.4 时间界的证明

标记节点的原因是我们需要给任意节点的秩R（子节点的个数）确定一个界。具有N个后裔的任意节点的秩为O(log N)。

##### 引理11.1令X是斐波那契堆中的任意节点。令Ci为X的第i个最年轻的儿子。则Ci的秩至少是i-2。

##### 引理11.2 令Fk是由F0 = 1, F1=1,以及Fk=Fk-1+Fk-2定义的斐波那 契数。秩为R>=1的任意节点至少有FR+1个后裔(包括它自己)。

##### 引理11. 3 斐波那契堆中任意节点的秩为O(log N)。

##### 定理11.4 斐波那契堆对于Insert、Merge和DecreaseKey的摊还时间界均为O(1),而对于 DeleteMin 则是O(logN).

## 11.5 伸展树

一个确实有效的位势函数θ定义为

  θ(T) = 累加求和logS(i)

其中S(i)代表i的后裔的个数(包括i自身)。这个位势函数是对树T所有节点i所取的S(i)的 对数和。

##### 引理11.4 如果a+b<=c,且a和b均为正整数，那么 log a + log b<= 2 log c - 2

##### 定理11. 5 在节点X展开一棵根为T的树的摊还时间最多为3(R(T)-R(X)) + 1 = O( log N)。

# 第十二章 高级数据结构及其实现

## 12.1 自顶向下的伸展树

在访问的 任意时刻，我们都有一个当前节点X,它是其子树的根；在图中将它表示成“中间”树。树 L把节点都存放在小于X的树T中，但不在X的子树中；类似地，树R把节点存在大于X 的子树中，但不在X的子树中。初始时X为T的根，而L和R是空树。

展开：

- 如果旋转是一次单旋转，那么根在Y的树变成中间树的新根。X和子树B连接而成为 R中最小项的左儿子；X的左儿子逻辑上成为NULL。结果，X成为R的新的最小项。为使单旋转情形适用，Y不一定必须是一片树叶。如果我们查找小于Y的一项，而Y没有左儿子(但确有一个右儿子)，那么这种单旋转情形将是适用的。
- 对于一字形旋转，我们有类似的剖析。关键是在X和Y之间施行一次旋转。之字形旋 转把底部节点Z带到中间树的顶部，并把子树X和Y分别附接到R和L上。Y被附接从而成为L中的最大项。
- 之字形旋转这一步多少可以得到简化，因为没有旋转要执行，Z不再是中间树的根，Y取而代之。

插入：

- 一个新的指针(如果需要)被分配，且如果T是空的，那么建立一棵单节点树。否则，我们围绕Item展开T。若T的新根的数据等于 Item,则我们有一个复制拷贝；我们不是再次插入Item,而是为将来的插入保留New- Node并立即返回。如果T的新根含有大于Item的值，那么T的新根和它的右子树变成 NewNode的一棵右子树，而T的左子树则成为NewNode的左子树。如果T的新根含有小于Item的值，那么类似的逻辑仍然适用。在这两种情况下，NewNode均成为新的根。

## 12.2 红黑树

红黑树是具有下列着色性质的二叉查找树：

1.  每一个节点或者着红色，或者着黑色。
2.  根是黑色的。
3.  如果一个节点是红色的，那么它的子节点必须是黑色的。
4.  从一个节点到一个NULL指针的每一条路径必须包含相同数目的黑色节点。

通常把新项作为树叶放到树中；NULL节点都是黑色的

### 12.2.1 自底向上插入

新插入的项（红色）的父节点是黑色的，那么插入完成；如果父节点是红色的，且兄弟节点不是红的：令X是新加的树叶，P是它的父节点，S是该父节点的兄弟（若存在），G是祖父节点。在这种情形只有X和P是红的，G是黑的，否 则就会在插入前有两个相连的红色节点，违反了红黑树的法则。采用伸展树的术语， X、P和G可以形成一个一字形链或之字形链（两个方向中的任意一个方向）。第一种情形对应F和G之间的单旋转，而第二种情形对应双旋转，该双旋转首先在X 和P间进行，然后在X和G之间进行。在两种情形下，子树的新根均被涂成黑色，因此，即使原来的曾祖是红的，我们也排 除了两个相邻红节点的可能性。

### 12.2.2 自顶向下红黑树

- 在向下的过程中当我们看到一个节点X有两个红儿子 的时候，我们让X成为红的而让它的两个儿子是黑的。兄弟节点是红的被从顶向下过程中的行动所排除。
- 因为一些子树可能是空的，以及处理根的特殊的情况（尤其是根没有父亲），我们使用两个标记节点：一个是为根，一个是NulINode,它的作用像在伸展树中那样是指 示一个NULL指针。
- 一个双旋转 实际上是两个单旋转，而且只有当通向X的分支取相反方向时才进行。
- 当沿树向下进行的时候，Insert必须记录父亲、祖父和曾祖。
- 在一 次旋转之后，存储在祖父和曾祖中的值将不再正确。不过，可以肯定到下一次再需要它们 的时候它们将被重新存储。

### 12.2.3自顶向下删除

- 要删除一个带有两个儿子的节点，我们用右子树上的最小节点代替它；该节点必然 最多有一个儿子，然后将该节点删除。只有一个右儿子的节点可以用相同的方式删除，而只有一个是儿子的节点通过用其左子树上最大节点替换，然后可将该节点删除。
- 保证从上到下删除期间树叶是红的

## 12.3 确定性跳跃表

首先需要两个定义：

1. 定义：如果至少存在一个指针从一个元素指向另一个元素，称两个元素是链接的 (linked) 。
2. 定义：两个在高度为h链接的元素间的间隙容量(gap size)等于它们之间高度为h-1 的元素的个数。

- 1-2-3确定性跳跃表满足这样的性质：每一个间隙（除在头和尾之间可能的零间隙外）的容量为1、2或3。
- 当我们沿任意一层行进仅仅通过常数个指针然后就可下降到低一层。
- 为了执行插入，我们必须保证当一个高度为h的新节点加入进来时不会产生具有四个 高度为h的节点的间隙：设我们在第L层上,如果要降到的间隙容量是3,那么我们提高该间隙的中间项使其高度为L,从而形成两个容量为1的间隙。由于这使得朝向删除的 道路上消陇了容量为3的间隙，因此插入是安全的。
- 删除的困难出现在间隙容量为1的情况。当我们看到将要下降到一个容量为1的间隙时，我们把这个间隙放大：或者是通过从相邻间隙（如果容量不为1）借来的方式，或者通过降低该间隙与邻间隙分开的节点的高度的方式。由于这两个都是容量为1的间隙，因此结果变成容量为3的间隙。

## 12.4 AA树

我们采纳一些法则。

1.  首先，我们加入只有右儿子可以是红的的条件，这就消除了约一半的可能重新构建 的情形。它也消除在删除算法中一个恼人的情形：如果一个内部节点只有一个儿 子，那么这个儿子一定是右儿子（它刚好是红色的），因为黑色左儿子将会违反红黑树的条件4。因此，我们总可以用一个内部节点的右子树中的最小节点代替该内部节点。
2.  我们递归地编写这些过程。
3.  我们把信息存在一个短整型数中，而不是把一个颜色位和每个节点一起存储。这个信息就是节点的层次。节点的层次：

- 是1（若该节点是树叶）。
- 是它的父节点的层次（若该节点是红的）。
- 比它的父节点的层次少1（若该节点是黑的）。

水平链接是一个节点与同层次上的儿子之间的连接。这种结构需求使 得水平链接是向右的指针，并且不能有两个连续的水平链接。

当出现一个左水平链接通过右旋转消除，当出现两个连续的右水平链接通 过左旋转消除。

删除：首先，我们记得，如果一个节点不是树叶，那么它必然有一个右儿子, 这意味着，当删除一个节点的时候，我们总可以用其右子树上最小的儿子代替这个节点,这保证它是在第一层上。

## 12.5 treap树

- 它像跳跃表一样使用随机数并且对任意的输入都能给出O(log N)的期望时间的性能。
- 一个treap树就是 一棵二叉查找树，但其节点优先级满足堆序性质：任意节点的优先级必须至少和它父亲的 优先级一样大。
- 其每一项都有不同优先级的不同项的集合只能由一个treap树表示。
- 插入：在一项作为树叶加入之后，我们将它沿着该treap树向上旋转直到它的优先级满足堆序为止。
- 删除：在要删除的项找到 以后，通过把它的优先级增加到无穷大并沿着低优先级诸儿子的路径向下旋转而可将其删除。 一旦它是树叶，就可以把它除去。

## 12.6 k-d树

二维査找树具有简单的性质：在奇数层上的分支按照第一个关键字进行，而在偶数层

上的分支按照第二个关键字进行。根是任意选取的奇数层。

插入：在沿树下行时,我们需要保留当前的层。为保持程序代码简单，我们假设基本的项是两个元素的数组。此 时我们需要把层限制在0和1之间。

正交范围査询给出其第一个关键字在一个特殊的值集合之间且第二个关键字在另一个 特殊的值集合之间的所有的项。为找到特定的项，可以令Low和High等于我们要查找的项。为了执行一次部分匹配查询，我们让在这次匹配中涉及不到的关键字的范围为一∞到∞。其余范围设置为低点和高点等于匹配中所涉及的关键字的值。

## 12.7 匹配堆

- 配对堆的具体实现用到左儿子、右兄弟表示方法。
- 每个节点包含一个额外的指针，作为最左儿子的节点含有一个指向其 父亲的指针；否则这个节点就是一个右兄弟并含有一个指向它的左兄弟的指针。我们将把 这个域叫作Prev域。
- 为执行一次DecreaseKey,我们降低 所需要的节点的值。将调整后的节点从它的父节点切除，通过合并所得到的两个堆而完成 DecreaseKey操作。
- 为了执行DeleteMin,我们将根除去，得到堆的一个集合。如果根 有c个儿子，那么对合并过程进行c-1次调用将该堆重建。
- 合并可以让具有较大根的子堆成为另一个子堆的最左的儿子
- 两趟合并法 ：首先，我们从左到右扫描，合并诸儿子对。在第一次扫描之后，我们有一半数量的树要合并。然后执行第二趟扫描，从右到左。在每一步，我们将第一次扫描剩下的最右边的树和当前合并的结果合并。
