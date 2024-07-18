package com.client;

import java.net.URISyntaxException;

public class Main {
    public static void main(String[] args) throws URISyntaxException {
        String wsUrl = "ws://<服务器地址>?token=<jvQuant token>";
        Client fd = new Client(wsUrl);
        fd.connect();
    }
}
