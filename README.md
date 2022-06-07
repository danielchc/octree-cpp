# octree-cpp

## Prerequisites

**GCC**

```
sudo apt install gcc-9 g++-9 cmake
update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-9 100
update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-9 100
```

**LASlib**
```
mkdir lib && cd lib
wget https://lastools.github.io/download/LAStools.zip && unzip LAStools.zip && rm LAStools.zip
(cd LAStools && cmake . && make)
````

## Build
```
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

## Run
```
./build/octree-cpp -i data/PNOA_2015_GAL-W_520-4674_ORT-CLA-COL-vigo.las --bucket-size 64
```

## References

- J. Behley, V. Steinhage, A.B. Cremers. *Efficient Radius Neighbor Search in Three-dimensional Point Clouds*, Proc. of the IEEE International Conference on Robotics and Automation (ICRA), 2015. papper