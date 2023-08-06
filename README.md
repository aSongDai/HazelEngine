# HazelEngine

## Problem
· 使用cherno的GLFW的时候，连接错误解决办法：将GLFW项目中的LINK->Code Generate->RuntimeLibrary修改为'/MT'，
	Event.h 中的operator<<()运算符重载错误， 我将其设置为了静态友元函数
