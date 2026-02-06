# Optikos

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