# **第五章 散列**

## 5.1一般想法

- 理想的散列表数据结构只不过是一个含有关键字的具有固定大小的数组。典型情况下一个关键字就是一个带有相关值（例如工资信息）的字符串。
- 表的大小记作TableSize并将其理解为散列表数据结构的一部分而不仅仅是浮动了全局的某个变量。

## 5.2散列函数

- 关键字若是整数：key mod TableSize（好的办法是保证表的大小是素数）
- 通常关键字是字符串，一种选择是把字符中字符ASCLL码加起来
- 一个好的散列函数：

```c
Index Hash(const char*key,int TableSize)
{
    unsigned int HashVal=0;
    while(*key!='0')
        HashVal=(HashVal<<5)+*key++;//向左移五位相当于*32
    return HashVal%TableSize;
}
```

## 5.3分离链接法

把hash算完后的同一个值的所有元素保留在一个表中，Insert时插入重复元通常要留出一个额外的域，这个域当重复元出现时增加一。

```c
H->TheList=malloc(sizeof(list)*H->TableSize);//散列构造
H->TheList=malloc(sizeof(struct Listnode)*H->TableSize);//重复元的表构造
```

我们定义散列表的装填因子λ为散列表中的元素个数与散列表大小的比值，尽量使 λ=1；

## 5.4开放定址法

hi(x)=(Hash(x)+F(i)) mod TableSize;且 F(0)=0.

装填因子应该低于0.5。

### 5.4.1线性探测法

F是i的线性函数，典型是F(i)=i;如果超过一半的表被填满的话，那么线性探测就不是一个好办法。

### 5.4.2平方探测法

- F(i)=i*i;
- 如果表是一半空的，且表的大小是素数，那么我们总能够插入一个新的元素对平方探测，一旦表被填满超过一半了，当表的大小不是素数时甚至在表被填满一般之前就不能一次找到它单元了。这是因为嘴都有一半的表可以用作解决冲突的备选位置。
- 在找下一个探测单元时，可以用F(i)=F(i-1)+2i-1；来确定。

### 5.4.3双散列

F(i)=i*hash(x);

## 5.5再散列

- 建立另外一个大约大两倍的表（而且使用一个相关的新散列函数），扫描整个原始散列表，计算每个（非删除的）元素的新散列值并插入新表中。
- 如果超过某个装填因子就把散列扩大二倍再重新把数据填入。

## 5.6可扩散列

- 它允许用两次磁盘访问执行一次Find。
- 例：树的根含有四个指针，他们有这些数据的前两位确定。每片树叶中树的前两位都是相同的。用D代表根所使用的位数，有时称其为目录。于是，目录中的项数为2的n次方。所有未被分裂的树叶现在各由两个相邻目录所指。



# 第六章优先队列（堆）

对一些进程比较短的，应该尽快的结束，或者比较重要的应该具有优先权，为解决这样的特殊应用，需要优先队列来解决。

## 6.1模型

优先队列是允许至少两种操作的数据结构：Insert和DeleteMin，Insert等价于之前的入队，DeleteMin是找出返回和删除优先队列中的最小元素。

## 6.2一些简单的实现

- 使用一个链表插入，遍历最小值删除，基于DeleteMin使用次数不多于删除操作次数，因此这个办法更好一些。
- 二叉查找树

## 6.3二叉堆

同二叉查找树一样，堆也有两个性质，即结构性和堆序性。堆的操作必须要到堆的所有性质都被满足时才能终止。

### 6.3.1结构性质

- 堆是一棵完全被填满的二叉树，有可能的例外是在底层，底层上的元素从左到右填入，这样的树称为完全二叉树。

- 因为完全二叉树很有规律，所以它可以用一个数组表示而不需要指针：对于数组中任意位置i，其左儿子在位置2i，右儿子在2i+1，它的父亲则在[i/2]上。唯一问题在于堆大小要事先估计。

- 因此一个堆数据结构将由一个数组，一个代表最大值的整数以及当前的堆大小组成。

### 6.3.2堆序性质

由于我们想要快速的找出最小元，因此最小元应该在根上。任意节点应该小于他的所有后裔。

### 6.3.3基本的堆操作

- 插入

  插入时在下一个空闲位创建一个空穴。若X可以放在空穴中且不破坏堆序性质则插入完成，若破坏则把空穴的父节点上的元素移入该空穴中，空穴朝着根方向上行一步，直至X能被放入空穴中。我们可以把一个很小的值放到位置0处，必须保证这个值小于等于堆中的任何值，称之为*标记*，避    免了每次插入最小值时都要执行一次的测试。

```c
for(int i=++H->Size;H->Elements[i/2]>X;i/=2)
    H->Elements[i]=H->Elements[i/2];//如果父节点大于X则把父节点放到空穴
H->Elements[i]=X;//当父节点小于等于X时把X放入当前空穴中
```

删除最小元

将堆中最后一个元素X置入沿着从根开始包含最小儿子的一条路径上的一个正确位置。不要假设节点总有两个儿子，因为倒数第二层也许只会有一个孩子。

```c
int i;
for(i=1;i*2<=H->Size;i*=2)//从上往下找
{
    child=i*2;
    if(child!=H->Size&&H->Elements[child+1]<H->Elements[child])//第一个判断条件就是在确定此时i不是只有一个孩子
        child++;
    if(LastElement>H->Elements[child])
        H->Elements[i]=H->Elements[child];//孩子往上移
    else
        break;//否则最后一个元素放入此处
}
H->Elements[i]=LastElement;
```

### 6.3.4其他的堆操作

若果重要的是要知道元素都在什么地方，那么除堆外，还必须用到诸如散列表等某些其他的数据结构。（该模型不允许查看堆内部）

- BuildHeap

  一般的算法是将N个关键字以任意顺序放入树中，保持结构特性，再用percolateDown(N/2)从节点N/2下滤。

- percolateDown

  从当前节点开始依次减一，每次比较进行两次：一次是两个孩子比较大小，第二次是父亲和小孩子比较大小。

辨析两种树：理想二叉树和完全二叉树；理想二叉树是除了最后一层以外其他所有层的节点都有两个子节点。完全二叉树是最后一层的节点都连续集中在左边。

###### 定理6.1

包含2的(h+1)次方-1个节点、高为h的理想二叉树的节点高度和为(2的h+1次方-1)-(h+1)

这个和为完全二叉树的节点高度的和的上界。由归纳法可以证明完全树高度和是N-b(N)，其中b(N)是再N的二进制表示法中1的个数。

## 6.4优先队列的应用

### 6.4.1选择问题

找到一个数组中第k大的数字

- 算法6A

  将N个元素读入一个数组，对数组应用BuildHeap，最后执行K次DeleteMin操作。、

- 算法6B

  前K个元素通过调用一次BuildHeap以总时间O(K)被置入堆中，标记这个第k大的元素为Sk，Sk是S中最小的元素，如果新元素更大则替换Sk，最后的Sk为我们想得到的数。

### 6.4.2事件模拟

模拟由处理中的事件组成。这里两个事件是：一位顾客到达，以及一位顾客的离去而腾出一名出纳员。进行这种模拟的一个方法是启动在0滴答（单位时间量）处的一台模拟钟表。我们让钟表一次走一个滴答，同时查看是否有一个事件发生。如果有那么处理这个事件，搜集统计资料。当没有顾客留在输入流中且所有的出纳员都闲着的时候，模拟结束。

## 6.5d-堆

d-堆的所有节点都有d个儿子（因此二叉堆是2-堆）。在实践中4-堆可以胜过2-堆。除了不能执行Find外，堆实现最明显的缺点是：将两个堆合并成为一个堆是困难的操作。

## 6.6左式堆

左式堆有相同的堆序性质，左式堆也是二叉树。左式堆和二叉树唯一的区别是：左式堆不是理想平衡的，而实际上是趋向于非常不平衡的。

### 6.6.1左式堆性质

- 我们把任意节点X的零路径长Npl(X)定义为从X到一个没有两个儿子的节点的最短路径长。因此具有0个或1个节点的Npl为0，Npl(NULL)=-1.

- 左式堆的性质是：对于堆中的每一个节点X，左儿子的零路径长至少与右儿子的零路径长一样大。

- 左式堆趋向于加深左路径，所以右路径应该短。

  ###### 定理6.2

  在右路径上有r个节点的左式树必然至少有2的r次方-1个节点。

### 6.6.2左式堆的操作

- 对左式堆的基本操作是合并。除数据、左指针和右指针所用空间外，每一个单元还要有一个指示零路径长的项。
- 合并时先将具有大的根值的堆H1和具有小的根值的堆H2的右子堆合并，之后让这个合并好的新的堆成为H2的右子堆。
- 因为二叉堆的插入什么都不返回所以与左式堆插入不兼容，需要用宏定义来解决。deleteMin也是。

## 6.7斜堆

- 斜堆是具有堆序的二叉树。但是不存在对树的结构限制。
- 合并操作与左式堆差不多，除了一点，对于左式堆我们查看是否左儿子和右儿子满足左式堆堆序性质并交换那些不满足者；对于斜堆，除了这些右路径上所有结点的最大者不交换他们的儿子，其他交换是无条件的。因为自然递归就会发生这种情况其实也不算特殊情形。
- 斜堆的优点：不需要附加空间来保留路径长以及不需要测试何时交换儿子。

## 6.8二项队列

### 6.8.1二项队列结构

- 二项队列不是一棵堆序的树，而是堆序树的集合，称之为森林。
- 堆序树中的每一棵都是有约束的形式，叫做二项树。
- 每一个高度上至多存在一棵二项树。
- 高度为零的二项树是一棵单节点树；高度为k的二项树Bk通过将一棵二项树Bk-1附接到另一棵二项树Bk-1的根上而构成。
- 高度为k的二项树恰好有2的k个节点。
- 我们能够用二项树的集合唯一的表示任意大小的优先队列。大小为13的优先队列可以用森林B3,B2,B0表示。可以表示写为1101.

### 6.8.2二项队列的操作

- 最小元可以搜索所有树的根来找出。
- 合并就是将两个队列加到一起来完成。高度一样的让根大的成为根小的子树。为使合并更高效，把这些树放到按高度排序的二项队列中。
- DeleteMin：从H中出去带有最小根结点的树，剩下的形成新的队列H1，除去的这棵树再除去它的根节点，剩下的形成新的优先队列H2。合并H1和H2。

### 6.8.3二项队列的实现

二项树的每个节点儿子都存在一个链表中，而且每个节点都有一个指向第一个儿子和右兄弟。二项树中的诸儿子以递减次序排列。子树排列由大到小。











