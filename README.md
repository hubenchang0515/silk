# silk
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