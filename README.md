# 3DViewer
#### Download packages (if it needs)
```
sudo apt install -y qt6-base-dev qtcreator 
```

## Application
### Make wrapper for CMake
#### 1. Configuration of assembly files
```
make
```
#### 2. Launch the application
```
make rv
```
### CMake assemble


#### 1. Configuration of assembly files
```
cmake -B build -DCMAKE_BUILD_TYPE=Debug
```

#### 2. Project compilation
```
cmake --build build --parallel $(nproc)
```

#### 3. Launch the application
```
cmake --build build --target run_3dviewer
```

#### 4. Tests
```
cmake --build build --target 
```



