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

* RuntimeError:can not open CFlow file in the file ../../source/userapi_se/ThostFtdcApiImplBase.cpp
  * The directory this application needed is not satisfied
#### Appendix A:The Instrument ID Rules
* SHANGQI:[a-z]{2}[0-9]{4}
* ZHONGJIN:[A-Z]{2}{0-9}{4}
* ZHENGSHANGSUO:[A-Z]{2}[0-9]{3}
* DASHANGSUO:[a-z]{2}[0-9]{4}
**NB:IN THIS PROJECT YOU ONLY NEED TO CARE ABOUT THE ZHONGJINSUO INSTRUMENT RULES**
