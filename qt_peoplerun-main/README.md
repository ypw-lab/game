## QT小游戏（ikun出品）

**玩法：**跑酷类小游戏，躲避 “kunkun” 同时吃到尽可能多的金币，跟马里奥一样，吃到金币机器人会获得短暂的攻击能力。可发射导弹用来击毁 “kunkun” 和他最爱的“篮球”。

**不要触碰到“kunkun”和他的篮球，不然“哎哟~~”**

**目录结构：** 

* widget.h/.cpp : 实现游戏登录界面
* game_wgt.h/.cpp: 实现游戏主界面，其实就是不停接收鼠标事件，然后设置计时器不停重绘当前画面。有关人物的走动其实就是两个图不停重绘的过程。
* barrier.h/.cpp ： 就是各类障碍以及金币都在这个里面实现
* role.h/.cpp : 就是对人物各种状态的实现

**游戏界面：**

![2023-09-11 12_59_16](D:\MY_software\截屏\save\2023-09-11 12_59_16.png)



 ![2023-09-11 12_59_33](D:\MY_software\截屏\save\2023-09-11 12_59_33.png)



![2023-09-11 13_00_19](D:\MY_software\截屏\save\2023-09-11 13_00_19.png)