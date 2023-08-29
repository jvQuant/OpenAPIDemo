package main

import (
	"bytes"
	"compress/flate"
	"github.com/gorilla/websocket"
	"log"
	"time"
)

func main() {
	//连接地址
	wsUrl := "ws://<服务器地址>?token=<jvQuant token>"
	conn, _, err := websocket.DefaultDialer.Dial(wsUrl, nil)
	if err != nil {
		log.Fatalln("连接错误：", err)
	}
	//接收协程
	go func() {
		receive(conn)
	}()

	//发送订阅
	cmd := "all=lv2_600519,lv1_000001"
	err = conn.WriteMessage(websocket.TextMessage, []byte(cmd))
	if err != nil {
		log.Fatalln("发送指令错误：", err)
	}
	log.Println("发送指令成功，等待接收")
	for {
		time.Sleep(time.Second)
	}
}

func receive(conn *websocket.Conn) {
	for {
		//阻塞接收
		messageType, rb, err := conn.ReadMessage()
		if err != nil {
			log.Fatalln("接收错误：", err)
			return
		}
		//文本消息
		if messageType == websocket.TextMessage {
			log.Println("Text响应:", string(rb))
		}
		//二进制消息
		if messageType == websocket.BinaryMessage {
			unZipByte := DeCompress(rb)
			log.Println("Binary推送:", string(unZipByte))
		}
	}
}

//解压方法
func DeCompress(b []byte) []byte {
	var buffer bytes.Buffer
	buffer.Write([]byte(b))
	reader := flate.NewReader(&buffer)
	var result bytes.Buffer
	result.ReadFrom(reader)
	reader.Close()
	return result.Bytes()
}
