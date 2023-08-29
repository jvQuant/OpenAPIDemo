#!python3
# -*- coding:utf-8 -*-
import time
import websocket
import zlib


# 发送订阅
def on_open(ws):
    ws.send("all=lv2_600519,lv1_000001")


# 接收推送
def on_message(ws, message, type, flag):
    # 命令返回文本消息
    if type == websocket.ABNF.OPCODE_TEXT:
        print(time.strftime('%H:%M:%S', time.localtime(time.time())), "Text响应:", message)
        print(time.strftime('%H:%M:%S', time.localtime(time.time())), "Text响应:", message)
    # 行情推送压缩二进制消息，在此解压缩
    if type == websocket.ABNF.OPCODE_BINARY:
        rb = zlib.decompress(message, -zlib.MAX_WBITS)
        print(time.strftime('%H:%M:%S', time.localtime(time.time())), "Binary响应:", rb.decode("utf-8"))


def on_error(ws, error):
    print(error)


def on_close(ws, code, msg):
    print(time.strftime('%H:%M:%S', time.localtime(time.time())), "连接已断开")


wsUrl = "ws://<服务器地址>?token=<jvQuant token>"
ws = websocket.WebSocketApp(wsUrl,
                            on_open=on_open,
                            on_data=on_message,
                            on_error=on_error,
                            on_close=on_close)
ws.run_forever()