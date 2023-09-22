# Klepsydra SDK

```bash
sudo apt install build-essential git cmake
git clone https://github.com/klepsydra-technologies/kpsr-sdk.git
cd kpsr-sdk/
git submodule update --init
mkdir build && cd build/
cmake ..
make -j$(nproc)
make test
sudo make install
```
