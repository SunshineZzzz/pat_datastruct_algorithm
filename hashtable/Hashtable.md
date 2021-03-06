# 什么是hashtable

散列表（Hash table，也叫哈希表），是根据键（Key）而直接访问在内存储存位置的数据结构。也就是说，它通过计算一个关于键值的函数，将所需查询的数据映射到表中一个位置来访问记录，这加快了查找速度。这个映射函数称做散列函数，存放记录的数组称做散列表。

`HashFunction(Key) = index，arr[index] = Key`

# 散列函数

1. 直接定址法：取关键字或关键字的某个线性函数值为散列地址。即hash(k)= k 或 hash(k)=a x k + b，其中a，b为常数（这种散列函数叫做自身函数）

2. 除留余数法：取关键字被某个不大于散列表表长m的数p除后所得的余数为散列地址。即hash(k)=b mod p，p <= m。对p的选择很重要，一般取素数或m，若p选择不好，容易产生冲突。

# 负载系数/载荷因子

散列表的载荷因子定义为： load factor = 填入表中的元素个数 / 散列表的长度

load factor 是散列表装满程度的标志因子。由于表长是定值，load factor 与“填入表中的元素个数”成正比，所以，load factor 越大，表明填入表中的元素越多，产生冲突的可能性就越大；反之，load factor  越小，标明填入表中的元素越少，产生冲突的可能性就越小。实际上，散列表的平均查找长度是载荷因子的函数，只是不同处理冲突的方法有不同的函数。

对于开放定址法(线性探测或者二次探测)，荷载因子是特别重要因素，应严格限制在0.7-0.8以下。超过0.8，查表时的CPU缓存不命中（cache missing）按照指数曲线上升。因此，一些采用开放定址法的hash库，如Java的系统库限制了荷载因子为0.75，超过此值将resize散列表。

# 处理冲突

## 线性探测(linear probing)

## 二次探测(quadratic probing)

## 开链(separate chaining)