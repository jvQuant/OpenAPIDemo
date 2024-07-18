#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <string>
#include <iostream>
#include <memory>
#include <assert.h>
#include <cstring>
#include "zlib.h"
#define CHUNK 16384
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;
typedef websocketpp::client <websocketpp::config::asio_client> client;
typedef websocketpp::config::asio_client::message_type::ptr message_ptr;
int DecompressString(const char *in_str, size_t in_len, std::string &out_str);

/**
 * 接收处理
 */
void on_message(client *c, websocketpp::connection_hdl hdl, message_ptr msg) {
    //文本消息
    if (msg->get_opcode()==websocketpp::frame::opcode::text){
        std::cout <<"Text响应:"<<msg->get_payload().c_str()<< std::endl;
    }
    //二进制消息
    if (msg->get_opcode()==websocketpp::frame::opcode::binary){
        std::string tmp = "";
        std::string &out_decompress = tmp;
        DecompressString( msg->get_payload().c_str(), msg->get_payload().size(), out_decompress);
        std::cout <<"Binary响应:"<<out_decompress<< std::endl;
    }
}

/**
 * 连接处理
 */
void on_open(client *c, websocketpp::connection_hdl hdl) {
    //发送订阅指令
    c->send(hdl, "add=lv1_600519,lv2_600519", websocketpp::frame::opcode::text);
    std::cout << "连接成功" << std::endl;
}

int main(int argc, char *argv[]) {
    //服务地址
    std::string wsUrl = "ws://<服务器地址>?token=<jvQuant token>";

    client c;
    //连接相关
    try {
        //debug日志开关
//        c.set_access_channels(websocketpp::log::alevel::all);
        c.clear_access_channels(websocketpp::log::alevel::all);
        c.init_asio();

        // 注册处理函数
        c.set_message_handler(bind(&on_message, &c, ::_1, ::_2));
        c.set_open_handler(bind(&on_open, &c, _1));

        websocketpp::lib::error_code ec;
        client::connection_ptr con = c.get_connection(wsUrl, ec);
        if (ec) {
            std::cout << "连接失败: " << ec.message() << std::endl;
            return 0;
        }
        c.connect(con);
        c.run();
    } catch (websocketpp::exception const &e) {
        std::cout << e.what() << std::endl;
    }
}
/**
 *解压缩方法
 */
int DecompressString(const char *in_str, size_t in_len, std::string &out_str) {
    if (!in_str)
        return Z_DATA_ERROR;
    int ret;
    unsigned have;
    z_stream strm;
    unsigned char out[CHUNK];
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;
    ret = inflateInit2(&strm, -MAX_WBITS);
    if (ret != Z_OK)
        return ret;
    std::shared_ptr <z_stream> sp_strm(&strm, [](z_stream *strm) {
        (void) inflateEnd(strm);
    });
    const char *end = in_str + in_len;
    size_t pos_index = 0;
    size_t distance = 0;
    int flush = 0;
    do {
        distance = end - in_str;
        strm.avail_in = (distance >= CHUNK) ? CHUNK : distance;
        strm.next_in = (Bytef *) in_str;
        in_str += strm.avail_in;
        flush = (in_str == end) ? Z_FINISH : Z_NO_FLUSH;
        do {
            strm.avail_out = CHUNK;
            strm.next_out = out;
            ret = inflate(&strm, Z_NO_FLUSH);
            if (ret == Z_STREAM_ERROR)
                break;
            switch (ret) {
                case Z_NEED_DICT:
                    ret = Z_DATA_ERROR;
                case Z_DATA_ERROR:
                case Z_MEM_ERROR:
                    return ret;
            }
            have = CHUNK - strm.avail_out;
            out_str.append((const char *) out, have);
        } while (strm.avail_out == 0);
    } while (flush != Z_FINISH);
    return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}

