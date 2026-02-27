# Optikos

![demo](https://github.com/IlanVinograd/Optikos/blob/main/res/images/example1.gif?raw=true)

```powershell
rm -r build
```

```powershell
cmake --preset windows-msvc
```

```powershell
cmake --preset windows-msvc && cmake --build build && .\build\Debug\Optikos.exe
```

```powershell
cmake --preset windows-msvc -D ENABLE_GPU_PROFILING=ON && cmake --build build && .\build\Debug\Optikos.exe
```

#perforamnce profiling
2/16/26: 
=== GPU Profiling (after 17820 frames) ===
Max: 2.68288 ms
Min: 0.008192 ms
Avg: 0.049523 ms
Avg FPS: 20192.6