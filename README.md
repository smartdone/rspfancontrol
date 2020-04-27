## 树莓派风扇控制

### 依赖库

https://github.com/WiringPi/WiringPi

### 编译

1. 克隆[WiringPi](https://github.com/WiringPi/WiringPi)然后编译
2. 安装cmake等工具
```
sudo apt install gcc g++ cmake ninja-build
```
3. 克隆本工程编译

```shell
git clone --recursive https://github.com/smartdone/rspfancontrol.git
mkdir build
cd build
cmake -GNinja ../
ninja
ninja install
```

### 按电路修改配置文件，并且启用风扇控制服务

电路搭建参考[树莓派3B PNP三极管 智能温控风扇](https://yuerblog.cc/2018/10/31/raspberry3b-pi-pnp-smart-cooling-fan/)


