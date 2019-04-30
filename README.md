### Tiny & Effective Server: Xserver ###

#### Which is Xserver?

Xserver 是一个完全使用C语言编写的多线程并发性服务器程序,采用的设计思路：
Xserver启动一个TCP监听，然后生成子线程等待主线程派发任务，主线程一直等待客户端链接，如果客户端链接成功，那么派发这个连接的客户端给对应的子线程
子线程里面使用epoll完成多路复用，子线程读取客户端的请求URL信息后，加载对应的extension目录的.so文件，然后调用其方法获取返回的文本信息返回给客户端

目标机器配置：

```
josin@josin-PC:~/xserver$ grep MemTotal /proc/meminfo
MemTotal:       16324232 kB
josin@josin-PC:~/xserver$ cat /proc/cpuinfo | grep name | cut -f2 -d: | uniq -c
      4  Intel(R) Core(TM) i5-4460  CPU @ 3.20GHz
```

概括而言：

```
client -> Xserver -> parse request url -> loading .so -> calling function -> response the data to client
```

压力测试
```
ab -n100000 -c1000 -r -k http://localhost:8181/
```

```
josin@josin-PC:~$ ab -n100000 -c1000 -r -k http://localhost:8181/
This is ApacheBench, Version 2.3 <$Revision: 1826891 $>
Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
Licensed to The Apache Software Foundation, http://www.apache.org/

Benchmarking localhost (be patient)
Completed 10000 requests
Completed 20000 requests
Completed 30000 requests
Completed 40000 requests
Completed 50000 requests
Completed 60000 requests
Completed 70000 requests
Completed 80000 requests
Completed 90000 requests
Completed 100000 requests
Finished 100000 requests


Server Software:
Server Hostname:        localhost
Server Port:            8181

Document Path:          /
Document Length:        26 bytes

Concurrency Level:      1000
Time taken for tests:   4.206 seconds
Complete requests:      100000
Failed requests:        0
Keep-Alive requests:    0
Total transferred:      12800000 bytes
HTML transferred:       2600000 bytes
Requests per second:    23777.23 [#/sec] (mean)
Time per request:       42.057 [ms] (mean)
Time per request:       0.042 [ms] (mean, across all concurrent requests)
Transfer rate:          2972.15 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0   20  92.4     11    1040
Processing:     5   22   8.4     20      68
Waiting:        0   17   7.8     16      67
Total:          7   42  93.3     33    1084

Percentage of the requests served within a certain time (ms)
  50%     33
  66%     39
  75%     42
  80%     44
  90%     47
  95%     50
  98%     55
  99%     73
 100%   1084 (longest request)
```




