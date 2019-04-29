### Tiny & Effective Server: Xserver ###

#### Which is Xserver?

Xserver 是一个完全使用C语言编写的多线程并发性服务器程序,采用的设计思路：
Xserver启动一个TCP监听，然后生成子线程等待主线程派发任务，主线程一直等待客户端链接，如果客户端链接成功，那么派发这个连接的客户端给对应的子线程
子线程里面使用epoll完成多路复用，子线程读取客户端的请求URL信息后，加载对应的extension目录的.so文件，然后调用其方法获取返回的文本信息返回给客户端

概括而言：

```
client -> Xserver -> parse request url -> loading .so -> calling function -> response the data to client
```

压力测试
```
ab -n100000 -c100 -r -k http://localhost:8181/
```

```
josin@josin-PC:~$ ab -n100000 -c100 -r -k http://localhost:8181/
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

Concurrency Level:      100
Time taken for tests:   3.895 seconds
Complete requests:      100000
Failed requests:        0
Keep-Alive requests:    0
Total transferred:      12800000 bytes
HTML transferred:       2600000 bytes
Requests per second:    25673.26 [#/sec] (mean)
Time per request:       3.895 [ms] (mean)
Time per request:       0.039 [ms] (mean, across all concurrent requests)
Transfer rate:          3209.16 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0    1   0.5      1       5
Processing:     0    3   2.0      2      30
Waiting:        0    2   1.9      2      29
Total:          0    4   1.9      4      31

Percentage of the requests served within a certain time (ms)
  50%      4
  66%      4
  75%      4
  80%      4
  90%      5
  95%      6
  98%      8
  99%     10
 100%     31 (longest request)
```




