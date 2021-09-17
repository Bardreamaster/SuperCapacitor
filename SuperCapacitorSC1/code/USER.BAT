SET PATH=J:\MDK\ARM\ARMCC\Bin;J:\Git\Git\bin;C:\Program Files (x86)\Common Files\Oracle\Java\javapath;C:\Program Files (x86)\Common Files\Intel\Shared Libraries\redist\intel64\compiler;C:\Program Files\Intel\iCLS Client\;C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\Wbem;C:\WINDOWS\System32\WindowsPowerShell\v1.0\;C:\WINDOWS\System32\OpenSSH\;D:\TDMGCC\bin;D:\MinGW\mingw64\bin;C:\Program Files\Java\jdk1.8.0_201\bin;C:\Program Files\Java\jdk1.8.0_201\jre\bin;C:\Program Files\Microsoft SQL Server\Client SDK\ODBC\110\Tools\Binn\;C:\Program Files (x86)\Microsoft SQL Server\120\Tools\Binn\;C:\Program Files\Microsoft SQL Server\120\Tools\Binn\;C:\Program Files\Microsoft SQL Server\120\DTS\Binn\;C:\Program Files (x86)\Windows Kits\8.1\Windows Performance Toolkit\;J:\MATLAB\bin;C:\Program Files (x86)\Intel\Intel(R) Management Engine Components\DAL;C:\Program Files\Intel\Intel(R) Management Engine Components\DAL;C:\Program Files\Intel\WiFi\bin\;C:\Program Files\Common Files\Intel\WirelessCommon\;C:\Users\dell\AppData\Local\Programs\Python\Python37\Scripts\;C:\Users\dell\AppData\Local\Programs\Python\Python37\;C:\Users\dell\AppData\Local\Microsoft\WindowsApps;;D:\IDEA\IntelliJ IDEA 2018.3.4\bin;;J:\Microsoft VS Code\bin;I:\PyCharm\PyCharm Community Edition 2019.3.4\bin;
SET CPU_TYPE=STM32F103C8
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=USER
SET CPU_CLOCK=0x007A1200
"J:\MDK\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\main.__i"
"J:\MDK\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\adc.__i"
"J:\MDK\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\delay.__i"
"J:\MDK\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\led.__i"
"J:\MDK\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\timer.__i"
"J:\MDK\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\usart.__i"
"J:\MDK\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\switch.__i"
"J:\MDK\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\powerlimit.__i"
"J:\MDK\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\misc.__i"
"J:\MDK\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\stm32f10x_adc.__i"
"J:\MDK\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\stm32f10x_can.__i"
"J:\MDK\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\stm32f10x_exti.__i"
"J:\MDK\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\stm32f10x_gpio.__i"
"J:\MDK\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\stm32f10x_rcc.__i"
"J:\MDK\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\stm32f10x_tim.__i"
"J:\MDK\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\stm32f10x_usart.__i"
"J:\MDK\ARM\ARMCC\Bin\ArmAsm" --Via ".\objects\startup_stm32f10x_md._ia"
"J:\MDK\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\system_stm32f10x.__i"
"J:\MDK\ARM\ARMCC\Bin\ArmLink" --Via ".\Objects\SC1.lnp"
"J:\MDK\ARM\ARMCC\Bin\fromelf.exe" ".\Objects\SC1.axf" --i32combined --output ".\Objects\SC1.hex"
