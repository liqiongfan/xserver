### Tiny & Effective Server: Xserver ###

#### Xserver是什么？

Xserver是一个完全采用C语言编写的多线程、并发型、模块化的服务器程序，支持Linux系统环境，优先采用epoll多路复用机制，具体的设计体系架构如下图所示：

![](https://raw.githubusercontent.com/liqiongfan/xserver/master/Xserver.png)

Xserver的体系架构简单、性能把控度100%，因为采用C语言开发因此能够将机器的性能压榨到极致，比较适合推送服务、消息IM系统等并发场景比较高的系统使用。

#### 扩展开发手册 ####

扩展开发可以使用C语言或者C++语言开发，生成so文件即可，暂未处理BSD系统的kqueue机制，后续增加后支持dylib扩展，具体的开发方法如下：

Xserver默认情况下自动解析http请求协议，按照标准格式进行解析，解析的结果会通过参数返回给扩展库的回调函数的参数中，扩展方法的原型如下：

```
void (HTTP_FUNC)(list *request_headers, list *query_string_list);
```

遍历 **Xserver** 自带的 **list** 结构可以使用 **Xserver宏** 遍历即可：

其中 **request_headers** 列表中含有几个固定的键值：

| 字段               | 含义         | 取值                        |
| ------------------ | ------------ | --------------------------- |
| **request_method** | 请求方法名称 | GET\|PUT\|POST\|DELETE 等等 |
| **request_uri**    | 请求URL      | 除去host之后的路径取值      |
| **http_version**   | HTTP协议版本 | HTTP/1.1                    |
| **http_body**      | 请求的包主体 | GET请求无包体               |

```
list *_temp = EMPTY_PTR;
LIST_FOREACH_VAL(request_headers, _temp) {
    
    /* list_data结构体包含一个name字段：键名
     * value:键值 */
    list_data *_kv = (list_data *)_temp->node.data_ptr;
    
    printf("%s:%s\t", _kv->name, _kv->value);
    
} LIST_FOREACH_END();
```

不要担心内存泄漏问题，Xserver会自动在调用库方法返回后自动释放内存。

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




