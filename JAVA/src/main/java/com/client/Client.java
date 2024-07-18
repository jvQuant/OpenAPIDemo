package com.client;
import org.java_websocket.client.WebSocketClient;
import org.java_websocket.handshake.ServerHandshake;
import java.net.URI;
import java.net.URISyntaxException;
import java.nio.ByteBuffer;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.util.zip.Inflater;
import java.util.zip.DataFormatException;

public class Client extends WebSocketClient {

    SimpleDateFormat sdf = new SimpleDateFormat("HH:mm:ss");

    public Client(String url) throws URISyntaxException {
        super(new URI(url));
    }

    @Override
    public void onOpen(ServerHandshake shake) {
        //发送订阅命令
        this.send("add=lv1_600519,lv2_600519");
    }

    /**
     * 命令返回文本消息
     */
    @Override
    public void onMessage(String paramString) {
        System.out.println(sdf.format(new Date()) + " Text响应：" + paramString);
    }

    @Override
    public void onClose(int paramInt, String paramString, boolean paramBoolean) {
        System.out.println("连接关闭");
    }

    @Override
    public void onError(Exception e) {
        System.out.println("连接异常" + e);
    }

    /**
     * 行情接收处理
     */
    @Override
    public void onMessage(ByteBuffer bytes) {
        super.onMessage(bytes);
        String s="";
        try {
            //二进制解压缩
            byte[] dec=decompress(bytes.array());
            s = new String(dec, "UTF-8");
        }catch (IOException e){
            System.err.println("Binary解析IO异常:"+e.getMessage());
            return;
        }
        catch (DataFormatException e){
            System.err.println("Binary解析格式异常:"+e.getMessage());
            return;
        }
        System.out.println(sdf.format(new Date()) + " Binary响应：" + s);
    }

    /**
     * 解压缩方法
     */
    public static byte[] decompress(byte[] compressedData) throws DataFormatException {
        Inflater inflater = new Inflater(true);
        inflater.setInput(compressedData);
        ByteArrayOutputStream outputStream = new ByteArrayOutputStream(compressedData.length);
        byte[] buffer = new byte[1024];
        while (!inflater.finished()) {
            int count = inflater.inflate(buffer);
            outputStream.write(buffer, 0, count);
        }
        inflater.end();
        return outputStream.toByteArray();
    }
}