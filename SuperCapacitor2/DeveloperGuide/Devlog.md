2019.9.25
ltc1473到货，超级电容板焊接完成。f103可正常烧录程序，跑马灯实验。

测试3508电机低压运行状态：
   9伏电压启动，可正常运转，转速低；限流3A，降压至6.8伏电机停止工作，重新升高电压至十三伏恢复工作状态。
   今天测试电机的代码有pid控制，学生电源24v供电，电流只能到2.5安，转速明显低于直接用电池驱动，尚未确认原因，推测为代码限制了某项性质。

讲解了超级电容板的基本实现原理，说明代码需要的部分。

明日计划：
    写超级电容板程序，测试开关导通性能，测试超级电容充放电电压情况。

存疑：
    低压为电机供电的优势不明确，如果可以测试同功率下低压与高压供电对电机性能无太大影响，那么可以简化超级电容的充放电电路，但是大电流对超级电容板也有高要求。 即需要寻找一个不限流的低压源，或者做/买个降压模块测试。
    


2019.9.26
    超级电容板程序完成控制逻辑部分，已测试读取电压部分，串口。测试过程中由于魏锦启在硬件上的设计缺陷，将RNS电阻短接，导致降压模块无法正常工作，无法继续测试电流读取功能。
    确认9v仅为电容最大程度输出时电机正常工作的最低电压。
    分析了超级电容板的闭环控制逻辑，代码编写完成，尚未调节其中相关参数。
    
明日计划：
    按照今日寻找的方案更改电路板，完成读取电流功能，测试电容板上的开关性能，测试充电情况。


2019.9.27
    今日进度约等于零。超级电容组焊到一起。电容板五伏输出无效，原因未知。电容板导线炸出，断路，推测原因为电流过大，检测发现mos管短路，推测可能为mos击穿，导致电源短路。
    同时第一块板子修改过多，系统错误叠加具有巨大的不可预知性。

2019.9.28
    重新焊接新的电容板，消除了原有的跳线，可正常运行f103芯片。
    购买了大功率电阻器，等待到货。补充购买了若干dcdc芯片。
    明日计划：继续测试降压模块的降压能力，恢复9.26的测试。
              试探究第一块板子烧坏的原因。
    后天计划：更改修复原理图。
    
2019.10.1---10.5
    电流计，电压测试可以正常检测。电流计参数：55mV/A。MOS可以正常导通。
    重新焊接了剩余5块pcb板。但都出现bug，集中在一下几点：
1.ltc1473，实际测试了两块芯片，不受输入电平控制。
2.IRS2130，实际测试了3块芯片，不受pwm控制，受恒定电平控制。
3.f103芯片某端口（PA3）无法输出高电平，只有一块芯片有此现象。
4.3.3v与GND因未知原因短路，2块板子出现此情况。一块推测是f103烧毁，一块原因未知。

    测试了一种方案： 电池--电容--负载  单路连接，通过模块限制电池的输出电流，以限制电池的输出功率。  
    
    测试电路：电源，电容，负载三部分并联，通过24v 5A模块限制电流。
    测试结果：24v电源，5A限流 给超级电容充满电需30s。超级电容充满电24v。电池断电后，单3508电机空载最大转速输出持续约3min。压降至6.8V电机停转。
    测试使用的超级电容：12个2.7V、120F电容串联，总32.4V、10F。
    
    经测试证明单路串联供电可行，低压大电流供电极为可行，单尚无法提供大电流，也无法获取大功率受控负载。
    
    技术分析：单路连接方案相当于原双路控制方案的支路版本。单路控制优点在于结构简单，控制方便。双路控制优点在于可靠性强。
    下阶段主要目标：
    寻找或开发可控（受芯片控制）恒压限流开关。尝试在单路连接旁路增加保险支路，防止模块损坏导致的供电断开。    （前两句号直接存在先后关系）
    找并培训新的电子硬件组成员。


2019.10.27
  对开关向下进行验证，发现芯片输出与预期不符：
详：开关芯片IRS2103，在接入含两mos的电源干路中时，驱动电压VCC=12V,输入电压HI=LI=3.3V，pmw频率2kHz，幅值3.3V，输出HO/LO均为mV级，反馈电压VB也为mV级但略大于HO/LO，反馈电压VS略高于VCC，即输出HO/LO不足以抬高MOS栅极电压；在芯片及外围电路独立运作时，发现LO与LI同相位（按照说明书LO与LI应反相），导致开关中的两路MOS会同时打开，即相当于VCC-24V直接经过MOS接地，导致短路，致使MOS被击穿，产生电火花。
  额外问题：对电压反馈脚进行测量时会干扰其他脚的输出状态。
  解决方案：
    1.换新的IRS2103，重新验证不同驱动电压下的芯片输出状态，推测有可能是两块IRS2103在重复焊接过程中出现了预期之外的错误。
    2.换用LTC4449，一款pwm独立出来用于驱动高侧NMOS的芯片。

近期进展：
    1.用新的分体板找到了MOS频繁爆炸的原因，获取了IRS2103的底层数据。接触到了MOS驱动的底层原理。
    2.安排李逸飞学习了AD，立创EDA。分配了超级电容均衡分压的任务。

下期安排：
    1.购买新的驱动芯片，期中考试结束后同步测试IRS2103，还有完成未完成的LTC1473的验证使用。
    2.安排验证均衡分压的进度。
    3.考虑功率控制的软件控制逻辑，实现方法。


2019.11.25
IRS2103 LTC1473正常工作，可以正常用pwm调节输入输出。CAN意外烧毁，正在排查原因。
整合为一块统一的板，准备下一步的上车测试。

独立的超级电容部分正在验证分压状况。

写电容板的控制代码。

数据记录：IRS2103自举电路中电容采用470nf，时间常数匹配即可正常驱动

2020.2.15
截止至2020年2月15日，超级电容共进行了两版测试版，现为正式版第一版。
最新的硬件测试条件及结果：电池+超级电容控制板+2000J超级电容+3508电机，通过手动为电机增加负载，在电池限制功率5-15W（软件控制），实际负载功率5-20W状态下反复充放电15-20min，电容无过热表现，电压无明显抖动，但运行时间过长控制板大电流通路一MOS被烧毁。
现行代码控制基本逻辑：在底盘输出尚未超功率时通过电池输出电能，在功率接近阈值时切换为超级电容输出，可支持短暂的地盘超功率行为，底盘功率恢复正常或电容电量不足时会切换回电池输出。电池输出有空闲功率时为电容充电。
总结了现用电容板的技术参数和参考资料。

2020.3.8
第二版超级电容原理图结束（具体功能详见说明文档）
2020.3.12
第二版超级电容PCB第三次布线成功结束
2020.3.20
第二版超级电容3D模型导出
