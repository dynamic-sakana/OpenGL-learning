#include <iostream>
#include <fstream>
#include <mutex>
#include <string>

class Log {
public:
	// 获取单例实例
	static Log& getInstance() {
		static Log instance; // C++11 的线程安全静态局部变量
		return instance;
	}

	// 禁止拷贝构造和赋值操作符
	Log(const Log&) = delete;
	Log& operator=(const Log&) = delete;

	// 写日志
	void write(const std::string& message) {
		std::lock_guard<std::mutex> lock(mutex_); // 保证线程安全
		logFile_ << message << std::endl;
	}

private:
	Log() {
		logFile_.open("log.txt", std::ios::out); // 打开日志文件
		if (!logFile_.is_open()) {
			throw std::runtime_error("Unable to open log file!");
		}
	}

	~Log() {
		if (logFile_.is_open()) {
			logFile_.close(); // 关闭日志文件
		}
	}

	std::ofstream logFile_; // 日志文件
	std::mutex mutex_;      // 线程安全的互斥锁
};