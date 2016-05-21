Python 2/3 Tests
----------------

Tested on Ubuntu 14.04.

Default builds against Python 2:

```bash
mkdir build
cmake -G Ninja ../
ninja
python -c 'import helloworld23 as hello;print(hello.hello())'
```

Outputs:

```bash
Hello Python 2!
```

To build with Python 3:

```bash
mkdir build
cmake -G Ninja -DPYTHON_EXECUTABLE=/usr/bin/python3 ../
ninja
python -c 'import helloworld23 as hello;print(hello.hello())'
```

Outputs:

```bash
Hello Python 3!
```
