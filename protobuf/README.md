A basic hello-world for protocol buffers. Demonstrates ease of exchange of structured data from
C++ to Python.

- `serdes.cpp` has some data in cpp's std::unordered_map
- `format.proto` defines structure of this data
- `serdes.cpp` dumps this data into binary form in `serdes_dump` file
- `serdes.py` is able to read the dumped file and get the same data in python object

Used the following protoc command to auto generate cpp header file and python package:

```
protoc format.proto --cpp_out=/path/to/your/project
protoc format.proto --python_out=/path/to/your/project
```

Command to compile `serdes.cpp`:
```
g++ serdes.cpp format.pb.cc -g -o serdes -lprotobuf
```

In case you don't have proto compiler installed, you can get it using:
```
sudo apt install protobuf-compiler libprotobuf-dev
```


