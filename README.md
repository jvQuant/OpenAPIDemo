## websocket行情接入


[行情测试](http://jvquant.com/websocket.html) http://jvquant.com/websocket.html

[交易在线测试](http://jvquant.com/trade.html) http://jvquant.com/trade.html

[官方文档地址](http://jvquant.com/wiki.html) http://jvquant.com/wiki.html

## 分配服务器


`注意：`每次分配的服务器地址会发生变化，连接服务前，请务必调用该接口获取最新的服务器地址。

获取服务器:

接口参数:

| # | 参数名 | 类型 | 描述 |
| --- | --- | --- | --- |
| 1 | market | string | 市场标志,沪深为ab |
| 2 | type | string | 接口类别,行情类别为websocket |
| 3 | token | string | jvQuant token |

接口返回:

| # | 参数名 | 类型 | 描述 |
| --- | --- | --- | --- |
| 1 | code | string | 请求状态码 |
| 2 | server | string | 分配服务器地址及端口号 |

返回示例:

## code规范

jvQuant支持沪深主板、科创板、创业板，股票以及可转债行情，提供level1和level2数据推送。

订阅代码由`行情标志`和`证券代码`组成，用分隔符"`_`"连接。

如:

lv1\_600519，代表贵州茅台level1行情

lv2\_127063，代表贵轮转债level2行情

| # | 行情标志 | 类型 | 描述 |
| --- | --- | --- | --- |
| 1 | lv1 | string | level1行情 |
| 2 | lv2 | string | level2行情 |

## 连接登录

使用分配的服务器地址，通过websokcet协议连接服务器。

websocket接口地址:

## 订阅行情

创建websocket连接后，您可以输入以下指令进行行情订阅:

| # | 指令 | 参数 | 描述 |
| -- | --- | --- | --- |
| 1 | add | string | 增加订阅code |
| 2 | del | string | 删除订阅code |
| 3 | all | string | 覆盖全部code |
| 4 | list | string | 查看全部订阅code |
| 5 | his | string | (history)查看今日已订阅的code汇总信息 |

指令后接code参数,用分隔符"`=`"连接，多个code用分隔符"`,`"分隔。

例:

`add=lv1_600519,lv2_127063` ，表示增加订阅lv1\_600519,lv2\_127063行情。

`del=lv1_600519,lv2_127063` ，表示删除订阅lv1\_600519,lv2\_127063行情。

`all=lv1_600519` ，表示覆盖全部订阅code。

`all=` ，后接参数为空，表示删除全部订阅code。

`list` ，无需参数，表示查看全部订阅code。

## 解析行情

为提高数据传输速率，行情推送采用二进制方式传输，请在接收端解压缩为字符串。

### level1

level1行情推送数据以换行符"`\n`"为分隔，每一行以lv1\_xxxxxx=为开头，代表该类别code对应的行情。

lv1每笔交易数据字段以"`,`"为分隔符，定义如下:

推送时间`,`证券名称`,`最新价格`,`涨幅`,`成交量`,`成交额`,`买五档\[挂单数量,挂单价格\]`,`卖五档\[挂单数量,挂单价格\]

leve1推送数据包格式如下:

``lv1_证券代码1=推送时间`,`证券名称`,`最新价格`,`涨幅`,`成交量`,`成交额`,`买五档[挂单数量,挂单价格]`,`卖五档[挂单数量,挂单价格]...`` ``lv1_证券代码2=推送时间`,`证券名称`,`最新价格`,`涨幅`,`成交量`,`成交额`,`买五档[挂单数量,挂单价格]`,`卖五档[挂单数量,挂单价格]...``

### level2

level2行情推送数据以换行符"`\n`"为分隔，每一行以lv2\_xxxxxx=为开头，代表该类别code对应的行情。

同一时刻会存在多笔交易，以"`|`"为分隔符。

lv2每笔交易数据字段以"`,`"为分隔符，定义如下:

成交时间(毫秒)`,`成交编号`,`成交价格`,`成交数量/(股)

推送数据包格式如下:

`lv2_证券代码1=成交时间1,成交编号1,成交价格1,成交数量1|成交编号2,成交时间2,成交价格2,成交数量2...` `lv2_证券代码2=成交时间1,成交编号1,成交价格1,成交数量1|成交编号2,成交时间2,成交价格2,成交数量2...`

[行情测试](http://jvquant.com/websocket.html)

## 交易接入

jvQuant OpenAPI直达券商，提供多种登录及交易方式。

您只需输入对应券商的资金账号密码，即可调用jvQuant OpenAPI进行交易。

\*个人账户仅支持东方财富登录，机构账户无限制。

## 分配服务器

为实现更好的用户体验，jvQuant会根据您所在的地区分配合适的服务器。

`注意：`每次分配的服务器地址会发生变化，连接服务前，请务必调用该接口获取最新的服务器地址。

分配服务器地址:

接口参数:

| # | 参数名 | 类型 | 描述 |
| --- | --- | --- | --- |
| 1 | market | string | 市场标志,沪深为ab |
| 2 | type | string | 接口类别,交易类别为trade |
| 3 | token | string | jvQuant token |

接口返回:

| # | 参数名 | 类型 | 描述 |
| --- | --- | --- | --- |
| 1 | code | string | 请求状态码 |
| 2 | server | string | 分配服务器地址及端口号 |

返回示例:

## 登录柜台

输入交易账户及密码，通过柜台验证后返回授权交易凭证ticket。

请妥善保管好交易凭证，在ticket有效期内，您可以免登录进行后续的交易操作。

接口地址:

接口参数:

| # | 参数名 | 类型 | 描述 |
| --- | --- | --- | --- |
| 1 | token | string | jvQuant token |
| 2 | acc | string | 12位资金账号 |
| 3 | pass | string | 资金交易密码 |

接口返回:

| # | 参数名 | 类型 | 描述 |
| --- | --- | --- | --- |
| 1 | code | string | 请求状态码 |
| 2 | ticket | string | 登录凭证 |
| 2 | expire | int | ticket有效时间(秒) |

返回示例:

## 查询持仓信息

接口地址:

接口参数:

| # | 参数名 | 类型 | 描述 |
| --- | --- | --- | --- |
| 1 | token | string | jvQuant token |
| 2 | ticket | string | 交易凭证ticket |

接口返回:

| # | 参数名 | 类型 | 描述 |
| --- | --- | --- | --- |
| 1 | message | string | 错误信息 |
| 2 | total | string | 账户总资产 |
| 2 | usable | string | 账户可用资金 |
| 3 | day\_earn | string | 账户当日盈亏 |
| 4 | hold\_earn | string | 账户持仓盈亏 |
| 5 | hold\_list | array | 账户持仓明细 |
| 5.1 | hold\_list\[x\].code | string | 账户持仓证券列表 |
| 5.2 | hold\_list\[x\].name | string | 持仓证券名 |
| 5.3 | hold\_list\[x\].hold\_vol | string | 持仓数量 |
| 5.4 | hold\_list\[x\].hold\_vol | string | 持仓数量 |
| 5.5 | hold\_list\[x\].usable\_vol | string | 可用数量 |
| 5.6 | hold\_list\[x\].usable\_vol | string | 可用数量 |
| 5.7 | hold\_list\[x\].day\_earn | string | 当日盈亏 |
| 5.8 | hold\_list\[x\].hold\_earn | string | 持仓盈亏 |

返回示例:

## 查询交易信息

接口地址:

接口参数:

| # | 参数名 | 类型 | 描述 |
| --- | --- | --- | --- |
| 1 | token | string | jvQuant token |
| 2 | ticket | string | 交易凭证ticket |

接口返回:

| # | 参数名                     | 类型     | 描述 |
| --- |-------------------------|--------| --- |
| 1 | message                 | string | 错误信息 |
| 2 | list                    | array  | 交易明细列表 |
| 2.1 | list\[x\].order\_id     | string | 委托编号 |
| 2.2 | list\[x\].day           | string | 委托日期 |
| 2.3 | list\[x\].time          | string | 委托时间 |
| 2.4 | list\[x\].code          | string | 委托证券代码 |
| 2.5 | list\[x\].name          | string | 委托证券名 |
| 2.6 | list\[x\].type          | string | 委托类型 |
| 2.7 | list\[x\].status        | string | 委托状态 |
| 2.8 | list\[x\].order\_price  | string | 委托价格 |
| 2.9 | list\[x\].order\_volume | string | 委托数量 |
| 2.10 | list\[x\].deal\_price   | string | 成交价格 |
| 2.11 | list\[x\].deal\_volume  | string | 成交数量 |

返回示例:

## 委托报单

接口地址:

接口参数:

| # | 参数名 | 类型 | 描述 |
| --- | --- | --- | --- |
| 1 | trade | string | 买入(buy)或卖出(sale) |
| 2 | token | string | jvQuant token |
| 3 | ticket | string | 交易凭证ticket |
| 4 | code | string | 证券代码 |
| 5 | name | string | 证券名称 |
| 6 | price | float | 委托价格 |
| 7 | volume | int | 委托数量 |

接口返回:

| # | 参数名 | 类型 | 描述 |
| --- | --- | --- | --- |
| 1 | message | string | 错误信息 |
| 2 | order\_id | string | 委托编号 |

返回示例:

## 撤销报单

接口地址:

接口参数:

| # | 参数名 | 类型 | 描述 |
| --- | --- | --- | --- |
| 1 | token | string | jvQuant token |
| 2 | ticket | string | 交易凭证ticket |
| 3 | order\_id | string | 委托编号 |

接口返回:

| # | 参数名 | 类型 | 描述 |
| --- | --- | --- | --- |
| 1 | code | string | 返回状态码 |
| 2 | message | string | 错误信息 |

返回示例:

[交易测试](http://jvquant.com/trade.html)

[官方文档地址](http://jvquant.com/wiki.html) http://jvquant.com/wiki.html
