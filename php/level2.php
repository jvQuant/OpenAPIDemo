<?php

//需安装swoole扩展
use Swoole\Coroutine\Http\Client;
use function Swoole\Coroutine\run;

run(function () {
    //服务器地址
    $host = '<服务器地址>';
    //服务器端口
    $port = <服务器端口>;

    //连接
    $conn = new Client($host, $port);
    $conn->upgrade("/?token=<jvQuant token>");

    //发送订阅
    $conn->push("add=lv2_600519,lv1_000001");

    //开启接收协程
    go("receive", $conn);
});

function receive($client)
{
    while (true) {
        $data = $client->recv();
        $time = date("H:i:s");
        //解压
        @$zipStr = gzinflate($data->data);
        if ($zipStr) {
            echo "{$time} Binary推送:{$zipStr}\n";
        } else {
            echo "{$time} Text响应:{$data->data}\n";
        }
    }
}