# silk

![build](https://github.com/hubenchang0515/silk/actions/workflows/cmake.yml/badge.svg)
[![codecov](https://codecov.io/gh/hubenchang0515/silk/branch/master/graph/badge.svg?token=15D23UVNZR)](https://codecov.io/gh/hubenchang0515/silk)

C programing language base library - C 语言基础库

## Usage
* header file: `silk/silk.h`
* link option: `-lsilk`

## Build & Install

```
mkdir build
cd build
cmake ..
make
sudo make install
```

Build unit test and generate code coverage report - 构建单元测试并生成覆盖率报告: 
```
mkdir build
cd build
cmake .. -DUNIT_TEST
make
make coverage
```

## Description

Supported features:  

* [x] vector
* [ ] string
* [ ] map