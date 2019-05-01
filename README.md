### Tiny & Effective Server: Xserver ###

#### Xserver是什么？

Xserver是一个完全采用C语言编写的多线程、并发型、模块化的服务器程序，支持Linux系统环境，优先采用epoll多路复用机制，具体的设计体系架构如下图所示：

![](/Users/josin/xserver/Xserver.png)

Xserver的体系架构简单、性能把控度100%，因为采用C语言开发因此能够将机器的性能压榨到极致，比较适合推送服务、消息IM系统等并发场景比较高的系统使用。



压力测试的目标机器配置：

```
16GB内存，4核i5-4460 3.2GHz的Intel CPU
```

压力测试命令与测试结果：
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




