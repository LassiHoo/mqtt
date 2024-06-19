# Mqtt assingment for Kempower
It is recommended to use the latest Ubuntu version

## installing the compiler and make
```
sudo apt-get update
```
```
sudo apt-get install build-essential
```
```
sudo apt install cmake
```

## installing required libraries


```
sudo apt-get install build-essential gcc make cmake cmake-gui cmake-curses-gui
```

```
sudo apt-get install libssl-dev
```

```
sudo apt-get install doxygen graphviz
```

```
git clone https://github.com/eclipse/paho.mqtt.c.git
```
```
cd paho.mqtt.c
```
```
git checkout v1.3.13
```
```
cmake -Bbuild -H. -DPAHO_ENABLE_TESTING=OFF -DPAHO_BUILD_STATIC=ON \
    -DPAHO_WITH_SSL=ON -DPAHO_HIGH_PERFORMANCE=ON
```

```
sudo cmake --build build/ --target install
``` 

```
sudo ldconfig
```




install paho alto mqtt cpp library:
```
git clone https://github.com/eclipse/paho.mqtt.cpp
```
```
cd paho.mqtt.cpp

```
git submodule update --init --recursive

```

```
cmake -Bbuild -H. -DPAHO_BUILD_STATIC=ON -DPAHO_BUILD_DOCUMENTATION=ON -DPAHO_BUILD_SAMPLES=ON

```

```
sudo cmake --build build/ --target install

```


## compiling the mqtt application

```
mkdir -p build && cd build && cmake .. && make


## setting up the mqtt broket

sudo apt update 

sudo apt install -y mosquitto

sudo apt install -y mosquitto-clients
```

