# Python Binding for MI
你可以使用python脚本来计算MI了。代码来自[REFERENCE](#ref)


### 示例
test.py

```
from MI import MI

mi = MI(3, "TVTri.lm", "HomoDictPoly+Tone.txt", False)
prob1 = mi.probSum("| zhong1 guo2 ren2 min2 sheng1 huo2 |")
prob2 = mi.probSum("| | zhong1 guo2 ren2 min2 | sheng1 huo2 |")
print(f"Prob1: {prob1} Prob2: {prob2}")
```
对应的输出为
```
Loading TVTri.lm...
LM::initUnigramWithBOW done!
LM::initBigramWithBOW done!
LM::initTrigram done!
LM::LM ORDER: 3.

MI::initDict done!
MI::MI BOUNDNESS: unbounded.

Prob1: 3.2250619558440197e-07 Prob2: 3.225047104312583e-07
```
### 安装

1. 编译pybind11
```
cd pybind11
cmake . & make -j 10
cd ..
```
2. 安装MI模块
 
建议使用conda。在当前目录执行以下命令
```
pip install .
```
## 说明
这是个简单python wrapper。我们实例化一个MI
```
mi = MI(3, "TVTri.lm", "HomoDictPoly+Tone.txt", False)
```
其中
```
MI(order, LM_file, Pinyin2word, bounded)
```
mi.probSum用于计算概率。

## <span id="ref"> REFERENCE </span>
如果你也进行相关工作，请引用论文：

```
TODO
```
