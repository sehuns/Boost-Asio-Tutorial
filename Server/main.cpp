#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;


// 서버 컴퓨터의 날짜 및 시간 정보를 반환
string make_daytime_string() //클라이언트가 접속했을 때 보내줌
{
	time_t now = time(0);
	return ctime(&now);
}

int main()
{
	try { 
		// 80번 : http, 13번 : daytime
		// 기본적으로 Boost Asio 프로그램은 하나의 IO Service 객체를 가짐
		boost::asio::io_service io_service;
		// TCP 프로토콜의 13번 포트로 연결 받는 수동 소켓 생성
		tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 13));
		// 모든 클라이언트에 대해 무한 반복 수행
		while (1)
		{
			// 소켓 객채를 생성해 연결 기다림
			tcp::socket socket(io_service);
			acceptor.accept(socket);
			// 연결 완료되면 해당 클라이언트에 보낼 메시지 생성
			string message = make_daytime_string();
			// 클라이언트에게 전송
			boost::system::error_code ignored_error;
			boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
		}
	}
	catch (exception& e) {
		cerr << e.what() << '\n';
	}
	return 0;
}



