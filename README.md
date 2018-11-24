## macOS High Sierra / Mojave

### How to build required dependencies

### gl3w
```commandline
git clone http://github.com/skaslev/gl3w
cd gl3w
python gl3w_gen.py
```
### glfw
```commandline
git clone https://github.com/glfw/glfw.git
cd glfw
cmake -DBUILD_SHARED_LIBS=ON .
make
sudo make install
```
### OR
```commandline
brew install glfw
```