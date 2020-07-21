# Dockerfile to use [`pagmo`](https://esa.github.io/pagmo2/index.html)

This repository provide Dockerfile to use `pagmo`.

Build docker image.
```bash
$ docker image build -t pagmo:latest .
```

Run container and enter the environment. Here, you share the any files in your local current directory with `/usr/local/src` of the docker environment.
```bash
$ docker container run -v ${PWD}:/usr/local/src -it pagmo:latest
```

In the docker environment, you can compile your dource code (here, maker.cpp) as follows.
```bash
$ g++ -std=c++17 maker.cpp -I /usr/local/include/pagmo/ -L /usr/local/lib/libpagmo.so.5 -l pagmo
```

## Note
The `maker.cpp` is created to use hypervolume functions. This program computes hypervolumes of randomly sampled 1000 points in 3-d dimensions by using `pagmo`.
