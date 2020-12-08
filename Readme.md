# High Frequency Trading System

#### 1.General Discription

* This is a futures auto-trading  project according to the strategy users configured.
*  It could collect the data from CTP and store it into the remote MySQL database.

#### 2. Requirements

* OS Platform:Linux-x86-64
* Dynamic Lib:Please make sure the MySQL development lib is installed on the target device.
* Dynamic Lib:Please make sure the Curl Lib is installed on the target device.The download url is here https://curl.se/download/curl-7.73.0.tar.gz

#### 3.Run

* command:print the following command in the project directory to make this project run on your device.If an error occurred,please check the instructions and requirements above.

  ```shell
  make
  make run;
  ```

#### 4.Tips && QA

* The whole project could run but no messages received.

  * Please make sure your device is connected to the Internet.

  * Please make sure your contract serial number is valid.

  * Please make sure it is trading period.For more details about the trading period,please look up the following table. 

  

![image-20201130193607111](/home/march1917/.config/Typora/typora-user-images/image-20201130193607111.png)

```shell
第一套：

    标准CTP：

        第一组：Trade Front：180.168.146.187:10100，Market Front：180.168.146.187:10110；【电信】（看穿式前置，使用监控中心生产秘钥）

        第二组：Trade Front：180.168.146.187:10101，Market Front：180.168.146.187:10111；【电信】（看穿式前置，使用监控中心生产秘钥）

        第三组：Trade Front：218.202.237.33 :10102，Market Front：218.202.237.33 :10112；【移动】（看穿式前置，使用监控中心生产秘钥）

        用户注册后，默认的APPID为simnow_client_test，认证码为0000000000000000（16个0），默认不开终端认证，程序化用户可以选择不开终端认证接入。

        交易阶段(服务时间)：与实际生产环境保持一致。

     CTP FIX 网关（看穿式）：

        第一组：Trade Front: 180.168.146.187:10104，Market Front：180.168.146.187:10114；【电信】

        CTP FIX网关相关资料请到常用下载->综合交易平台api下载页面查看。

        交易阶段(服务时间)：与实际生产环境保持一致。

第二套（支持上期所期权）：

        第一组：Trade Front：180.168.146.187:10202，Market Front：180.168.146.187:10212；【电信】（看穿式前置，使用监控中心生产秘钥）

        第二组：Trade Front：218.202.237.33:10203，Market Front：218.202.237.33:10213；【移动】（看穿式前置，使用监控中心生产秘钥）

        新注册用户，需要等到第二个交易日才能使用第二套环境。

        密码修改需要等到第二个交易日才能更新到第二套环境。

        交易品种：五所所有期货品种以及上期所所有期权品种

        账户资金：初始资金两千万。不支持出入金，请用户利用好各自资金。

        交易阶段(服务时间)：与实际生产环境保持一致。

        结算：与第一套一样，各自独立结算。

        声明：第二套系统目前处于试运行状态，待系统稳定运行一段时间后，会提前通知，与第一套合并成一套系统。

        客户端软件下载：点击下载客户端。

第三套：

    交易前置：180.168.146.187:10130，行情前置：180.168.146.187:10131；【7x24】（看穿式前置，使用监控中心生产秘钥）

    第三套环境仅服务于CTP API开发爱好者，仅为用户提供CTP API测试需求，不提供结算等其它服务。

    新注册用户，需要等到第三个交易日才能使用第二套环境。

    账户、钱、仓跟第一套环境上一个交易日保持一致。

    交易阶段(服务时间)：交易日，16：00～次日09：00；非交易日，16：00～次日15：00。

    用户通过SimNow的账户（上一个交易日之前注册的账户都有效）接入环境，建议通过商业终端进行模拟交易的用户使用第一套环境。
```

