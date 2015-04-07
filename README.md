
MetaTrader 编程入门教程大全

-------------------------------------------------------------------------------------------------------
MQL4 Reference

MetaQuotes Language 4 (MQL4) 是一种新的内置型程序用来编写交易策略。 这种语言可以创建你自己的智能交易，使自己的交易策略能够完全自动地执行。而且，MQL4 还能自定义客户指标，脚本和数据库。<\r>
MQL内包含了大量可以分析当前及历史报价所必须的函数，以及一些基本的运算和逻辑操作。并内置了一些基本的指标和操作命令。<\r>

MetaEditor 4集合了编写 MQL4 程序代码的各种语句，它能帮助使用者方便地写出规范的代码。 MetaQuotes Language Dictionary 是 MQL4 语言的帮助工具，它包含了我们在使用工程中所有可能用到的函数。   MetaQuotes Language 4 可以编写不同作用的程序代码: 

智能交易 是一种连接到特定图表的自动交易系统。它能够根据设置的节点自动启动 ，当它开始运行后，它不会同时去处理另一个新的指令(也就是说必须等到当前程序完成)。 这种交易系统能够在提醒用户可以交易的同时，将交易定单自动送到交易服务器。与大多数交易系统一样， 它也能够用历史数据测试交易策略，并在图表上显示出来。

智能交易存储在 terminal_directory\experts。

自定义指标 可用来编写新的技术指标，和内置的指标一样，它不能用来进行自动交易， 只能作为分析数据的工具。  自定义指标储存在 terminal_directory\experts\indicators。  脚本 是执行单一功能的一段程序，和智能交易不同，脚本不能单独执行，只能被调用。 脚本存储在 terminal_dictionary\experts\scripts。  数据库 常被使用的自定义函数的集合。数据库不能单独运行。 数据库建议存储在terminal_directory\experts\libraries。 包含文件 包含文件常被使用的程序块源代码，这些文件能够被包含在智能交易，脚本，客户指标和数据库 的源代码中。 使用包含文件比调用资料库更灵活快捷。   包含文件交易储存在 terminal_directory\experts\include。 
