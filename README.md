# silk

![build](https://github.com/hubenchang0515/silk/actions/workflows/cmake.yml/badge.svg)
[![codecov](https://codecov.io/gh/hubenchang0515/silk/branch/master/graph/badge.svg?token=15D23UVNZR)](https://codecov.io/gh/hubenchang0515/silk)

C programing language base library - C 语言基础库

## Usage - 使用
* header file: `silk/silk.h`
* link option: `-lsilk`

## Build & Install - 构建与安装

```
mkdir build
cd build
cmake ..
cmake --build .
sudo cmake --build . --target install
```

### Build Unit Test - 构建单元测试

```
mkdir build
cd build
cmake .. -DUNIT_TEST
cmake --build .
```

generate code test coverage report - 生成代码测试覆盖率报告:   
> Depends on `gcov`, `lcov` and `genhtml`   
```
cmake --build . --target coverage
```

check memory error - 检测内存错误:   
> Depends on `valgrind`   
```
cmake --build . --target memcheck
```

> if you build unit test by MSVC, will only generate the executable file `silk_unit_test` without coverage info. run it directly to judge if it pass.   
> ___
> 如果你通过 MSVC 构建单元测试，将会只生成一个不含覆盖率信息的可执行文件 `silk_unit_test`。直接运行它来判断是否通过。

## Description

Supported features:  

* [x] vector
* [x] list
* [ ] string
* [ ] map